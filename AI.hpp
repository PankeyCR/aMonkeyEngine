
#ifndef AI_hpp
#define AI_hpp
#define AI_AVAILABLE

#include "cppObject.hpp"
#include "Cast.hpp"

#ifdef AI_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"
	
	#define AILog(location,method,type,mns) ame_Log(this,location,"AI",method,type,mns)
#else
	#ifdef DefaultApplication_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"
		
		#define AILog(location,method,type,mns) ame_LogDebug(this,location,"AI",method,type)
	#else
		#define AILog(location,method,type,mns) 
	#endif
#endif

namespace ame{

template<class DATA>
class AI IMPLEMENTATION_cppObject {
	public:
		DATA data;
		
		using DATAMethod = void(*)(const DATA&);
		using AIMethod = void(*)(const AI<DATA>&);

		AI(){
			AILog(ame_Log_StartMethod, "Constructor",  "println", "default");
			AILog(ame_Log_EndMethod, "Constructor",  "println", "");
		}
		AI(const DATA& c_data){
			AILog(ame_Log_StartMethod, "Constructor",  "println", "const DATA& c_data");
			data = c_data;
			AILog(ame_Log_EndMethod, "Constructor",  "println", "");
		}
		AI(DATA&& c_data){
			AILog(ame_Log_StartMethod, "Constructor",  "println", "DATA&& c_data");
			data = move(c_data);
			AILog(ame_Log_EndMethod, "Constructor",  "println", "");
		}
		virtual ~AI(){
			AILog(ame_Log_StartMethod, "Destructor",  "println", "");
			AILog(ame_Log_EndMethod, "Destructor",  "println", "");
		}

		virtual void operator=(const AI<DATA>& c_ai){
			AILog(ame_Log_StartMethod, "operator=",  "println", "const AI<DATA>& c_ai");
			data = c_ai.data;
			AILog(ame_Log_EndMethod, "operator=",  "println", "");
		}

		virtual void operator=(AI<DATA>&& c_ai){
			AILog(ame_Log_StartMethod, "operator=",  "println", "AI<DATA>&& c_ai");
			data = move(c_ai.data);
			AILog(ame_Log_EndMethod, "operator=",  "println", "");
		}

		virtual bool operator==(const AI<DATA>& c_ai){
			AILog(ame_Log_StartMethod, "operator==",  "println", "const AI<DATA>& c_ai");
			AILog(ame_Log_EndMethod, "operator==",  "println", "");
			return c_ai.data == data;
		}

		virtual bool operator!=(const AI<DATA>& c_ai){
			AILog(ame_Log_StartMethod, "operator!=",  "println", "const AI<DATA>& c_ai");
			AILog(ame_Log_EndMethod, "operator!=",  "println", "");
			return c_ai.data != data;
		}

		virtual void operator=(const DATA& c_data){
			AILog(ame_Log_StartMethod, "operator=",  "println", "const DATA& c_data");
			data = c_data;
			AILog(ame_Log_EndMethod, "operator=",  "println", "");
		}

		virtual void operator=(DATA&& c_data){
			AILog(ame_Log_StartMethod, "operator=",  "println", "DATA&& c_data");
			data = move(c_data);
			AILog(ame_Log_EndMethod, "operator=",  "println", "");
		}

		virtual bool operator==(const DATA& c_data){
			AILog(ame_Log_StartMethod, "operator==",  "println", "const DATA& c_data");
			AILog(ame_Log_EndMethod, "operator==",  "println", "");
			return c_data == data;
		}

		virtual bool operator!=(const DATA& c_data){
			AILog(ame_Log_StartMethod, "operator!=",  "println", "const DATA& c_data");
			AILog(ame_Log_EndMethod, "operator!=",  "println", "");
			return c_data != data;
		}

		virtual void run(DATAMethod method){
			AILog(ame_Log_StartMethod, "Constructor",  "println", "DATAMethod method");
			method(data);
			AILog(ame_Log_EndMethod, "Constructor",  "println", "");
		}

		virtual void run(DATAMethod* method){
			AILog(ame_Log_StartMethod, "Constructor",  "println", "DATAMethod* method");
			(**method)(data);
			AILog(ame_Log_EndMethod, "Constructor",  "println", "");
		}

		virtual void run(AIMethod method){
			AILog(ame_Log_StartMethod, "Constructor",  "println", "AIMethod method");
			method(*this);
			AILog(ame_Log_EndMethod, "Constructor",  "println", "");
		}

		virtual void run(AIMethod* method){
			AILog(ame_Log_StartMethod, "Constructor",  "println", "AIMethod* method");
			(**method)(*this);
			AILog(ame_Log_EndMethod, "Constructor",  "println", "");
		}

		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){return Class<AI<DATA>>::getClass();}
		virtual bool instanceof(cppObjectClass* cls){return cls == Class<AI<DATA>>::getClass();}
		#endif
		
	protected:
};

}

#endif