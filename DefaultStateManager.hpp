
#ifndef CONFIGURATION_DefaultStateManager_hpp
#define CONFIGURATION_DefaultStateManager_hpp

	#include "ame_Enviroment.hpp"

	#if defined(DISABLE_DefaultStateManager)
		#define DefaultStateManager_hpp

		#define IMPLEMENTATION_DefaultStateManager
		#define IMPLEMENTING_DefaultStateManager
	#else
		#if defined(DISABLE_IMPLEMENTATION_DefaultStateManager)
			#define IMPLEMENTATION_DefaultStateManager
			#define IMPLEMENTING_DefaultStateManager
		#endif
	#endif
#endif

#ifndef DefaultStateManager_hpp
#define DefaultStateManager_hpp
#define DefaultStateManager_AVAILABLE

#ifndef DISABLE_IMPLEMENTATION_DefaultStateManager
	#define IMPLEMENTATION_DefaultStateManager IMPLEMENTATION(public DefaultStateManager)
	#define IMPLEMENTING_DefaultStateManager IMPLEMENTING(public DefaultStateManager)
#endif

#ifndef ame_Enviroment_Defined

#endif

#ifdef ame_Windows
    #include <chrono>
#endif

#ifdef ame_ArduinoIDE
	#include "Arduino.h"
#endif

#include "List.hpp"
#include "Class.hpp"
#include "PrimitiveList.hpp"
#include "AppStateManager.hpp"
#include "System.hpp"

#ifdef DefaultStateManager_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"
	
	#define DefaultStateManagerLog(location,method,type,mns) ame_Log(this,location,"DefaultStateManager",method,type,mns)
#else
	#ifdef DefaultStateManager_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"
		
		#define DefaultStateManagerLog(location,method,type,mns) ame_LogDebug(this,location,"DefaultStateManager",method,type)
	#else
		#define DefaultStateManagerLog(location,method,type,mns) 
	#endif
#endif

namespace ame{

/*
*	Class Configuration:
*	DISABLE_AppStateManager
*	DISABLE_Class
*	DISABLE_IMPLEMENTATION_AppStateManager
*/
class DefaultStateManager IMPLEMENTATION_AppStateManager {
    public:
		DefaultStateManager(){
			DefaultStateManagerLog(ame_Log_StartMethod, "Constructor", "println", "");
			DefaultStateManagerLog(ame_Log_EndMethod, "Constructor", "println", "");
		}
		virtual ~DefaultStateManager(){
			DefaultStateManagerLog(ame_Log_StartMethod, "Destructor", "println", "");
			DefaultStateManagerLog(ame_Log_EndMethod, "Destructor", "println", "");
		}

		virtual AppState* add(AppState* state){
			DefaultStateManagerLog(ame_Log_StartMethod, "add",  "println", "");
			initializeStates.addPointer(state);
			DefaultStateManagerLog(ame_Log_EndMethod, "add", "println", "");
			return state;
		}
		
		virtual AppState* getByPosition(int a_index){
			return appStateList.getByPosition(a_index);
		}
		
		virtual AppState* getById(Note appstateId){
			DefaultStateManagerLog(ame_Log_StartMethod, "getById",  "println", "");
			for(int x = 0; x < appStateList.getPosition(); x++){
				AppState* m_state = appStateList.getByPosition(x);
				if(m_state->getId() == appstateId){
					DefaultStateManagerLog(ame_Log_EndMethod, "getById", "println", "");
					return m_state;
				}
			}
			for(int x = 0; x < initializeStates.getPosition(); x++){
				AppState* m_state = initializeStates.getByPosition(x);
				if(m_state->getId() == appstateId){
					DefaultStateManagerLog(ame_Log_EndMethod, "getById", "println", "");
					return m_state;
				}
			}
			DefaultStateManagerLog(ame_Log_EndMethod, "getById", "println", "");
			return nullptr;
		}
		
		
		virtual AppState* getInitializedStateByPosition(int a_index){
			return appStateList.getByPosition(a_index);
		}
		
		virtual AppState* getInitializedStateById(Note appstateId){
			DefaultStateManagerLog(ame_Log_StartMethod, "getById",  "println", "");
			for(int x = 0; x < appStateList.getPosition(); x++){
				AppState* m_state = appStateList.getByPosition(x);
				if(m_state->getId() == appstateId){
					DefaultStateManagerLog(ame_Log_EndMethod, "getById", "println", "");
					return m_state;
				}
			}
			DefaultStateManagerLog(ame_Log_EndMethod, "getById", "println", "");
			return nullptr;
		}
		
