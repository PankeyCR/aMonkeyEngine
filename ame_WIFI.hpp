
#ifndef CONFIGURATION_ame_WIFI_hpp
#define CONFIGURATION_ame_WIFI_hpp

	#include "ame_Enviroment.hpp"

	#if defined(DISABLE_ame_WIFI)
		#define ame_WIFI_hpp
	#endif
#endif

#ifndef ame_WIFI_hpp
#define ame_WIFI_hpp
#define ame_WIFI_AVAILABLE 

#include "Note.hpp"
#include "NoteHelper.hpp"
#include "PrimitiveList.hpp"

#ifndef ame_Enviroment_Defined

#endif

#ifdef ame_Windows

#endif

#ifdef ame_ArduinoIDE
	#include "Arduino.h"
#endif

#if defined(ARDUINO_ARCH_ESP8266)
	#include "WiFi.h"
#elif defined(ARDUINO_ARCH_ESP32)
	#include "WiFi.h"
	#include <esp_wifi.h>
#endif

#ifdef ame_WIFI_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"
	
	#define ame_WIFILog(location,method,type,mns) ame_Log(nullptr,location,"ame_WIFI",method,type,mns)
#else
	#ifdef ame_WIFI_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"
		
		#define ame_WIFILog(location,method,type,mns) ame_LogDebug(nullptr,location,"ame_WIFI",method,type)
	#else
		#define ame_WIFILog(location,method,type,mns) 
	#endif
#endif

namespace ame{

#ifdef ame_ArduinoIDE
void initializeWIFI(Note a_ip, Note a_gateway, Note a_subnet, Note a_dns, uint8_t* a_mac, Note name, Note pasword){
	ame_WIFILog(ame_Log_StartMethod, "initializeWIFI",  "println", "");
	// IPAddress
	IPAddress ip = toIPAddress(a_ip);
	IPAddress gateway = toIPAddress(a_gateway);
	IPAddress subnet = toIPAddress(a_subnet);
	IPAddress dns = toIPAddress(a_subnet);
	
	WiFi.mode(WIFI_STA);
	WiFi.setSleep(false);
	
	esp_wifi_set_mac(WIFI_IF_STA, a_mac);
	if(!WiFi.config(ip,gateway,subnet,dns)) {
		ame_WIFILog(ame_Log_Statement, "initializeWIFI",  "println", "STA Failed to configure");
	}
	WiFi.begin(name.pointer(), pasword.pointer());
	if(WiFi.status() == WL_CONNECTED) {
		ame_WIFILog(ame_Log_Statement, "initializeWIFI",  "println", "connected");
		delay(1000);
	}
	ame_WIFILog(ame_Log_EndMethod, "initializeWIFI",  "println", "");
}

void haltUntilWIFIConnection(){
	ame_WIFILog(ame_Log_StartMethod, "haltUntilWIFIConnection",  "println", "");
	while (WiFi.status() != WL_CONNECTED) {
		ame_WIFILog(ame_Log_StartMethod, "haltUntilWIFIConnection",  "println", ".");
		delay(1000);
	}
	ame_WIFILog(ame_Log_EndMethod, "haltUntilWIFIConnection",  "println", "");
}

bool hasLAN(){
	return WiFi.status() == WL_CONNECTED;
}

void printWIFI(Stream* port){
	if(port == nullptr){
		return;
	}
	if(WiFi.status() == WL_CONNECTED){
		port->println("WIFI connected");
	}else{
		port->println("WIFI disconnected");
	}
	port->print("WIFI ip: ");
	port->println(WiFi.localIP());
}

void WIFICommands(const PrimitiveList<Note>& a_commands){

}
#endif

}

#endif
