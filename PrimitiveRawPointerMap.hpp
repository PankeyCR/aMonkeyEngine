
#ifndef PrimitiveRawPointerMap_hpp
#define PrimitiveRawPointerMap_hpp
#define PrimitiveRawPointerMap_AVAILABLE

#include "RawPointerMap.hpp"
#include "MapIterator.hpp"

#ifdef PrimitiveRawPointerMap_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"

	#define PrimitiveRawPointerMapLog(location,method,type,mns) ame_Log((void*)this,location,"PrimitiveRawPointerMap",method,type,mns)
	#define const_PrimitiveRawPointerMapLog(location,method,type,mns) ame_Log((void*)this,location,"PrimitiveRawPointerMap",method,type,mns)
#else
	#ifdef PrimitiveRawPointerMap_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"

		#define PrimitiveRawPointerMapLog(location,method,type,mns) ame_LogDebug((void*)this,location,"PrimitiveRawPointerMap",method,type)
		#define const_PrimitiveRawPointerMapLog(location,method,type,mns)
	#else
		#define PrimitiveRawPointerMapLog(location,method,type,mns)
		#define const_PrimitiveRawPointerMapLog(location,method,type,mns)
	#endif
#endif

namespace ame{

template <class K,class V>
class PrimitiveRawPointerMap : virtual public RawPointerMap<K,V>{
    public:

		PrimitiveRawPointerMap(){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "Constructor", "println", "");
			PrimitiveRawPointerMapLog(ame_Log_EndMethod, "Constructor", "println", "");
		}

		PrimitiveRawPointerMap(const PrimitiveRawPointerMap<K,V>& c_map){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "Constructor", "println", "");
			this->setOwner(false);
			this->expandLocal(c_map.getPosition());

