
#ifndef Random_hpp
#define Random_hpp
#define Random_AVAILABLE

#include "cppObject.hpp"
#include "Function.hpp"
#include "RealRandom.hpp"

namespace ame{

template<class T>
class Random IMPLEMENTATION_cppObject {
	protected:
		T m_max;
		T m_min;
		T m_seed;
		Function<T>* m_sequence = nullptr;
	
    public:
		Random(){}

		Random(Function<T>* c_random){
			m_sequence = c_random;
		}

		Random(T c_max, T c_min, T c_seed){
			m_max = c_max;
			m_min = c_min;
			m_seed = c_seed;
		}

		Random(T c_max, T c_min, T c_seed, Function<T>* c_random){
			m_max = c_max;
			m_min = c_min;
			m_seed = c_seed;
			m_sequence = c_random;
		}

		Random(const Random<T>& c_random){
			m_max = c_random.m_max;
			m_min = c_random.m_min;
			m_seed = c_random.m_seed;
			if(c_random.m_sequence != nullptr){
				m_sequence = c_random.m_sequence->clone();
			}
		}

		virtual ~Random(){
			if(m_sequence != nullptr){
				delete m_sequence;
			}
		}
		
		virtual void setFunction(Function<T>* a_function)){
			if(m_sequence != nullptr){
				delete m_sequence;
			}
			m_sequence = a_function;
		}

		virtual void set(T a_max, T a_min, T a_seed){
			m_max = a_max;
			m_min = a_min;
			m_seed = a_seed;
		}
		
		virtual void setMax(T a_max){
			m_max = a_max;
		}
		
		virtual void setMin(T a_min){
			m_min = a_min;
		}
		
		virtual T getMax() const{
			return m_max;
		}
		
		virtual T getMin() const{
			return m_min;
		}
		
		virtual void setSeed(T a_seed){
			m_seed = a_seed;
		}
		
		virtual T getSeed() const{
			return m_seed;
		}
		
		virtual T getRandom(){
			if(m_sequence == nullptr){
				return 0;
			}
			return m_sequence->f(m_max, m_min, m_seed);
		}
			
		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){return Class<Random>::getClass();}
		virtual bool instanceof(cppObjectClass* cls){return cls == Class<Random>::getClass();}
		virtual cppObject* clone(){return new Random(*this);}
		#endif

		virtual void operator=(const Random& a_random){
			m_max = a_random.m_max;
			m_min = a_random.m_min;
			m_seed = a_random.m_seed;
			if(m_sequence != nullptr){
				delete m_sequence;
			}
			if(a_random.m_sequence != nullptr){
				m_sequence = a_random.m_sequence->clone();
			}
		}
		virtual bool operator==(const Random& a_random){
			return m_max == a_random.m_max && m_min == a_random.m_min && m_seed == a_random.m_seed && m_sequence->equal(a_random.m_sequence);
		}
		virtual bool operator!=(const Random& obj){
			return m_max != a_random.m_max && m_min != a_random.m_min && m_seed != a_random.m_seed && !m_sequence->equal(a_random.m_sequence);
		}
};

}

#endif