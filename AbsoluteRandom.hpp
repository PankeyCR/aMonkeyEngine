
#ifndef AbsoluteRandom_hpp
#define AbsoluteRandom_hpp
#define AbsoluteRandom_AVAILABLE

#include "Note.hpp"
#include "Random.hpp"
#include "RealRandom.hpp"

#ifdef AbsoluteRandom_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"

	#define AbsoluteRandomLog(location,method,type,mns) ame_Log(this,location,"AbsoluteRandom",method,type,mns)
	#define const_AbsoluteRandomLog(location,method,type,mns)
#else
	#ifdef AbsoluteRandom_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"

		#define AbsoluteRandomLog(location,method,type,mns) ame_LogDebug(this,location,"AbsoluteRandom",method,type)
		#define const_AbsoluteRandomLog(location,method,type,mns)
	#else
		#define AbsoluteRandomLog(location,method,type,mns)
		#define const_AbsoluteRandomLog(location,method,type,mns)
	#endif
#endif

namespace ame{

//seed from 0 - 1000
class AbsoluteRandom : public Random{
	protected:
		RealRandom *realRandom = nullptr;
		float limitMax;
		
    public:
		AbsoluteRandom(){
			this->realRandom = new RealRandom();
			this->realRandom->setSeed(78545l);
			this->realRandom->setMax(78545l);
			setMax(100);
			setMin(0);
			limitMax = ((float)2147483646/1000000.0f);
		}
		AbsoluteRandom(const AbsoluteRandom& r){
			this->realRandom = new RealRandom();
			this->realRandom->setSeed(r.getSeed());
			this->realRandom->setMax(78545l);
			setMax(100);
			setMin(0);
			limitMax = ((float)2147483646/1000000.0f);
		}
		AbsoluteRandom(float seed){
			this->realRandom = new RealRandom();
			this->realRandom->setSeed(seed);
			this->realRandom->setMax(seed);
			setMax(100);
			setMin(0);
			limitMax = ((float)2147483646/1000000.0f);
		}
		AbsoluteRandom(float max, float min, float seed){
			this->realRandom = new RealRandom();
			this->realRandom->setSeed(seed);
			this->realRandom->setMax(seed);
			setMax(max);
			setMin(min);
			limitMax = ((float)2147483646/1000000.0f);
		}
		virtual ~AbsoluteRandom(){
			delete this->realRandom;
		}
		virtual float getRandom(){
			float eseed = this->realRandom->getRandom();
			if(eseed!=0){
				this->seed = eseed;
			}
			float time = ((float)micros()/1000000.0f);
			float d = getMax()-getMin();
			float dx = (limitMax/(this->seed*10.0f));
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
			return x+getMin();
		}
		
};

}

#endif