		virtual AppState* getUnInitializedStateByPosition(int a_index){
			return initializeStates.getByPosition(a_index);
		}
		
		virtual AppState* getUnInitializedStateById(Note appstateId){
			DefaultStateManagerLog(ame_Log_StartMethod, "getById",  "println", "");
			for(int x = 0; x < initializeStates.getPosition(); x++){
				AppState* m_state = initializeStates.getByPosition(x);
				if(m_state->getId() == appstateId){
					DefaultStateManagerLog(ame_Log_EndMethod, "getById", "println", "");
					return m_state;
				}
			}
			DefaultStateManagerLog(ame_Log_EndMethod, "getById", "println", "");
			return nullptr;
		}
		
		virtual AppState* removeByPosition(int a_index){
			return appStateList.removeByPosition(a_index);
		}
		
		virtual AppState* removeById(Note appstateId){
			DefaultStateManagerLog(ame_Log_StartMethod, "getById",  "println", "");
			for(int x = 0; x < appStateList.getPosition(); x++){
				AppState* m_state = appStateList.getByPosition(x);
				if(m_state->getId() == appstateId){
					DefaultStateManagerLog(ame_Log_EndMethod, "getById", "println", "");
					return appStateList.removeByPosition(x);
				}
			}
			for(int x = 0; x < initializeStates.getPosition(); x++){
				AppState* m_state = initializeStates.getByPosition(x);
				if(m_state->getId() == appstateId){
					DefaultStateManagerLog(ame_Log_EndMethod, "getById", "println", "");
					return initializeStates.removeByPosition(x);
				}
			}
			DefaultStateManagerLog(ame_Log_EndMethod, "getById", "println", "");
			return nullptr;
		}

		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE)
		virtual AppState* get(cppObjectClass* cls){
			DefaultStateManagerLog(ame_Log_StartMethod, "get",  "println", "");
			for(int x = 0; x < appStateList.getPosition(); x++){
				AppState* m_state = appStateList.getByPosition(x);
				if(m_state->getClass() == cls){
					DefaultStateManagerLog(ame_Log_EndMethod, "get", "println", "");
					return m_state;
				}
			}
			for(int x = 0; x < initializeStates.getPosition(); x++){
				AppState* m_state = initializeStates.getByPosition(x);
				if(m_state->getClass() == cls){
					DefaultStateManagerLog(ame_Log_EndMethod, "get", "println", "");
					return m_state;
				}
			}
			DefaultStateManagerLog(ame_Log_EndMethod, "get", "println", "");
			return nullptr;
		}

		virtual AppState* get(Note appstateId, cppObjectClass* cls){
			DefaultStateManagerLog(ame_Log_StartMethod, "get",  "println", "");
			for(int x = 0; x < appStateList.getPosition(); x++){
				AppState* m_state = appStateList.getByPosition(x);
				if(m_state->getClass() == cls && m_state->getId() == appstateId){
				DefaultStateManagerLog(ame_Log_EndMethod, "get", "println", "");
					return m_state;
				}
			}
			for(int x = 0; x < initializeStates.getPosition(); x++){
				AppState* m_state = initializeStates.getByPosition(x);
				if(m_state->getClass() == cls && m_state->getId() == appstateId){
					DefaultStateManagerLog(ame_Log_EndMethod, "get", "println", "");
					return m_state;
				}
			}
			DefaultStateManagerLog(ame_Log_EndMethod, "get", "println", "");
			return nullptr;
		}

		virtual AppState* getInitializedState(cppObjectClass* cls){
			DefaultStateManagerLog(ame_Log_StartMethod, "getInitializedState",  "println", "");
			for(int x = 0; x < appStateList.getPosition(); x++){
				AppState* m_state = appStateList.getByPosition(x);
				if(m_state->getClass() == cls){
					DefaultStateManagerLog(ame_Log_EndMethod, "getInitializedState", "println", "");
					return m_state;
				}
			}
			DefaultStateManagerLog(ame_Log_EndMethod, "getInitializedState", "println", "");
			return nullptr;
		}

