
#ifndef CONFIGURATION_Application_hpp
#define CONFIGURATION_Application_hpp

	#include "ame_Enviroment.hpp"

	#if defined(DISABLE_Application)
		#define Application_hpp

		#ifndef AppState_IMPLEMENTATION_AVAILABLE
			#define IMPLEMENTATION_Application
			#define IMPLEMENTING_Application
			#define Application_IMPLEMENTATION_AVAILABLE
		#endif
		
		#ifndef AppState_IMPLEMENTATION_AVAILABLE
			#define IMPLEMENTATION_AppState
			#define IMPLEMENTING_AppState
			#define AppState_IMPLEMENTATION_AVAILABLE
		#endif
	#else
		#if defined(DISABLE_IMPLEMENTATION_Application)
			#ifndef AppState_IMPLEMENTATION_AVAILABLE
				#define IMPLEMENTATION_Application
				#define IMPLEMENTING_Application
				#define Application_IMPLEMENTATION_AVAILABLE
			#endif
			
			#ifndef AppState_IMPLEMENTATION_AVAILABLE
				#define IMPLEMENTATION_AppState
				#define IMPLEMENTING_AppState
				#define AppState_IMPLEMENTATION_AVAILABLE
			#endif
		#endif
	#endif
	
#endif //End Configuration

#ifndef Application_hpp
#define Application_hpp
#define Application_AVAILABLE

#ifndef DISABLE_IMPLEMENTATION_Application
	#define IMPLEMENTATION_Application IMPLEMENTATION(public Application)
	#define IMPLEMENTING_Application IMPLEMENTING(public Application)
#endif

#include "cppObject.hpp"

namespace ame{
	class Application;
}

#include "RenderManager.hpp"
#include "AppStateManager.hpp"
#include "AppSettings.hpp"
#include "TimeControl.hpp"
#include "AbstractClass.hpp"
#include "System.hpp"

namespace ame{

/*
*	Class Configuration:
*	DISABLE_RenderManager
*	DISABLE_AppStateManager
*	DISABLE_AppSettings
*	DISABLE_TimeControl
*	DISABLE_cppObject
*	DISABLE_cppObjectClass
*	DISABLE_AbstractClass
*	DISABLE_IMPLEMENTATION_cppObject
*/
class Application IMPLEMENTATION_cppObject {
    public:
		virtual ~Application(){}

		#if defined(RenderManager_AVAILABLE)
		virtual RenderManager* setRenderManager(RenderManager* r_manager){
			if(r_manager == nullptr){
				return this->m_render;
			}
			if(this->m_render != r_manager){
				if(this->m_render != nullptr){
					delete this->m_render;
				}
			}
			this->m_render = r_manager;
			return this->m_render;
		}

		virtual RenderManager* getRenderManager(){
			return this->m_render;
		}
		#endif

		#if defined(AppStateManager_AVAILABLE)
		virtual AppStateManager* setStateManager(AppStateManager* a_appstate){
			if(a_appstate == nullptr){
				return this->m_states;
			}
			if(this->m_states != a_appstate){
				if(this->m_states != nullptr){
					delete this->m_states;
				}
			}
			this->m_states = a_appstate;
			return this->m_states;
		}

		virtual AppStateManager* getStateManager(){
			return this->m_states;
		}
		#endif

		#if defined(AppSettings_AVAILABLE)
		virtual AppSettings* setSettings(AppSettings* a_setting){
			if(a_setting == nullptr){
				return this->m_settings;
			}
			if(this->m_settings != a_setting){
				if(this->m_settings != nullptr){
					delete this->m_settings;
				}
			}
			this->m_settings = a_setting;
			return this->m_settings;
		}

		virtual AppSettings* getSettings(){
			return this->m_settings;
		}
		#endif

		#if defined(TimeControl_AVAILABLE)
		virtual TimeControl* setTimeControl(TimeControl* a_timecontrol){
			if(a_timecontrol == nullptr){
				return this->m_timer;
			}
			if(this->m_timer != a_timecontrol){
				if(this->m_timer != nullptr){
					delete this->m_timer;
				}
			}
			this->m_timer = a_timecontrol;
			return this->m_timer;
		}

		virtual TimeControl *getTimeControl(){
			return this->m_timer;
		}
		#endif

		#if defined(MemoryPool_AVAILABLE)
		virtual MemoryPool* setMemoryPool(MemoryPool* a_memory){
			if(a_memory == nullptr){
				return this->m_memory;
			}
			if(this->m_memory != a_memory){
				if(this->m_memory != nullptr){
					delete this->m_memory;
				}
			}
			this->m_memory = a_memory;
			return this->m_memory;
		}

		virtual MemoryPool* getMemoryPool(){
			return this->m_memory;
		}
		#endif


		virtual void initialize(){}

		virtual float update()=0;
		
		virtual float tpc(){
			return m_tpc;
		}

		virtual float generateTpc(){
			this->m_now = System::microSeconds();

			this->m_tpc = (float)(this->m_now - this->m_prev)/1000000;
			this->m_prev = this->m_now;

			return this->m_tpc;
		}

		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(AbstractClass_AVAILABLE)
		virtual cppObjectClass* getClass(){
			return AbstractClass<Application>::getClass();
		}

		virtual bool instanceof(cppObjectClass* cls){
			return cls == AbstractClass<Application>::getClass();
		}
		#endif

	protected:
		#if defined(RenderManager_AVAILABLE)
		RenderManager* m_render = nullptr;
		#endif
		
		#if defined(AppStateManager_AVAILABLE)
		AppStateManager* m_states = nullptr;
		#endif
		
		#if defined(AppSettings_AVAILABLE)
		AppSettings* m_settings = nullptr;
		#endif
		
		#if defined(TimeControl_AVAILABLE)
		TimeControl* m_timer = nullptr;
		#endif
		
		#if defined(MemoryPool_AVAILABLE)
		MemoryPool* m_memory = nullptr;
		#endif

		long m_now = 0;
		long m_prev = 0;
		float m_tpc = 0;
};

}

#endif
