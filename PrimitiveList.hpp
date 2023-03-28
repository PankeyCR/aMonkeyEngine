
#ifndef PrimitiveList_hpp
#define PrimitiveList_hpp
#define PrimitiveList_AVAILABLE

#include "ame_ErrorWarning.hpp"
#include "PrimitiveRawList.hpp"
#include "ListIterator.hpp"
#include "List.hpp"
#include "Class.hpp"

#ifdef PrimitiveList_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"

	#define PrimitiveListLog(location,method,type,mns) ame_Log(this,location,"PrimitiveList",method,type,mns)
	#define const_PrimitiveListLog(location,method,type,mns)
#else
	#ifdef PrimitiveList_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"

		#define PrimitiveListLog(location,method,type,mns) ame_LogDebug(this,location,"PrimitiveList",method,type)
		#define const_PrimitiveListLog(location,method,type,mns)
	#else
		#define PrimitiveListLog(location,method,type,mns)
		#define const_PrimitiveListLog(location,method,type,mns)
	#endif
#endif

namespace ame{

template<class T>
class PrimitiveList : public PrimitiveRawList<T>, public List<T>{
	protected:
		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(TemplateClass_AVAILABLE)
		static cppObjectClass* m_primitive_list_class;
		#endif
		
	public:
		PrimitiveList(){}
		
		PrimitiveList(const PrimitiveList<T>& a_list){
			this->m_values = new T*[a_list.getSize()];
			this->m_size = a_list.getSize();
			for(int x = 0; x < a_list.getPosition(); x++){
				T* f_value = a_list.getByPosition(x);
				if(f_value == nullptr){
					this->addPointer(nullptr);
					continue;
				}
				this->addLValue(*f_value);
			}
		}
		
		PrimitiveList(int c_size, bool c_own, bool c_reordering) : PrimitiveRawList<T>(c_size, c_own, c_reordering){}
		
		virtual ~PrimitiveList(){}
		
		//cppObject part
		virtual void onDelete(){
			this->resetDelete();
		}
		
		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){
			return Class<PrimitiveList<T>>::getClass();
		}
		
		virtual bool instanceof(cppObjectClass* cls){
			return cls == Class<PrimitiveList<T>>::getClass();
		}

		virtual PrimitiveList<T>* clone(){
			PrimitiveList<T>* list = new PrimitiveList<T>(this->m_size);
			for(int xl = 0; xl < this->getPosition(); xl++){
				list->addLValue(*this->m_values[xl]);
			}
			return list;
		}

		virtual PrimitiveList<T>* clone(bool owningMemory){
			PrimitiveList<T>* list = new PrimitiveList<T>(this->m_size, owningMemory, this->m_reorder);
			for(int xl = 0; xl < this->getPosition(); xl++){
				list->addLValue(*this->m_values[xl]);
			}
			return list;
		}
		#endif
	
		////////////////////////////////////////////operator part///////////////////////////////////////////////
		
		
		virtual PrimitiveList<T>& operator=(const PrimitiveList<T>& a_list){
			this->resetDelete();
			for(int x = 0; x < a_list.getPosition(); x++){
				T* f_list_value = a_list.getByPosition(x);
				if(f_list_value == nullptr){
					this->addPointer(nullptr);
					continue;
				}
				this->addLValue(*a_list.getByPosition(x));
			}
			return *this;
		}
		
		virtual bool operator==(const PrimitiveList<T>& a_list){
			if(this->getPosition() != a_list.getPosition()){
				return false;
			}
			for(int x = 0; x < a_list.getPosition(); x++){
				T* f_list_value = a_list.getByPosition(x);
				T* f_value = this->getByPosition(x);
				if(f_list_value == nullptr && f_value == nullptr){
					continue;
				}
				if(f_list_value == nullptr || f_value == nullptr){
					return false;
				}
				if(*f_list_value != *f_value){
					return false;
				}
			}
			return true;
		}

		virtual bool operator!=(const PrimitiveList<T>& a_list){
			if(this->getPosition() != a_list.getPosition()){
				return true;
			}
			for(int x = 0; x < a_list.getPosition(); x++){
				T* f_list_value = a_list.getByPosition(x);
				T* f_value = this->getByPosition(x);
				if(f_list_value == nullptr && f_value == nullptr){
					continue;
				}
				if(f_list_value == nullptr || f_value == nullptr){
					return true;
				}
				if(*f_list_value != *f_value){
					return true;
				}
			}
			return false;
		}
		
	protected:
};

#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(TemplateClass_AVAILABLE)
template<class T>
cppObjectClass* PrimitiveList<T>::m_primitive_list_class = new TemplateClass<PrimitiveList<T>>();
#endif

}

#endif