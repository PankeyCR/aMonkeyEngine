
#ifndef ReferenceCount_hpp
#define ReferenceCount_hpp
#define ReferenceCount_AVAILABLE

#include "MemoryStorageManager.hpp"

#ifdef ReferenceCount_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"

	#define ReferenceCountLog(location,method,type,mns) ame_Log((void*)this,location,"ReferenceCount",method,type,mns)
#else
	#ifdef ReferenceCount_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"

		#define ReferenceCountLog(location,method,type,mns) ame_LogDebug((void*)this,location,"ReferenceCount",method,type)
	#else
		#define ReferenceCountLog(location,method,type,mns)
	#endif
#endif

namespace ame{

template<class T>
class ReferenceCount : public MemoryStorageManager<T>{
	public:
		ReferenceCount(){
			ReferenceCountLog(ame_Log_StartMethod, "Constructor", "println", "");
			ReferenceCountLog(ame_Log_EndMethod, "Constructor", "println", "");
		}
		virtual ~ReferenceCount(){
			ReferenceCountLog(ame_Log_StartMethod, "Destructor", "println", "");
			ReferenceCountLog(ame_Log_EndMethod, "Destructor", "println", "");
		}

		virtual void addingPointer(T* a_value){
			ReferenceCountLog(ame_Log_StartMethod, "addingPointer", "println", "");
			a_value->addObject();
			ReferenceCountLog(ame_Log_EndMethod, "addingPointer", "println", "");
		}

		virtual void removingPointer(T* a_value){
			ReferenceCountLog(ame_Log_StartMethod, "removingPointer", "println", "");
			a_value->removeObject();
			ReferenceCountLog(ame_Log_StartMethod, "removingPointer", "println", "Reference count left:");
			ReferenceCountLog(ame_Log_StartMethod, "removingPointer", "println", a_value->getReferenceCount());
			
			if(!a_value->isReferenced()){
				delete a_value;
			}
			ReferenceCountLog(ame_Log_EndMethod, "removingPointer", "println", "");
		}
};

}

#endif