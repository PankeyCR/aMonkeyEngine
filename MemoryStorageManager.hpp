
#ifndef MemoryStorageManager_hpp
#define MemoryStorageManager_hpp
#define MemoryStorageManager_AVAILABLE

#include "ManegedMemory.hpp"

namespace ame{

template<class T>
class MemoryStorageManager : public ManegedMemory{
	public:
		MemoryStorageManager(){}
		virtual ~MemoryStorageManager(){}

		virtual void addingPointer(T* a_value){}

		virtual void removingPointer(T* a_value){}

		virtual void addingManager(){}

		virtual MemoryStorageManager<T>* removingManager(){return nullptr;}
};

}

#endif