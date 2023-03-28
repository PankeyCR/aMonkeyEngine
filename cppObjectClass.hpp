
#ifndef DISABLE_cppObjectClass_hpp
#define DISABLE_cppObjectClass_hpp

	#if defined(DISABLE_cppObjectClass)
		#define cppObjectClass_hpp
	#endif
#endif

#ifndef cppObjectClass_hpp
#define cppObjectClass_hpp
#define cppObjectClass_AVAILABLE 

namespace ame{

class cppObjectClass;

}

#include "Annotation.hpp"
#include "Method.hpp"

namespace ame{

class cppObjectClass{	
	public:
		cppObjectClass(){}
		cppObjectClass(char* c_name){m_name = c_name;}
		virtual ~cppObjectClass(){}
		
		virtual cppObjectClass* getClass(){return nullptr;}
		virtual bool instanceof(cppObjectClass* cls){return false;}
		
		virtual void setName(char* a_name){
			m_name = a_name;
		}
		
		virtual char* getName(){
			return m_name;
		}
		
		virtual long getType(){
			return -1;
		}
		
		#if defined(cppObject_AVAILABLE)
		virtual cppObject* newInstance(){
			return nullptr;
		}
		#endif
		
		virtual void* newPointer(){
			return nullptr;
		}

		virtual cppObjectClass* clone(){return new cppObjectClass(m_name);}

		#if defined(Annotation_AVAILABLE)
		virtual Annotation* addAnnotation(Annotation* a_annotation){
			RawPointerList<Annotation>* i_annotations = this->getAnnotations();
			if(i_annotations == nullptr || a_annotation == nullptr){
				return nullptr;
			}
			return i_annotations->addPointer(a_annotation);
		}

		virtual RawPointerList<Annotation>* getAnnotations(){
			return nullptr;
		}
		
		virtual Annotation* getAnnotation(cppObjectClass* cls){
			return nullptr;
		}
		#endif

		#if defined(Method_AVAILABLE)
		virtual Method* addMethod(Method* a_method){
			RawPointerList<Method>* i_methods = this->getMethods();
			if(i_methods == nullptr || a_method == nullptr){
				return nullptr;
			}
			return i_methods->addPointer(a_method);
		}

		virtual RawPointerList<Method>* getMethods(){
			return nullptr;
		}
		
		virtual Method* getMethod(cppObjectClass* cls){
			return nullptr;
		}
		
		virtual Method* getMethodByName(char* a_name){
			return nullptr;
		}
		#endif
		
		virtual void operator=(cppObjectClass b){
			
		}
		virtual bool operator==(cppObjectClass b){
			return false;
		}
		virtual bool operator!=(cppObjectClass b){
			return false;
		}
	protected:
		char* m_name = nullptr;
};

}

#endif