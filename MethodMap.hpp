
#ifndef MethodMap_hpp
#define MethodMap_hpp
#define MethodMap_AVAILABLE

#include "PrimitiveMethodMap.hpp"

namespace ame{

template<class... Args>
struct MethodMap {
	
	using Raw_NTMethod = void(*)(Args...);
	
	static PrimitiveMethodMap<cppObjectClass,Args...>* m_method_map;
	
	static void add(cppObjectClass* a_cls, Raw_NTMethod* a_method){
		if(m_method_map == nullptr){
			return;
		}
		m_method_map->addPointers(a_cls, a_method);
	}
	
	static void add(cppObjectClass* a_cls, Raw_NTMethod a_method){
		if(m_method_map == nullptr){
			return;
		}
		m_method_map->addLValue(a_cls, a_method);
	}
	
	static void remove(cppObjectClass* a_cls){
		if(m_method_map == nullptr){
			return;
		}
		m_method_map->removeDeleteByPointer(a_cls);
	}
	
	static Raw_NTMethod* getPointer(cppObjectClass* a_cls){
		if(m_method_map == nullptr){
			return nullptr;
		}
		return m_method_map->getByLValue(a_cls);
	}
	
	static bool invoke(cppObjectClass* a_cls, Args... a_invoke){
		if(m_method_map == nullptr){
			return false;
		}
		return m_method_map->invokeByPointer(a_cls, a_invoke...);
	}
	
	static bool invokeAll(Args... a_invoke){
		if(m_method_map == nullptr){
			return false;
		}
		return m_method_map->invokeAll(a_invoke...);
	}
};

template<class... Args>
PrimitiveMethodMap<cppObjectClass,Args...>* MethodMap<Args...>::m_method_map = new PrimitiveMethodMap<cppObjectClass,Args...>();

}

#endif