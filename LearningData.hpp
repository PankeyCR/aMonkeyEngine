
#ifndef LearningData_hpp
#define LearningData_hpp
#define LearningData_AVAILABLE

#include "cppObject.hpp"
#include "Random.hpp"
#include "AbsoluteRandom.hpp"
#include "Function.hpp"
#include "PrimitiveList.hpp"

namespace ame{

template<class T>
class LearningData IMPLEMENTATION_cppObject {
	public:
		LearningData(){}
		LearningData(const LearningData<T>& c_metric){
			this->m_random = c_metric.m_random;
			this->m_inputs = c_metric.m_inputs;
			this->m_output = c_metric.m_output;
			this->m_epochs = c_metric.m_epochs;
			this->m_error = c_metric.m_error;
		}
		virtual ~LearningData(){} 
		
		void random(const Random& a_random){
			m_random = a_random;
		}
		
		void random(float a_max,float a_min,float a_seed){
			m_random.setMax(a_max);
			m_random.setMin(a_min);
			m_random.setSeed(a_seed);
		}
		virtual void minimalerror(T a_error){
			m_error = a_error;
		}
		
		template<class... Args>
		void inputs(Args... a_inputs){
			m_inputs.resetDelete();
			m_inputs.addPack(a_inputs...);
		}

		void output(T a_output){
			m_output = a_output;
		}

		void epochs(long a_epochs){
			m_epochs = a_epochs;
		}
		
		float getRandom(){
			return m_random.getRandom();
		}
		int getInputSize(){
			return m_inputs.getPosition();
		}
		T getInput(){
			T* i_input = m_inputs.getByPosition(0);
			if(i_input == nullptr){
				return T();
			}
			return *i_input;
		}

		T getInput(int x){
			T* i_input = m_inputs.getByPosition(x);
			if(i_input == nullptr){
				return T();
			}
			return *i_input;
		}

		PrimitiveList<T> getInputs(){
			return m_inputs;
		}

		T getOutput(){
			return m_output;
		}

		long getEpochs(){
			return m_epochs;
		}

		T getError(){
			return m_error;
		}

		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){return Class<LearningData<T>>::getClass();}
		virtual bool instanceof(cppObjectClass* cls){return cls == Class<LearningData<T>>::getClass();}
		#endif

		virtual void operator=(const LearningData<T>>& a_metric){
			this->m_random = a_metric.m_random;
			this->m_inputs = a_metric.m_inputs;
			this->m_output = a_metric.m_output;
			this->m_epochs = a_metric.m_epochs;
			this->m_error = a_metric.m_error;
		}

		virtual bool operator==(const LearningData<T>>& a_metric){
			this->m_random == a_metric.m_random &&
			this->m_inputs == a_metric.m_inputs &&
			this->m_output == a_metric.m_output &&
			this->m_epochs == a_metric.m_epochs &&
			this->m_error == a_metric.m_error;
		}

		virtual bool operator!=(const LearningData<T>>& a_metric){
			this->m_random != a_metric.m_random &&
			this->m_inputs != a_metric.m_inputs &&
			this->m_output != a_metric.m_output &&
			this->m_epochs != a_metric.m_epochs &&
			this->m_error != a_metric.m_error;
		}
		
	protected:
		Random m_random;
		PrimitiveList<T> m_inputs;
		T m_output;
		long m_epochs = 100;
		T m_error;
};

}

#endif