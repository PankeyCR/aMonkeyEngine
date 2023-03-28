
#ifndef CONFIGURATION_ListDelivery_hpp
#define CONFIGURATION_ListDelivery_hpp

	#include "ame_Enviroment.hpp"

	#if defined(DISABLE_ListDelivery)
		#define ListDelivery_hpp
	#endif
#endif

#ifndef ListDelivery_hpp
#define ListDelivery_hpp
#define ListDelivery_AVAILABLE

#include "MessageDelivery.hpp"
#include "ListDelivery.hpp"
#include "SerialListenerState.hpp"
#include "NoteHelper.hpp"
#include "Class.hpp"

#ifdef ListDelivery_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"
	
	#define ListDeliveryLog(location,method,type,mns) ame_Log(this,location,"ListDelivery",method,type,mns)
#else
	#ifdef ListDelivery_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"
		
		#define ListDeliveryLog(location,method,type,mns) ame_LogDebug(this,location,"ListDelivery",method,type)
	#else
		#define ListDeliveryLog(location,method,type,mns) 
	#endif
#endif

namespace ame{

class ListDelivery : public MessageDelivery{	
    public:	
		ListDelivery(){
			ListDeliveryLog(ame_Log_StartMethod, "Constructor", "println", "Default Constructor");
			ListDeliveryLog(ame_Log_EndMethod, "Constructor", "println", "");
		}
		ListDelivery(SerialListenerState<MessageList>* c_message_listener_state){
			ListDeliveryLog(ame_Log_StartMethod, "Constructor", "println", "");
			this->m_listener_message_state = c_message_listener_state;
			ListDeliveryLog(ame_Log_EndMethod, "Constructor", "println", "");
		}
		ListDelivery(SerialListenerState<PrimitiveList<Note>>* c_note_listener_state){
			ListDeliveryLog(ame_Log_StartMethod, "Constructor", "println", "");
			this->m_listener_note_state = c_note_listener_state;
			ListDeliveryLog(ame_Log_EndMethod, "Constructor", "println", "");
		}
		virtual ~ListDelivery(){
			ListDeliveryLog(ame_Log_StartMethod, "Destructor", "println", "Default Constructor");
			ListDeliveryLog(ame_Log_EndMethod, "Destructor", "println", "");
		}
		
		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE) && defined(SerialNetwork_AVAILABLE)
		virtual void initialize(SerialNetwork* a_state){
			ListDeliveryLog(ame_Log_StartMethod, "initialize", "println", "Default Constructor");
			if(a_state == nullptr){
				ListDeliveryLog(ame_Log_EndMethod, "initialize", "println", "");
				return;
			}
			this->serialState = state;
			if(this->m_listener_message_state == nullptr){
				this->m_listener_message_state = this->serialState->getApplication()->getStateManager()->getState<SerialListenerState<MessageList>>();
			}
			if(this->m_listener_note_state == nullptr){
				this->m_listener_note_state = this->serialState->getApplication()->getStateManager()->getState<SerialListenerState<PrimitiveList<Note>>>();
			}
			ListDeliveryLog(ame_Log_EndMethod, "initialize", "println", "");
		}
		#endif
		
		virtual bool DeliverMessage(const Message& a_mns){
			ListDeliveryLog(ame_Log_StartMethod, "DeliverMessage", "println", "");
			#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
			if(this->m_listener_message_state == nullptr && this->serialState != nullptr){
				ListDeliveryLog(ame_Log_Statement, "DeliverMessage", "println", "this->m_listener_note_state == nullptr && this->serialState != nullptr");
				this->m_listener_message_state = this->serialState->getApplication()->getStateManager()->getState<SerialListenerState<MessageList>>();
			}
			#endif
			if(this->m_listener_message_state == nullptr){
				ListDeliveryLog(ame_Log_Statement, "DeliverMessage", "println", "this->m_listener_note_state == nullptr");
				ListDeliveryLog(ame_Log_EndMethod, "DeliverMessage", "println", "return false");
				return false;
			}
			PrimitiveList<Note> i_commands = splitNote(a_mns.text(), m_split_char);
			MessageList i_message_list;
			i_message_list.id(a_mns.id());
			i_message_list.name(a_mns.name());
			i_message_list.type(a_mns.type());
			i_message_list.list(i_commands);
			this->m_listener_message_state->addInput(i_message_list);
			ListDeliveryLog(ame_Log_EndMethod, "DeliverMessage", "println", "return true");
			return true;
		}
		
		virtual bool DeliverMessage(const Note& a_mns){
			ListDeliveryLog(ame_Log_StartMethod, "DeliverMessage", "println", "");
			#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
			if(this->m_listener_note_state == nullptr && this->serialState != nullptr){
				ListDeliveryLog(ame_Log_Statement, "DeliverMessage", "println", "this->m_listener_note_state == nullptr && this->serialState != nullptr");
				this->m_listener_note_state = this->serialState->getApplication()->getStateManager()->getState<SerialListenerState<Note>>();
			}
			#endif
			if(this->m_listener_note_state == nullptr){
				ListDeliveryLog(ame_Log_Statement, "DeliverMessage", "println", "this->m_listener_note_state == nullptr");
				ListDeliveryLog(ame_Log_EndMethod, "DeliverMessage", "println", "return false");
				return false;
			}
			PrimitiveList<Note> i_commands = splitNote(a_mns, m_split_char);
			this->m_listener_note_state->addInput(i_commands);
			ListDeliveryLog(ame_Log_EndMethod, "DeliverMessage", "println", "return true");
			return true;
		}

		virtual bool DeliverMessage(const ByteArray& a_mns){
			ListDeliveryLog(ame_Log_StartMethod, "DeliverMessage", "println", "Default Constructor");
			ListDeliveryLog(ame_Log_EndMethod, "DeliverMessage", "println", "");
			return false;
		}
		
		virtual bool StreamDeliverMessage(char a_mns){
			ListDeliveryLog(ame_Log_StartMethod, "StreamDeliverMessage", "println", "Default Constructor");
			ListDeliveryLog(ame_Log_EndMethod, "StreamDeliverMessage", "println", "");
			return false;
		}
		virtual bool StreamDeliverMessage(ame_Byte a_mns){
			ListDeliveryLog(ame_Log_StartMethod, "StreamDeliverMessage", "println", "Default Constructor");
			ListDeliveryLog(ame_Log_EndMethod, "StreamDeliverMessage", "println", "");
			return false;
		}
			
		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){return Class<ListDelivery>::getClass();}
		virtual bool instanceof(cppObjectClass* cls){
			return cls == Class<ListDelivery>::getClass() || MessageDelivery::instanceof(cls);
		}
		#endif
		
	protected:
		SerialListenerState<MessageList>* m_listener_message_state = nullptr;
		SerialListenerState<PrimitiveList<Note>>* m_listener_note_state = nullptr;
		SerialListenerState<PrimitiveList<ByteArray>>* m_listener_byte_state = nullptr;

		char m_split_char = ' ';
};

}

#endif