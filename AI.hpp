
#ifndef AI_hpp
#define AI_hpp
#define AI_AVAILABLE

#include "cppObject.hpp"

namespace ame{

template<class DATA>
class AI IMPLEMENTATION_cppObject {
	public:
		DATA data;
		
		using DATAMethod = void(*)(const DATA&);
		using AIMethod = void(*)(const AI<DATA>&);

		AI(){}
		virtual ~AI(){}

		virtual void run(DATAMethod method){
			method(data);
		}

		virtual void run(DATAMethod* method){
			(**method)(data);
		}

		virtual void run(AIMethod method){
			method(*this);
		}

		virtual void run(AIMethod* method){
			(**method)(*this);
		}

		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){return Class<AI<T,Args...>>::getClass();}
		virtual bool instanceof(cppObjectClass* cls){return cls == Class<AI<T,Args...>>::getClass();}
		#endif
		
	protected:
};

}

#endif