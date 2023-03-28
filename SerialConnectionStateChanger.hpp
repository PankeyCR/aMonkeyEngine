
#ifndef CONFIGURATION_SerialConnectionStateChanger_hpp
#define CONFIGURATION_SerialConnectionStateChanger_hpp

	#include "ame_Enviroment.hpp"

	#if defined(DISABLE_SerialConnectionStateChanger)
		#define SerialConnectionStateChanger_hpp
	#endif
#endif

#ifndef SerialConnectionStateChanger_hpp
#define SerialConnectionStateChanger_hpp
#define SerialConnectionStateChanger_AVAILABLE

#include "SerialPort.hpp"
#include "PortProtocol.hpp"

namespace ame{

class SerialConnectionStateChanger{
    public:
		SerialConnectionStateChanger(){}
		virtual ~SerialConnectionStateChanger(){}
		
		virtual void onGlobalConnection(){}
		virtual void onGlobalDisconnection(){}
		
		virtual void onConnection(SerialPort* port, PortProtocol* protocol){}
		virtual void onDisconnection(SerialPort* port, PortProtocol* protocol){}
		
		virtual void operator=(SerialConnectionStateChanger b){}
		virtual bool operator==(SerialConnectionStateChanger b){
			return false;
		}
		virtual bool operator!=(SerialConnectionStateChanger b){
			return false;
		}
	protected:
};

}

#endif