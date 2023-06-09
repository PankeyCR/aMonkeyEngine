
#ifndef PrimitiveMethodMap_hpp
#define PrimitiveMethodMap_hpp
#define PrimitiveMethodMap_AVAILABLE

#include "PrimitiveRawMap.hpp"

namespace ame{

template<class K, class... Args>
class PrimitiveMethodMap{
	protected:
		PrimitiveRawMap<K,void (*)(Args...)> m_method_map;
	public:
		using EventMethodMap = void (*)(Args...);
		
		PrimitiveMethodMap(){}
		virtual ~PrimitiveMethodMap(){}
		
		virtual void add(K a_key, EventMethodMap a_method){
			m_method_map.addLValues(a_key, a_method);
		}
		
		virtual void addLValue(K* a_key, EventMethodMap a_method){
			m_method_map.addPointers(a_key, new EventMethodMap(a_method));
		}
		
		virtual void addPointers(K* a_key, EventMethodMap* a_method){
			m_method_map.addPointers(a_key, a_method);
		}
		
		virtual void addPointer(K a_key, EventMethodMap* a_method){
			m_method_map.addPointer(a_key, a_method);
		}

		virtual bool invoke(K a_key, Args... args){
			EventMethodMap* i_event = m_method_map.getValueByLValue(a_key);
			if(i_event == nullptr){
				return false;
			}
			(**i_event)(args...);
			return true;
		}

		virtual bool invokeByPointer(K* a_key, Args... args){
			EventMethodMap* i_event = m_method_map.getValueByPointer(a_key);
			if(i_event == nullptr){
				return false;
			}
			(**i_event)(args...);
			return true;
		}

		virtual bool invokeByPosition(int a_position, Args... args){
			EventMethodMap* i_event = m_method_map.getValueByPosition(a_position);
			if(i_event == nullptr){
				return false;
			}
			(**i_event)(args...);
			return true;
		}

		virtual void invokeAll(Args... args){
			for(int x = 0; x < m_method_map.getPosition(); x++){
				(**m_method_map.getValueByPosition(x))(args...);
			}
		}
		
		virtual int getPosition(){
			return m_method_map.getPosition();
		}
		
		virtual K* getKeyByPosition(int x){
			return m_method_map.getKeyByPosition(x);
		}
		
		virtual K getKey(int x){
			K* i_key = m_method_map.getKeyByPosition(x);
			if(i_key == nullptr){
				return K();
			}
			return *i_key;
		}
		
		virtual EventMethodMap* getMethod(int x){
			EventMethodMap* i_method = m_method_map.getValueByPosition(x);
			return i_method;
		}
};

}

#endif