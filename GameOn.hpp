
#ifndef CONFIGURATION_GameOn_hpp
#define CONFIGURATION_GameOn_hpp

	#include "ame_Enviroment.hpp"

	#if defined(DISABLE_GameOn)
		#define GameOn_hpp

		#define IMPLEMENTATION_GameOn
		#define IMPLEMENTING_GameOn
	#else
		#if defined(DISABLE_IMPLEMENTATION_GameOn)
			#define IMPLEMENTATION_GameOn
			#define IMPLEMENTING_GameOn
		#endif
	#endif
#endif

#ifndef GameOn_hpp
#define GameOn_hpp
#define GameOn_AVAILABLE

#ifndef DISABLE_IMPLEMENTATION_GameOn
	#define IMPLEMENTATION_GameOn IMPLEMENTATION(public GameOn)
	#define IMPLEMENTING_GameOn IMPLEMENTING(public GameOn)
#endif

#include "cppObject.hpp"
#include "Class.hpp"

#ifdef GameOn_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"

	#define GameOnLog(location,method,type,mns) ame_Log(this,location,"GameOn",method,type,mns)
	#define const_GameOnLog(location,method,type,mns)
#else
	#ifdef GameOn_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"

		#define GameOnLog(location,method,type,mns) ame_LogDebug(this,location,"GameOn",method,type)
		#define const_GameOnLog(location,method,type,mns)
	#else
		#define GameOnLog(location,method,type,mns)
		#define const_GameOnLog(location,method,type,mns)
	#endif
#endif

namespace ame{

class GameOn : public cppObject{
    public:
		GameOn(){
			GameOnLog(ame_Log_StartMethod, "Constructor",  "println", "");
			GameOnLog(ame_Log_EndMethod, "Constructor",  "println", "");
		}
		GameOn(const GameOn& c_game_on){
			GameOnLog(ame_Log_StartMethod, "Constructor",  "println", "");
			m_parent = c_game_on.m_parent;
			m_enabler = c_game_on.m_enabler;
			m_id = c_game_on.m_id;
			GameOnLog(ame_Log_EndMethod, "Constructor",  "println", "");
		}
		GameOn(GameOn* c_parent, bool c_enable, int c_id){
			GameOnLog(ame_Log_StartMethod, "Constructor",  "println", "");
			m_parent = c_parent;
			m_enabler = c_enable;
			m_id = c_id;
			GameOnLog(ame_Log_EndMethod, "Constructor",  "println", "");
		}
		virtual ~GameOn(){
			GameOnLog(ame_Log_StartMethod, "Destructor",  "println", "");
			GameOnLog(ame_Log_EndMethod, "Destructor",  "println", "");
		}
		virtual void setParent(GameOn* c_parent){
			GameOnLog(ame_Log_StartMethod, "setParent",  "println", "");
			m_parent = c_parent;
			GameOnLog(ame_Log_EndMethod, "setParent",  "println", "");
		}
		
		virtual GameOn* getParent(){
			GameOnLog(ame_Log_StartMethod, "getParent",  "println", "");
			GameOnLog(ame_Log_EndMethod, "getParent",  "println", "");
			return m_parent;
		}
		
		
        virtual void setId(int c_id){
			GameOnLog(ame_Log_StartMethod, "setId",  "println", "");
			m_id = c_id;
			GameOnLog(ame_Log_EndMethod, "setId",  "println", "");
		}
		
        virtual int getId(){
			GameOnLog(ame_Log_StartMethod, "getId",  "println", "");
			GameOnLog(ame_Log_EndMethod, "getId",  "println", "");
			return m_id;
		}
		
        virtual void setParentId(int id){
			GameOnLog(ame_Log_StartMethod, "setParentId",  "println", "");
			if(m_parent != nullptr){
				m_parent->setId(id);
			}
			GameOnLog(ame_Log_EndMethod, "setParentId",  "println", "");
		}
		
        virtual int getParentId(){
			GameOnLog(ame_Log_StartMethod, "getParentId",  "println", "");
			if(m_parent != nullptr){
				GameOnLog(ame_Log_EndMethod, "getParentId",  "println", "");
				return m_parent->getId();
			}
			GameOnLog(ame_Log_EndMethod, "getParentId",  "println", "");
			return -1;
		}
			
		
		virtual bool isEnable(){
			GameOnLog(ame_Log_StartMethod, "isEnable",  "println", "");
			GameOnLog(ame_Log_EndMethod, "isEnable",  "println", "");
			return m_enabler;
		}
			
		virtual void enable(){
			GameOnLog(ame_Log_StartMethod, "enable",  "println", "");
			m_enabler = true;
			GameOnLog(ame_Log_EndMethod, "enable",  "println", "");
		}
		
		virtual void disable(){
			GameOnLog(ame_Log_StartMethod, "disable",  "println", "");
			m_enabler = false;
			GameOnLog(ame_Log_EndMethod, "disable",  "println", "");
		}
		
		
		virtual void update(float tpc){
			
		}
		
        virtual void operator=(const GameOn& c_game_on){
			GameOnLog(ame_Log_StartMethod, "operator=",  "println", "");
			m_parent = c_game_on.m_parent;
			m_enabler = c_game_on.m_enabler;
			m_id = c_game_on.m_id;
			GameOnLog(ame_Log_EndMethod, "operator=",  "println", "");
		}
		
        virtual bool operator==(const GameOn& c_game_on){
			GameOnLog(ame_Log_StartMethod, "operator==",  "println", "");
			GameOnLog(ame_Log_EndMethod, "operator==",  "println", "");
			return m_parent == c_game_on.m_parent && m_id == c_game_on.m_id;
		}
		
        virtual bool operator!=(const GameOn& c_game_on){
			GameOnLog(ame_Log_StartMethod, "operator!=",  "println", "");
			GameOnLog(ame_Log_EndMethod, "operator!=",  "println", "");
			return m_parent != c_game_on.m_parent && m_id != c_game_on.m_id;
		}
		
		virtual cppObjectClass* getClass(){
			return Class<GameOn>::getClass();
		}
		
		virtual bool instanceof(cppObjectClass* cls){
			return cls == Class<GameOn>::getClass();
		}
		
        virtual GameOn* clone(){
			return new GameOn(m_parent, m_enabler, m_id);
		}		
    
	protected:	
		GameOn* m_parent = nullptr;
		bool m_enabler = false;
		int m_id = -1;
};

#define CreateComponentMacro(T)\
class T : public GameOn{\
    public:\
	T(){}\
	virtual ~T(){}\
	virtual cppObjectClass* getClass(){return Class<T>::getClass();}\
	virtual bool instanceof(cppObjectClass* cls){return cls == Class<T>::getClass() || GameOn::instanceof(cls);}\
};\


#define ComponentMacro(T)\
	virtual cppObjectClass* getClass(){return Class<T>::getClass();}\
	virtual bool instanceof(cppObjectClass* cls){return cls == Class<T>::getClass() || GameOn::instanceof(cls);}\


#define ComponentMacros(T,G)\
	virtual cppObjectClass* getClass(){return Class<T>::getClass();}\
	virtual bool instanceof(cppObjectClass* cls){return cls == Class<T>::getClass() || G::instanceof(cls);}\

}//end ame namespace


#endif