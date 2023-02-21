
#ifndef GameSystem_hpp
#define GameSystem_hpp
#define GameSystem_AVAILABLE

#include "BaseAppState.hpp"
#include "PrimitiveList.hpp"

#ifdef GameSystem_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"
	
	#define GameSystemLog(location,method,type,mns) ame_Log(this,location,"GameSystem",method,type,mns)
	#define GameSystemMethodLog(location,method,type,mns) ame_Log(nullptr,location,"RawMethod",method,type,mns)
	#define const_GameSystemLog(location,method,type,mns) 
	#define StaticGameSystemLog(pointer,location,method,type,mns) ame_Log(pointer,location,"GameSystem",method,type,mns)
#else
	#ifdef GameSystem_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"
		
		#define GameSystemLog(location,method,type,mns) ame_LogDebug(this,location,"GameSystem",method,type)
		#define GameSystemMethodLog(location,method,type,mns) ame_LogDebug(nullptr,location,"RawMethod",method,type)
		#define const_GameSystemLog(location,method,type,mns) 
		#define StaticGameSystemLog(pointer,location,method,type,mns) ame_LogDebug(pointer,location,"GameSystem",method,type)
	#else
		#define GameSystemLog(location,method,type,mns) 
		#define GameSystemMethodLog(location,method,type,mns) 
		#define const_GameSystemLog(location,method,type,mns) 
		#define StaticGameSystemLog(pointer,location,method,type,mns) 
	#endif
#endif

namespace ame{
	
template<class ENTITY, class COMPONENT, class SYSTEMCOMPONENT>
class GameSystem : public BaseAppState{
	public:
		GameSystem(){}

		GameSystem(cppObjectClass* c_class){
			m_component_class = c_class;
		}

		GameSystem(Note c_id){
			this->setId(c_id);
		}

		GameSystem(Note c_id, cppObjectClass* c_class){
			this->setId(c_id);
			m_component_class = c_class;
		}

		virtual ~GameSystem(){}

		virtual cppObjectClass* getClass(){
			return Class<GameSystem<ENTITY,COMPONENT,SYSTEMCOMPONENT>>::getClass();
		}

		virtual bool instanceof(cppObjectClass* cls){
			return cls == Class<GameSystem<ENTITY,COMPONENT,SYSTEMCOMPONENT>>::getClass() || AppState::instanceof(cls);
		}

		virtual void initializeComponents(Application* app){
			GameSystemLog(ame_Log_StartMethod, "initializeComponents",  "println", "");
			m_manager = (GameManager<ENTITY,COMPONENT>*)app->getStateManager()->get(Class<GameManager<ENTITY,COMPONENT>>::getClass());
			if(m_manager == nullptr){
				GameSystemLog(ame_Log_EndMethod, "initializeComponents",  "println", "m_manager == nullptr");
				return;
			}
			GameSystemLog(ame_Log_Statement, "initializeComponents",  "println", Note("ENTITY Class Type: ") + Note(Class<ENTITY>::getType()));
			GameSystemLog(ame_Log_Statement, "initializeComponents",  "println", Note("COMPONENT Class Type: ") + Note(Class<COMPONENT>::getType()));
			GameSystemLog(ame_Log_Statement, "initializeComponents",  "println", Note("SYSTEMCOMPONENT Class Type: ") + Note(Class<SYSTEMCOMPONENT>::getType()));
			if(m_component_class == nullptr){
				m_component_class = Class<SYSTEMCOMPONENT>::getClass();
			}
			m_components = m_manager->getComponentsByClass(m_component_class);
			GameSystemLog(ame_Log_EndMethod, "initializeComponents",  "println", "");
		}

		virtual void initialize(Application* app){
			GameSystemLog(ame_Log_StartMethod, "initialize",  "println", "");
			BaseAppState::initialize(app);
			initializeComponents(app);
			if(m_components == nullptr){
				GameSystemLog(ame_Log_EndMethod, "initialize",  "println", "components == nullptr");
				return;
			}
			GameSystemLog(ame_Log_EndMethod, "initialize",  "println", "");
		}

		virtual void update(float tpc){
			GameSystemLog(ame_Log_StartMethod, "update",  "println", "");
			if(!m_enable){
				GameSystemLog(ame_Log_EndMethod, "update",  "println", "!m_enable");
				return;
			}
			if(m_components == nullptr){
				GameSystemLog(ame_Log_Statement, "update",  "println", "components == nullptr");
				return;
			}
			for(int x = 0; x < m_components->getPosition(); x++){
				GameSystemLog(ame_Log_Statement, "update",  "println", "iterating components");
				GameSystemLog(ame_Log_Statement, "initializeComponents",  "println", Note("iteration: ") + Note(x));
				SYSTEMCOMPONENT* f_component = (SYSTEMCOMPONENT*)m_components->getByPosition(x);
				updateComponents(f_component, tpc);
			}
			updateState(tpc);
			GameSystemLog(ame_Log_EndMethod, "update",  "println", "");
		}

		virtual void updateComponents(SYSTEMCOMPONENT* component, float tpc){
			GameSystemLog(ame_Log_StartMethod, "updateComponents",  "println", "");
			GameSystemLog(ame_Log_EndMethod, "updateComponents",  "println", "");
		}

	protected:
		PrimitiveList<COMPONENT>* m_components = nullptr;
		GameManager<ENTITY,COMPONENT>* m_manager = nullptr;
		cppObjectClass* m_component_class = nullptr;
};

}

#endif