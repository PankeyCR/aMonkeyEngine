
#ifndef Object_hpp
#define Object_hpp
#define Object_AVAILABLE

#include "Note.hpp"
#include "cppObject.hpp"

namespace ame{

class Object : public cppObject{
    public:
		Object(cppObject* c_pointer){
			m_pointer = c_pointer;
			if(m_pointer != nullptr){
				m_pointer->addObject();
				m_class = c_pointer->getClass();
			}
		}
		Object(cppObjectClass* c_class){
			m_class = c_class;
		}
		Object(cppObject* c_pointer, cppObjectClass* c_class){
			m_pointer = c_pointer;
			m_class = c_class;
		}
		Object(const Object& m_object){
			m_pointer = m_object.m_pointer;
			m_class = m_object.m_class;
		}
		
		Object(){}
		
		virtual ~Object(){
			if(m_pointer != nullptr){
				m_pointer->removeObject();
				if(!m_pointer->isManaged() && !m_pointer->isReferenced()){
					delete m_pointer;
				}
			}
		}
		
		virtual void onDelete(){
			if(m_pointer == nullptr){
				return;
			}
			m_pointer->onDelete();
		}
		
		virtual bool copy(cppObject* a_obj){
			if(m_pointer == nullptr){
				return false;
			}
			return m_pointer->copy(a_obj);
		}
		virtual bool move(cppObject* a_obj){
			if(m_pointer == nullptr){
				return false;
			}
			return m_pointer->move(a_obj);
		}
		virtual bool duplicate(cppObject* a_obj){
			if(m_pointer == nullptr){
				return false;
			}
			return m_pointer->duplicate(a_obj);
		}
		
		virtual bool equal(cppObject *a_obj){
			if(m_pointer == nullptr){
				return false;
			}
			return m_pointer->equal(a_obj);
		}
		
		virtual bool instanceof(cppObjectClass* cls){
			if(m_pointer == nullptr){
				return false;
			}
			return m_pointer->instanceof(cls);
		}
		virtual cppObjectClass* getClass(){
			if(m_pointer == nullptr){
				return nullptr;
			}
			return m_pointer->getClass();
		}

		virtual cppObject* clone(void){
			if(m_pointer == nullptr){
				return nullptr;
			}
			return m_pointer->clone();
		}
		virtual cppObject* clone(bool owningMemory){
			if(m_pointer == nullptr){
				return nullptr;
			}
			return m_pointer->clone(owningMemory);
		}
		
		virtual cppObject* move(){
			if(m_pointer == nullptr){
				return nullptr;
			}
			return m_pointer->move();
		}
		virtual cppObject* duplicate(){
			if(m_pointer == nullptr){
				return nullptr;
			}
			return m_pointer->duplicate();
		}
	private:
		cppObject* m_pointer = nullptr;
		cppObjectClass* m_class = nullptr;
};

}

#endif