
#ifndef WindowsUsb_hpp
#define WindowsUsb_hpp
#define WindowsUsb_AVAILABLE

#include "cppObject.hpp"
#include "System.hpp"

#ifndef ame_Enviroment_Defined

#endif

#ifdef ame_Windows
	#include <iostream>
	#include <windows.h>
	#include <tchar.h>
#endif

#ifdef ame_ArduinoIDE
	#include "Arduino.h"
#endif

#include "SerialPort.hpp"

namespace ame{

class WindowsUsb : public SerialPort{	
    public:
		WindowsUsb() : m_port_handle(nullptr) {}
		WindowsUsb(const Note& a_com) : m_port_handle(nullptr) {
			this->connect(a_com, 9600);
		}
		WindowsUsb(const HANDLE& a_handle) : m_port_handle(a_handle) {
			this->connect(a_handle, 9600);
		}
        
		virtual ~WindowsUsb(){
			if (m_port_handle != nullptr) {
				CloseHandle(m_port_handle);
				m_port_handle = nullptr;
			}
		}
		virtual int available(){
			return 0;
		}
		virtual int read(){
			Note message;
			size_t bufferSize = 256;
			if (m_port_handle == nullptr) {
				std::cerr << "Port is not open" << std::endl;
				return false;
			}

			DWORD bytesRead;
			char* buffer = new char[bufferSize];

			if (!ReadFile(m_port_handle, buffer, static_cast<DWORD>(bufferSize), &bytesRead, nullptr)) {
				delete[] buffer;
				std::cerr << "Failed to read from port" << std::endl;
				return false;
			}

			message.addLocalArrayPointer(buffer, bytesRead);

			delete[] buffer;
			return true;
		}

		virtual int peek(){
			return 0;
		}
		virtual size_t write(uint8_t a_char){
			if (m_port_handle == nullptr) {
				std::cerr << "Port is not open" << std::endl;
				return false;
			}

			DWORD bytesWritten;
			Note i_char = a_char;
			if (!WriteFile(m_port_handle, i_char.pointer(), static_cast<DWORD>(i_char.length()), &bytesWritten, nullptr)) {
				std::cerr << "Failed to write to port" << std::endl;
				return false;
			}

			return true;
		}
		virtual bool connected(){
        	return (m_port_handle != nullptr);
		}

		virtual bool connect(const Note& a_address){
			return this->connect(a_address.pointer(), 9600);
		}

		virtual bool connect(const Note& a_address, int port){
			return this->connect(a_address.pointer(), port);
		}

		virtual bool connect(const char* a_address){
			return this->connect(a_address, 9600);
		}

		LPCWSTR ConvertToLPCWSTR(const std::string& str) {
			int bufferLength = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
			if (bufferLength == 0) {
				std::cerr << "Failed to convert string to LPCWSTR" << std::endl;
				return nullptr;
			}

			wchar_t* buffer = new wchar_t[bufferLength];
			MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, buffer, bufferLength);

			return buffer;
		}

		virtual bool connect(const char* a_address, int port){
			HANDLE hPort = CreateFile(a_address, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
			
			return this->connect(hPort, port);
		}

		virtual bool connect(HANDLE a_handle, int port){
        	m_port_handle = a_handle;

			DWORD errMsg = GetLastError();

			System::console.println(errMsg);

			if (m_port_handle == INVALID_HANDLE_VALUE) {
				std::cerr << "Failed to open port 1" << std::endl;
				return false;
			}

			DCB dcbSerialParams = { 0 };
			dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

			if (!GetCommState(m_port_handle, &dcbSerialParams)) {
				std::cerr << "Failed to get port state 2" << std::endl;
				CloseHandle(m_port_handle);
				m_port_handle = nullptr;
				return false;
			}

			dcbSerialParams.BaudRate = port;  // Configura la velocidad de baudios (puedes ajustarla según tus necesidades)
			dcbSerialParams.ByteSize = 8;         // Configura el tamaño de byte
			dcbSerialParams.StopBits = ONESTOPBIT; // Configura los bits de parada
			dcbSerialParams.Parity = NOPARITY;     // Configura la paridad (sin paridad)

			if (!SetCommState(m_port_handle, &dcbSerialParams)) {
				std::cerr << "Failed to set port state 3" << std::endl;
				CloseHandle(m_port_handle);
				m_port_handle = nullptr;
				return false;
			}

			COMMTIMEOUTS timeouts = { 0 };
			timeouts.ReadIntervalTimeout = 50;
			timeouts.ReadTotalTimeoutConstant = 50;
			timeouts.ReadTotalTimeoutMultiplier = 10;
			timeouts.WriteTotalTimeoutConstant = 50;
			timeouts.WriteTotalTimeoutMultiplier = 10;

			if (!SetCommTimeouts(m_port_handle, &timeouts)) {
				std::cerr << "Failed to set port timeouts 4" << std::endl;
				CloseHandle(m_port_handle);
				m_port_handle = nullptr;
			}
			return true;
		}
		virtual void stop(){
			if (m_port_handle != nullptr) {
				CloseHandle(m_port_handle);
				m_port_handle = nullptr;
			}
		}

		static HANDLE getCOM_HANDLE(int a_index){
			std::string portName = "\\\\.\\COM" + std::to_string(a_index);
			HANDLE hPort = CreateFile(portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
			return hPort;
		}

		static Note getCOM(int a_index){
			std::string portName = "\\\\.\\COM" + std::to_string(a_index);
			HANDLE hPort = CreateFile(portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
			if (hPort != INVALID_HANDLE_VALUE) {
				CloseHandle(hPort);
				return Note(portName.c_str());
			}
			return "";
		}

		// virtual Note getCOM(){
		// 	// Enumerar los puertos COM disponibles
		// 	for (int i = 1; i <= 256; ++i) {
		// 	    // Construir el nombre del puerto COM
		// 	    std::string portName = "\\\\.\\COM" + std::to_string(i);

		// 	    // Abrir el puerto COM
		// 	    HANDLE hPort = CreateFile(portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

		// 	    // Verificar si el puerto está disponible
		// 	    if (hPort != INVALID_HANDLE_VALUE) {
		// 	        std::cout << "COM" << i << " esta disponible" << std::endl;

		// 	        // Cerrar el puerto
		// 	        CloseHandle(hPort);
		// 	    }
		// 	}
		// }

		virtual operator bool(){return true;}
		virtual void operator=(WindowsUsb b){}
		virtual bool operator==(WindowsUsb b){return true;}
		virtual bool operator!=(WindowsUsb b){return true;}
		
		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){return Class<WindowsUsb>::getClass();}
		virtual bool instanceof(cppObjectClass* cls){
			return cls == Class<WindowsUsb>::getClass() || SerialPort::instanceof(cls);
		}
		#endif
	protected:
    	HANDLE m_port_handle;
		bool m_connected = false;
		COMSTAT m_status = { 0 };
		DWORD m_errors = 0;
};

}

#endif