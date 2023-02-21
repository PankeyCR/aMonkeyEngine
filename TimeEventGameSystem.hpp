
#ifndef TimeEventGameSystem_hpp
#define TimeEventGameSystem_hpp
#define TimeEventGameSystem_AVAILABLE

#include "GameSystem.hpp"
#include "PrimitiveMethodMap.hpp"

#ifdef TimeEventGameSystem_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"
	
	#define TimeEventGameSystemLog(location,method,type,mns) ame_Log(this,location,"TimeEventGameSystem",method,type,mns)
	#define TimeEventGameSystemMethodLog(location,method,type,mns) ame_Log(nullptr,location,"RawMethod",method,type,mns)
	#define const_TimeEventGameSystemLog(location,method,type,mns) 
	#define StaticTimeEventGameSystemLog(pointer,location,method,type,mns) ame_Log(pointer,location,"TimeEventGameSystem",method,type,mns)
#else
	#ifdef TimeEventGameSystem_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"
		
		#define TimeEventGameSystemLog(location,method,type,mns) ame_LogDebug(this,location,"TimeEventGameSystem",method,type)
		#define TimeEventGameSystemMethodLog(location,method,type,mns) ame_LogDebug(nullptr,location,"RawMethod",method,type)
		#define const_TimeEventGameSystemLog(location,method,type,mns) 
		#define StaticTimeEventGameSystemLog(pointer,location,method,type,mns) ame_LogDebug(pointer,location,"TimeEventGameSystem",method,type)
	#else
		#define TimeEventGameSystemLog(location,method,type,mns) 
		#define TimeEventGameSystemMethodLog(location,method,type,mns) 
		#define const_TimeEventGameSystemLog(location,method,type,mns) 
		#define StaticTimeEventGameSystemLog(pointer,location,method,type,mns) 
	#endif
#endif

namespace ame{
	
template<class ENTITY, class COMPONENT, class SYSTEMCOMPONENT = COMPONENT>
class TimeEventGameSystem : public GameSystem<ENTITY,COMPONENT,SYSTEMCOMPONENT>{
	public:
		using m_Method = void (*)(SYSTEMCOMPONENT*);

		TimeEventGameSystem() : GameSystem<ENTITY,COMPONENT,SYSTEMCOMPONENT>(){}

		TimeEventGameSystem(cppObjectClass* c_class) : GameSystem<ENTITY,COMPONENT,SYSTEMCOMPONENT>(c_class){}

		TimeEventGameSystem(Note c_id) : GameSystem<ENTITY,COMPONENT,SYSTEMCOMPONENT>(c_id){}

		TimeEventGameSystem(Note c_id, cppObjectClass* c_class) : GameSystem<ENTITY,COMPONENT,SYSTEMCOMPONENT>(c_id, c_class){}

		virtual ~TimeEventGameSystem(){}

		virtual cppObjectClass* getClass(){
			return Class<TimeEventGameSystem<ENTITY,COMPONENT,SYSTEMCOMPONENT>>::getClass();
		}

		virtual bool instanceof(cppObjectClass* cls){
			return cls == Class<TimeEventGameSystem<ENTITY,COMPONENT,SYSTEMCOMPONENT>>::getClass() || GameSystem<ENTITY,COMPONENT,SYSTEMCOMPONENT>::instanceof(cls);
		}

		virtual void initializeState(){}

		virtual void updateComponents(SYSTEMCOMPONENT* component, float tpc){
			TimeEventGameSystemLog(ame_Log_StartMethod, "updateComponents",  "println", "");
			if(!m_event_enable){
				return;
			}
			m_time += tpc;
			if(event_running >= m_method.getPosition()){
				TimeEventGameSystemLog(ame_Log_EndMethod, "updateComponents",  "println", "event_running >= m_method.getPosition()");
				return;
			}
			float i_time = m_method.getKey(event_running);
			if(m_time > i_time){
				TimeEventGameSystemLog(ame_Log_Statement, "updateComponents",  "println", Note("time: ") + Note(m_time));
				TimeEventGameSystemLog(ame_Log_Statement, "updateComponents",  "println", Note("event_running: ") + Note(event_running));
				m_Method* i_method = m_method.getMethod(event_running);
				(**i_method)(component);
				event_running++;
				// if(component->repeatMethod()){
				// 	this->addEvent(component->repeatTime(), *i_method);
				// }
				if(event_running >= m_method.getPosition()){
					TimeEventGameSystemLog(ame_Log_Statement, "updateComponents",  "println", "event_running >= m_method.getPosition()");
					TimeEventGameSystemLog(ame_Log_Statement, "updateComponents",  "println", "m_event_enable = false");
					m_event_enable = false;
				}
			}
			TimeEventGameSystemLog(ame_Log_EndMethod, "updateComponents",  "println", "");
		}

		virtual void updateState(float tpc){}

		virtual void addEvent(float a_time, m_Method a_method){
			TimeEventGameSystemLog(ame_Log_StartMethod, "addEvent",  "println", "");
			m_method.add(a_time, a_method);
			// if(m_method.isEmpty()){
			// 	m_method.addPointer(a_time, a_method);
			// 	TimeEventGameSystemLog(ame_Log_EndMethod, "addEvent",  "println", "m_method.isEmpty()");
			// 	return;
			// }
			// for(int x = 0; x < m_method.getPosition(); x++){
			// 	Pair<float,m_Method>* f_pair = m_method.getByPosition(x);
			// 	int f_time = *f_pair->x1;

			// 	if(a_time < f_time){
			// 		TimeEventGameSystemLog(ame_Log_EndMethod, "addEvent",  "println", "adding event");
			// 		TimeEventGameSystemLog(ame_Log_EndMethod, "addEvent",  "println", Note("index: ") + Note(x));
			// 		TimeEventGameSystemLog(ame_Log_EndMethod, "addEvent",  "println", Note("event time: ") + Note(a_time));
			// 		TimeEventGameSystemLog(ame_Log_EndMethod, "addEvent",  "println", Note("insert before time: ") + Note(f_time));
			// 		m_method.insertPointer(x, f_pair);
			// 	}
			// }
			TimeEventGameSystemLog(ame_Log_EndMethod, "addEvent",  "println", "");
		}

		virtual void start(){
			m_event_enable = true;
			event_running = 0;
			m_time = 0;
		}

	protected:
		PrimitiveMethodMap<float,SYSTEMCOMPONENT*> m_method;

		bool m_event_enable = false;
		int event_running = 0;
		float m_time = 0;
};

}

#endif