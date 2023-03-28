
#ifndef UDPNetwork_hpp
#define UDPNetwork_hpp
#define UDPNetwork_AVAILABLE

#include "SerialNetwork.hpp"
#include "Message.hpp"
#include "PrimitiveMap.hpp"
#include "Pair.hpp"
#include <EthernetUdp.h>

#ifdef UDPNetwork_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"
	
	#define UDPNetworkLog(location,method,type,mns) ame_Log(this,location,"UDPNetwork",method,type,mns)
#else
	#ifdef UDPNetwork_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"
		
		#define UDPNetworkLog(location,method,type,mns) ame_LogDebug(this,location,"UDPNetwork",method,type)
	#else
		#define UDPNetworkLog(location,method,type,mns) 
	#endif
#endif

namespace ame{

/*
*	Class Configuration:
*	DISABLE_IMPLEMENTATION_BaseAppState
*/
class UDPNetwork : public SerialNetwork{	
    public:	
		UDPNetwork(){}
		UDPNetwork(int c_port) : m_port(c_port){}
		virtual ~UDPNetwork(){}

		virtual void setPort(int a_port){
			m_port = a_port;
		}

		virtual int getPort(){
			return m_port;
		}

		virtual void udpSend(IPAddress a_ip, int a_port, Note a_message){
			// a_message.copyToExternPointer(m_send, ' ', UDP_TX_PACKET_MAX_SIZE);
			Udp.beginPacket(a_ip, a_port);
			// Udp.write(m_send, UDP_TX_PACKET_MAX_SIZE);
			Udp.print(a_message);
			Udp.endPacket();
		}
		
		virtual void instantSend(Note a_message){
			for(int x = 0; x < m_ports.getPosition(); x++){
				Note* f_note = m_ports.getKeyByPosition(x);
				Pair<IPAddress,int>* f_pair = m_ports.getValueByPosition(x);
				if(f_note == nullptr || f_pair == nullptr){
					continue;
				}
				if(f_pair->hasNull()){
					continue;
				}
				IPAddress f_ip = *f_pair->x1;
				int f_port = *f_pair->x2;
				this->udpSend(f_ip, f_port, a_message);
			}
		}
		
		virtual void instantSend(ByteArray a_message){}

		virtual void instantSend(Note a_name, Note a_message){
			Pair<IPAddress,int>* i_pair = m_ports.getValueByLValue(a_name);
			if(i_pair->hasNull()){
				return;
			}
			IPAddress i_ip = *i_pair->x1;
			int i_port = *i_pair->x2;
			this->udpSend(i_ip, i_port, a_message);
		}

		virtual void instantSend(Note a_name, ByteArray a_message){}
		
		virtual void send(Note a_message){
			for(int x = 0; x < m_ports.getPosition(); x++){
				Note* f_note = m_ports.getKeyByPosition(x);
				Pair<IPAddress,int>* f_pair = m_ports.getValueByPosition(x);
				if(f_note == nullptr || f_pair == nullptr){
					continue;
				}
				if(f_pair->hasNull()){
					continue;
				}
				IPAddress f_ip = *f_pair->x1;
				int f_port = *f_pair->x2;
				this->udpSend(f_ip, f_port, a_message);
			}
		}
		
		virtual void send(ByteArray a_message){}

		virtual void send(Note a_name, Note a_message){
			Pair<IPAddress,int>* i_pair = m_ports.getValueByLValue(a_name);
			if(i_pair->hasNull()){
				return;
			}
			IPAddress i_ip = *i_pair->x1;
			int i_port = *i_pair->x2;
			this->udpSend(i_ip, i_port, a_message);
		}

		virtual void send(Note a_name, ByteArray a_message){}
		
		virtual bool isConnected(Note a_name){return false;}
    
		virtual void connect() {}
		
		virtual void connect(Note a_name) {}
		    
		virtual void disconect() {}
		
