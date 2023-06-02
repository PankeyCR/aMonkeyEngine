
#ifndef DefaultPortProtocol_hpp
#define DefaultPortProtocol_hpp
#define DefaultPortProtocol_AVAILABLE

#include "ame_Enviroment.hpp"

#ifndef ame_Enviroment_Defined

#endif

#ifdef ame_Windows

#endif

#ifdef ame_ArduinoIDE
	#include "Arduino.h"
#endif

#include "PortProtocol.hpp"
#include "SerialPort.hpp"
#include "Note.hpp"
#include "MessageDelivery.hpp"

#ifdef DefaultPortProtocol_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"
	
	#define DefaultPortProtocolLog(location,method,type,mns) ame_Log(this,location,"DefaultPortProtocol",method,type,mns)
	#define const_DefaultPortProtocolLog(location,method,type,mns) 
	#define StaticDefaultPortProtocolLog(pointer,location,method,type,mns) ame_Log(pointer,location,"DefaultPortProtocol",method,type,mns)
#else
	#ifdef DefaultApplication_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"
		
		#define DefaultPortProtocolLog(location,method,type,mns) ame_LogDebug(this,location,"DefaultPortProtocol",method,type)
		#define const_DefaultPortProtocolLog(location,method,type,mns) 
		#define StaticDefaultPortProtocolLog(pointer,location,method,type,mns) ame_LogDebug(pointer,location,"DefaultPortProtocol",method,type)
	#else
		#define DefaultPortProtocolLog(location,method,type,mns) 
		#define const_DefaultPortProtocolLog(location,method,type,mns) 
		#define StaticDefaultPortProtocolLog(pointer,location,method,type,mns) 
	#endif
#endif

namespace ame{

class DefaultPortProtocol : public PortProtocol{	
    public:
		DefaultPortProtocol(){
			DefaultPortProtocolLog(ame_Log_StartMethod, "Constructor",  "println", "");
			DefaultPortProtocolLog(ame_Log_EndMethod, "Constructor",  "println", "");
		}
		DefaultPortProtocol(bool s){
			DefaultPortProtocolLog(ame_Log_StartMethod, "Constructor",  "println", "");
			this->safeDelete = s;
			DefaultPortProtocolLog(ame_Log_EndMethod, "Constructor",  "println", "");
		}
		DefaultPortProtocol(MessageDelivery* c_delivery){
			DefaultPortProtocolLog(ame_Log_StartMethod, "Constructor",  "println", "");
			this->m_delivery = c_delivery;
			DefaultPortProtocolLog(ame_Log_EndMethod, "Constructor",  "println", "");
		}
		virtual ~DefaultPortProtocol(){
			DefaultPortProtocolLog(ame_Log_StartMethod, "Destructor",  "println", "");
			DefaultPortProtocolLog(ame_Log_EndMethod, "Destructor",  "println", "");
		}
		
		virtual void InstantBroadcastMessage(SerialPort* port, Note mns){
			DefaultPortProtocolLog(ame_Log_StartMethod, "InstantBroadcastMessage",  "println", "");
			DefaultPortProtocolLog(ame_Log_Statement, "InstantBroadcastMessage",  "println", port->getName());
			DefaultPortProtocolLog(ame_Log_Statement, "InstantBroadcastMessage",  "println", mns);
			Note send_note = addNoteValue(mns, '\n');
			port->print(send_note);
			DefaultPortProtocolLog(ame_Log_EndMethod, "InstantBroadcastMessage",  "println", "");
		}
		
		virtual void InstantPrivateMessage(SerialPort* port, Note mns){
			DefaultPortProtocolLog(ame_Log_StartMethod, "InstantPrivateMessage",  "println", port->getName());
			DefaultPortProtocolLog(ame_Log_Statement, "InstantPrivateMessage",  "println", mns);
			port->print(mns+'\n');
			DefaultPortProtocolLog(ame_Log_EndMethod, "InstantPrivateMessage",  "println", "");
		}
		
		virtual void BroadcastMessage(SerialPort* port, Note mns){
			DefaultPortProtocolLog(ame_Log_StartMethod, "BroadcastMessage",  "println", port->getName());
			DefaultPortProtocolLog(ame_Log_Statement, "BroadcastMessage",  "println", mns);
			port->print(mns+'\n');
			DefaultPortProtocolLog(ame_Log_EndMethod, "BroadcastMessage",  "println", "");
		}
		
		virtual void PrivateMessage(SerialPort* port, Note mns){
			DefaultPortProtocolLog(ame_Log_StartMethod, "PrivateMessage",  "println", port->getName());
			DefaultPortProtocolLog(ame_Log_Statement, "PrivateMessage",  "println", mns);
			port->print(mns+'\n');
			DefaultPortProtocolLog(ame_Log_EndMethod, "PrivateMessage",  "println", "");
		}
		
		virtual bool GlobalConect(SerialPort* port){
			DefaultPortProtocolLog(ame_Log_StartMethod, "GlobalConect",  "println", "");
			DefaultPortProtocolLog(ame_Log_EndMethod, "GlobalConect",  "println", "");
			return false;
		}
		virtual bool Conect(SerialPort* port){
			DefaultPortProtocolLog(ame_Log_StartMethod, "Conect",  "println", "");
			DefaultPortProtocolLog(ame_Log_EndMethod, "Conect",  "println", "");
			return true;
		}
		virtual bool UpdateConect(SerialPort* port){
			DefaultPortProtocolLog(ame_Log_StartMethod, "UpdateConect",  "println", "");
			DefaultPortProtocolLog(ame_Log_EndMethod, "UpdateConect",  "println", "");
			return true;
		}
		
