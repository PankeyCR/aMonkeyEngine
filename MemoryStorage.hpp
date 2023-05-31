
#ifndef MemoryStorage_hpp
#define MemoryStorage_hpp
#define MemoryStorage_AVAILABLE

#include "MemoryStorageManager.hpp"
#include "ManegedMemory.hpp"
#include "Pointer.hpp"

namespace ame{

template<class T>
class MemoryStorage : public ManegedMemory{
	public:
		MemoryStorage(){}
		virtual ~MemoryStorage(){
			if(m_manager != nullptr){
				delete m_manager;
			}
		}
		
		virtual bool isNull()const=0;
		virtual bool isEmpty()const=0;
		
		virtual void setSize(int a_size){this->m_size = a_size;}
		virtual int getSize() const {return this->m_size;}
		
		virtual void set(int a_position, T* a_value)=0;
		virtual void set(int a_position, const Pointer<T>& a_value)=0;
		
		virtual Pointer<T> get(int a_position)const=0;

		virtual bool contain(T* a_value)=0;
		virtual bool contain(const Pointer<T>& a_value)=0;
		
		virtual int getIndex(T* a_value)=0;
		virtual int getIndex(const Pointer<T>& a_value)=0;

		virtual void clear()=0;

		virtual bool removeByPointer(T* a_value)=0;
		virtual bool removeByPointer(const Pointer<T>& a_value)=0;

		virtual Pointer<T> removeByPosition(int a_position)=0;

		virtual int reorder()=0;

		virtual bool expandLocal(int a_adding_size)=0;

		virtual MemoryStorage<T>* clone()const=0;

		virtual void addManager(MemoryStorageManager<T>* a_manager){
			PointerLog(ame_Log_StartMethod, "addManager", "println","MemoryStorageManager<T>* a_manager");
			if(this->m_manager == a_manager){
				PointerLog(ame_Log_EndMethod, "addManager", "println","a_manager == nullptr");
				return;
			}
			this->removeManager();
			if(a_manager == nullptr){
				PointerLog(ame_Log_EndMethod, "addManager", "println","a_manager == nullptr");
				return;
			}
			this->m_manager = a_manager;
			this->m_manager->addingManager();
			PointerLog(ame_Log_EndMethod, "addManager", "println","");
		}

		virtual void removeManager(){
			PointerLog(ame_Log_StartMethod, "removeManager", "println","");
			if(this->m_manager != nullptr){
				this->m_manager = this->m_manager->removingManager();
			}
			PointerLog(ame_Log_EndMethod, "removeManager", "println","");
		}
		
		virtual MemoryStorageManager<T>* getManager(){return this->m_manager;}

	protected:
		virtual void addingMemory(T* a_value){
			if(this->m_manager != nullptr && a_value != nullptr){
				this->m_manager->addingPointer(a_value);
			}
		}
		
		virtual void removingMemory(T* a_value){
			if(this->m_manager != nullptr && a_value != nullptr){
				this->m_manager->removingPointer(a_value);
			}
		}
		
	protected:
		int m_size = 0;
		MemoryStorageManager<T>* m_manager = nullptr;
};

}

#endif