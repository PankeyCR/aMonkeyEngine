
#ifndef ame_Logger_hpp
#define ame_Logger_hpp

#ifndef ame_Log_Module
	#define ame_Log_Module(pointer,location,name,method,type,mns) 
#endif

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
		#include "ame_Logger_position.hpp"
		#include "ame_String.hpp"
		#include "System.hpp"

		namespace ame{
		  
			template<class T>
			void LogPrint_(void* a_log_pointer, int location, const ame_String& name, const ame_String& method, const ame_String& type, T mns){
				ame_Log_Module(a_log_pointer, location, name, method, type, mns);

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

