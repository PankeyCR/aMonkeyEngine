

#ifndef MonkeyTime_h
#define MonkeyTime_h

#include "Arduino.h"
#include "Now.h"
#include "TimeCheck.h"

class MonkeyTime {
    public:		
		MonkeyTime();
		virtual ~MonkeyTime();
		
		virtual void run();
		virtual void computeManualTime(long time);
		virtual void computeTime();
		virtual void computeTime(long time);
		virtual void setStartTime(long time);
		virtual long getStartTime();
		virtual void setCurrentTime(long time);
		virtual long getCurrentTimer();
		virtual void setTime(long time);
		virtual long getTime();
		virtual void setEndTime(long time);
		virtual long getEndTime();
		virtual void start(long time);
		virtual void start();
		virtual void end(long time);
		virtual void end();
		virtual void restart(long time);
		virtual void restart();
		virtual bool isRunning();
		virtual int getTPC();
		virtual int getTPCandRestart();
		virtual void restartTPC();
		virtual void Tick();
		virtual void setTick(long tick);
		virtual long getTick();
		virtual void resetTick();
		virtual bool isNow(float time);
		virtual bool isNow(float time,float offset);
		virtual bool isNow(TimeCheck check,float time);
		virtual bool isNow(TimeCheck check,float time,float offset);
		virtual void setTimeOffset(TimeCheck check);
		virtual TimeCheck getTimeOffset();
		
    
	protected:	
		long currentTimer = 0;
		long microTimer = 0;
		long tpcTimer = 0;
		long tickTimer = 0;
    
		long startTime = 0;
		long scale = 1000000;
		long endTime = 0;
		bool running = false;  
		TimeCheck timecheck;
		bool enable;
		long _micros = 1000000;
};


#endif 