		virtual AppState* getInitializedState(Note appstateId, cppObjectClass* cls){
			DefaultStateManagerLog(ame_Log_StartMethod, "getInitializedState",  "println", "");
			for(int x = 0; x < appStateList.getPosition(); x++){
				AppState* m_state = appStateList.getByPosition(x);
				if(m_state->getClass() == cls && m_state->getId() == appstateId){
					DefaultStateManagerLog(ame_Log_EndMethod, "getInitializedState", "println", "");
					return m_state;
				}
			}
			DefaultStateManagerLog(ame_Log_EndMethod, "getInitializedState", "println", "");
			return nullptr;
		}


		virtual AppState* getUnInitializedState(cppObjectClass* cls){
			DefaultStateManagerLog(ame_Log_StartMethod, "getUnInitializedState",  "println", "");
			for(int x = 0; x < initializeStates.getPosition(); x++){
				AppState* m_state = initializeStates.getByPosition(x);
				if(m_state->getClass() == cls){
					DefaultStateManagerLog(ame_Log_EndMethod, "getUnInitializedState", "println", "");
					return m_state;
				}
			}
			DefaultStateManagerLog(ame_Log_EndMethod, "getUnInitializedState", "println", "");
			return nullptr;
		}

		virtual AppState* getUnInitializedState(Note appstateId, cppObjectClass* cls){
			DefaultStateManagerLog(ame_Log_StartMethod, "getUnInitializedState",  "println", "");
			for(int x = 0; x < initializeStates.getPosition(); x++){
				AppState* m_state = initializeStates.getByPosition(x);
				if(m_state->getClass() == cls && m_state->getId() == appstateId){
					DefaultStateManagerLog(ame_Log_EndMethod, "getUnInitializedState", "println", "");
					return m_state;
				}
			}
			DefaultStateManagerLog(ame_Log_EndMethod, "getUnInitializedState", "println", "");
			return nullptr;
		}


		virtual AppState* remove(cppObjectClass* cls){
			DefaultStateManagerLog(ame_Log_StartMethod, "remove",  "println", "");
			AppState *appstate = nullptr;
			for(int x = 0; x < appStateList.getPosition(); x++){
				AppState* m_state = appStateList.getByPosition(x);
				if(m_state->getClass() == cls){
					appstate = m_state;
					if(appstate == nullptr){
						return nullptr;
					}
					appstate->onDisable();
					appStateList.removeByPointer(appstate);
			DefaultStateManagerLog(ame_Log_EndMethod, "remove", "println", "");
					return appstate;
				}
			}
			for(int x = 0; x < initializeStates.getPosition(); x++){
				AppState* m_state = initializeStates.getByPosition(x);
				if(m_state->getClass() == cls){
					appstate = m_state;
					if(appstate == nullptr){
						return nullptr;
					}
					appstate->onDisable();
					initializeStates.removeByPointer(appstate);
			DefaultStateManagerLog(ame_Log_EndMethod, "remove", "println", "");
					return appstate;
				}
			}
			DefaultStateManagerLog(ame_Log_EndMethod, "remove", "println", "");
			return appstate;
		}

		virtual AppState* remove(Note appstateId, cppObjectClass* cls){
			DefaultStateManagerLog(ame_Log_StartMethod, "remove",  "println", "");
			AppState *appstate = nullptr;
			for(int x = 0; x < appStateList.getPosition(); x++){
				AppState* m_state = appStateList.getByPosition(x);
				if(m_state->getClass() == cls && m_state->getId() == appstateId){
					appstate = m_state;
					if(appstate == nullptr){
						return nullptr;
					}
					appstate->onDisable();
					appStateList.removeByPointer(appstate);
					return appstate;
				}
			}
			for(int x = 0; x < initializeStates.getPosition(); x++){
				AppState* m_state = initializeStates.getByPosition(x);
				if(m_state->getClass() == cls && m_state->getId() == appstateId){
					appstate = m_state;
					if(appstate == nullptr){
						DefaultStateManagerLog(ame_Log_EndMethod, "remove", "println", "");
						return nullptr;
					}
					appstate->onDisable();
					initializeStates.removeByPointer(appstate);
					DefaultStateManagerLog(ame_Log_EndMethod, "remove", "println", "");
					return appstate;
				}
			}
			DefaultStateManagerLog(ame_Log_EndMethod, "remove", "println", "");
			return appstate;
		}

