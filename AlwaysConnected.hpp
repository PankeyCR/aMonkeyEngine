
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
			m_myName = s;
			AlwaysConnectedLog(ame_Log_EndMethod, "Contructor",  "println", "");
		}
		AlwaysConnected(SerialState* c_serial_state){
			AlwaysConnectedLog(ame_Log_EndMethod, "Contructor",  "println", "");
			m_serialState = c_serial_state;
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
			m_app = a_app;
			#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
			m_serialState = (SerialState*)m_app->getStateManager()->get(Class<SerialState>::getClass());
			#endif
			AlwaysConnectedLog(ame_Log_EndMethod, "initializeState",  "println", "");
		}
		#endif
		
		virtual void updateState(float tpc){
			AlwaysConnectedLog(ame_Log_EndMethod, "updateState",  "println", "");
			#if defined(Application_AVAILABLE)
			if(m_serialState == nullptr){
				#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
				m_serialState = (SerialState*)m_app->getStateManager()->get(Class<SerialState>::classType);
				#endif
				return;
			}
			#endif
			m_time += tpc;
			if(m_time < m_time_limite){
				return;
			}
			m_time = 0.0f;
			for(int x = 0; x < m_serialports.getPosition(); x++){
				SerialPort* i_serialport = m_serialports.getByPosition(x);
				if(i_serialport == nullptr){
					continue;
				}
				Note i_name = i_serialport->getName();
				IPAddress i_ip = *m_ips.getByPosition(x);
				int i_port = *m_ports.getByPosition(x);
				PortProtocol* i_portprotocol = m_portprotocols.getByPosition(x);
				if(i_serialport->connected()){
					continue;
				}
				AlwaysConnectedLog(ame_Log_Statement, "updateState",  "println", "");
				AlwaysConnectedLog(ame_Log_Statement, "updateState",  "println", Note("iteration ")+Note(x));
				if(i_serialport->connect(i_ip, i_port) && m_serialState != nullptr){
					m_serialState->addSerialPort(i_serialport, i_portprotocol);
					if(m_myName != ""){
						m_serialState->send(i_serialport, Note("MyNameIs ") + m_myName);
					}
				}
			}
			AlwaysConnectedLog(ame_Log_EndMethod, "updateState",  "println", "");
		}

		virtual void add(Note a_name, IPAddress a_ip, int a_port, SerialPort* a_serial_port, PortProtocol* a_port_protocol){
			AlwaysConnectedLog(ame_Log_EndMethod, "add",  "println", "");
			a_serial_port->setName(a_name);
			m_ips.addLValue(a_ip);
			m_ports.addLValue(a_port);
			m_serialports.addPointer(a_serial_port);
			m_portprotocols.addPointer(a_port_protocol);
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
			for(int t = 0; t < m_serialports.getPosition(); t++){
				if(m_serialports.getByPosition(t)->getName() == n){
					x = t;
					break;
				}
			}
			if(x == -1){
				return;
			}
			m_ips.removeDeleteByPosition(x);
			m_ports.removeDeleteByPosition(x);
			m_serialports.removeDeleteByPosition(x);
			m_portprotocols.removeDeleteByPosition(x);
			AlwaysConnectedLog(ame_Log_EndMethod, "remove",  "println", "");
		}
	protected:
		#if defined(Application_AVAILABLE)
		Application* m_app = nullptr;
		#endif
		SerialState* m_serialState = nullptr;
		PrimitiveList<IPAddress> m_ips;
		PrimitiveList<int> m_ports;
		PrimitiveList<SerialPort> m_serialports;
		PrimitiveList<PortProtocol> m_portprotocols;
		float m_time = 0;
		float m_time_limite = 5.5f;
		Note m_myName = "micro";
};

}

#endif
