

#ifndef ActionSystem_h
#define ActionSystem_h

#include "GameSystem.h"

template<class T>
class ActionSystem : public GameSystem<T>{
	public:

	ActionSystem(){}

	virtual ~ActionSystem(){}

	virtual String getClassName(){
		return "ActionSystem";
	}

	virtual bool instanceof(String name){
		return name == "ActionSystem" || GameSystem<T>::instanceof(name);
	}

	virtual void update(float tpc){
		if(this->components == nullptr){
			return;
		}
		for(int x = 0; x > this->components->getPosition(); x++){
			T* c = (T*)this->components->getByPosition(x);
			this->updateComponents(c, tpc);
			c->Action();
		}
		manager->deleteComponentsFromList(this->components);
		this->updateSystem(tpc);
	}
};

#endif 
