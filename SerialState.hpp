
#ifndef CONFIGURATION_SerialState_hpp
#define CONFIGURATION_SerialState_hpp

	#include "ame_Enviroment.hpp"

	#if defined(DISABLE_SerialState)
		#define SerialState_hpp
	#endif
#endif

#ifndef SerialState_hpp
#define SerialState_hpp
#define SerialState_AVAILABLE

#include "SerialStateController.hpp"

#include "PrimitiveList.hpp"
#include "PrimitiveMap.hpp"

#ifdef SerialState_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"

	#define SerialStateLog(location,method,type,mns) ame_Log(this,location,"SerialState",method,type,mns)
#else
	#ifdef SerialState_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"

		#define SerialStateLog(location,method,type,mns) ame_LogDebug(this,location,"SerialState",method,type)
	#else
		#define SerialStateLog(location,method,type,mns)
	#endif
#endif

namespace ame{

class SerialState : public SerialStateController{
    public:
		SerialState(){
			SerialStateLog(ame_Log_StartMethod, "Constructor", "println", "");
			SerialStateLog(ame_Log_EndMethod, "Constructor", "println", "");
		}
		virtual ~SerialState(){
			SerialStateLog(ame_Log_StartMethod, "Destructor", "println", "");
			SerialStateLog(ame_Log_EndMethod, "Destructor", "println", "");
		}

		virtual void updateState(float tpc){
			for(int x = 0; x < this->m_servers.getPosition(); x++){
				auto f_entry = m_servers.getMapEntryByPosition(x);
				SerialServer* server = f_entry.getKey();
				ServerProtocol* serverProtocol = f_entry.getValue();
				if(server == nullptr || serverProtocol == nullptr){
					continue;
				}
				SerialPort* port = serverProtocol->getUpdateSerialPort(server);
				if(port != nullptr){
					SerialStateLog(ame_Log_Statement, "update",  "println", "serial != nullptr");
					serverProtocol->UpdateSerialPort(port);
				}
				serverProtocol->update(server, tpc);
			}
			for(int index = 0; index < this->m_ports.getPosition(); index++){
				auto f_entry = this->m_ports.getMapEntryByPosition(index);
				SerialPort* port = f_entry.getKey();
				PortProtocol* portProtocol = f_entry.getValue();
				if(port == nullptr || portProtocol == nullptr){
					SerialStateLog(ame_Log_Statement, "update",  "println", "port == nullptr || portProtocol == nullptr");
					continue;
				}
				if(!port->connected()){
					SerialStateLog(ame_Log_Statement, "update",  "println", "!port->connected()");
					portProtocol->UpdateDisconect(port);
					if(portProtocol->SafeDelete()){
						SerialStateLog(ame_Log_Statement, "update",  "println", "portProtocol->SafeDelete()");
						onDisconnection(port, portProtocol);
						this->m_ports.removeDeleteByPosition(index);
						index--;
					}else{
						SerialStateLog(ame_Log_Statement, "update",  "println", "!portProtocol->SafeDelete()");
						onDisconnection(port, portProtocol);
						this->m_ports.removeByPosition(index);
						index--;
					}
				}else{
					// SerialStateLog(ame_Log_Statement, "update",  "println", Note("index: ") + Note(index));
					// SerialStateLog(ame_Log_Statement, "update",  "println", Note("Port Name: ") + port->getName());
					if(port->available() > 0) {
						// Serial.println("port->available() > 0");
						SerialStateLog(ame_Log_Statement, "update",  "println", "port->available() > 0");
						portProtocol->Read(index,port);
					}
					for(int x = 0; x < m_broadMessages.getPosition(); x++){
						portProtocol->BroadcastMessage(port, *m_broadMessages.getByPosition(x));
					}
					portProtocol->update(port,tpc);
				}
			}
			m_broadMessages.resetDelete();

			for(int x = 0; x < m_clientMessages.getPosition(); x++){
				int index = *m_clientMessages.getKeyByPosition(x);
				auto f_entry = m_ports.getMapEntryByPosition(index);
				SerialPort* port = f_entry.getKey();
				PortProtocol* portProtocol = f_entry.getValue();
				if(port == nullptr || portProtocol == nullptr){
					continue;
				}
				portProtocol->PrivateMessage(port, *m_clientMessages.getValueByPosition(x));
			}
			m_clientMessages.resetDelete();
		}
			
		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){
			return Class<SerialState>::getClass();
		}
		
		virtual bool instanceof(cppObjectClass* cls){
			return cls == Class<SerialState>::getClass() || SerialStateController::instanceof(cls);
		}
		#endif

	protected:
};

}

#endif
