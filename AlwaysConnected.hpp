
#ifndef CONFIGURATION_AlwaysConnected_hpp
#define CONFIGURATION_AlwaysConnected_hpp

	#include "ame_Enviroment.hpp"

	#if defined(DISABLE_AlwaysConnected)
		#define AlwaysConnected_hpp
	#endif
#endif

#ifndef AlwaysConnected_hpp
#define AlwaysConnected_hpp
#define AlwaysConnected_AVAILABLE

#ifdef ame_ArduinoIDE
	#include "Arduino.h"
#endif

#include "Application.hpp"
#include "SerialState.hpp"
#include "PrimitiveList.hpp"
#include "BaseAppState.hpp"
#include "Note.hpp"
#include "NoteHelper.hpp"

#ifdef AlwaysConnected_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"
	
	#define AlwaysConnectedLog(location,method,type,mns) ame_Log(this,location,"AlwaysConnected",method,type,mns)
	#define const_AlwaysConnectedLog(location,method,type,mns) 
	#define StaticAlwaysConnectedLog(pointer,location,method,type,mns) ame_Log(pointer,location,"AlwaysConnected",method,type,mns)
#else
	#ifdef AlwaysConnected_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"
		
		#define AlwaysConnectedLog(location,method,type,mns) ame_LogDebug(this,location,"AlwaysConnected",method,type)
		#define const_AlwaysConnectedLog(location,method,type,mns) 
		#define StaticAlwaysConnectedLog(pointer,location,method,type,mns) ame_LogDebug(pointer,location,"AlwaysConnected",method,type)
	#else
		#define AlwaysConnectedLog(location,method,type,mns) 
		#define const_AlwaysConnectedLog(location,method,type,mns) 
		#define StaticAlwaysConnectedLog(pointer,location,method,type,mns) 
	#endif
#endif

namespace ame{

/*
*	Class Configuration:
*	DISABLE_IMPLEMENTATION_BaseAppState
*/
class AlwaysConnected IMPLEMENTATION_BaseAppState {
    public:
		AlwaysConnected(){
			AlwaysConnectedLog(ame_Log_EndMethod, "Contructor",  "println", "");
			AlwaysConnectedLog(ame_Log_EndMethod, "Contructor",  "println", "");
		}
		AlwaysConnected(Note s){
			AlwaysConnectedLog(ame_Log_EndMethod, "Contructor",  "println", "");
			myName = s;
			AlwaysConnectedLog(ame_Log_EndMethod, "Contructor",  "println", "");
		}
		AlwaysConnected(SerialState* c_serial_state){
			AlwaysConnectedLog(ame_Log_EndMethod, "Contructor",  "println", "");
			serialState = c_serial_state;
			AlwaysConnectedLog(ame_Log_EndMethod, "Contructor",  "println", "");
		}
		virtual ~AlwaysConnected(){
			AlwaysConnectedLog(ame_Log_EndMethod, "Destructor",  "println", "");
			AlwaysConnectedLog(ame_Log_EndMethod, "Destructor",  "println", "");
		}

		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){return Class<AlwaysConnected>::getClass();}
		virtual bool instanceof(cppObjectClass* cls){
			return cls == Class<AlwaysConnected>::getClass() || AppState::instanceof(cls);
		}
		#endif
		
		#if defined(Application_AVAILABLE)
		virtual void initializeState(Application* a_app){
			AlwaysConnectedLog(ame_Log_EndMethod, "initializeState",  "println", "");
			AlwaysConnectedLog(ame_Log_Statement, "initializeState",  "println", "");
			app = a_app;
			#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
			serialState = (SerialState*)app->getStateManager()->get(Class<SerialState>::getClass());
			#endif
			AlwaysConnectedLog(ame_Log_EndMethod, "initializeState",  "println", "");
		}
		#endif
		
		virtual void updateState(float tpc){
			AlwaysConnectedLog(ame_Log_EndMethod, "updateState",  "println", "");
			#if defined(Application_AVAILABLE)
			if(serialState == nullptr){
				#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
				serialState = (SerialState*)app->getStateManager()->get(Class<SerialState>::classType);
				#endif
				return;
			}
			#endif
			time += tpc;
			if(time < time_limite){
				return;
			}
			time = 0.0f;
			for(int x = 0; x < serialports.getPosition(); x++){
				SerialPort* serialport = serialports.getByPosition(x);
				if(serialport == nullptr){
					continue;
				}
				Note name = serialport->getName();
				IPAddress ip = *ips.getByPosition(x);
				int port = *ports.getByPosition(x);
				PortProtocol* portprotocol = portprotocols.getByPosition(x);
				if(serialport->connected()){
					continue;
				}
				AlwaysConnectedLog(ame_Log_Statement, "updateState",  "println", "");
				AlwaysConnectedLog(ame_Log_Statement, "updateState",  "println", Note("iteration ")+Note(x));
				if(serialport->connect(ip,port) && serialState != nullptr){
					serialState->addSerialPort(serialport,portprotocol);
					if(myName != ""){
						serialState->send(serialport, Note("MyNameIs ") + myName);
					}
				}
			}
			AlwaysConnectedLog(ame_Log_EndMethod, "updateState",  "println", "");
		}

		virtual void add(Note a_name, IPAddress a_ip, int a_port, SerialPort* a_serial_port, PortProtocol* a_port_protocol){
			AlwaysConnectedLog(ame_Log_EndMethod, "add",  "println", "");
			a_serial_port->setName(a_name);
			ips.addLValue(a_ip);
			ports.addLValue(a_port);
			serialports.addPointer(a_serial_port);
			portprotocols.addPointer(a_port_protocol);
			a_port_protocol->setSafeDelete(false);
			AlwaysConnectedLog(ame_Log_EndMethod, "add",  "println", "");
		}

		virtual void add(Note a_name, Note a_ip, int a_port, SerialPort* a_serial_port, PortProtocol* a_port_protocol){
			AlwaysConnectedLog(ame_Log_EndMethod, "add",  "println", "");
			this->add(a_name, toIPAddress(a_ip), a_port, a_serial_port, a_port_protocol);
			AlwaysConnectedLog(ame_Log_EndMethod, "add",  "println", "");
		}

		virtual void remove(Note n){
			AlwaysConnectedLog(ame_Log_EndMethod, "remove",  "println", "");
			int x=-1;
			for(int t = 0; t < serialports.getPosition(); t++){
				if(serialports.getByPosition(t)->getName() == n){
					x = t;
					break;
				}
			}
			if(x == -1){
				return;
			}
			ips.removeDeleteByPosition(x);
			ports.removeDeleteByPosition(x);
			serialports.removeDeleteByPosition(x);
			portprotocols.removeDeleteByPosition(x);
			AlwaysConnectedLog(ame_Log_EndMethod, "remove",  "println", "");
		}
	protected:
		#if defined(Application_AVAILABLE)
		Application* app = nullptr;
		#endif
		SerialState* serialState = nullptr;
		PrimitiveList<IPAddress> ips;
		PrimitiveList<int> ports;
		PrimitiveList<SerialPort> serialports;
		PrimitiveList<PortProtocol> portprotocols;
		float time = 0;
		float time_limite = 5.5f;
		Note myName = "micro";
};

}

#endif
