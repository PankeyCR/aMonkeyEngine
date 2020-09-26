
#ifndef LoopState_h
#define LoopState_h

#include "AppState.h"

class LoopState : public AppState{
	public:
		Application *App;
		LoopState(Stream *port){
			serial = port;
		}
		void initialize(Application *app){
			App = app;
		}
		void update(float tpc){
		  serial->println(App->getTimeControl()->getTime());
		}
		
		String getClassName(){
		  return "LoopState";
		}
		
	private:
		Stream *serial=NULL;
};

#endif 