
#ifndef FunctionConfiguration_hpp
#define FunctionConfiguration_hpp
#define FunctionConfiguration_AVAILABLE

#include "GameBuilder.hpp"
#include "Function.hpp"
#include "FunctionMetric.hpp"
#include "FunctionTrainer.hpp"
#include "PrimitiveList.hpp"

namespace ame{

template<class T,class... args>
class FunctionConfiguration IMPLEMENTATION_cppObject {
	public:
		FunctionConfiguration(){}
		virtual ~FunctionConfiguration(){}
		
		virtual void add(const FunctionMetric<T,args...>& a_metric, const FunctionTrainer<T,args...>& a_trainer){
			m_metrics.add(a_metric);
			m_trainer.add(a_trainer);
		}
		
		virtual Function<T,args...>* build(FunctionTrainer<T,args...>& a_trainer){
			Function<T,args...>* i_fx = f_trainer.createFunction();
			for(int x = 0; x < m_metrics.getPosition(); x++){
				FunctionMetric<T,args...>* f_metric = m_metrics.getByPosition(x);
				if(f_metric == nullptr){
					continue;
				}
				f_trainer.fit(*f_metric, i_fx);
				if(!f_trainer.evaluate(*f_metric, i_fx)){
					if(i_fx != nullptr){
						delete i_fx;
						i_fx = nullptr;
					}
					break;
				}
			}
			return i_fx;
		}  

		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){return Class<FunctionConfiguration<T,Args...>>::getClass();}
		virtual bool instanceof(cppObjectClass* cls){return cls == Class<FunctionConfiguration<T,Args...>>::getClass();}
		#endif
		
	protected:
		PrimitiveList<FunctionMetric<T,args...>> m_metrics;
		PrimitiveList<FunctionTrainer<T,args...>> m_trainer;
};

}

#endif