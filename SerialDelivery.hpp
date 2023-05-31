
#ifndef CONFIGURATION_SerialDelivery_hpp
#define CONFIGURATION_SerialDelivery_hpp

	#include "ame_Enviroment.hpp"

	#if defined(DISABLE_SerialDelivery)
		#define SerialDelivery_hpp
	#endif
#endif

#ifndef SerialDelivery_hpp
#define SerialDelivery_hpp
#define SerialDelivery_AVAILABLE

#include "Message.hpp"
#include "MessageDelivery.hpp"
#include "SerialListenerState.hpp"
#include "Class.hpp"

#ifdef SerialDelivery_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"
	
	#define SerialDeliveryLog(location,method,type,mns) ame_Log(this,location,"SerialDelivery",method,type,mns)
#else
	#ifdef SerialDelivery_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"
		
		#define SerialDeliveryLog(location,method,type,mns) ame_LogDebug(this,location,"SerialDelivery",method,type)
	#else
		#define SerialDeliveryLog(location,method,type,mns) 
	#endif
#endif

namespace ame{

class SerialDelivery : public MessageDelivery{	
    public:	
		SerialDelivery(){
			SerialDeliveryLog(ame_Log_StartMethod, "Constructor", "println", "Default Constructor");
			SerialDeliveryLog(ame_Log_EndMethod, "Constructor", "println", "");
		}
		SerialDelivery(SerialListenerState<Message>* c_message_listener_state){
			SerialDeliveryLog(ame_Log_StartMethod, "Constructor", "println", "");
			this->m_listener_message_state = c_message_listener_state;
			SerialDeliveryLog(ame_Log_EndMethod, "Constructor", "println", "");
		}
		SerialDelivery(SerialListenerState<Note>* c_note_listener_state){
			SerialDeliveryLog(ame_Log_StartMethod, "Constructor", "println", "");
			this->m_listener_note_state = c_note_listener_state;
			SerialDeliveryLog(ame_Log_EndMethod, "Constructor", "println", "");
		}
		virtual ~SerialDelivery(){
			SerialDeliveryLog(ame_Log_StartMethod, "Destructor", "println", "Default Constructor");
			SerialDeliveryLog(ame_Log_EndMethod, "Destructor", "println", "");
		}
		
		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual void initialize(SerialNetwork* a_state){
			SerialDeliveryLog(ame_Log_StartMethod, "initialize", "println", "Default Constructor");
			this->serialNetwork = a_state;
			if(this->m_listener_message_state == nullptr){
				this->m_listener_message_state = this->serialNetwork->getApplication()->getStateManager()->getState<SerialListenerState<Message>>();
			}
			if(this->m_listener_note_state == nullptr){
				this->m_listener_note_state = this->serialNetwork->getApplication()->getStateManager()->getState<SerialListenerState<Note>>();
			}
			if(this->m_listener_byte_state == nullptr){
				this->m_listener_byte_state = this->serialNetwork->getApplication()->getStateManager()->getState<SerialListenerState<ByteArray>>();
			}
			SerialDeliveryLog(ame_Log_EndMethod, "initialize", "println", "");
		}
		#endif
		
		virtual bool DeliverMessage(const Message& a_mns){
			SerialDeliveryLog(ame_Log_StartMethod, "DeliverMessage", "println", "Message");
			SerialDeliveryLog(ame_Log_Statement, "DeliverMessage", "println", "Message:");
			SerialDeliveryLog(ame_Log_Statement, "DeliverMessage", "println", a_mns);
			#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
			if(this->m_listener_message_state == nullptr && this->serialNetwork != nullptr){
				SerialDeliveryLog(ame_Log_Statement, "DeliverMessage", "println", "this->m_listener_note_state == nullptr && this->serialNetwork != nullptr");
				this->m_listener_message_state = this->serialNetwork->getApplication()->getStateManager()->getState<SerialListenerState<Message>>();
			}
			#endif
			if(this->m_listener_message_state == nullptr){
				SerialDeliveryLog(ame_Log_Statement, "DeliverMessage", "println", "this->m_listener_note_state == nullptr");
				SerialDeliveryLog(ame_Log_EndMethod, "DeliverMessage", "println", "return false");
				return false;
			}
			this->m_listener_message_state->addInput(a_mns);
			SerialDeliveryLog(ame_Log_EndMethod, "DeliverMessage", "println", "return true");
			return true;
		}
		
		virtual bool DeliverMessage(const Note& a_mns){
			SerialDeliveryLog(ame_Log_StartMethod, "DeliverMessage", "println", "Note");
			SerialDeliveryLog(ame_Log_Statement, "DeliverMessage", "println", "Message:");
			SerialDeliveryLog(ame_Log_Statement, "DeliverMessage", "println", a_mns);
			#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
			if(this->m_listener_note_state == nullptr && this->serialNetwork != nullptr){
				SerialDeliveryLog(ame_Log_Statement, "DeliverMessage", "println", "this->m_listener_note_state == nullptr && this->serialNetwork != nullptr");
				this->m_listener_note_state = this->serialNetwork->getApplication()->getStateManager()->getState<SerialListenerState<Note>>();
			}
			#endif
			if(this->m_listener_note_state == nullptr){
				SerialDeliveryLog(ame_Log_Statement, "DeliverMessage", "println", "this->m_listener_note_state == nullptr");
				SerialDeliveryLog(ame_Log_EndMethod, "DeliverMessage", "println", "return false");
				return false;
			}
			this->m_listener_note_state->addInput(a_mns);
			SerialDeliveryLog(ame_Log_EndMethod, "DeliverMessage", "println", "return true");
			return true;
		}

		virtual bool DeliverMessage(const ByteArray& a_mns){
			SerialDeliveryLog(ame_Log_StartMethod, "DeliverMessage", "println", "ByteArray");
			SerialDeliveryLog(ame_Log_EndMethod, "DeliverMessage", "println", "");
			return false;
		}
		
		virtual bool StreamDeliverMessage(char a_mns){
			SerialDeliveryLog(ame_Log_StartMethod, "StreamDeliverMessage", "println", "Default Constructor");
			SerialDeliveryLog(ame_Log_EndMethod, "StreamDeliverMessage", "println", "");
			return false;
		}
		virtual bool StreamDeliverMessage(ame_Byte a_mns){
			SerialDeliveryLog(ame_Log_StartMethod, "StreamDeliverMessage", "println", "Default Constructor");
			SerialDeliveryLog(ame_Log_EndMethod, "StreamDeliverMessage", "println", "");
			return false;
		}
			
		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){return Class<SerialDelivery>::getClass();}
		virtual bool instanceof(cppObjectClass* cls){
			return cls == Class<SerialDelivery>::getClass() || MessageDelivery::instanceof(cls);
		}
		#endif
		
	protected:
		SerialListenerState<Message>* m_listener_message_state = nullptr;
		SerialListenerState<Note>* m_listener_note_state = nullptr;
		SerialListenerState<ByteArray>* m_listener_byte_state = nullptr;
};

}

#endif