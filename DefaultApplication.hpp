
#ifndef CONFIGURATION_DefaultApplication_hpp
#define CONFIGURATION_DefaultApplication_hpp

	#include "ame_Enviroment.hpp"

	#if defined(DISABLE_DefaultApplication)
		#define DefaultApplication_hpp

		#define IMPLEMENTATION_DefaultApplication
		#define IMPLEMENTING_DefaultApplication
	#else
		#if defined(DISABLE_IMPLEMENTATION_DefaultApplication)
			#define IMPLEMENTATION_DefaultApplication
			#define IMPLEMENTING_DefaultApplication
		#endif
	#endif
#endif

#ifndef DefaultApplication_hpp
#define DefaultApplication_hpp
#define DefaultApplication_AVAILABLE

#ifndef DISABLE_IMPLEMENTATION_DefaultApplication
	#define IMPLEMENTATION_DefaultApplication IMPLEMENTATION(public DefaultApplication)
	#define IMPLEMENTING_DefaultApplication IMPLEMENTING(public DefaultApplication)
#endif

#include "Application.hpp"
#include "DefaultStateManager.hpp"
#include "SimpleTimer.hpp"
#include "DefaultSettings.hpp"

#ifdef DefaultApplication_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"
	
	#define DefaultApplicationLog(location,method,type,mns) ame_Log(this,location,"DefaultApplication",method,type,mns)
	#define const_DefaultApplicationLog(location,method,type,mns) 
	#define StaticDefaultApplicationLog(pointer,location,method,type,mns) ame_Log(pointer,location,"DefaultApplication",method,type,mns)
#else
	#ifdef DefaultApplication_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"
		
		#define DefaultApplicationLog(location,method,type,mns) ame_LogDebug(this,location,"DefaultApplication",method,type)
		#define const_DefaultApplicationLog(location,method,type,mns) 
		#define StaticDefaultApplicationLog(pointer,location,method,type,mns) ame_LogDebug(pointer,location,"DefaultApplication",method,type)
	#else
		#define DefaultApplicationLog(location,method,type,mns) 
		#define const_DefaultApplicationLog(location,method,type,mns) 
		#define StaticDefaultApplicationLog(pointer,location,method,type,mns) 
	#endif
#endif

namespace ame{

/*
*	Class Configuration:
*	DISABLE_Application
*	DISABLE_DefaultStateManager
*	DISABLE_DefaultSettings
*	DISABLE_SimpleTimer
*	DISABLE_IMPLEMENTATION_Application
*/
class DefaultApplication IMPLEMENTATION_Application {
	public:
		DefaultApplication(){
			DefaultApplicationLog(ame_Log_StartMethod, "Constructor", "println", "");
			#if defined(DefaultStateManager_AVAILABLE) && defined(AppStateManager_AVAILABLE)
			AppStateManager* c_state_manager = this->setStateManager(new DefaultStateManager());
			c_state_manager->setApplication(this);
			#endif
			#if defined(DefaultSettings_AVAILABLE) && defined(AppSettings_AVAILABLE)
			this->setSettings(new DefaultSettings());
			#endif
			#if defined(TimeControl_AVAILABLE) && defined(SimpleTimer_AVAILABLE)
			this->setTimeControl(SimpleTimer::getInstance());
			#endif
			DefaultApplicationLog(ame_Log_EndMethod, "Constructor", "println", "");
		}
		virtual ~DefaultApplication(){
			DefaultApplicationLog(ame_Log_StartMethod, "Destructor", "println", "");
			DefaultApplicationLog(ame_Log_EndMethod, "Destructor", "println", "");
		}

		virtual float update(){
			DefaultApplicationLog(ame_Log_StartMethod, "update", "println", "");

			m_tpc = this->generateTpc();

			#if defined(AppStateManager_AVAILABLE)
			AppStateManager* u_states = this->getStateManager();
			if(u_states == nullptr){
				return m_tpc;
			}
			#endif

			#if defined(AppStateManager_AVAILABLE) && defined(MemoryPool_AVAILABLE)
			MemoryPool* u_pool = this->getMemoryPool();
			if(u_pool != nullptr){
				DefaultApplicationLog(ame_Log_Statement, "update", "println", "MemoryPool update");
				u_pool->update(m_tpc);
			}
			#endif
			
			#if defined(AppStateManager_AVAILABLE) && defined(RenderManager_AVAILABLE)
			RenderManager* u_render = this->getRenderManager();
			if(u_render != nullptr){
				DefaultApplicationLog(ame_Log_Statement, "update", "println", "RenderManager update");
				u_render->update(m_tpc);
			}
			#endif

			#if defined(AppStateManager_AVAILABLE)
			u_states->update(m_tpc);
			#endif

			DefaultApplicationLog(ame_Log_EndMethod, "update", "println", "");
			return m_tpc;
		}

		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){return Class<DefaultApplication>::getClass();}
		
		virtual bool instanceof(cppObjectClass* cls){
			return cls == Class<DefaultApplication>::getClass() || Application::instanceof(cls);
		}
		#endif

	protected:
};

}

#endif