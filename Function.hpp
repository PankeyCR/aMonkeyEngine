
#ifndef Function_hpp
#define Function_hpp
#define Function_AVAILABLE

#include "cppObject.hpp"
#include "PrimitiveList.hpp"

namespace ame{

template<class T>
class Function IMPLEMENTATION_cppObject {
	public:
		Function(){}
		virtual ~Function(){}

		template<class... Args>
		T f(Args... a_args){
			PrimitiveList<T> i_list;
			i_list.addPack(a_args...);
			return this->function(i_list);
		}

		virtual T function(const PrimitiveList<T>& a_variables)=0;

		virtual void initializeConstantes(int a_size, T a_value){
			for(int x = 0; x < a_size; x++){
				m_constantes.add(a_value);
			}
		}

		virtual void setConstante(int a_index, T a_value){m_constantes.set(a_index, a_value);}

		virtual T getConstante(int a_index){
			if(m_constantes.getPosition() <= a_index){
				return T();
			}
			return m_constantes[a_index];
		}

		virtual Function<T>* clone(){
			return nullptr;
		}
			
		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){return Class<Function<T>>::getClass();}
		
		virtual bool instanceof(cppObjectClass* cls){return cls == Class<Function<T>>::getClass();}

		virtual bool equal(cppObject* a_obj){
			if(a_obj == nullptr){
				return false;
			}
			if(!a_obj->instanceof(this->getClass())){
				return false;
			}
			Function<T>* i_function = (Function<T>*)a_obj;
			return m_constantes == i_function->m_constantes;
		}
		#else
		virtual bool equal(Function<T>* a_function){
			return m_constantes == a_function->m_constantes;
		}
		#endif

		virtual void operator=(const Function<T>& a_function){
			m_constantes = a_function.m_constantes;
		}

		virtual bool operator==(const Function<T>& a_function){
			return m_constantes == a_function.m_constantes;
		}

		virtual bool operator!=(const Function<T>& a_function){
			return m_constantes != a_function.m_constantes;
		}

	protected:
		PrimitiveList<T> m_constantes;
};

}

#endif