
#ifndef GenericClass_hpp
#define GenericClass_hpp
#define GenericClass_AVAILABLE

#include "Note.hpp"
#include "Object.hpp"
#include "ClassCount.hpp"
#include "PrimitiveRawList.hpp"

namespace ame{

class GenericClass : public cppObjectClass{	
	public:
		GenericClass(){
			m_type = getGenericClassCount();
			annotationList = new PrimitiveRawList<Annotation>();
			methodList = new PrimitiveRawList<Method>();
		}
		GenericClass(char* c_note){
			m_type = getGenericClassCount();
			m_name = c_note;
			annotationList = new PrimitiveRawList<Annotation>();
			methodList = new PrimitiveRawList<Method>();
		}
		GenericClass(char* c_note, RawList<Annotation>* c_annotationList, RawList<Method>* c_methodList){
			m_type = getGenericClassCount();
			m_name = c_note;
			annotationList = c_annotationList;
			methodList = c_methodList;
		}
		virtual ~GenericClass(){}
		
		virtual long getType(){
			return m_type;
		}
		
		virtual cppObject* newInstance(){
			return new Object(nullptr, this);
		}
		
		virtual void* newPointer(){
			return nullptr;
		}
		
		virtual Method* getMethodByName(char* a_name){
			RawPointerList<Method>* i_methods = this->getMethods();
			if(i_methods == nullptr){
				return nullptr;
			}
			for(int x = 0; x < i_methods->getPosition(); x++){
				Method* f_method = i_methods->getByPosition(x);
				if(f_method == nullptr){
					continue;
				}
				Note i_name_1 = a_name;
				Note i_name_2 = f_method->getName();
				if( i_name_1 == i_name_2 ){
					return f_method;
				}
			}

			return nullptr;
		}
		
		virtual RawList<Annotation>* getAnnotations(){
			return annotationList;
		}
		
		virtual Annotation* getAnnotation(cppObjectClass* cls){
			if(annotationList == nullptr){
				return nullptr;
			}
			for(int x = 0; x < annotationList->getPosition(); x++){
				Annotation* a = annotationList->getByPosition(x);
				if(a->getClass() == cls){
					return a;
				}
			}
			return nullptr;
		}
		
		virtual RawList<Method>* getMethods(){
			return methodList;
		}
		
		virtual Method* getMethod(cppObjectClass* cls){
			if(methodList == nullptr){
				return nullptr;
			}
			for(int x = 0; x < methodList->getPosition(); x++){
				Method* m = methodList->getByPosition(x);
				if(m->getClass() == cls){
					return m;
				}
			}
			return nullptr;
		}
	
	protected:
		
		long m_type = -1;
		RawList<Annotation>* annotationList = nullptr;
		RawList<Method>* methodList = nullptr;
};

}

#endif