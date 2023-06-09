
#ifndef ame_Simple_Logger_hpp
#define ame_Simple_Logger_hpp

#include "ame_Logger_position.hpp"
#include "ame_String.hpp"
#include "System.hpp"

namespace ame{
	
template<class T>
void Simple_LogPrint_(void* a_log_pointer, int location, const ame_String& name, const ame_String& method, const ame_String& type, T mns){

	// if(	method != "insertLine" && 
	// 	method != "getIndex" && 
	// 	method != "insertLocalArrayPointer"/* && 
	// 	method != "getKeyIndexByLValue" /*&& method != "setMapEntry"*/){
	// 	return;
	// }
	#ifdef ame_SystemFullLog
		System::console.print("Loggin class: ");
		System::console.print(name);
		System::console.print(" - Method: ");
		System::console.print(method);
		System::console.print(" - Location: ");
		System::console.print(location);
		System::console.print(" - Log: ");
		System::console.println(mns);
	#elif defined(ame_Arduino_Log)
		Serial.console.print("Loggin class: ");
		Serial.console.print(name);
		Serial.console.print(" - Method: ");
		Serial.console.print(method);
		Serial.console.print(" - Location: ");
		Serial.console.print(location);
		Serial.console.print(" - Log: ");
		Serial.console.println(mns);
	#endif
}

}

#endif 

