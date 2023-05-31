
#ifndef Pointer_hpp
#define Pointer_hpp
#define Pointer_AVAILABLE

#include "ManegedMemory.hpp"
#include "ReferenceCount.hpp"

#ifdef Pointer_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"

	#define PointerLog(location,method,type,mns) ame_Log(this,location,"Pointer",method,type,mns)
#else
	#ifdef Pointer_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"

		#define PointerLog(location,method,type,mns) ame_LogDebug(this,location,"Pointer",method,type)
	#else
		#define PointerLog(location,method,type,mns)
	#endif
#endif

namespace ame{

template<class T>
class Pointer : public ManegedMemory{
	public:
		Pointer(){
			PointerLog(ame_Log_StartMethod, "Contructor", "println","T* a_pointer");
			PointerLog(ame_Log_EndMethod, "Contructor", "println","");
		}

		Pointer(T* a_pointer){
			PointerLog(ame_Log_StartMethod, "Contructor", "println","T* a_pointer");
			this->addPointer(a_pointer, nullptr);
			PointerLog(ame_Log_EndMethod, "Contructor", "println","");
		}
		
		Pointer(T* a_pointer, MemoryStorageManager<T>* a_manager){
			PointerLog(ame_Log_StartMethod, "Contructor", "println","T* a_pointer, MemoryStorageManager<T>* a_manager");
			this->addPointer(a_pointer, a_manager);
			PointerLog(ame_Log_EndMethod, "Contructor", "println","");
		}

		Pointer(const Pointer &a_pointer){
			PointerLog(ame_Log_StartMethod, "Contructor", "println","const Pointer &a_pointer");
			this->addPointer(a_pointer.m_pointer, a_pointer.m_manager);
			PointerLog(ame_Log_EndMethod, "Contructor", "println","");
		}

		virtual ~Pointer(){
			PointerLog(ame_Log_StartMethod, "Destructor", "println","const Pointer &a_pointer");
			this->removePointer();
			PointerLog(ame_Log_EndMethod, "Destructor", "println","");
		}

		virtual T* operator ->(){
			return m_pointer;
		}

		virtual T* get()const{
			return m_pointer;
		}

		virtual bool isNull(){
			return m_pointer == nullptr;
		}

		virtual void operator=(const Pointer& a_pointer){
			PointerLog(ame_Log_StartMethod, "operator=", "println","");
			this->removePointer();
			this->addPointer(a_pointer.m_pointer, a_pointer.m_manager);
			PointerLog(ame_Log_EndMethod, "operator=", "println","");
		}

		virtual bool operator==(const Pointer& a_pointer){
			PointerLog(ame_Log_StartMethod, "operator==", "println","");
			//m_pointer == a_pointer.m_pointer && m_manager == a_pointer.m_manager
			PointerLog(ame_Log_EndMethod, "operator==", "println", m_pointer == a_pointer.m_pointer);
			return m_pointer == a_pointer.m_pointer;
		}

		virtual bool operator!=(const Pointer& a_pointer){
			PointerLog(ame_Log_StartMethod, "operator!=", "println","");
			//m_pointer == a_pointer.m_pointer && m_manager == a_pointer.m_manager
			PointerLog(ame_Log_EndMethod, "operator!=", "println", m_pointer == a_pointer.m_pointer);
			return m_pointer != a_pointer.m_pointer;
		}

	protected:
		virtual void addPointer(T* a_pointer, MemoryStorageManager<T>* a_manager){
			PointerLog(ame_Log_StartMethod, "addPointer", "println","T* a_pointer, MemoryStorageManager<T>* a_manager");
			if(a_pointer == nullptr && a_manager == nullptr){
				PointerLog(ame_Log_EndMethod, "addPointer", "println","a_pointer == nullptr && a_manager == nullptr");
				return;
			}
			if(a_pointer == nullptr && a_manager != nullptr){
				m_manager = a_manager;
				m_manager->addingManager();
				PointerLog(ame_Log_EndMethod, "addPointer", "println","a_pointer == nullptr && a_manager != nullptr");
				return;
			}
			m_manager = a_manager;
			m_manager->addingManager();

			m_pointer = a_pointer;
			m_manager->addingPointer(m_pointer);
			PointerLog(ame_Log_EndMethod, "addPointer", "println","");
		}
		
		virtual void removePointer(){
			PointerLog(ame_Log_StartMethod, "removePointer", "println","");
			if(m_manager != nullptr){
				if(m_pointer != nullptr){
					m_manager->removingPointer(m_pointer);
				}
				m_manager->removingManager();
			}
			PointerLog(ame_Log_EndMethod, "removePointer", "println","");
		}

	protected:
		T* m_pointer;
		MemoryStorageManager<T>* m_manager = nullptr;
};

}

#endif