			for(int x = 0; x < c_map.getPosition(); x++){
				K* k = c_map.getKeyByPosition(x);
				V* v = c_map.getValueByPosition(x);
				this->addPointers(k,v);
				c_map->setMapEntryByPosition(x, MapEntry<K,V>());
			}
			PrimitiveRawPointerMapLog(ame_Log_EndMethod, "Constructor", "println", "");
		}

		PrimitiveRawPointerMap(int c_size){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "Constructor", "println", "");
			this->expandLocal(c_size);
			PrimitiveRawPointerMapLog(ame_Log_EndMethod, "Constructor", "println", "");
		}

		PrimitiveRawPointerMap(int c_size, bool c_key_own, bool c_value_own, bool c_reorder){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "Constructor", "println", "");
			this->setKeyOwner(c_key_own);
			this->setValueOwner(c_value_own);
			this->expandLocal(c_size);
			m_reorder = c_reorder;
			PrimitiveRawPointerMapLog(ame_Log_EndMethod, "Constructor", "println", "");
		}

		virtual ~PrimitiveRawPointerMap(){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "Destructor", "println", "");
			if(this->m_keys != nullptr && this->m_values != nullptr){
				PrimitiveRawPointerMapLog(ame_Log_Statement, "Destructor", "println", "this->m_keys != nullptr && this->m_values != nullptr");
				if(this->hasOwner()){
					PrimitiveRawPointerMapLog(ame_Log_StartMethod, "Destructor", "println", "this->m_owner");
					for(int x = 0; x < this->getPosition(); x++){
						if(this->m_keys[x] != nullptr && this->isKeyOwner()){
							delete this->m_keys[x];
						}
						if(this->m_values[x] != nullptr && this->isValueOwner()){
							delete this->m_values[x];
						}
					}
					PrimitiveRawPointerMapLog(ame_Log_StartMethod, "Destructor", "println", "after deleting");
				}
				this->setPosition(0);
				this->setSize(0);
				delete[] this->m_keys;
				delete[] this->m_values;
				this->m_keys = nullptr;
				this->m_values = nullptr;
			}
			PrimitiveRawPointerMapLog(ame_Log_EndMethod, "Destructor", "println", "");
		}

		virtual bool isEmpty()const{
			const_PrimitiveRawPointerMapLog(ame_Log_StartMethod, "isEmpty", "println", "");
			const_PrimitiveRawPointerMapLog(ame_Log_EndMethod, "isEmpty", "println", "");
			return this->getPosition() == 0 || this->m_keys == nullptr || this->m_values == nullptr;
		}

		virtual MapEntry<K,V> addPointers(K* a_key, V* a_value){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "addPointers", "println", "");
			if(this->isEmpty()){
				this->expandLocal(this->m_expandSize);
			}
			if(this->getPosition() >= this->getSize()){
				this->expandLocal(this->m_expandSize);
			}
			if(this->getPosition() >= this->getSize()){
				if(a_key != nullptr && this->isKeyOwner()){
					delete a_key;
				}
				if(a_value != nullptr && this->isValueOwner()){
					delete a_value;
				}
				return MapEntry<K,V>();
			}
			this->m_keys[this->getPosition()] = a_key;
			this->m_values[this->getPosition()] = a_value;
			this->incrementPosition();
			PrimitiveRawPointerMapLog(ame_Log_EndMethod, "addPointers", "println", "");
			return MapEntry<K,V>(a_key, a_value);
		}

		virtual MapEntry<K,V> addMapEntry(MapEntry<K,V> a_map_entry){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "addMapEntry", "println", "");
			if(this->isEmpty()){
				this->expandLocal(this->m_expandSize);
			}
			if(this->getPosition() >= this->getSize()){
				this->expandLocal(this->m_expandSize);
			}
			if(this->getPosition() >= this->getSize()){
				if(a_map_entry.getKey() != nullptr && this->isKeyOwner()){
					a_map_entry.deleteKeyEntry();
				}
				if(a_map_entry.getValue() != nullptr && this->isValueOwner()){
					a_map_entry.deleteValueEntry();
				}
				PrimitiveRawPointerMapLog(ame_Log_EndMethod, "addMapEntry", "println", "");
				return MapEntry<K,V>();
			}
			this->m_keys[this->getPosition()] = a_map_entry.getKey();
			this->m_values[this->getPosition()] = a_map_entry.getValue();
			this->incrementPosition();
			PrimitiveRawPointerMapLog(ame_Log_EndMethod, "addMapEntry", "println", "");
			return MapEntry<K,V>(a_map_entry);
		}

		virtual MapEntry<K,V> setPointers(K* a_key, V* a_value){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "setPointers", "println", "");
			int i_index = this->getKeyIndexByPointer(a_key);
			if(i_index == -1){
				PrimitiveRawPointerMapLog(ame_Log_EndMethod, "setPointers", "println", "");
				return MapEntry<K,V>();
			}
			PrimitiveRawPointerMapLog(ame_Log_EndMethod, "setPointers", "println", "");
			return this->setValuePointerByPosition(i_index, a_value);
		}

		virtual MapEntry<K,V> setMapEntry(MapEntry<K,V> a_map_entry){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "setMapEntry", "println", "");
			int i_index = this->getKeyIndexByPointer(a_map_entry.getKey());
			if(i_index == -1){
				PrimitiveRawPointerMapLog(ame_Log_EndMethod, "setMapEntry", "println", "");
				return MapEntry<K,V>();
			}
			PrimitiveRawPointerMapLog(ame_Log_EndMethod, "setMapEntry", "println", "");
			return this->setMapEntryByPosition(i_index, a_map_entry);
		}

		virtual MapEntry<K,V> setKeyPointerByPosition(int a_position, K* a_key){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "setKeyPointerByPosition", "println", "");
			if(a_position >= this->getPosition()){
				if(a_key != nullptr && this->isKeyOwner()){
					delete a_key;
				}
				PrimitiveRawPointerMapLog(ame_Log_EndMethod, "setKeyPointerByPosition", "println", "");
				return MapEntry<K,V>();
			}
			MapEntry<K,V> i_entry = this->getMapEntryByPosition(a_position);
			K* i_key = i_entry.getKey();
			if(a_key == i_key){
				PrimitiveRawPointerMapLog(ame_Log_EndMethod, "setKeyPointerByPosition", "println", "");
				return i_entry;
			}
			if(this->isKeyOwner() && i_key != nullptr){
				delete i_key;
			}
			this->m_keys[a_position] = a_key;
			PrimitiveRawPointerMapLog(ame_Log_EndMethod, "setKeyPointerByPosition", "println", "");
			return MapEntry<K,V>(a_key, i_entry.getValue());
		}

		virtual MapEntry<K,V> setValuePointerByPosition(int a_position, V* a_value){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "setValuePointerByPosition", "println", "");
			if(a_position >= this->getPosition()){
				if(a_value != nullptr && this->isValueOwner()){
					delete a_value;
				}
				PrimitiveRawPointerMapLog(ame_Log_EndMethod, "setValuePointerByPosition", "println", "");
				return MapEntry<K,V>();
			}
			MapEntry<K,V> i_entry = this->getMapEntryByPosition(a_position);
			V* i_value = i_entry.getValue();
			if(a_value == i_value){
				PrimitiveRawPointerMapLog(ame_Log_EndMethod, "setValuePointerByPosition", "println", "");
				return i_entry;
			}
			if(this->isValueOwner() && i_value != nullptr){
				delete i_value;
			}
			this->m_values[a_position] = a_value;
			PrimitiveRawPointerMapLog(ame_Log_EndMethod, "setValuePointerByPosition", "println", "");
			return MapEntry<K,V>(i_entry.getKey(), a_value);
		}

		virtual MapEntry<K,V> setMapEntryByPosition(int a_position, MapEntry<K,V> a_map_entry){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "setMapEntryByPosition", "println", "");
			if(a_position >= this->getPosition()){
				if(a_map_entry.getKey() != nullptr && this->isKeyOwner()){
					a_map_entry.deleteKeyEntry();
				}
				if(a_map_entry.getValue() != nullptr && this->isValueOwner()){
					a_map_entry.deleteValueEntry();
				}
				PrimitiveRawPointerMapLog(ame_Log_EndMethod, "setMapEntryByPosition", "println", "a_position >= this->getPosition()");
				return MapEntry<K,V>();
			}
			MapEntry<K,V> i_entry = this->getMapEntryByPosition(a_position);
			K* i_key = i_entry.getKey();
			V* i_value = i_entry.getValue();
			if(this->hasOwner()){
				PrimitiveRawPointerMapLog(ame_Log_Statement, "setMapEntryByPosition", "println", "this->isOwner()");
				if(i_key != nullptr && i_key != a_map_entry.getKey() && this->isKeyOwner()){
					PrimitiveRawPointerMapLog(ame_Log_Statement, "setMapEntryByPosition", "println", "i_key != nullptr && i_key != a_map_entry.getKey()");
					delete i_key;
				}
				if(i_value != nullptr && i_value != a_map_entry.getValue() && this->isValueOwner()){
					PrimitiveRawPointerMapLog(ame_Log_Statement, "setMapEntryByPosition", "println", "i_value != nullptr && i_value != a_map_entry.getValue()");
					delete i_value;
				}
			}
			this->m_keys[a_position] = a_map_entry.getKey();
			this->m_values[a_position] = a_map_entry.getValue();
			PrimitiveRawPointerMapLog(ame_Log_EndMethod, "setMapEntryByPosition", "println", "");
			return a_map_entry;
		}

		virtual bool containPairPointers(K* a_key, V* a_value){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "containPairPointers", "println", "");
			for(int x = 0; x < this->getPosition(); x++){
				if(this->m_keys[x] == a_key && this->m_values[x] == a_value){
					PrimitiveRawPointerMapLog(ame_Log_EndMethod, "containPairPointers", "println", "");
					return true;
				}
			}
			PrimitiveRawPointerMapLog(ame_Log_EndMethod, "containPairPointers", "println", "");
			return false;
		}

		virtual bool containMapEntry(MapEntry<K,V> a_map_entry){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "containMapEntry", "println", "");
			for(int x = 0; x < this->getPosition(); x++){
				if(this->m_keys[x] == a_map_entry.getKey() && this->m_values[x] == a_map_entry.getValue()){
					PrimitiveRawPointerMapLog(ame_Log_EndMethod, "containMapEntry", "println", "");
					return true;
				}
			}
			PrimitiveRawPointerMapLog(ame_Log_EndMethod, "containMapEntry", "println", "");
			return false;
		}

		virtual bool containKeyByPointer(K* a_key){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "containKeyByPointer", "println", "");
			for(int x = 0; x < this->getPosition(); x++){
				if(this->m_keys[x] == a_key){
					PrimitiveRawPointerMapLog(ame_Log_EndMethod, "containKeyByPointer", "println", "");
					return true;
				}
			}
			PrimitiveRawPointerMapLog(ame_Log_EndMethod, "containKeyByPointer", "println", "");
			return false;
		}

		virtual bool containValueByPointer(V* a_value){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "containValueByPointer", "println", "");
			for(int x = 0; x < this->getPosition(); x++){
				if(this->m_values[x] == a_value){
					PrimitiveRawPointerMapLog(ame_Log_EndMethod, "containValueByPointer", "println", "");
					return true;
				}
			}
			PrimitiveRawPointerMapLog(ame_Log_EndMethod, "containValueByPointer", "println", "");
			return false;
		}

		virtual V* getValueByPointer(K* a_key){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "getValueByPointer", "println", "");
			for(int x = 0; x < this->getPosition(); x++){
				if(this->m_keys[x] == a_key){
					PrimitiveRawPointerMapLog(ame_Log_EndMethod, "getValueByPointer", "println", "");
					return this->m_values[x];
				}
			}
			PrimitiveRawPointerMapLog(ame_Log_EndMethod, "getValueByPointer", "println", "");
			return nullptr;
		}

		virtual V* getValueByPosition(int a_position) const{
			const_PrimitiveRawPointerMapLog(ame_Log_StartMethod, "getValueByPosition", "println", "");
			if(a_position >= this->getPosition() || this->isEmpty()){
				const_PrimitiveRawPointerMapLog(ame_Log_EndMethod, "getValueByPosition", "println", "");
				return nullptr;
			}
			const_PrimitiveRawPointerMapLog(ame_Log_EndMethod, "getValueByPosition", "println", "");
			return this->m_values[a_position];
		}

		virtual MapEntry<K,V> getMapEntryByPosition(int a_position) const{
			const_PrimitiveRawPointerMapLog(ame_Log_StartMethod, "getMapEntryByPosition", "println", "");
			if(a_position >= this->getPosition()){
				const_PrimitiveRawPointerMapLog(ame_Log_EndMethod, "getMapEntryByPosition", "println", "a_position >= this->getPosition()");
				return MapEntry<K,V>();
			}
			const_PrimitiveRawPointerMapLog(ame_Log_EndMethod, "getMapEntryByPosition", "println", a_position);
			return MapEntry<K,V>(this->m_keys[a_position], this->m_values[a_position]);
		}

		virtual K* getKeyByPosition(int a_position) const{
			const_PrimitiveRawPointerMapLog(ame_Log_StartMethod, "getKeyByPosition", "println", "");
			if(a_position >= this->getPosition()){
				PrimitiveRawPointerMapLog(ame_Log_EndMethod, "getKeyByPosition", "println", "");
				return nullptr;
			}
			const_PrimitiveRawPointerMapLog(ame_Log_EndMethod, "getKeyByPosition", "println", "");
			return this->m_keys[a_position];
		}

		virtual K* getKeyByPointer(V* a_value){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "getKeyByPointer", "println", "");
			for(int x = 0; x < this->getPosition(); x++){
				if(this->m_values[x] == a_value){
					PrimitiveRawPointerMapLog(ame_Log_EndMethod, "getKeyByPointer", "println", "");
					return this->m_keys[x];
				}
			}
			PrimitiveRawPointerMapLog(ame_Log_EndMethod, "getKeyByPointer", "println", "");
			return nullptr;
		}

		virtual void reset(){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "reset", "println", "");
			this->setPosition(0);
			PrimitiveRawPointerMapLog(ame_Log_EndMethod, "reset", "println", "");
		}

		virtual void resetDelete(){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "resetDelete", "println", "");
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "resetDelete", "println", "this->getPosition()");
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "resetDelete", "println", this->getPosition());
			for(int x = 0; x < this->getPosition(); x++){
				PrimitiveRawPointerMapLog(ame_Log_StartMethod, "resetDelete", "println", "this->isOwner()");
				PrimitiveRawPointerMapLog(ame_Log_StartMethod, "resetDelete", "println", this->isOwner());
				if(this->hasOwner()){
					PrimitiveRawPointerMapLog(ame_Log_StartMethod, "resetDelete", "println", "deleting index: ");
					PrimitiveRawPointerMapLog(ame_Log_StartMethod, "resetDelete", "println", x);
					if(!this->isKeyOwner()){
						delete this->m_keys[x];
					}
					if(!this->isValueOwner()){
						delete this->m_values[x];
					}
				}
				this->m_keys[x] = nullptr;
				this->m_values[x] = nullptr;
			}
			this->setPosition(0);
			PrimitiveRawPointerMapLog(ame_Log_EndMethod, "resetDelete", "println", "");
		}

		virtual void resetDeleteKey(){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "resetDeleteKey", "println", "");
			for(int x = 0; x < this->getPosition(); x++){
				if(this->isKeyOwner()){
					delete this->m_keys[x];
				}
				this->m_keys[x] = nullptr;
			}
			PrimitiveRawPointerMapLog(ame_Log_EndMethod, "resetDeleteKey", "println", "");
		}

		virtual void resetDeleteValue(){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "resetDeleteValue", "println", "");
			for(int x = 0; x < this->getPosition(); x++){
				if(this->isValueOwner()){
					delete this->m_values[x];
				}
				this->m_values[x] = nullptr;
			}
			PrimitiveRawPointerMapLog(ame_Log_EndMethod, "resetDeleteValue", "println", "");
		}

		virtual MapEntry<K,V> removeByKeyPointer(K* a_key){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "removeByKeyPointer", "println", "");
			if(this->isEmpty()){
				PrimitiveRawPointerMapLog(ame_Log_EndMethod, "removeByKeyPointer", "println", "");
				return MapEntry<K,V>();
			}
			int i_position = 0;
			for(int x = 0; x < this->getPosition(); x++){
				if(a_key == this->m_keys[x]){
					i_position = x;
					break;
				}
			}
			PrimitiveRawPointerMapLog(ame_Log_EndMethod, "removeByKeyPointer", "println", "");
			return this->removeByPosition(i_position);
		}

		virtual MapEntry<K,V> removeByValuePointer(V* a_value){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "removeByValuePointer", "println", "");
			if(this->isEmpty()){
				PrimitiveRawPointerMapLog(ame_Log_EndMethod, "removeByValuePointer", "println", "");
				return MapEntry<K,V>();
			}
			int i_position = 0;
			for(int x = 0; x < this->getPosition(); x++){
				if(a_value == this->m_values[x]){
					i_position = x;
					break;
				}
			}
			PrimitiveRawPointerMapLog(ame_Log_EndMethod, "removeByValuePointer", "println", "");
			return this->removeByPosition(i_position);
		}

		virtual MapEntry<K,V> removeByPosition(int a_position){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "removeByPosition", "println", "");
			if(a_position >= this->getPosition() || this->isEmpty() || a_position < 0){
				PrimitiveRawPointerMapLog(ame_Log_EndMethod, "removeByPosition", "println", "");
				return MapEntry<K,V>();
			}
			K* i_key = this->m_keys[a_position];
			V* i_value = this->m_values[a_position];
			this->m_keys[a_position] = nullptr;
			this->m_values[a_position] = nullptr;
			int i_iteration = this->getPosition();
			this->decrementPosition();
			if(!this->m_reorder){
				PrimitiveRawPointerMapLog(ame_Log_EndMethod, "removeByPosition", "println", "");
				return MapEntry<K,V>(i_key, i_value);
			}
			for(int x = a_position + 1; x < i_iteration; x++){
				this->m_keys[x - 1] = this->m_keys[x];
				this->m_values[x - 1] = this->m_values[x];
			}
			PrimitiveRawPointerMapLog(ame_Log_EndMethod, "removeByPosition", "println", "");
			return MapEntry<K,V>(i_key, i_value);
		}

		virtual int getKeyIndexByPointer(K* a_key){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "getKeyIndexByPointer", "println", "");
			for(int x = 0; x < this->getPosition(); x++){
				if(a_key == this->m_keys[x]){
					PrimitiveRawPointerMapLog(ame_Log_EndMethod, "getKeyIndexByPointer", "println", x);
					return x;
				}
			}
			PrimitiveRawPointerMapLog(ame_Log_EndMethod, "getKeyIndexByPointer", "println", "return -1");
			return -1;
		}

		virtual int getIndexByPointer(V* a_value){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "getIndexByPointer", "println", "");
			for(int x=0; x < this->getPosition(); x++){
				if(a_value == this->m_values[x]){
					PrimitiveRawPointerMapLog(ame_Log_EndMethod, "getIndexByPointer", "println", "");
					return x;
				}
			}
			PrimitiveRawPointerMapLog(ame_Log_EndMethod, "getIndexByPointer", "println", "");
			return -1;
		}

		//resize length by adding more space
		virtual void expandLocal(int a_size){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "expandLocal", "println", "");
			int i_size = this->getSize() + a_size;
			PrimitiveRawPointerMapLog(ame_Log_Statement, "expandLocal", "println", Note("Expanding size: ") + Note(i_size));
			if(i_size <= 1){
				PrimitiveRawPointerMapLog(ame_Log_EndMethod, "expandLocal", "println", "i_size <= 1");
				return;
			}
			K** nK;
			V** nV;
			nK = new K*[i_size];
			nV = new V*[i_size];
			for(int x=0; x < this->getPosition(); x++){
				nK[x] = this->m_keys[x];
				nV[x] = this->m_values[x];
			}
			if(this->m_keys != nullptr){
				delete[] this->m_keys;
			}
			if(this->m_values != nullptr){
				delete[] this->m_values;
			}
			this->m_keys = nK;
			this->m_values = nV;
			this->m_size = i_size;
			PrimitiveRawPointerMapLog(ame_Log_EndMethod, "expandLocal", "println", "");
		}

		virtual PrimitiveRawPointerMap<K,V>* expand(int a_size){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "expand", "println", "");
			int i_size = this->m_size + a_size;
			PrimitiveRawPointerMap<K,V> *nprimitive = new PrimitiveRawPointerMap<K,V>(i_size);
			for(int x = 0; x < this->getPosition(); x++){
				nprimitive->addPointers(this->m_keys[x],this->m_values[x]);
			}
			PrimitiveRawPointerMapLog(ame_Log_EndMethod, "expand", "println", "");
			return nprimitive;
		}

		virtual PrimitiveRawPointerMap<K,V>& operator=(const PrimitiveRawPointerMap<K,V>& a_map){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "operator=", "println", "");
			PrimitiveRawPointerMapLog(ame_Log_EndMethod, "operator=", "println", "");
			return *this;
		}

		virtual bool operator==(const PrimitiveRawPointerMap<K,V>& a_map){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "operator==", "println", "");
			PrimitiveRawPointerMapLog(ame_Log_EndMethod, "operator==", "println", "");
			return false;
		}

		virtual bool operator!=(const PrimitiveRawPointerMap<K,V>& a_map){
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "operator!=", "println", "");
			PrimitiveRawPointerMapLog(ame_Log_StartMethod, "operator!=", "println", "");
			return false;
		}

	protected:
		bool m_reorder = true;
		int m_expandSize = 5;

		K** m_keys = nullptr;
		V** m_values = nullptr;
};

}

#endif
