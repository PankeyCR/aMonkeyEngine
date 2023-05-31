
#ifndef ame_Logger_hpp
#define ame_Logger_hpp

#ifndef ame_LogDebug
	#define ame_LogDebug(pointer,location,name,method,type) 
#endif

#ifndef ame_Debuging
	#define ame_Debuging(location,method) ame_LogDebug(nullptr,location,"raw",method,"println")
#endif

#ifndef ame_ClassDebuging
	#define ame_ClassDebuging(location,name,method) ame_LogDebug(nullptr,location,name,method,"println")
#endif
  
#ifdef ame_LogApp
	#ifdef ame_LogPrint
		#include "ame_Logger_config.hpp"
		#include "ame_String.hpp"
		#include "System.hpp"

		namespace ame{
		  
			template<class T>
			void LogPrint_(void* a_log_pointer, int location, const ame_String& name, const ame_String& method, const ame_String& type, T mns){
			
				// if(	method != "copyPointer"/* && 
					// method != "operator+="/* && 
					// method != "getKeyIndexByLValue" /*&& method != "setMapEntry"*/){
				// 	return;
				// }
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

				ame_LogDebug(a_log_pointer, location, name, method, type);
			}
		  
		}

		#ifndef ame_Log
			#define ame_Log(pointer,location,name,method,type,mns) LogPrint_(pointer,location,name,method,type,mns)
		#endif
	#else
		#ifndef ame_Log
			#define ame_Log(pointer,location,name,method,type,mns) 
		#endif
	#endif
	
#else
	
	#ifndef ame_Log
		#define ame_Log(pointer,location,name,method,type,mns) 
	#endif
	
#endif

#define ame_Loging(location,method) ame_Log(nullptr,location,"raw",method,"println","Loging Event") 
#define ame_Loger(location,method,mns) ame_Log(nullptr,location,"raw",method,"println",mns) 

#define ame_ClassLoging(location,name,method) ame_Log(nullptr,location,name,method,"println","Loging Event") 

#endif 

