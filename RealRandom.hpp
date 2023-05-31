
#ifndef RealRandom_hpp
#define RealRandom_hpp
#define RealRandom_AVAILABLE

#include "Function.hpp"

#ifdef RealRandom_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"

	#define RealRandomLog(location,method,type,mns) ame_Log(this,location,"RealRandom",method,type,mns)
#else
	#ifdef RealRandom_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"

		#define RealRandomLog(location,method,type,mns) ame_LogDebug(this,location,"RealRandom",method,type)
	#else
		#define RealRandomLog(location,method,type,mns)
	#endif
#endif

namespace ame{

class RealRandom : public Function<float>{
    public:
		RealRandom(){
			float limitMax = ((float)2147483646/1000000.0f);
			this->initializeConstantes(1,limitMax);
			RealRandomLog(ame_Log_StartMethod, "Contructor", "println",limitMax);
		}
		RealRandom(const RealRandom& a_random){
			float limitMax = ((float)2147483646/1000000.0f);
			this->initializeConstantes(1,limitMax);
			RealRandomLog(ame_Log_StartMethod, "Contructor", "println",limitMax);
		}
		
		virtual ~RealRandom(){}
		
		virtual float function(const PrimitiveList<float>& a_variables){
			if(a_variables.getPosition() < 3){
				return 0;
			}
			float i_max = a_variables[0];
			float i_min = a_variables[1];
			float i_seed_1 = a_variables[2];
			float time = ((float)micros()/1000000.0f);
			float d = i_max - i_min;
			float dx = ((float)this->getConstante(0)/(i_seed * 10.0f));
			float tdx = ((float)(time / dx));
			float tx = (((float)(tdx))-((long)(tdx)));
			float x = d*tx;
			RealRandomLog(ame_Log_StartMethod, "getRandom", "println","");
			RealRandomLog(ame_Log_StartMethod, "getRandom", "println","RealRandom");
			RealRandomLog(ame_Log_StartMethod, "getRandom", "print","time ");RealRandomLog(ame_Log_StartMethod, "getRandom", "println",Note(time));
			RealRandomLog(ame_Log_StartMethod, "getRandom", "print","d ");RealRandomLog(ame_Log_StartMethod, "getRandom", "println",Note(d));
			RealRandomLog(ame_Log_StartMethod, "getRandom", "print","dx ");RealRandomLog(ame_Log_StartMethod, "getRandom", "println",Note(dx));
			RealRandomLog(ame_Log_StartMethod, "getRandom", "print","tdx ");RealRandomLog(ame_Log_StartMethod, "getRandom", "println",Note(tdx));
			RealRandomLog(ame_Log_StartMethod, "getRandom", "print","tx ");RealRandomLog(ame_Log_StartMethod, "getRandom", "println",Note(tx));
			RealRandomLog(ame_Log_StartMethod, "getRandom", "print","x ");RealRandomLog(ame_Log_StartMethod, "getRandom", "println",Note(x));
			RealRandomLog(ame_Log_StartMethod, "getRandom", "println","");
			return x + i_min;
		}

		virtual Function<T>* clone(){
			return new RealRandom();
		}

		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){return Class<RealRandom>::getClass();}
		virtual bool instanceof(cppObjectClass* cls){return cls == Class<RealRandom>::getClass() || Function<float>::instanceof(cls);}
		#endif
};

}

#endif