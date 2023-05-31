
#ifndef CONFIGURATION_ServerProtocol_hpp
#define CONFIGURATION_ServerProtocol_hpp

	#include "ame_Enviroment.hpp"

	#if defined(DISABLE_ServerProtocol)
		#define ServerProtocol_hpp
	#endif
#endif

#ifndef ServerProtocol_hpp
#define ServerProtocol_hpp
#define ServerProtocol_AVAILABLE

#include "cppObject.hpp"
#include "SerialNetwork.hpp"

namespace ame{

/*
*	Class Configuration:
*	DISABLE_IMPLEMENTATION_cppObject
*/
class ServerProtocol IMPLEMENTATION_cppObject {	
    public:
		ServerProtocol(){}
		
		virtual ~ServerProtocol(){}
		
		virtual void initialize(SerialState* state){
			this->serialState = state;
		}

		virtual SerialState* getSerialState(){
			return this->serialState;
		}
		
		virtual SerialPort* getUpdateSerialPort(SerialServer* server){return nullptr;}
		
		virtual void UpdateSerialPort(SerialPort* port){}
		
		virtual void update(SerialServer* server, float tpc){}
		
		virtual void NetworkMessage(SerialServer* a_server, Note a_mns){}
		
		virtual void operator=(ServerProtocol b){}
		virtual bool operator==(ServerProtocol b){return true;}
		virtual bool operator!=(ServerProtocol b){return true;}
		
		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){return Class<ServerProtocol>::getClass();}
		virtual bool instanceof(cppObjectClass* cls){
			return cls == Class<ServerProtocol>::getClass();
		}
		#endif
		
	protected:
		SerialState* serialState = nullptr;
};

}

#endif