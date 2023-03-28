
#ifndef CONFIGURATION_SerialStateController_hpp
#define CONFIGURATION_SerialStateController_hpp

	#include "ame_Enviroment.hpp"

	#if defined(DISABLE_SerialStateController)
		#define SerialStateController_hpp
	#endif
#endif

#ifndef SerialStateController_hpp
#define SerialStateController_hpp
#define SerialStateController_AVAILABLE

#include "SerialNetwork.hpp"
#include "PrimitiveList.hpp"
#include "PrimitiveMap.hpp"

namespace ame{
	class SerialStateController;
}

#include "SerialServer.hpp"
#include "ServerProtocol.hpp"

#include "SerialPort.hpp"
#include "PortProtocol.hpp"

#include "SerialConnectionStateChanger.hpp"
#include "Message.hpp"

#ifdef SerialStateController_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"

	#define SerialStateControllerLog(location,method,type,mns) ame_Log(this,location,"SerialStateController",method,type,mns)
#else
	#ifdef SerialStateController_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"

		#define SerialStateControllerLog(location,method,type,mns) ame_LogDebug(this,location,"SerialStateController",method,type)
	#else
		#define SerialStateControllerLog(location,method,type,mns)
	#endif
#endif

namespace ame{

class SerialStateController : public SerialNetwork{
    public:
		using MethodStateChanger = void (*)(SerialPort*,PortProtocol*);
		using MethodStateGlobalChanger = void (*)();
		
		virtual ~SerialStateController(){
			SerialStateControllerLog(ame_Log_StartMethod, "Destructor", "println", "");
			SerialStateControllerLog(ame_Log_EndMethod, "Destructor", "println", "");
		}

		//The onConnections methods are only used if the port and the protocol are not nullptr

		virtual void onGlobalConnection(){
			SerialStateControllerLog(ame_Log_StartMethod, "onGlobalConnection", "println", "");
			for(int xDisc = 0; xDisc < m_methodStateGlobalChanger_onConnection.getPosition(); xDisc++){
				MethodStateGlobalChanger* schanger = m_methodStateGlobalChanger_onConnection.getByPosition(xDisc);
				(*schanger)();//change
			}
			for(int xDisc = 0; xDisc < m_stateChanger.getPosition(); xDisc++){
				SerialConnectionStateChanger* schanger = m_stateChanger.getByPosition(xDisc);
				schanger->onGlobalConnection();
			}
			SerialStateControllerLog(ame_Log_EndMethod, "onGlobalConnection", "println", "");
		}

		virtual void onGlobalDisconnection(){
			SerialStateControllerLog(ame_Log_StartMethod, "onGlobalDisconnection", "println", "");
			for(int xDisc = 0; xDisc < m_methodStateGlobalChanger_onDisconnection.getPosition(); xDisc++){
				MethodStateGlobalChanger* schanger = m_methodStateGlobalChanger_onDisconnection.getByPosition(xDisc);
				(*schanger)();//change
			}
			for(int xDisc = 0; xDisc < m_stateChanger.getPosition(); xDisc++){
				SerialConnectionStateChanger* schanger = m_stateChanger.getByPosition(xDisc);
				schanger->onGlobalDisconnection();
			}
			SerialStateControllerLog(ame_Log_EndMethod, "onGlobalDisconnection", "println", "");
		}

		virtual void onConnection(){
			SerialStateControllerLog(ame_Log_StartMethod, "onConnection", "println", "");
			for(int x_ports = 0; x_ports < m_ports.getPosition(); x_ports++){
				auto f_entry = m_ports.getMapEntryByPosition(x_ports);
				SerialPort* f_ports = f_entry.getKey();
				PortProtocol* f_protocol = f_entry.getValue();
				for(int xDisc = 0; xDisc < m_methodStateChanger_onConnection.getPosition(); xDisc++){
					MethodStateChanger* schanger = m_methodStateChanger_onConnection.getByPosition(xDisc);
					(*schanger)(f_ports, f_protocol);//change
				}
				for(int xDisc = 0; xDisc < m_stateChanger.getPosition(); xDisc++){
					SerialConnectionStateChanger* schanger = m_stateChanger.getByPosition(xDisc);
					schanger->onConnection(f_ports, f_protocol);
				}
			}
			SerialStateControllerLog(ame_Log_EndMethod, "onConnection", "println", "");
		}

