
#ifndef CONFIGURATION_SerialNetwork_hpp
#define CONFIGURATION_SerialNetwork_hpp

	#include "ame_Enviroment.hpp"

	#if defined(DISABLE_SerialNetwork)
		#define SerialNetwork_hpp
	#endif
#endif

#ifndef SerialNetwork_hpp
#define SerialNetwork_hpp
#define SerialNetwork_AVAILABLE

#include "BaseAppState.hpp"
#include "Message.hpp"
#include "Note.hpp"
#include "NoteHelper.hpp"
#include "ByteArray.hpp"
#include "NetworkConnectivity.hpp"
#include "NetworkReliability.hpp"

namespace ame{
	class SerialNetwork;
}

#include "MessageDelivery.hpp"

#ifdef SerialNetwork_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"
	
	#define SerialNetworkLog(location,method,type,mns) ame_Log(this,location,"SerialNetwork",method,type,mns)
#else
	#ifdef SerialNetwork_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"
		
		#define SerialNetworkLog(location,method,type,mns) ame_LogDebug(this,location,"SerialNetwork",method,type)
	#else
		#define SerialNetworkLog(location,method,type,mns) 
	#endif
#endif

namespace ame{

/*
*	Class Configuration:
*	DISABLE_IMPLEMENTATION_BaseAppState
*/
class SerialNetwork IMPLEMENTATION_BaseAppState {	
    public:	
		virtual ~SerialNetwork(){}
			
		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){
			return Class<SerialNetwork>::getClass();
		}
		
		virtual bool instanceof(cppObjectClass* cls){
			return cls == Class<SerialNetwork>::getClass()
			#if defined(BaseAppState_AVAILABLE)
			|| BaseAppState::instanceof(cls)
			#endif
			;
		}
		#endif
		
		virtual void setIP(Note a_ip){m_ip = a_ip;}
		virtual void setMAC(Note a_mac){m_mac = a_mac;}

		virtual Note getIP(){return this->m_ip;}
		virtual Note getMAC(){return this->m_mac;}
		
		virtual void instantSend(Note a_message){}
		
		virtual void instantSend(ByteArray a_message){}

		virtual void instantSend(Note a_name, Note a_message){}

		virtual void instantSend(Note a_name, ByteArray a_message){}
		
		virtual void send(Note a_message){}
		
		virtual void send(ByteArray a_message){}

		virtual void send(Note a_name, Note a_message){}

		virtual void send(Note a_name, ByteArray a_message){}
		
		virtual bool isConnected(Note a_name){return false;}
    
		virtual void connect() {}
		
		virtual void connect(Note a_name) {}
		    
		virtual void disconect() {}
		
		virtual void disconect(Note a_name) {}
		
		virtual bool ping(Note a_name){
			return false;
		}
		
		virtual void setDelivery(MessageDelivery* a_delivery){
			m_delivery = a_delivery;
			if(m_delivery == nullptr){
				return;
			}
			#if defined(AppState_AVAILABLE)
			if(this->hasInitialize()){
				m_delivery->initialize(this);
			}
			#endif
		}
		
		virtual MessageDelivery* getDelivery(){
			return m_delivery;
		}
		
		virtual bool DeliverMessage(const Message& a_mns){
			return m_delivery->DeliverMessage(a_mns);
		}
		
		virtual bool DeliverMessage(const Note& a_mns){
			if(isNoteEmpty(a_mns)){
				return false;
			}
			return m_delivery->DeliverMessage(a_mns);
		}
		
		virtual bool DeliverMessage(const ByteArray& a_mns){
			if(a_mns.isEmpty()){
				return false;
			}
			return m_delivery->DeliverMessage(a_mns);
		}
		
		virtual void setConnectivity(NetworkConnectivity a_connectivity){
			m_connectivity = a_connectivity;
		}
		
		virtual void setReliability(NetworkReliability a_reliability){
			m_reliability = a_reliability;
		}
		
		virtual void initializeState(){
			SerialNetworkLog(ame_Log_StartMethod, "initializeState", "println", "");
			if(m_delivery != nullptr){
				m_delivery->initialize(this);
			}
			SerialNetworkLog(ame_Log_EndMethod, "initializeState", "println", "");
		}
		
		virtual void updateState(float tpc){
			
		}
		
	protected:
		Note m_ip = "150.1.0.0";
		Note m_mac = "0.0.0.0.0.0,0";
	
		MessageDelivery* m_delivery = nullptr;
		
		NetworkConnectivity m_connectivity = NetworkConnectivity::Mesh;
		NetworkReliability m_reliability = NetworkReliability::Tcp;
};

}

#endif