
#ifndef NoRepiteRandom_hpp
#define NoRepiteRandom_hpp
#define NoRepiteRandom_AVAILABLE

#include "Function.hpp"
#include "RealRandom.hpp"

#ifdef NoRepiteRandom_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"

	#define NoRepiteRandomLog(location,method,type,mns) ame_Log(this,location,"NoRepiteRandom",method,type,mns)
#else
	#ifdef NoRepiteRandom_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"

		#define NoRepiteRandomLog(location,method,type,mns) ame_LogDebug(this,location,"NoRepiteRandom",method,type)
	#else
		#define NoRepiteRandomLog(location,method,type,mns)
	#endif
#endif

namespace ame{

class NoRepiteRandom : public Function<float,float,float,float>{
	protected:
		RealRandom *m_realRandom = nullptr;
		
    public:
		NoRepiteRandom(){
			this->m_realRandom = new RealRandom();
			float limitMax = ((float)2147483646/1000000.0f);
			this->initializeConstantes(4,0);
			this->setConstante(0,limitMax);
			this->setConstante(1,100000.0f);
			this->setConstante(2,0.0f);
			this->setConstante(3,1.0f);
		}
		virtual ~NoRepiteRandom(){
			delete this->m_realRandom;
		}
		virtual float f(float a_max, float a_min, float a_seed){
			float i_seed = this->m_realRandom->f(this->getConstante(1), this->getConstante(2), a_seed);
			float time = ((float)micros()/1000000.0f);
			float d = a_max - a_min;
			float dx = (this->getConstante(0) / (i_seed * this->getConstante(3)));
			float tdx = ((float)(time/dx));
			float tx = (((float)(tdx))-((long)(tdx)));
			float x = d*tx;
			NoRepiteRandomLog(ame_Log_Statement, "getRandom", "println","");
			NoRepiteRandomLog(ame_Log_Statement, "getRandom", "println","NoRepiteRandom");
			NoRepiteRandomLog(ame_Log_Statement, "getRandom", "print","time ");NoRepiteRandomLog(ame_Log_Statement, "getRandom", "println",Note(time));
			NoRepiteRandomLog(ame_Log_Statement, "getRandom", "print","d ");NoRepiteRandomLog(ame_Log_Statement, "getRandom", "println",Note(d));
			NoRepiteRandomLog(ame_Log_Statement, "getRandom", "print","dx ");NoRepiteRandomLog(ame_Log_Statement, "getRandom", "println",Note(dx));
			NoRepiteRandomLog(ame_Log_Statement, "getRandom", "print","tdx ");NoRepiteRandomLog(ame_Log_Statement, "getRandom", "println",Note(tdx));
			NoRepiteRandomLog(ame_Log_Statement, "getRandom", "print","tx ");NoRepiteRandomLog(ame_Log_Statement, "getRandom", "println",Note(tx));
			NoRepiteRandomLog(ame_Log_Statement, "getRandom", "print","x ");NoRepiteRandomLog(ame_Log_Statement, "getRandom", "println",Note(x));
			NoRepiteRandomLog(ame_Log_Statement, "getRandom", "println","");
			this->setConstante(3, 1.0f / (x + a_min + 0.1f));
			return x + a_min;
		}
		
};

}

#endif