		virtual void onDisconnection(){
			SerialStateControllerLog(ame_Log_StartMethod, "onDisconnection", "println", "");
			for(int x_ports = 0; x_ports < m_ports.getPosition(); x_ports++){
				auto f_entry = m_ports.getMapEntryByPosition(x_ports);
				SerialPort* f_ports = f_entry.getKey();
				PortProtocol* f_protocol = f_entry.getValue();
				for(int xDisc = 0; xDisc < m_methodStateChanger_onDisconnection.getPosition(); xDisc++){
					MethodStateChanger* schanger = m_methodStateChanger_onDisconnection.getByPosition(xDisc);
					(*schanger)(f_ports, f_protocol);//change
				}
				for(int xDisc = 0; xDisc < m_stateChanger.getPosition(); xDisc++){
					SerialConnectionStateChanger* schanger = m_stateChanger.getByPosition(xDisc);
					schanger->onDisconnection(f_ports, f_protocol);
				}
			}
			SerialStateControllerLog(ame_Log_EndMethod, "onDisconnection", "println", "");
		}

		virtual void onConnection(SerialPort* a_serialport, PortProtocol* a_portprotocol){
			SerialStateControllerLog(ame_Log_StartMethod, "onConnection", "println", "");
			for(int xDisc = 0; xDisc < m_methodStateChanger_onConnection.getPosition(); xDisc++){
				MethodStateChanger* schanger = m_methodStateChanger_onConnection.getByPosition(xDisc);
				(*schanger)(a_serialport, a_portprotocol);//change
			}
			for(int xDisc = 0; xDisc < m_stateChanger.getPosition(); xDisc++){
				SerialConnectionStateChanger* schanger = m_stateChanger.getByPosition(xDisc);
				schanger->onConnection(a_serialport, a_portprotocol);
			}
			SerialStateControllerLog(ame_Log_EndMethod, "onConnection", "println", "");
		}

		virtual void onDisconnection(SerialPort* a_serialport, PortProtocol* a_portprotocol){
			SerialStateControllerLog(ame_Log_StartMethod, "onDisconnection", "println", "");
			for(int xDisc = 0; xDisc < m_methodStateChanger_onDisconnection.getPosition(); xDisc++){
				MethodStateChanger* schanger = m_methodStateChanger_onDisconnection.getByPosition(xDisc);
				(*schanger)(a_serialport, a_portprotocol);//change
			}
			for(int xDisc = 0; xDisc < m_stateChanger.getPosition(); xDisc++){
				SerialConnectionStateChanger* schanger = m_stateChanger.getByPosition(xDisc);
				schanger->onDisconnection(a_serialport, a_portprotocol);
			}
			SerialStateControllerLog(ame_Log_EndMethod, "onDisconnection", "println", "");
		}

		virtual MapEntry<SerialServer,ServerProtocol> addSerialServer(SerialServer* a_serial, ServerProtocol* a_protocol){
			SerialStateControllerLog(ame_Log_StartMethod, "addSerialServer", "println", "");
			SerialStateControllerLog(ame_Log_EndMethod, "addSerialServer", "println", "");
			if(a_protocol != nullptr && this->hasInitialize()){
				a_protocol->initialize(this);
			}
			return m_servers.addPointers(a_serial, a_protocol);
		}

		virtual void initializeSerialServers(SerialStateController* a_serialState){
			SerialStateControllerLog(ame_Log_StartMethod, "initializeSerialServers", "println", "");
			for(int x = 0; x < m_servers.getPosition(); x++){
				ServerProtocol* f_protocol = m_servers.getValueByPosition(x);
				if(f_protocol == nullptr){
					continue;
				}
				f_protocol->initialize(a_serialState);
			}
			SerialStateControllerLog(ame_Log_EndMethod, "initializeSerialServers", "println", "");
		}

		virtual SerialServer* getSerialServer(int index){
			SerialStateControllerLog(ame_Log_StartMethod, "getSerialServer", "println", "int index");
			SerialStateControllerLog(ame_Log_EndMethod, "getSerialServer", "println", "");
			return m_servers.getKeyByPosition(index);
		}

		virtual int getSerialServerSize(){
			return m_servers.getPosition();
		}

		virtual bool containSerialServer(SerialServer* a_server){
			return m_servers.containKeyByPointer(a_server);
		}

		virtual bool containSerialServer(Note name){
			for(int x = 0; x < m_servers.getPosition(); x++){
				SerialServer* i_server = m_servers.getKeyByPosition(x);
				if(i_server == nullptr){
					continue;
				}
				if(i_server->getName() == name){
					return true;
				}
			}
			return false;
		}

		virtual MapEntry<SerialServer,ServerProtocol> removeSerialServer(SerialServer* a_server){
			SerialStateControllerLog(ame_Log_StartMethod, "removeSerialServer", "println", "");
			SerialStateControllerLog(ame_Log_EndMethod, "removeSerialServer", "println", "");
			return m_servers.removeByKeyPointer(a_server);
		}

