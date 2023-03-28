
#ifndef FunctionTrainer_hpp
#define FunctionTrainer_hpp
#define FunctionTrainer_AVAILABLE

#include "Function.hpp"
#include "FunctionMetric.hpp"

namespace ame{

template<class T,class... Args>
class FunctionTrainer IMPLEMENTATION_cppObject {
	public:
		FunctionTrainer(){}
		virtual ~FunctionTrainer(){}
		
		virtual Function<T,Args...>* createFunction(){
			return nullptr;
		}

		virtual void fit(const FunctionMetric<T,Args...>& a_metric, Function<T,Args...>* a_fx){
			
		}
		virtual bool evaluate(const FunctionMetric<T,Args...>& a_metric, Function<T,Args...>* a_fx){
			T i_result = a_fx->f(a...);
			return ((metric->getOutput() - ) < metric->getError()) && 
					((metric->getOutput() - fx->f(a...)) > 0);
		}
		virtual void operator=(FunctionTrainer b){
			
		}
		virtual bool operator==(FunctionTrainer b){
			return false;
		}
		virtual bool operator!=(FunctionTrainer b){
			return false;
		}

		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){return Class<FunctionTrainer<T,Args...>>::getClass();}
		virtual bool instanceof(cppObjectClass* cls){return cls == Class<FunctionTrainer<T,Args...>>::getClass();}
		#endif
		
	protected:
};

}

#endif