		virtual bool GlobalDisconect(SerialPort* port){
			DefaultPortProtocolLog(ame_Log_StartMethod, "GlobalDisconect",  "println", "");
			port->flush();
			port->stop();
			DefaultPortProtocolLog(ame_Log_EndMethod, "GlobalDisconect",  "println", "");
			return true;
		}
		virtual bool Disconect(SerialPort* port){
			DefaultPortProtocolLog(ame_Log_StartMethod, "Disconect",  "println", "");
			port->flush();
			port->stop();
			DefaultPortProtocolLog(ame_Log_EndMethod, "Disconect",  "println", "");
			return true;
		}
		virtual bool UpdateDisconect(SerialPort* port){
			DefaultPortProtocolLog(ame_Log_StartMethod, "UpdateDisconect",  "println", "");
			port->flush();
			port->stop();
			DefaultPortProtocolLog(ame_Log_EndMethod, "UpdateDisconect",  "println", "");
			return true;
		}
		
		void Read(int index, SerialPort* port){
			char i_char = port->read();
			if((i_char == '\n') && messageText.length() != 0){
				DefaultPortProtocolLog(ame_Log_Statement, "Read",  "println", "adding Message to serialState");
				DefaultPortProtocolLog(ame_Log_Statement, "Read",  "println", Note("messageText: ") + messageText);
				DefaultPortProtocolLog(ame_Log_Statement, "Read",  "println", Note("index: ") + Note(index));
				DefaultPortProtocolLog(ame_Log_Statement, "Read",  "println", "raw");
				this->DeliverMessage(messageText);
				messageText = "";
			}
			if(i_char != '\r' && i_char != '\n'){
				DefaultPortProtocolLog(ame_Log_Statement, "Read",  "println", Note("adding char to messageText: ") + Note(i_char));
				messageText = addNoteValue(messageText, i_char);
			}
		}
		
		virtual bool DeliverMessage(const Message& a_mns){
			DefaultPortProtocolLog(ame_Log_StartMethod, "DeliverMessage",  "println", "");
			// DefaultPortProtocolLog(ame_Log_StartMethod, "DeliverMessage",  "println", "Message:");
			// DefaultPortProtocolLog(ame_Log_StartMethod, "DeliverMessage",  "println", a_mns);
			if(m_delivery != nullptr){
				DefaultPortProtocolLog(ame_Log_EndMethod, "DeliverMessage",  "println", "");
				return m_delivery->DeliverMessage(a_mns);
			}
			if(m_serialState == nullptr){
				DefaultPortProtocolLog(ame_Log_EndMethod, "DeliverMessage",  "println", "");
				return false;
			}
			MessageDelivery* i_delivery = m_serialState->getDelivery();
			if(i_delivery == nullptr){
				DefaultPortProtocolLog(ame_Log_EndMethod, "DeliverMessage",  "println", "");
				return false;
			}
			DefaultPortProtocolLog(ame_Log_EndMethod, "DeliverMessage",  "println", "");
			return i_delivery->DeliverMessage(a_mns);
		}
		
		virtual bool DeliverMessage(const Note& a_mns){
			DefaultPortProtocolLog(ame_Log_StartMethod, "DeliverMessage",  "println", "");
			DefaultPortProtocolLog(ame_Log_Statement, "DeliverMessage",  "println", "Message:");
			DefaultPortProtocolLog(ame_Log_Statement, "DeliverMessage",  "println", a_mns);
			if(m_delivery != nullptr){
				DefaultPortProtocolLog(ame_Log_EndMethod, "DeliverMessage",  "println", "");
				return m_delivery->DeliverMessage(a_mns);
			}
			if(m_serialState == nullptr){
				DefaultPortProtocolLog(ame_Log_EndMethod, "DeliverMessage",  "println", "");
				return false;
			}
			MessageDelivery* i_delivery = m_serialState->getDelivery();
			if(i_delivery == nullptr){
				DefaultPortProtocolLog(ame_Log_EndMethod, "DeliverMessage",  "println", "");
				return false;
			}
			DefaultPortProtocolLog(ame_Log_EndMethod, "DeliverMessage",  "println", "");
			return i_delivery->DeliverMessage(a_mns);
		}
		
		virtual bool DeliverMessage(const ByteArray& a_mns){
			DefaultPortProtocolLog(ame_Log_StartMethod, "DeliverMessage",  "println", "");
			if(m_delivery != nullptr){
				return m_delivery->DeliverMessage(a_mns);
			}
			if(m_serialState == nullptr){
				return false;
			}
			MessageDelivery* i_delivery = m_serialState->getDelivery();
			if(i_delivery == nullptr){
				return false;
			}
			DefaultPortProtocolLog(ame_Log_EndMethod, "DeliverMessage",  "println", "");
			return i_delivery->DeliverMessage(a_mns);
		}
		
	protected:
		Note messageText = "";
};

}

#endif