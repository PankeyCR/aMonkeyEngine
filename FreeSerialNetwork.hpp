
#ifndef CONFIGURATION_FreeSerialNetwork_hpp
#define CONFIGURATION_FreeSerialNetwork_hpp

	#include "ame_Enviroment.hpp"

	#if defined(DISABLE_FreeSerialNetwork)
		#define FreeSerialNetwork_hpp
	#endif
#endif

#ifndef FreeSerialNetwork_hpp
#define FreeSerialNetwork_hpp
#define FreeSerialNetwork_AVAILABLE

#include "SerialState.hpp"

#include "PrimitiveList.hpp"
#include "PrimitiveMap.hpp"

#ifdef FreeSerialNetwork_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"

	#define FreeSerialNetworkLog(location,method,type,mns) ame_Log(this,location,"FreeSerialNetwork",method,type,mns)
#else
	#ifdef FreeSerialNetwork_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"

		#define FreeSerialNetworkLog(location,method,type,mns) ame_LogDebug(this,location,"FreeSerialNetwork",method,type)
	#else
		#define FreeSerialNetworkLog(location,method,type,mns)
	#endif
#endif

namespace ame{

class FreeSerialNetwork : public SerialState{
    public:
		FreeSerialNetwork(){
			FreeSerialNetworkLog(ame_Log_StartMethod, "Constructor", "println", "");
			FreeSerialNetworkLog(ame_Log_EndMethod, "Constructor", "println", "");
		}
		virtual ~FreeSerialNetwork(){
			FreeSerialNetworkLog(ame_Log_StartMethod, "Destructor", "println", "");
			FreeSerialNetworkLog(ame_Log_EndMethod, "Destructor", "println", "");
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
					FreeSerialNetworkLog(ame_Log_Statement, "update",  "println", "serial != nullptr");
					serverProtocol->UpdateSerialPort(port);
				}
				serverProtocol->update(server, tpc);
			}
			for(int index = 0; index < this->m_ports.getPosition(); index++){
				auto f_entry = this->m_ports.getMapEntryByPosition(index);
				SerialPort* port = f_entry.getKey();
				PortProtocol* portProtocol = f_entry.getValue();
				if(port == nullptr || portProtocol == nullptr){
					FreeSerialNetworkLog(ame_Log_Statement, "update",  "println", "port == nullptr || portProtocol == nullptr");
					continue;
				}
				if(!port->connected()){
					FreeSerialNetworkLog(ame_Log_Statement, "update",  "println", "!port->connected()");
					portProtocol->UpdateDisconect(port);
					if(portProtocol->SafeDelete()){
						FreeSerialNetworkLog(ame_Log_Statement, "update",  "println", "portProtocol->SafeDelete()");
						onDisconnection(port, portProtocol);
						this->m_ports.removeDeleteByPosition(index);
						index--;
					}else{
						FreeSerialNetworkLog(ame_Log_Statement, "update",  "println", "!portProtocol->SafeDelete()");
						onDisconnection(port, portProtocol);
						this->m_ports.removeByPosition(index);
						index--;
					}
				}else{
					// FreeSerialNetworkLog(ame_Log_Statement, "update",  "println", Note("index: ") + Note(index));
					// FreeSerialNetworkLog(ame_Log_Statement, "update",  "println", Note("Port Name: ") + port->getName());
					if(port->available() > 0) {
						// Serial.println("port->available() > 0");
						FreeSerialNetworkLog(ame_Log_Statement, "update",  "println", "port->available() > 0");
						portProtocol->Read(index, port);
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
			return Class<FreeSerialNetwork>::getClass();
		}
		
		virtual bool instanceof(cppObjectClass* cls){
			return cls == Class<FreeSerialNetwork>::getClass() || SerialState::instanceof(cls);
		}
		#endif

	protected:
};

}

#endif
