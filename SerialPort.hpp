
#ifndef CONFIGURATION_SerialPort_hpp
#define CONFIGURATION_SerialPort_hpp

	#include "ame_Enviroment.hpp"

	#if defined(DISABLE_SerialPort)
		#define SerialPort_hpp
	#endif
#endif

#ifndef SerialPort_hpp
#define SerialPort_hpp
#define SerialPort_AVAILABLE

#include "cppObject.hpp"
#include "Note.hpp"
#include "ByteArray.hpp"

#ifdef ame_Windows
	#include "ame_Stream.hpp"
#endif

#ifdef ame_ArduinoIDE
	#include "Arduino.h"
	#include "Stream.h"
	#include "IPAddress.h"
#endif

namespace ame{

/*
*	Class Configuration:
*	DISABLE_IMPLEMENTATION_cppObject
*/
class SerialPort : public Stream IMPLEMENTING_cppObject {

    public:
		SerialPort(){}
		virtual ~SerialPort(){}
		
		virtual uint8_t status(){return 0;}
		virtual int available(){return 0;}
		virtual int read(){return -1;}
		virtual byte readByte(){return 255;}
		virtual Note readNote(){return "";}
		virtual int peek(){return -1;}
		virtual size_t write(uint8_t chr){return 0;}
		virtual bool connected(){return false;}
		virtual bool connect(const Note& a_address){return connect(a_address,-1);}
		virtual bool connect(const Note& a_address, int port){return false;}
		virtual bool connect(const char* a_address){return connect(a_address,-1);}
		virtual bool connect(const char* a_address, int port){return false;}
		#ifdef ame_ArduinoIDE
		virtual bool connect(IPAddress ip, int port){return false;}
		#endif
		virtual void stop(){}
		virtual void send(Note s){}
		virtual void send(ByteArray array){}
		
		
		virtual void setName(Note name){m_name = name;}
		virtual void setIP(Note a_ip){m_ip = a_ip;}

		virtual Note getName(){return m_name;}
		virtual Note getIP(){return this->m_ip;}

		virtual void flush(){}

		virtual operator bool(){return false;}
		virtual void operator=(SerialPort b){}
		virtual bool operator==(SerialPort b){return false;}
		virtual bool operator!=(SerialPort b){return true;}
		
		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){return Class<SerialPort>::getClass();}
		virtual bool instanceof(cppObjectClass* cls){return cls == Class<SerialPort>::getClass();}
		#endif
	protected:
		Note m_name;
		Note m_ip = "150.1.0.0";
};

}

#endif