
#ifndef AbsoluteRandom_hpp
#define AbsoluteRandom_hpp
#define AbsoluteRandom_AVAILABLE

#include "Function.hpp"
#include "RealRandom.hpp"

#ifdef AbsoluteRandom_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"

	#define AbsoluteRandomLog(location,method,type,mns) ame_Log(this,location,"AbsoluteRandom",method,type,mns)
#else
	#ifdef AbsoluteRandom_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"

		#define AbsoluteRandomLog(location,method,type,mns) ame_LogDebug(this,location,"AbsoluteRandom",method,type)
	#else
		#define AbsoluteRandomLog(location,method,type,mns)
	#endif
#endif

namespace ame{

//seed from 0 - 1000
class AbsoluteRandom : public Function<float>{
	protected:
		RealRandom *m_realRandom = nullptr;
		
    public:
		AbsoluteRandom(){
			this->m_realRandom = new RealRandom();
			float limitMax = ((float)2147483646/1000000.0f);
			this->initializeConstantes(3,0);
			this->setConstante(0,limitMax);
			this->setConstante(1,100000.0f);
			this->setConstante(2,0.0f);
		}
		virtual ~AbsoluteRandom(){
			delete this->m_realRandom;
		}
		virtual float function(const PrimitiveList<float>& a_variables){
			if(a_variables.getPosition() < 3){
				return 0;
			}
			float i_max = a_variables[0];
			float i_min = a_variables[1];
			float i_seed_1 = a_variables[2];
			float i_seed_2 = this->m_realRandom->f(this->getConstante(1), this->getConstante(2), i_seed_1);
			float time = ((float)micros()/1000000.0f);
			float d = i_max - i_min;
			float dx = (this->getConstante(0)/(i_seed_2));
			float tdx = ((float)(time/dx));
			float tx = (((float)(tdx))-((long)(tdx)));
			float x = d*tx;
			AbsoluteRandomLog(ame_Log_Statement, "getRandom", "println","");
			AbsoluteRandomLog(ame_Log_Statement, "getRandom", "println","absoluterandom");
			AbsoluteRandomLog(ame_Log_Statement, "getRandom", "print","time ");AbsoluteRandomLog(ame_Log_Statement, "getRandom", "println",Note(time));
			AbsoluteRandomLog(ame_Log_Statement, "getRandom", "print","d ");AbsoluteRandomLog(ame_Log_Statement, "getRandom", "println",Note(d));
			AbsoluteRandomLog(ame_Log_Statement, "getRandom", "print","dx ");AbsoluteRandomLog(ame_Log_Statement, "getRandom", "println",Note(dx));
			AbsoluteRandomLog(ame_Log_Statement, "getRandom", "print","tdx ");AbsoluteRandomLog(ame_Log_Statement, "getRandom", "println",Note(tdx));
			AbsoluteRandomLog(ame_Log_Statement, "getRandom", "print","tx ");AbsoluteRandomLog(ame_Log_Statement, "getRandom", "println",Note(tx));
			AbsoluteRandomLog(ame_Log_Statement, "getRandom", "print","x ");AbsoluteRandomLog(ame_Log_Statement, "getRandom", "println",Note(x));
			AbsoluteRandomLog(ame_Log_Statement, "getRandom", "println","");
			return x + i_min;
		}

		virtual Function<T>* clone(){
			return new AbsoluteRandom();
		}

		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){return Class<AbsoluteRandom>::getClass();}
		virtual bool instanceof(cppObjectClass* cls){return cls == Class<AbsoluteRandom>::getClass() || Random::instanceof(cls);}
		#endif
		
};

}

#endif