		virtual void disconect(Note a_name) {}
		
		virtual bool ping(Note a_name){
			return false;
		}
		
		virtual void initializeState(){
			UDPNetworkLog(ame_Log_StartMethod, "initializeState", "println", "");
			UDPNetworkLog(ame_Log_Statement, "initializeState", "println", "Port:");
			UDPNetworkLog(ame_Log_Statement, "initializeState", "println", m_port);
			SerialNetwork::initializeState();
			Udp.begin(m_port);
			UDPNetworkLog(ame_Log_EndMethod, "initializeState", "println", "");
		}
		
		virtual void updateState(float tpc){
			//UDPNetworkLog(ame_Log_StartMethod, "updateState", "println", "");
			int packetSize = Udp.parsePacket();
			if (packetSize) {
				UDPNetworkLog(ame_Log_Statement, "updateState", "println", "packetSize");
				UDPNetworkLog(ame_Log_Statement, "updateState", "println", packetSize);
				IPAddress i_remote = Udp.remoteIP();
				int i_port = Udp.remotePort();
				int i_id = this->getPortId(i_remote);
				if(i_id == -1){
					UDPNetworkLog(ame_Log_EndMethod, "updateState", "println", "i_id == -1");
					return;
				}
				// Udp.read(m_read, UDP_TX_PACKET_MAX_SIZE);
				// Note i_text;
				// i_text.addLocalArrayPointer(m_read, UDP_TX_PACKET_MAX_SIZE);

				Note i_text;
				while(Udp.available() > 0){
					i_text.addLocalValue(Udp.read());
				}
				Message i_message;
				i_message.id(i_id);
				i_message.name(*m_ports.getKeyByPosition(i_id));
				i_message.text(i_text);
				this->DeliverMessage(i_message);
				UDPNetworkLog(ame_Log_EndMethod, "updateState", "println", "packetSize");
			}
			//UDPNetworkLog(ame_Log_EndMethod, "updateState", "println", "");
		}

		virtual void addPort(const Note& a_name, IPAddress a_ip, int a_port){
			m_ports.addPointer(a_name, new Pair<IPAddress,int>(new IPAddress(a_ip), new int(a_port), true));
		}

		virtual void removePort(const Note& a_name, IPAddress a_ip, int a_port){
			m_ports.removeDeleteByKeyLValue(a_name);
		}

		virtual int getPortId(IPAddress a_ip){
			for(int x = 0; x < m_ports.getPosition(); x++){
				Pair<IPAddress,int>* f_pair = m_ports.getValueByPosition(x);
				if(f_pair == nullptr){
					continue;
				}
				if(f_pair->hasNull()){
					continue;
				}
				IPAddress f_ip = *f_pair->x1;
				if(f_ip == a_ip){
					return x;
				}
			}
			return -1;
		}

		virtual int getPortId(IPAddress a_ip, int a_port){
			for(int x = 0; x < m_ports.getPosition(); x++){
				Pair<IPAddress,int>* f_pair = m_ports.getValueByPosition(x);
				if(f_pair == nullptr){
					continue;
				}
				if(f_pair->hasNull()){
					continue;
				}
				IPAddress f_ip = *f_pair->x1;
				int f_port = *f_pair->x2;
				if(f_ip == a_ip && f_port == a_port){
					return x;
				}
			}
			return -1;
		}
			
		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){return Class<UDPNetwork>::getClass();}
		virtual bool instanceof(cppObjectClass* cls){return cls == Class<UDPNetwork>::getClass() || SerialNetwork::instanceof(cls);}
		#endif
		
	protected:
		unsigned int m_port = 101;
		char m_read[UDP_TX_PACKET_MAX_SIZE];
		char m_send[UDP_TX_PACKET_MAX_SIZE];

		EthernetUDP Udp;

		PrimitiveMap<Note,Pair<IPAddress,int>> m_ports;
};

}

#endif