		virtual bool contain(cppObjectClass* cls){
			DefaultStateManagerLog(ame_Log_StartMethod, "contain",  "println", "");
			for(int x = 0; x < appStateList.getPosition(); x++){
				AppState* m_state = appStateList.getByPosition(x);
				if(m_state->getClass() == cls){
					DefaultStateManagerLog(ame_Log_EndMethod, "contain", "println", "");
					return true;
				}
			}
			for(int x = 0; x < initializeStates.getPosition(); x++){
				AppState* m_state = initializeStates.getByPosition(x);
				if(m_state->getClass() == cls){
					DefaultStateManagerLog(ame_Log_EndMethod, "contain", "println", "");
					return true;
				}
			}
			DefaultStateManagerLog(ame_Log_EndMethod, "contain", "println", "");
			return false;
		}

		virtual bool contain(Note appstateId, cppObjectClass* cls){
			DefaultStateManagerLog(ame_Log_StartMethod, "contain",  "println", "");
			for(int x = 0; x < appStateList.getPosition(); x++){
				AppState* m_state = appStateList.getByPosition(x);
				if(m_state->getClass() == cls && m_state->getId() == appstateId){
					DefaultStateManagerLog(ame_Log_EndMethod, "contain", "println", "");
					return true;
				}
			}
			for(int x = 0; x < initializeStates.getPosition(); x++){
				AppState* m_state = initializeStates.getByPosition(x);
				if(m_state->getClass() == cls && m_state->getId() == appstateId){
					DefaultStateManagerLog(ame_Log_EndMethod, "contain", "println", "");
					return true;
				}
			}
			DefaultStateManagerLog(ame_Log_EndMethod, "contain", "println", "");
			return false;
		}
		#endif
		
		virtual int getTotalStatesSize(){
			return appStateList.getPosition() + initializeStates.getPosition();
		}
		
		virtual int getInitializedStatesSize(){
			return appStateList.getPosition();
		}
		
		virtual int getUnInitializedStatesSize(){
			return initializeStates.getPosition();
		}

		virtual void removeAll(){
			DefaultStateManagerLog(ame_Log_StartMethod, "removeAll",  "println", "");
			for(int x = 0; x < appStateList.getPosition(); x++){
				appStateList.getByPosition(x)->onDisable();
			}
			for(int x = 0; x < initializeStates.getPosition(); x++){
				initializeStates.getByPosition(x)->onDisable();
			}
			appStateList.reset();
			initializeStates.reset();
			DefaultStateManagerLog(ame_Log_EndMethod, "removeAll", "println", "");
		}

		virtual void removeDeleteAll(){
			DefaultStateManagerLog(ame_Log_StartMethod, "removeDeleteAll",  "println", "");
			for(int x = 0; x < appStateList.getPosition(); x++){
				appStateList.getByPosition(x)->onDisable();
			}
			for(int x = 0; x < initializeStates.getPosition(); x++){
				initializeStates.getByPosition(x)->onDisable();
			}
			appStateList.resetDelete();
			initializeStates.resetDelete();
			DefaultStateManagerLog(ame_Log_EndMethod, "removeDeleteAll", "println", "");
		}

		virtual void update(float a_tpc){
			DefaultStateManagerLog(ame_Log_StartMethod, "update",  "println", "");
			
			if(!initializeStates.isEmpty()){
				for(int x = 0; x < initializeStates.getPosition();x++){
					AppState* m_state = initializeStates.getByPosition(x);
					if(this->getApplication() != nullptr){
						m_state->initialize(this->getApplication());
						m_state->onEnable();
						appStateList.addPointer(m_state);
					}
				}
				DefaultStateManagerLog(ame_Log_StartMethod, "update",  "println", "initializeStates");
				initializeStates.reset();
			}
			for(int x = 0; x < appStateList.getPosition(); x++){
				DefaultStateManagerLog(ame_Log_StartMethod, "update",  "println", "iterating through all states");
				DefaultStateManagerLog(ame_Log_StartMethod, "update",  "println", "iteration: ");
				DefaultStateManagerLog(ame_Log_StartMethod, "update",  "println", x);
				AppState* m_state = appStateList.getByPosition(x);
				if(m_state == nullptr){
					DefaultStateManagerLog(ame_Log_StartMethod, "update",  "println", "m_state == nullptr");
					continue;
				}
				m_state->update(a_tpc);
			}
			DefaultStateManagerLog(ame_Log_EndMethod, "update", "println", "");
		}

		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){
			return Class<DefaultStateManager>::classType;
		}

		virtual bool instanceof(cppObjectClass* cls){
			return cls == Class<DefaultStateManager>::classType || AppStateManager::instanceof(cls);
		}
		#endif

	protected:
		PrimitiveList<AppState> appStateList;
		PrimitiveList<AppState> initializeStates;
};

}

#endif