		virtual bool removeDeleteSerialServer(SerialServer* a_server){
			SerialStateControllerLog(ame_Log_StartMethod, "removeDeleteSerialServer", "println", "");
			SerialStateControllerLog(ame_Log_EndMethod, "removeDeleteSerialServer", "println", "");
			return m_servers.removeDeleteByKeyPointer(a_server);
		}

		virtual MapEntry<SerialServer,ServerProtocol> removeSerialServer(int index){
			SerialStateControllerLog(ame_Log_StartMethod, "removeSerialServer", "println", "");
			SerialStateControllerLog(ame_Log_EndMethod, "removeSerialServer", "println", "");
			return m_servers.removeByPosition(index);
		}

		virtual bool removeDeleteSerialServer(int index){
			SerialStateControllerLog(ame_Log_StartMethod, "removeDeleteSerialServer", "println", "");
			SerialStateControllerLog(ame_Log_EndMethod, "removeDeleteSerialServer", "println", "");
			return m_servers.removeDeleteByPosition(index);
		}

		virtual void removeAllSerialServer(){
			SerialStateControllerLog(ame_Log_StartMethod, "removeAllSerialServer", "println", "");
			m_servers.reset();
			SerialStateControllerLog(ame_Log_EndMethod, "removeAllSerialServer", "println", "");
		}

		virtual void removeDeleteAllSerialServer(){
			SerialStateControllerLog(ame_Log_StartMethod, "removeAllSerialServer", "println", "");
			m_servers.resetDelete();
			SerialStateControllerLog(ame_Log_EndMethod, "removeAllSerialServer", "println", "");
		}

		virtual ServerProtocol* getServerProtocol(int index){
			return m_servers.getValueByPosition(index);
		}

		virtual ServerProtocol* getServerProtocol(SerialServer* a_server){
			return m_servers.getValueByPointer(a_server);
		}

		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE)
		virtual SerialServer* getSerialServer(cppObjectClass* cls){
			SerialStateControllerLog(ame_Log_StartMethod, "getSerialServer", "println", "cppObjectClass* cls");
			for(int x = 0; x < m_servers.getPosition(); x++){
				SerialServer* i_server = m_servers.getKeyByPosition(x);
				if(i_server == nullptr){
					continue;
				}
				if(i_server->getClass() == cls){
					SerialStateControllerLog(ame_Log_EndMethod, "getSerialServer", "println", "");
					return i_server;
				}
			}
			SerialStateControllerLog(ame_Log_EndMethod, "getSerialServer", "println", "");
			return nullptr;
		}

		virtual SerialServer* getSerialServer(Note name, cppObjectClass* cls){
			for(int x = 0; x < m_servers.getPosition(); x++){
				SerialServer* i_server = m_servers.getKeyByPosition(x);
				if(i_server == nullptr){
					continue;
				}
				if(i_server->getClass() == cls && i_server->getName() == name){
					return i_server;
				}
			}
			return nullptr;
		}
		
		virtual bool containSerialServer(cppObjectClass* cls){
			for(int x = 0; x < m_servers.getPosition(); x++){
				SerialServer* i_server = m_servers.getKeyByPosition(x);
				if(i_server == nullptr){
					continue;
				}
				if(i_server->getClass() == cls){
					return true;
				}
			}
			return false;
		}
		#endif

		virtual MapEntry<SerialPort,PortProtocol> addSerialPort(SerialPort* a_port, PortProtocol* a_protocol){
			SerialStateControllerLog(ame_Log_StartMethod, "addSerialPort",  "println", "SerialPort* a_port, PortProtocol* a_protocol");
			SerialStateControllerLog(ame_Log_EndMethod, "addSerialPort", "println", "");
			if(a_protocol != nullptr && this->hasInitialize()){
				a_protocol->initialize(this);
			}
			return m_ports.addPointers(a_port, a_protocol);
		}

		virtual void initializeSerialPorts(SerialStateController* a_serialState){
			SerialStateControllerLog(ame_Log_StartMethod, "initializeSerialPorts", "println", "");
			for(int x = 0; x < m_ports.getPosition(); x++){
				PortProtocol* f_protocol = m_ports.getValueByPosition(x);
				if(f_protocol == nullptr){
					continue;
				}
				f_protocol->initialize(a_serialState);
			}
			SerialStateControllerLog(ame_Log_EndMethod, "initializeSerialPorts", "println", "");
		}

		virtual PrimitiveMap<SerialPort,PortProtocol>& getSerialPorts(){
			return m_ports;
		}

