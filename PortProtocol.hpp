
#ifndef CONFIGURATION_PortProtocol_hpp
#define CONFIGURATION_PortProtocol_hpp

	#include "ame_Enviroment.hpp"

	#if defined(DISABLE_PortProtocol)
		#define PortProtocol_hpp
	#endif
#endif

#ifndef PortProtocol_hpp
#define PortProtocol_hpp
#define PortProtocol_AVAILABLE

#include "cppObject.hpp"
#include "Message.hpp"
#include "Note.hpp"
#include "ByteArray.hpp"

#include "MessageDelivery.hpp"

namespace ame{

/*
*	Class Configuration:
*	DISABLE_IMPLEMENTATION_cppObject
*/
class PortProtocol IMPLEMENTATION_cppObject {

    public:
		PortProtocol(){}
		virtual ~PortProtocol(){}
		
		virtual void initialize(SerialStateController* state){
			this->m_serialState = state;
		}

		virtual SerialStateController* getSerialStateController(){
			return this->m_serialState;
		}
		
		//this method has control of the sending of the message, so remember sending it
		virtual void InstantBroadcastMessage(SerialPort* port, Note mns){}
		
		//this method has control of the sending of the message, so remember sending it
		virtual void InstantPrivateMessage(SerialPort* port, Note mns){}
		
		virtual void InstantPrivateByteArrayMessage(SerialPort* port, ByteArray array){}
		
		virtual void GlobalConect(SerialPort* port){}
		virtual void Conect(SerialPort* port){}
		virtual void UpdateConect(SerialPort* port){}
		
		virtual void GlobalDisconect(SerialPort* port){}
		virtual void Disconect(SerialPort* port){}
		virtual void UpdateDisconect(SerialPort* port){}
		
		virtual void Read(int index, SerialPort* port){}
		
		//you need to send to message manually
		virtual void BroadcastMessage(SerialPort* port, Note mns){}
		//you need to send to message manually
		virtual void PrivateMessage(SerialPort* port, Note mns){}
		
		virtual void setSafeDelete(bool s){safeDelete = s;}
		virtual bool SafeDelete(){return safeDelete;}
		
		virtual void setDelivery(MessageDelivery* a_delivery){
			m_delivery = a_delivery;
		}
		
		virtual MessageDelivery* getDelivery(){
			return m_delivery;
		}
		
		virtual bool DeliverMessage(const Message& a_mns){
			if(m_delivery == nullptr){
				return false;
			}
			return m_delivery->DeliverMessage(a_mns);
		}
		virtual bool DeliverMessage(const Note& a_mns){
			if(m_delivery == nullptr){
				return false;
			}
			return m_delivery->DeliverMessage(a_mns);
		}
		virtual bool DeliverMessage(const ByteArray& a_mns){
			if(m_delivery == nullptr){
				return false;
			}
			return m_delivery->DeliverMessage(a_mns);
		}
		
		virtual void update(SerialPort* port, float tpc){}
		
		virtual void operator=(PortProtocol b){}
		virtual bool operator==(PortProtocol b){return true;}
		virtual bool operator!=(PortProtocol b){return true;}
		
		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){return Class<PortProtocol>::classType;}
		virtual bool equal(cppObject *b){
			if(b == this){
				return true;
			}
			return false;
		}
		virtual bool instanceof(cppObjectClass* cls){
			return cls == Class<PortProtocol>::classType || cppObject::instanceof(cls);
		}
		
		virtual cppObject *clone(){return nullptr;}
		#endif
		
	protected:
		bool safeDelete = true;
		SerialStateController* m_serialState = nullptr;
		MessageDelivery* m_delivery = nullptr;
};

}

#endif