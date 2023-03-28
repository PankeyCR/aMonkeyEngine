
#ifndef Random_hpp
#define Random_hpp
#define Random_AVAILABLE

#include "cppObject.hpp"
#include "Function.hpp"
#include "RealRandom.hpp"

namespace ame{

class Random IMPLEMENTATION_cppObject {
	protected:
		float m_max = 1;
		float m_min = 0;
		float m_seed = 1.0f;
		Function<float>* m_sequence = nullptr;
	
    public:
		Random(){
			m_sequence = new RealRandom();
		}
		Random(Function<float>* c_random){
			m_sequence = c_random;
		}
		Random(const Random& c_random){
			m_max = c_random.m_max;
			m_min = c_random.m_min;
			m_seed = c_random.m_seed;
			if(c_random.m_sequence == nullptr){
				m_sequence = new RealRandom();
			}else{
				Function<float,float,float,float>* i_sequence = c_random.m_sequence->clone();
				if(i_sequence == nullptr){
					m_sequence = new RealRandom();
				}else{
					m_sequence = i_sequence;
				}
			}
		}
		virtual ~Random(){
			if(m_sequence != nullptr){
				delete m_sequence;
			}
		}
		
		virtual void setMax(float a_max){
			m_max = a_max;
		}
		
		virtual void setMin(float a_min){
			m_min = a_min;
		}
		
		virtual float getMax() const{
			return m_max;
		}
		
		virtual float getMin() const{
			return m_min;
		}
		
		virtual void setSeed(float a_seed){
			m_seed = a_seed;
		}
		
		virtual float getSeed() const{
			return m_seed;
		}
		
		virtual float getRandom(){
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
			if(a_random.m_sequence == nullptr){
				m_sequence = new RealRandom();
			}else{
				Function<float,float,float,float>* i_sequence = a_random.m_sequence->clone();
				if(i_sequence == nullptr){
					m_sequence = new RealRandom();
				}else{
					m_sequence = i_sequence;
				}
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