		virtual SerialPort* getSerialPort(Note name){
			for(int x = 0; x < m_ports.getPosition(); x++){
				SerialPort* i_port = m_ports.getKeyByPosition(x);
				if(i_port == nullptr){
					continue;
				}
				if(i_port->getName() == name){
					return i_port;
				}
			}
			return nullptr;
		}

		virtual SerialPort* getSerialPort(int index){
			return m_ports.getKeyByPosition(index);
		}

		virtual int getSerialPortSize(){
			return m_ports.getPosition();
		}

		virtual bool containSerialPort(SerialPort* a_port){
			SerialStateControllerLog(ame_Log_StartMethod, "containSerialPort", "println", "");
			SerialStateControllerLog(ame_Log_EndMethod, "containSerialPort", "println", "");
			return m_ports.containKeyByPointer(a_port);
		}
		
		virtual bool containSerialPort(Note a_port){
			for(int x = 0; x < m_ports.getPosition(); x++){
				SerialPort* i_port = m_ports.getKeyByPosition(x);
				if(i_port == nullptr){
					continue;
				}
				if(i_port->getName() == a_port){
					return true;
				}
			}
			return false;
		}

		virtual MapEntry<SerialPort,PortProtocol> removeSerialPort(int index){
			SerialStateControllerLog(ame_Log_StartMethod, "removeSerialPort",  "println", "with protocol");
			SerialStateControllerLog(ame_Log_EndMethod, "removeSerialPort", "println", "");
			return m_ports.removeByPosition(index);
		}

		virtual bool removeDeleteSerialPort(int index){
			SerialStateControllerLog(ame_Log_StartMethod, "removeDeleteSerialPort",  "println", "with protocol");
			SerialStateControllerLog(ame_Log_EndMethod, "removeDeleteSerialPort", "println", "");
			return m_ports.removeDeleteByPosition(index);
		}

		virtual MapEntry<SerialPort,PortProtocol> removeSerialPort(SerialPort* a_port){
			SerialStateControllerLog(ame_Log_StartMethod, "removeSerialPort",  "println", "with protocol");
			SerialStateControllerLog(ame_Log_EndMethod, "removeSerialPort", "println", "");
			return m_ports.removeByKeyPointer(a_port);
		}

		virtual bool removeDeleteSerialPort(SerialPort* a_port){
			SerialStateControllerLog(ame_Log_StartMethod, "removeDeleteSerialPort",  "println", "with protocol");
			SerialStateControllerLog(ame_Log_EndMethod, "removeDeleteSerialPort", "println", "");
			return m_ports.removeDeleteByKeyPointer(a_port);
		}

		virtual void removeAllSerialPort(){
			SerialStateControllerLog(ame_Log_StartMethod, "removeAllSerialPort",  "println", "with protocol");
			m_ports.reset();
			SerialStateControllerLog(ame_Log_EndMethod, "removeAllSerialPort", "println", "");
		}

		virtual void removeDeleteAllSerialPort(){
			SerialStateControllerLog(ame_Log_StartMethod, "removeAllSerialPort",  "println", "with protocol");
			m_ports.resetDelete();
			SerialStateControllerLog(ame_Log_EndMethod, "removeAllSerialPort", "println", "");
		}

		virtual PortProtocol* getPortProtocol(int index){
			return m_ports.getValueByPosition(index);
		}

