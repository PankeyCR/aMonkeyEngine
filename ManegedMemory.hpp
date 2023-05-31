
#ifndef ManegedMemory_hpp
#define ManegedMemory_hpp
#define ManegedMemory_AVAILABLE

//#include "MemoryManager.hpp"

namespace ame{

class ManegedMemory{
    public:
		ManegedMemory(){}
		virtual ~ManegedMemory(){}
		
		// void* operator new(size_t size){
		// 	if(Memory::manager == nullptr){
		// 		return malloc(size);
		// 	}
		// 	return Memory::manager->allocateMemory(size);
		// }
		
		// void operator delete(void* pointerToDelete){
		// 	if(Memory::manager == nullptr){
		// 		free(pointerToDelete);
		// 		return;
		// 	}
		// 	Memory::manager->deleteMemory(pointerToDelete);
		// }

		virtual void onRecycleMemory(){}

		virtual void onDeleteMemory(){}

		//Reference count protection
		virtual void addObject(){m_count++;}
		virtual void removeObject(){m_count--;}
		virtual int getReferenceCount(){return m_count;}
		virtual bool isReferenced(){return m_count > 0;}
		
	protected:
		int m_count = 0;
};

}

#endif