
#ifndef DefaultServerProtocol_hpp
#define DefaultServerProtocol_hpp
#define DefaultServerProtocol_AVAILABLE 

#include "Application.hpp"
#include "ServerProtocol.hpp"
#include "SerialPort.hpp"
#include "Message.hpp"
#include "SerialState.hpp"

#ifndef ame_Enviroment_Defined

#endif

#ifdef ame_Windows

#endif

#ifdef ame_ArduinoIDE
	#include "Arduino.h"
#endif

#ifdef DefaultServerProtocol_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"
	
	#define DefaultServerProtocolLog(location,method,type,mns) ame_Log(this,location,"DefaultServerProtocol",method,type,mns)
	#define const_DefaultServerProtocolLog(location,method,type,mns) 
	#define StaticDefaultServerProtocolLog(pointer,location,method,type,mns) ame_Log(pointer,location,"DefaultServerProtocol",method,type,mns)
#else
	#ifdef DefaultServerProtocol_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"
		
		#define DefaultServerProtocolLog(location,method,type,mns) ame_LogDebug(this,location,"DefaultServerProtocol",method,type)
		#define const_DefaultServerProtocolLog(location,method,type,mns) 
		#define StaticDefaultServerProtocolLog(pointer,location,method,type,mns) ame_LogDebug(pointer,location,"DefaultServerProtocol",method,type)
	#else
		#define DefaultServerProtocolLog(location,method,type,mns) 
		#define const_DefaultServerProtocolLog(location,method,type,mns) 
		#define StaticDefaultServerProtocolLog(pointer,location,method,type,mns) 
	#endif
#endif

namespace ame{

template<class T>
class DefaultServerProtocol : public ServerProtocol{	
    public:
		DefaultServerProtocol(){
			DefaultServerProtocolLog(ame_Log_StartMethod, "Constructor",  "println", "");
			DefaultServerProtocolLog(ame_Log_EndMethod, "Constructor",  "println", "");
		}
		virtual ~DefaultServerProtocol(){
			DefaultServerProtocolLog(ame_Log_StartMethod, "Destructor",  "println", "");
			DefaultServerProtocolLog(ame_Log_EndMethod, "Destructor",  "println", "");
		}
		
		virtual SerialPort* getUpdateSerialPort(SerialServer* server){
			DefaultServerProtocolLog(ame_Log_StartMethod, "getUpdateSerialPort",  "println", "");
			if(this->serialState == nullptr){
				DefaultServerProtocolLog(ame_Log_EndMethod, "getUpdateSerialPort",  "println", "this->serialState == nullptr");
				return nullptr;
			}
			SerialPort* port = nullptr;
			port = server->accept();
			if(port == nullptr){
				DefaultServerProtocolLog(ame_Log_EndMethod, "getUpdateSerialPort",  "println", "port == nullptr");
				return nullptr;
			}
			DefaultServerProtocolLog(ame_Log_EndMethod, "getUpdateSerialPort",  "println", port->getName());
			return port;
		}
		
		virtual void UpdateSerialPort(SerialPort* port){
			DefaultServerProtocolLog(ame_Log_StartMethod, "UpdateSerialPort",  "println", "");
			if(this->serialState == nullptr){
				DefaultServerProtocolLog(ame_Log_EndMethod, "UpdateSerialPort",  "println", "this->serialState == nullptr");
				return;
			}
			if(!this->serialState->containSerialPort(port)){
				DefaultServerProtocolLog(ame_Log_Statement, "UpdateSerialPort",  "println", "!this->serialState->containSerialPort(port)");
				T* t_protocol = new T();
				initialMessage(port, t_protocol);
				this->serialState->addSerialPort(port, t_protocol);
				t_protocol->initialize(this->serialState);
			}
			DefaultServerProtocolLog(ame_Log_EndMethod, "UpdateSerialPort",  "println", "this->serialState == nullptr");
		}
		
		virtual void initialMessage(SerialPort* port, T* t){}
		
	protected:
};

}

#endif