		virtual PortProtocol* getPortProtocol(SerialPort* a_port){
			return m_ports.getValueByPointer(a_port);
		}

		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE)
		virtual SerialPort* getSerialPort(Note name, cppObjectClass* cls){
			for(int x = 0; x < m_ports.getPosition(); x++){
				SerialPort* i_port = m_ports.getKeyByPosition(x);
				if(i_port == nullptr){
					continue;
				}
				if(i_port->getName() == name && i_port->getClass() == cls){
					return i_port;
				}
			}
			return nullptr;
		}

		virtual SerialPort* getSerialPort(cppObjectClass* cls){
			for(int x = 0; x < m_ports.getPosition(); x++){
				SerialPort* i_port = m_ports.getKeyByPosition(x);
				if(i_port == nullptr){
					continue;
				}
				if(i_port->getClass() == cls){
					return i_port;
				}
			}
			return nullptr;
		}

		virtual bool containSerialPort(Note name, cppObjectClass* cls){
			for(int x = 0; x < m_ports.getPosition(); x++){
				SerialPort* i_port = m_ports.getKeyByPosition(x);
				if(i_port == nullptr){
					continue;
				}
				if(i_port->getClass() == cls && i_port->getName() == name){
					return true;
				}
			}
			return false;
		}

		virtual bool containSerialPort(cppObjectClass* cls){
			for(int x = 0; x < m_ports.getPosition(); x++){
				SerialPort* i_port = m_ports.getKeyByPosition(x);
				if(i_port == nullptr){
					continue;
				}
				if(i_port->getClass() == cls){
					return true;
				}
			}
			return false;
		}
		#endif

		virtual void addConnectionStateChanger(SerialConnectionStateChanger* changer){
			m_stateChanger.addPointer(changer);
		}
		
		virtual SerialConnectionStateChanger* removeConnectionStateChanger(SerialConnectionStateChanger* changer){
			return m_stateChanger.removeByPointer(changer);
		}

		virtual void removeDeleteConnectionStateChanger(SerialConnectionStateChanger* changer){
			m_stateChanger.removeDeleteByPointer(changer);
		}

		virtual void addGlobalConnectionStateChanger(MethodStateGlobalChanger changer){
			m_methodStateGlobalChanger_onConnection.addLValue(changer);
		}

		virtual void removeGlobalConnectionStateChanger(MethodStateGlobalChanger changer){
			m_methodStateGlobalChanger_onConnection.removeByLValue(changer);
		}

		virtual void removeDeleteGlobalConnectionStateChanger(MethodStateGlobalChanger changer){
			m_methodStateGlobalChanger_onConnection.removeDeleteByLValue(changer);
		}

		virtual void addGlobalDisconnectionStateChanger(MethodStateGlobalChanger changer){
			m_methodStateGlobalChanger_onDisconnection.addLValue(changer);
		}

		virtual void removeGlobalDisconnectionStateChanger(MethodStateGlobalChanger changer){
			m_methodStateGlobalChanger_onDisconnection.removeByLValue(changer);
		}

		virtual void removeDeleteGlobalDisconnectionStateChanger(MethodStateGlobalChanger changer){
			m_methodStateGlobalChanger_onDisconnection.removeDeleteByLValue(changer);
		}

		virtual void addConnectionStateChanger(MethodStateChanger changer){
			m_methodStateChanger_onConnection.addLValue(changer);
		}

		virtual void removeConnectionStateChanger(MethodStateChanger changer){
			m_methodStateChanger_onConnection.removeByLValue(changer);
		}

		virtual void removeDeleteConnectionStateChanger(MethodStateChanger changer){
			m_methodStateChanger_onConnection.removeDeleteByLValue(changer);
		}

		virtual void addDisconnectionStateChanger(MethodStateChanger changer){
			m_methodStateChanger_onDisconnection.addLValue(changer);
		}

		virtual void removeDisconnectionStateChanger(MethodStateChanger changer){
			m_methodStateChanger_onDisconnection.removeByLValue(changer);
		}

		virtual void removeDeleteDisconnectionStateChanger(MethodStateChanger changer){
			m_methodStateChanger_onDisconnection.removeDeleteByLValue(changer);
		}

		virtual void initializeState(){
			SerialNetworkLog(ame_Log_StartMethod, "initializeState", "println", "");
			if(m_delivery != nullptr){
				m_delivery->initialize(this);
			}
			this->initializeSerialServers(this);
			this->initializeSerialPorts(this);
			
			SerialNetworkLog(ame_Log_EndMethod, "initializeState", "println", "");
		}
		
		virtual void instantSend(Note mns){
			SerialNetworkLog(ame_Log_Statement, "instantSend",  "println", "method with Note as parameter");
			for(int x = 0; x < this->m_ports.getPosition(); x++){
				auto f_entry = this->m_ports.getMapEntryByPosition(x);
				SerialPort* f_ports = f_entry.getKey();
				PortProtocol* f_protocol = f_entry.getValue();
				if(f_ports == nullptr || f_protocol == nullptr){
					return;
				}
				SerialNetworkLog(ame_Log_Statement, "instantSend",  "println", "trying to send port named: ");
				SerialNetworkLog(ame_Log_Statement, "instantSend",  "println", f_ports->getName());
				f_protocol->InstantBroadcastMessage(f_ports, mns);
			}
			SerialNetworkLog(ame_Log_EndMethod, "instantSend", "println", "");
		}

		virtual void instantSend(ByteArray a_message){}

		virtual void instantSend(int index, Note mns){
			SerialNetworkLog(ame_Log_Statement, "instantSend",  "println", "method with int and Note as parameter");
			SerialNetworkLog(ame_Log_Statement, "instantSend",  "println", Note("index: ") + Note(index));
			auto f_entry = m_ports.getMapEntryByPosition(index);
			SerialPort* f_ports = f_entry.getKey();
			PortProtocol* i_protocol = f_entry.getValue();
			if(f_ports == nullptr || i_protocol == nullptr){
				SerialNetworkLog(ame_Log_Statement, "instantSend",  "println", "port == nullptr || protocol == nullptr");
				return;
			}
			SerialNetworkLog(ame_Log_Statement, "instantSend",  "println", "sending port named: ");
			SerialNetworkLog(ame_Log_Statement, "instantSend",  "println", f_ports->getName());
			i_protocol->InstantPrivateMessage(f_ports, mns);
			SerialNetworkLog(ame_Log_EndMethod, "instantSend", "println", "");
		}

		virtual void instantPortSend(SerialPort* a_port, Note mns){
			SerialNetworkLog(ame_Log_Statement, "instantPortSend",  "println", "method with serialport and Note as parameter");
			SerialPort* port = a_port;
			PortProtocol* protocol = this->getPortProtocol(a_port);
			if(port == nullptr || protocol == nullptr){
				SerialNetworkLog(ame_Log_Statement, "instantPortSend",  "println", "port == nullptr || protocol == nullptr");
				return;
			}
			protocol->InstantPrivateMessage(port, mns);
			SerialNetworkLog(ame_Log_EndMethod, "instantPortSend", "println", "");
		}

		virtual void instantSend(Note name, Note mns){
			SerialNetworkLog(ame_Log_Statement, "instantSend",  "println", "method with a Note and a Note as parameter");
			SerialPort* port = this->getSerialPort(name);
			PortProtocol* portProtocol = m_ports.getValueByPointer(port);
			if(port == nullptr || portProtocol == nullptr){
				SerialNetworkLog(ame_Log_Statement, "instantSend",  "println", "port == nullptr || protocol == nullptr");
				return;
			}
			portProtocol->InstantPrivateMessage(port, mns);
			SerialNetworkLog(ame_Log_EndMethod, "instantSend", "println", "");
		}

		virtual void instantByteArraySend(Note name, ByteArray array){
			SerialNetworkLog(ame_Log_Statement, "instantByteArraySend",  "println", "method with a Note and a Note as parameter");
			SerialPort* port = this->getSerialPort(name);
			PortProtocol* portProtocol = m_ports.getValueByPointer(port);
			if(port == nullptr || portProtocol == nullptr){
				SerialNetworkLog(ame_Log_Statement, "instantByteArraySend",  "println", "port == nullptr || protocol == nullptr");
				return;
			}
			portProtocol->InstantPrivateByteArrayMessage(port, array);
			SerialNetworkLog(ame_Log_EndMethod, "instantByteArraySend", "println", "");
		}

		virtual void instantSend(Message mns){
			SerialNetworkLog(ame_Log_Statement, "instantSend",  "println", "method with Message as parameter");
			for(int x = 0; x < this->m_ports.getPosition(); x++){
				auto f_entry = m_ports.getMapEntryByPosition(x);
				SerialPort* f_ports = f_entry.getKey();
				PortProtocol* f_protocol = f_entry.getValue();
				if(f_ports == nullptr || f_protocol == nullptr){
					SerialNetworkLog(ame_Log_Statement, "instantSend",  "println", "port == nullptr || protocol == nullptr");
					return;
				}
				if(mns.id() == -1){
					SerialNetworkLog(ame_Log_Statement, "instantSend",  "println", "portProtocols InstantBroadcastMessage");
					f_protocol->InstantBroadcastMessage(f_ports, mns.text());
				}else{
					SerialNetworkLog(ame_Log_Statement, "instantSend",  "println", "portProtocols InstantPrivateMessage");
					f_protocol->InstantPrivateMessage(f_ports, mns.text());
				}
			}
			SerialNetworkLog(ame_Log_EndMethod, "instantSend", "println", "");
		}

		virtual void send(Note mns){
			SerialNetworkLog(ame_Log_Statement, "send",  "println", "method with Note as parameter");
			m_broadMessages.addLValue(mns);
			SerialNetworkLog(ame_Log_EndMethod, "send", "println", "");
		}

		virtual void send(ByteArray a_message){}

		virtual void send(int index, Note mns){
			SerialNetworkLog(ame_Log_Statement, "send",  "println", "method with a int and a Note as parameters");
			SerialNetworkLog(ame_Log_Statement, "send",  "println", Note("index: ") + Note(index));
			m_clientMessages.addPointers(new int(index), new Note(mns));
			SerialNetworkLog(ame_Log_EndMethod, "send", "println", "");
		}

		virtual void send(Note name, Note mns){
			SerialNetworkLog(ame_Log_Statement, "send",  "println", "method with 2 Notes as parameters");
			for(int x = 0 ; x < this->m_ports.getPosition(); x++){
				auto f_entry = m_ports.getMapEntryByPosition(x);
				SerialPort* f_port = f_entry.getKey();
				if(f_port == nullptr){
					continue;
				}
				if(f_port->getName() == name){
					m_clientMessages.addPointers(new int(x), new Note(mns));
					SerialNetworkLog(ame_Log_Statement, "send",  "println", ame_String("adding"));
				}
			}
			SerialNetworkLog(ame_Log_EndMethod, "send", "println", "");
		}

		virtual void send(Note a_name, ByteArray a_message){}

		virtual void send(SerialPort* port, Note mns){
			SerialNetworkLog(ame_Log_Statement, "send",  "println", "method with 2 Notes as parameters");
			for(int x = 0 ; x < this->m_ports.getPosition(); x++){
				auto f_entry = m_ports.getMapEntryByPosition(x);
				SerialPort* f_port = f_entry.getKey();
				if(f_port == port){
					m_clientMessages.addPointers(new int(x), new Note(mns));
					SerialNetworkLog(ame_Log_Statement, "send",  "println", ame_String("adding"));
				}
			}
			SerialNetworkLog(ame_Log_EndMethod, "send", "println", "");
		}

		virtual void send(Message mns){
			SerialNetworkLog(ame_Log_Statement, "send",  "println", "method with Message as parameter");
			if(mns.id() == -1){
				SerialNetworkLog(ame_Log_Statement, "send",  "println", "no id");
				m_broadMessages.addLValue(mns.text());
			}else{
				SerialNetworkLog(ame_Log_Statement, "send",  "println", "with id");
				m_clientMessages.addPointers(new int(mns.id()), new Note(mns.text()));
			}
			SerialNetworkLog(ame_Log_EndMethod, "send", "println", "");
		}

		virtual void send(Message* mns){
			SerialNetworkLog(ame_Log_Statement, "send",  "println", "method with Message pointer as parameter");
			if(mns->id() == -1){
				SerialNetworkLog(ame_Log_Statement, "send",  "println", "no id");
				m_broadMessages.addLValue(mns->text());
			}else{
				//SerialNetworkLog(ame_Log_Statement, "send",  "println", "with id");
				m_clientMessages.addPointers(new int(mns->id()), new Note(mns->text()));
			}
			SerialNetworkLog(ame_Log_EndMethod, "send", "println", "");
		}

		virtual bool isConnected(Note namae){
			SerialNetworkLog(ame_Log_EndMethod, "isConnected", "println", "");
			for(int x = 0; x < this->m_ports.getPosition(); x++){
				SerialPort* i_port = this->m_ports.getKeyByPosition(x);
				if(i_port == nullptr){
					continue;
				}
				if(i_port->getName() == namae){
					return i_port->connected();
				}
			}
			SerialNetworkLog(ame_Log_EndMethod, "isConnected", "println", "");
			return false;
		}

		virtual void connect() {
			SerialNetworkLog(ame_Log_EndMethod, "connect", "println", "");
			for(int x = 0; x < this->m_ports.getPosition(); x++){
				auto f_entry = m_ports.getMapEntryByPosition(x);
				SerialPort* f_port = f_entry.getKey();
				PortProtocol* f_protocol = f_entry.getValue();
				if(f_port == nullptr || f_protocol == nullptr){
					continue;
				}
				f_protocol->GlobalConect(f_port);
				onConnection(f_port, f_protocol);
			}
			onGlobalConnection();
			SerialNetworkLog(ame_Log_EndMethod, "connect", "println", "");
		}

		virtual void connect(SerialPort* port) {
			SerialNetworkLog(ame_Log_EndMethod, "connect", "println", "");
			PortProtocol* i_protocol = this->m_ports.getValueByPointer(port);
			if(port == nullptr || i_protocol == nullptr){
				return;
			}
			i_protocol->Conect(port);
			onConnection(port, i_protocol);
			SerialNetworkLog(ame_Log_EndMethod, "connect", "println", "");
		}

		virtual void connect(Note a_name) {
			SerialNetworkLog(ame_Log_EndMethod, "connect", "println", "");
			for(int x = 0; x < this->m_ports.getPosition(); x++){
				auto f_entry = m_ports.getMapEntryByPosition(x);
				SerialPort* f_port = f_entry.getKey();
				PortProtocol* f_protocol = f_entry.getValue();
				if(f_port == nullptr || f_protocol == nullptr){
					continue;
				}
				if(a_name != f_port->getName()){
					continue;
				}
				f_protocol->Conect(f_port);
				onConnection(f_port, f_protocol);
			}
			SerialNetworkLog(ame_Log_EndMethod, "connect", "println", "");
		}

		virtual void addConnect(SerialPort* port, PortProtocol* protocol) {
			SerialNetworkLog(ame_Log_StartMethod, "addConnect",  "println", "with protocol");
			if(port == nullptr){
				return;
			}
			this->m_ports.addPointers(port, protocol);
			if(protocol == nullptr){
				return;
			}
			protocol->initialize(this);
			protocol->Conect(port);
			onConnection(port, protocol);
			SerialNetworkLog(ame_Log_EndMethod, "addConnect", "println", "");
		}

		virtual void disconect() {
			SerialNetworkLog(ame_Log_EndMethod, "disconect", "println", "");
			for(int x = 0; x < m_ports.getPosition(); x++){
				auto f_entry = m_ports.getMapEntryByPosition(x);
				SerialPort* f_port = f_entry.getKey();
				PortProtocol* f_protocol = f_entry.getValue();
				if(f_port == nullptr || f_protocol == nullptr){
					continue;
				}
				f_protocol->GlobalDisconect(f_port);
				onDisconnection(f_port, f_protocol);
			}
			onGlobalDisconnection();
			SerialNetworkLog(ame_Log_EndMethod, "disconect", "println", "");
		}

		virtual void disconectDelete() {
			SerialNetworkLog(ame_Log_EndMethod, "disconectDelete", "println", "");
			for(int x = 0; x < m_ports.getPosition(); x++){
				auto f_entry = m_ports.getMapEntryByPosition(x);
				SerialPort* f_port = f_entry.getKey();
				PortProtocol* f_protocol = f_entry.getValue();
				if(f_port == nullptr || f_protocol == nullptr){
					continue;
				}
				f_protocol->GlobalDisconect(f_port);
				onDisconnection(f_port, f_protocol);
			}
			onGlobalDisconnection();
			this->m_ports.resetDelete();
			SerialNetworkLog(ame_Log_EndMethod, "disconectDelete", "println", "");
		}

		virtual void disconect(SerialPort* port) {
			SerialNetworkLog(ame_Log_EndMethod, "disconect", "println", "");
			PortProtocol* i_protocol = m_ports.getValueByPointer(port);
			if(i_protocol == nullptr){
				return;
			}
			i_protocol->Disconect(port);
			SerialNetworkLog(ame_Log_EndMethod, "disconect", "println", "");
		}

		virtual void disconect(Note a_name) {
			SerialNetworkLog(ame_Log_EndMethod, "disconect", "println", "");
			for(int x = 0; x < m_ports.getPosition(); x++){
				auto f_entry = m_ports.getMapEntryByPosition(x);
				SerialPort* f_port = f_entry.getKey();
				PortProtocol* f_protocol = f_entry.getValue();
				if(f_port == nullptr || f_protocol == nullptr){
					continue;
				}
				if(a_name != f_port->getName()){
					continue;
				}
				f_protocol->GlobalDisconect(f_port);
				onDisconnection(f_port, f_protocol);
			}
			SerialNetworkLog(ame_Log_EndMethod, "disconect", "println", "");
		}

		virtual bool ping(Note note){
			SerialNetworkLog(ame_Log_StartMethod, "ping", "println", "");
			SerialNetworkLog(ame_Log_EndMethod, "ping", "println", "");
			#if defined(ame_Windows)
				return false;
			#elif defined(ame_ArduinoIDE)
				#if defined(ame_GENERIC_ESP32)
				return false;
				// return WIFI.ping() == WL_PING_SUCCESS;
				#else
					return false;
				#endif
			#else
				return false;
			#endif
		}
			
		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){
			return Class<SerialStateController>::getClass();
		}
		
		virtual bool instanceof(cppObjectClass* cls){
			return cls == Class<SerialStateController>::getClass() || SerialNetwork::instanceof(cls);
		}
		#endif

	protected:
		PrimitiveList<Note> m_broadMessages;
		PrimitiveMap<int,Note> m_clientMessages;

		PrimitiveMap<SerialServer,ServerProtocol> m_servers;
		PrimitiveMap<SerialPort,PortProtocol> m_ports;

		PrimitiveList<MethodStateChanger> m_methodStateChanger_onConnection;
		PrimitiveList<MethodStateChanger> m_methodStateChanger_onDisconnection;

		//StateChanger
		PrimitiveList<SerialConnectionStateChanger> m_stateChanger;

		PrimitiveList<MethodStateGlobalChanger> m_methodStateGlobalChanger_onConnection;
		PrimitiveList<MethodStateGlobalChanger> m_methodStateGlobalChanger_onDisconnection;
};

}

#endif
