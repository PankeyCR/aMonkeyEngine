
#ifndef WIFISerialServer_hpp
#define WIFISerialServer_hpp
#define WIFISerialServer_AVAILABLE 

#include "SerialNetwork.hpp"

#ifndef ame_Enviroment_Defined

#endif

#ifdef ame_Windows

#endif

#ifdef ame_ArduinoIDE
	#include "Arduino.h"
	#include "IPAddress.h"
#endif

#include "WIFISerialPort.hpp"

#if defined(ARDUINO_ARCH_ESP8266)
	#include "WiFi.h"
#elif defined(ARDUINO_ARCH_ESP32)
	#include "WiFi.h"
#endif

#ifdef WIFISerialServer_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"
	
	#define WIFISerialServerLog(location,method,type,mns) ame_Log(this,location,"WIFISerialServer",method,type,mns)
	#define const_WIFISerialServerLog(location,method,type,mns) 
	#define StaticWIFISerialServerLog(pointer,location,method,type,mns) ame_Log(pointer,location,"WIFISerialServer",method,type,mns)
#else
	#ifdef WIFISerialServer_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"
		
		#define WIFISerialServerLog(location,method,type,mns) ame_LogDebug(this,location,"WIFISerialServer",method,type)
		#define const_WIFISerialServerLog(location,method,type,mns) 
		#define StaticWIFISerialServerLog(pointer,location,method,type,mns) ame_LogDebug(pointer,location,"WIFISerialServer",method,type)
	#else
		#define WIFISerialServerLog(location,method,type,mns) 
		#define const_WIFISerialServerLog(location,method,type,mns) 
		#define StaticWIFISerialServerLog(pointer,location,method,type,mns) 
	#endif
#endif
namespace ame{

class WIFISerialServer : public SerialServer{	
    public:
    WIFISerialServer():server(80){
		WIFISerialServerLog(ame_Log_StartMethod, "Contructor",  "println", "server(80)");
		server.begin();
		WIFISerialServerLog(ame_Log_EndMethod, "Contructor",  "println", "");
    }
    WIFISerialServer(int port):server(port){
		WIFISerialServerLog(ame_Log_StartMethod, "Contructor",  "println", "server(port)");
		server.begin();
		WIFISerialServerLog(ame_Log_EndMethod, "Contructor",  "println", "");
    }
	
	virtual ~WIFISerialServer(){
		WIFISerialServerLog(ame_Log_StartMethod, "Destructor",  "println", "");
		WIFISerialServerLog(ame_Log_EndMethod, "Destructor",  "println", "");
	}
	
	SerialPort* accept(){
		WIFISerialServerLog(ame_Log_StartMethod, "accept",  "println", "");
		#if defined(ame_GENERIC_ESP32)
		WIFISerialServerLog(ame_Log_Statement, "accept",  "println", "ame_GENERIC_ESP32");
		WiFiClient client = server.accept();   // Listen for incoming clients
		#elif defined(ame_GENERIC_ESP8266)
		WIFISerialServerLog(ame_Log_Statement, "accept",  "println", "ame_GENERIC_ESP8266");
		WiFiClient client = server.available();
		#endif 
		if(client){
			WIFISerialServerLog(ame_Log_EndMethod, "accept",  "println", "if(client)");
			return new WIFISerialPort(client,"ethernet");
		}
		WIFISerialServerLog(ame_Log_EndMethod, "accept",  "println", "return nullptr");
		return nullptr;
	} 
	
	SerialPort* available(){
		WIFISerialServerLog(ame_Log_StartMethod, "available",  "println", "");
		WiFiClient client = server.available();   // Listen for incoming clients
		if(client){
			WIFISerialServerLog(ame_Log_EndMethod, "available",  "println", "if(client)");
			return new WIFISerialPort(client,"ethernet");
		}
		WIFISerialServerLog(ame_Log_EndMethod, "accept",  "println", "return nullptr");
		return nullptr;
	}
	
	virtual WiFiServer getServer(){
		return server;
	}
	
	#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
	virtual cppObjectClass* getClass(){return Class<WIFISerialServer>::getClass();}
	virtual bool equal(cppObject *b){
		WIFISerialServerLog(ame_Log_Statement, "available",  "println", "equal");
		if(b == this){
			return true;
		}
		if(b->instanceof(Class<WIFISerialServer>::getClass())){
			WIFISerialServer* c = (WIFISerialServer*)b;
			#if defined(ARDUINO_ESP32_DEV) || defined(LILYGO_WATCH_2020_V1) || defined(LILYGO_WATCH_2020_V2) || defined(LILYGO_WATCH_2020_V3)
			if(c->server == this->server){
				return true;
			}
			#elif defined(ARDUINO_ARCH_ESP8266)
			
			#endif
		}
		return false;
	}

	virtual bool instanceof(cppObjectClass* cls){
		return cls == Class<WIFISerialServer>::getClass() || SerialServer::instanceof(cls);
	}
	#endif

protected:
	WiFiServer server;
};

}

#endif