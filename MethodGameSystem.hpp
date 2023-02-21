
#ifndef MethodGameSystem_hpp
#define MethodGameSystem_hpp
#define MethodGameSystem_AVAILABLE

#include "GameSystem.hpp"
#include "Note.hpp"
#include "PrimitiveList.hpp"

#ifdef MethodGameSystem_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"
	
	#define MethodGameSystemLog(location,method,type,mns) ame_Log(this,location,"MethodGameSystem",method,type,mns)
	#define MethodGameSystemMethodLog(location,method,type,mns) ame_Log(nullptr,location,"RawMethod",method,type,mns)
	#define const_MethodGameSystemLog(location,method,type,mns) 
	#define StaticMethodGameSystemLog(pointer,location,method,type,mns) ame_Log(pointer,location,"MethodGameSystem",method,type,mns)
#else
	#ifdef MethodGameSystem_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"
		
		#define MethodGameSystemLog(location,method,type,mns) ame_LogDebug(this,location,"MethodGameSystem",method,type)
		#define MethodGameSystemMethodLog(location,method,type,mns) ame_LogDebug(nullptr,location,"RawMethod",method,type)
		#define const_MethodGameSystemLog(location,method,type,mns) 
		#define StaticMethodGameSystemLog(pointer,location,method,type,mns) ame_LogDebug(pointer,location,"MethodGameSystem",method,type)
	#else
		#define MethodGameSystemLog(location,method,type,mns) 
		#define MethodGameSystemMethodLog(location,method,type,mns) 
		#define const_MethodGameSystemLog(location,method,type,mns) 
		#define StaticMethodGameSystemLog(pointer,location,method,type,mns) 
	#endif
#endif

namespace ame{
	
template<class ENTITY, class COMPONENT, class SYSTEMCOMPONENT = COMPONENT>
class MethodGameSystem : public GameSystem<ENTITY,COMPONENT,SYSTEMCOMPONENT>{
	public:
		using m_Method = void (*)(SYSTEMCOMPONENT*,float);

		MethodGameSystem() : GameSystem<ENTITY,COMPONENT,SYSTEMCOMPONENT>(){}

		MethodGameSystem(cppObjectClass* c_class) : GameSystem<ENTITY,COMPONENT,SYSTEMCOMPONENT>(c_class){}

		MethodGameSystem(Note c_id) : GameSystem<ENTITY,COMPONENT,SYSTEMCOMPONENT>(c_id){}

		MethodGameSystem(Note c_id, cppObjectClass* c_class) : GameSystem<ENTITY,COMPONENT,SYSTEMCOMPONENT>(c_id, c_class){}

		virtual ~MethodGameSystem(){}

		virtual cppObjectClass* getClass(){
			return Class<MethodGameSystem<ENTITY,COMPONENT,SYSTEMCOMPONENT>>::getClass();
		}

		virtual bool instanceof(cppObjectClass* cls){
			return cls == Class<MethodGameSystem<ENTITY,COMPONENT,SYSTEMCOMPONENT>>::getClass() || GameSystem<ENTITY,COMPONENT,SYSTEMCOMPONENT>::instanceof(cls);
		}

		virtual void updateComponents(SYSTEMCOMPONENT* component, float tpc){
			MethodGameSystemLog(ame_Log_Statement, "updateComponents",  "println", "");
			for(int x = 0; x < m_method.getPosition(); x++){
				(**m_method.getByPosition(x))(component,tpc);
			}
		}

		virtual void addSystem(m_Method a_method){
			m_method.add(a_method);
		}

	protected:
		PrimitiveList<m_Method> m_method;
};

}

#endif