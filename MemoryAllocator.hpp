
#ifndef MemoryAllocator_hpp
#define MemoryAllocator_hpp
#define MemoryAllocator_AVAILABLE

#ifdef MemoryAllocator_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"

	#define MemoryAllocatorLog(location,method,type,mns) ame_Log((void*)this,location,"MemoryAllocator",method,type,mns)
	#define const_MemoryAllocatorLog(location,method,type,mns)
#else
	#ifdef MemoryAllocator_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"

		#define MemoryAllocatorLog(location,method,type,mns) ame_LogDebug((void*)this,location,"MemoryAllocator",method,type)
		#define const_MemoryAllocatorLog(location,method,type,mns)
	#else
		#define MemoryAllocatorLog(location,method,type,mns)
		#define const_MemoryAllocatorLog(location,method,type,mns)
	#endif
#endif

namespace ame{

template<class T>
class MemoryAllocator{
	public:
		MemoryAllocator(){}
		virtual ~MemoryAllocator(){}

		virtual void operator=(const MemoryAllocator<T>& c_MemoryAllocator){}
		virtual bool operator==(MemoryAllocator<T> b){return false;}
		virtual bool operator!=(MemoryAllocator<T> b){return false;}
	
	protected:
	
};

}

#endif