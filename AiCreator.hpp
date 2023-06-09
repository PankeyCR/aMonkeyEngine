
#ifndef AiCreator_hpp
#define AiCreator_hpp
#define AiCreator_AVAILABLE

#include "cppObject.hpp"
#include "PrimitiveList.hpp"
#include "Cast.hpp"

namespace ame{

template<class DATA, class DATASET>
class AiCreator IMPLEMENTATION_cppObject {
	public:
		typedef TrainMethod = void(*)(DATA, DATASET);
		AiCreator(){}
		virtual ~AiCreator(){}
		
		static AI<DATA>&& create(const DATASET& a_data, TrainMethod a_trainer){
			AI<DATA> i_ai;
			for(const DATA& f_data : a_data){
				a_trainer(f_data, i_ai);
			}
			return move(i_ai);
		}  
		
		// virtual AI* create(const DATASET& a_data, const Trainer<DATASET,AI>& a_trainer){
		// 	AI* i_ai = f_trainer.create();
		// 	for(const DATA& f_data : a_data){
		// 		a_trainer.fit(f_data, i_ai);
		// 		if(!a_trainer.evaluate(f_data, i_ai)){
		// 			if(i_ai != nullptr){
		// 				delete i_ai;
		// 			}
		// 			return nullptr;
		// 		}
		// 	}
		// 	return i_ai;
		// }  

		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){return Class<AiCreator<T,Args...>>::getClass();}
		virtual bool instanceof(cppObjectClass* cls){return cls == Class<AiCreator<T,Args...>>::getClass();}
		#endif
		
	protected:
};

}

#endif