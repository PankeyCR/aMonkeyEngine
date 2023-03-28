
#ifndef ame_ETHERNET_hpp
#define ame_ETHERNET_hpp
#define ame_ETHERNET_AVAILABLE 

#include "ame_Enviroment.hpp"

#ifndef ame_Enviroment_Defined

#endif

#ifdef ame_Windows

#endif

#ifdef ame_ArduinoIDE
	#include "Arduino.h"
#endif

#include "NoteHelper.hpp"

#ifdef ame_ETHERNET_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"
	
	#define ame_ETHERNETLog(location,method,type,mns) ame_Log(nullptr,location,"ame_ETHERNET",method,type,mns)
#else
	#ifdef ame_ETHERNET_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"
		
		#define ame_ETHERNETLog(location,method,type,mns) ame_LogDebug(nullptr,location,"ame_ETHERNET",method,type)
	#else
		#define ame_ETHERNETLog(location,method,type,mns) 
	#endif
#endif

namespace ame{

#ifdef ame_ArduinoIDE
void initializeETHERNET(IPAddress a_ip, IPAddress a_gateway, IPAddress a_subnet, int CS_pin, byte* mac){
	ame_ETHERNETLog(ame_Log_StartMethod, "initializeETHERNET",  "println", "IPAddress");
	ame_ETHERNETLog(ame_Log_StartMethod, "initializeETHERNET",  "println", "a_ip");
	ame_ETHERNETLog(ame_Log_StartMethod, "initializeETHERNET",  "println", a_ip);
	ame_ETHERNETLog(ame_Log_StartMethod, "initializeETHERNET",  "println", "a_gateway");
	ame_ETHERNETLog(ame_Log_StartMethod, "initializeETHERNET",  "println", a_gateway);
	ame_ETHERNETLog(ame_Log_StartMethod, "initializeETHERNET",  "println", "a_subnet");
	ame_ETHERNETLog(ame_Log_StartMethod, "initializeETHERNET",  "println", a_subnet);
	
	Ethernet.init(CS_pin);
	Ethernet.begin(mac, a_ip, a_gateway, a_subnet);
	
	ame_ETHERNETLog(ame_Log_StartMethod, "initializeETHERNET",  "println", "connected");
}

void initializeETHERNET(Note a_ip, Note a_gateway, Note a_subnet, int CS_pin, byte* mac){
	ame_ETHERNETLog(ame_Log_StartMethod, "initializeETHERNET",  "println", "Note");

	ame_ETHERNETLog(ame_Log_StartMethod, "initializeETHERNET",  "println", "a_ip");
	ame_ETHERNETLog(ame_Log_StartMethod, "initializeETHERNET",  "println", a_ip);
	ame_ETHERNETLog(ame_Log_StartMethod, "initializeETHERNET",  "println", "a_gateway");
	ame_ETHERNETLog(ame_Log_StartMethod, "initializeETHERNET",  "println", a_gateway);
	ame_ETHERNETLog(ame_Log_StartMethod, "initializeETHERNET",  "println", "a_subnet");
	ame_ETHERNETLog(ame_Log_StartMethod, "initializeETHERNET",  "println", a_subnet);
	
	initializeETHERNET(toIPAddress(a_ip), toIPAddress(a_gateway), toIPAddress(a_subnet), CS_pin, mac);
	ame_ETHERNETLog(ame_Log_StartMethod, "initializeETHERNET",  "println", "");
}

// void initializeETHERNET(Note a_ip, Note a_gateway, Note a_subnet, int CS_pin, ByteArray mac){
	// initializeETHERNET(a_ip.toIPAddress(), a_gateway.toIPAddress(), a_subnet.toIPAddress(), CS_pin, mac.pointer());
// }

void haltUntilEthernetConnection(){
	ame_ETHERNETLog(ame_Log_StartMethod, "haltUntilEthernetConnection",  "println", "");
	while (Ethernet.linkStatus() != LinkON) {
		ame_ETHERNETLog(ame_Log_StartMethod, "haltUntilEthernetConnection",  "println", ".");
		delay(1000);
	}
	ame_ETHERNETLog(ame_Log_EndMethod, "haltUntilEthernetConnection",  "println", "");
}


bool hasLAN(){
	return Ethernet.linkStatus() == LinkON;
}
#endif

}

#endif
