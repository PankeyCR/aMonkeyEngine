
#ifndef PointerArrayStorage_hpp
#define PointerArrayStorage_hpp
#define PointerArrayStorage_AVAILABLE

#include "MemoryStorage.hpp"

#ifdef PointerArrayStorage_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"

	#define PointerArrayStorageLog(location,method,type,mns) ame_Log((void*)this,location,"PointerArrayStorage",method,type,mns)
#else
	#ifdef PointerArrayStorage_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"

		#define PointerArrayStorageLog(location,method,type,mns) ame_LogDebug((void*)this,location,"PointerArrayStorage",method,type)
	#else
		#define PointerArrayStorageLog(location,method,type,mns)
	#endif
#endif

namespace ame{

template<class T>
class PointerArrayStorage : public MemoryStorage<T>{
	public:
		PointerArrayStorage(){
			PointerArrayStorageLog(ame_Log_StartMethod, "Constructor", "println", "");
			PointerArrayStorageLog(ame_Log_EndMethod, "Constructor", "println", "");
		}

		virtual ~PointerArrayStorage(){
			PointerArrayStorageLog(ame_Log_StartMethod, "Destructor", "println", "");
			if(this->m_values == nullptr){
				return;
			}
			for(int x = 0; x < this->getSize(); x++){
				this->removingMemory(this->m_values[x]);
				this->m_values[x] = nullptr;
			}
			this->setSize(0);
			delete[] this->m_values;
			this->m_values = nullptr;
			this->removeManager();
			PointerArrayStorageLog(ame_Log_EndMethod, "Destructor", "println", "");
		}
		
		virtual bool isNull()const{
			PointerArrayStorageLog(ame_Log_StartMethod, "isNull", "println", "");
			PointerArrayStorageLog(ame_Log_EndMethod, "isNull", "println", this->m_values == nullptr);
			return this->m_values == nullptr;
		}
		
		virtual bool isEmpty()const{
			PointerArrayStorageLog(ame_Log_StartMethod, "isEmpty", "println", "");
			PointerArrayStorageLog(ame_Log_Statement, "isEmpty", "println", "List Size:");
			PointerArrayStorageLog(ame_Log_Statement, "isEmpty", "println", this->getSize());
			PointerArrayStorageLog(ame_Log_EndMethod, "isEmpty", "println", this->getSize() == 0 || this->m_values == nullptr);
			return this->getSize() == 0 || this->m_values == nullptr;
		}

		virtual void set(int a_position, T* a_pointer){
			PointerArrayStorageLog(ame_Log_StartMethod, "set", "println", "T* a_pointer");
			PointerArrayStorageLog(ame_Log_StartMethod, "set", "println", "Position: ");
			PointerArrayStorageLog(ame_Log_StartMethod, "set", "println", a_position);
			if(this->isEmpty() && a_position >= this->getSize()){
				PointerArrayStorageLog(ame_Log_EndMethod, "set", "println", "this->isEmpty()");
				return;
			}
			if(this->m_values[a_position] == a_pointer){
				PointerArrayStorageLog(ame_Log_EndMethod, "set", "println", "this->m_values[a_position] == a_value");
				return;
			}
			this->removingMemory(this->m_values[a_position]);
			this->m_values[a_position] = a_pointer;
			this->addingMemory(a_pointer);
			PointerArrayStorageLog(ame_Log_EndMethod, "set", "println", "");
		}

		virtual void set(int a_position, const Pointer<T>& a_pointer){
			PointerArrayStorageLog(ame_Log_StartMethod, "set", "println", "const Pointer<T>& a_pointer");
			this->set(a_position, a_pointer.get());
			PointerArrayStorageLog(ame_Log_EndMethod, "set", "println", "");
		}
		
		virtual Pointer<T> get(int a_position)const{
			PointerArrayStorageLog(ame_Log_StartMethod, "get", "println", "");
			if(this->isEmpty() || a_position >= this->getSize()){
				return Pointer<T>(nullptr, this->m_manager);
			}
			PointerArrayStorageLog(ame_Log_EndMethod, "get", "println", "");
			return Pointer<T>(this->m_values[a_position], this->m_manager);
		}

		virtual bool contain(T* a_value){
			PointerArrayStorageLog(ame_Log_StartMethod, "contain", "println", "");
			if(this->isEmpty()){
				PointerArrayStorageLog(ame_Log_Statement, "contain", "println", "this->isEmpty()");
				PointerArrayStorageLog(ame_Log_EndMethod, "contain", "println", "return false");
				return false;
			}
			for(int x = 0; x < this->getSize(); x++){
				if(a_value == this->m_values[x]){
					PointerArrayStorageLog(ame_Log_Statement, "contain", "println", "a_value == this->m_values[x]");
					PointerArrayStorageLog(ame_Log_EndMethod, "contain", "println", "return true");
					return true;
				}
			}
			PointerArrayStorageLog(ame_Log_EndMethod, "contain", "println", "");
			return false;
		}

		virtual bool contain(const Pointer<T>& a_value){
			PointerArrayStorageLog(ame_Log_StartMethod, "contain", "println", "");
			PointerArrayStorageLog(ame_Log_EndMethod, "contain", "println", "");
			return this->contain(a_value.get());
		}
		
		virtual int getIndex(T* a_value){
			PointerArrayStorageLog(ame_Log_StartMethod, "getIndex", "println", "");
			if(this->isEmpty()){
				PointerArrayStorageLog(ame_Log_EndMethod, "getIndex", "println", "this->isEmpty()");
				return -1;
			}
			for(int x = 0; x < this->getSize(); x++){
				if(a_value == this->m_values[x]){
					PointerArrayStorageLog(ame_Log_EndMethod, "getIndex", "println", "a_value == this->m_values[x]");
					return x;
				}
			}
			PointerArrayStorageLog(ame_Log_EndMethod, "getIndex", "println", "");
			return -1;
		}

		virtual int getIndex(const Pointer<T>& a_value){
			PointerArrayStorageLog(ame_Log_StartMethod, "getIndex", "println", "");
			PointerArrayStorageLog(ame_Log_EndMethod, "getIndex", "println", "");
			return this->getIndex(a_value.get());
		}

		virtual void clear(){
			PointerArrayStorageLog(ame_Log_StartMethod, "clear", "println", "");
			if(this->isEmpty()){
				PointerArrayStorageLog(ame_Log_EndMethod, "clear", "println", "this->isEmpty()");
				return;
			}
			for(int x = 0; x < this->getSize(); x++){
				this->removingMemory(this->m_values[x]);
				this->m_values[x] = nullptr;
			}
			PointerArrayStorageLog(ame_Log_EndMethod, "clear", "println", "");
		}

		virtual bool removeByPointer(T* a_value){
			PointerArrayStorageLog(ame_Log_StartMethod, "removeByPointer", "println", "");
			int i_position = this->getIndex(a_value);
			PointerArrayStorageLog(ame_Log_EndMethod, "removeByPointer", "println", "removed position: ");
			PointerArrayStorageLog(ame_Log_EndMethod, "removeByPointer", "println", i_position);
			if(this->isEmpty() || i_position >= this->getSize() || i_position < 0){
				return false;
			}
			PointerArrayStorageLog(ame_Log_EndMethod, "removeByPointer", "println", "");
			this->removeByPosition(i_position);
			return true;
		}

		virtual bool removeByPointer(const Pointer<T>& a_value){
			PointerArrayStorageLog(ame_Log_StartMethod, "removeByPointer", "println", "");
			PointerArrayStorageLog(ame_Log_EndMethod, "removeByPointer", "println", "");
			return this->removeByPointer(a_value.get());
		}

		virtual Pointer<T> removeByPosition(int a_position){
			PointerArrayStorageLog(ame_Log_StartMethod, "removeByPosition", "println", "");
			if(this->isEmpty() || a_position >= this->getSize() || a_position < 0){
				return nullptr;
			}
			T* i_value = this->m_values[a_position];
			Pointer<T> i_pointer = Pointer<T>(i_value, this->m_manager);
			this->m_values[a_position] = nullptr;
			this->removingMemory(i_value);
			PointerArrayStorageLog(ame_Log_EndMethod, "removeByPosition", "println", "");
			return i_pointer;
		}

		virtual int reorder(){
			PointerArrayStorageLog(ame_Log_StartMethod, "reorder", "println", "");
			if(this->isNull()){
				PointerArrayStorageLog(ame_Log_EndMethod, "clear", "println", "this->isNull()");
				return -1;
			}
			if(this->isEmpty()){
				PointerArrayStorageLog(ame_Log_EndMethod, "clear", "println", "this->isEmpty()");
				return 0;
			}
			int i_offset = 0;
			for(int x = 0; x < this->getSize(); x++){
				T* f_value = this->m_values[x];
				if(f_value == nullptr){
					continue;
				}
				this->m_values[i_offset] = f_value;
				i_offset++;
			}
			PointerArrayStorageLog(ame_Log_EndMethod, "reorder", "println", "");
			return i_offset;
		}

		virtual MemoryStorage<T>* clone()const{
			PointerArrayStorageLog(ame_Log_StartMethod, "clone", "println", "");
			PointerArrayStorage<T>* i_clone = new PointerArrayStorage<T>();
			i_clone->expandLocal(this->getSize());
			for(int x = 0; x < this->getSize(); x++){
				i_clone->set(x, this->get(x));
			}
			PointerArrayStorageLog(ame_Log_EndMethod, "clone", "println", "");
			return i_clone;
		}

		virtual bool expandLocal(int a_size){
			PointerArrayStorageLog(ame_Log_StartMethod, "expandLocal", "println", "");
			
			int i_size = this->getSize() + a_size;
			PointerArrayStorageLog(ame_Log_Statement, "expandLocal", "println", "List Size:");
			PointerArrayStorageLog(ame_Log_Statement, "expandLocal", "println", this->getSize());	
			PointerArrayStorageLog(ame_Log_Statement, "expandLocal", "println", "List extra size added:");
			PointerArrayStorageLog(ame_Log_Statement, "expandLocal", "println", a_size);
			PointerArrayStorageLog(ame_Log_Statement, "expandLocal", "println", "List new size:");
			PointerArrayStorageLog(ame_Log_Statement, "expandLocal", "println", i_size);
			if(i_size <= 1){
				PointerArrayStorageLog(ame_Log_EndMethod, "expandLocal", "println", "new size is too small");
				return false;
			}
			T **nT;
			nT = new T*[i_size];
			for(int x = 0; x < this->getSize(); x++){
				PointerArrayStorageLog(ame_Log_Statement, "expandLocal", "println", "iteration:");
				PointerArrayStorageLog(ame_Log_Statement, "expandLocal", "println", x);
				if(this->m_values != nullptr){
					nT[x] = this->m_values[x];
				}
			}
			for(int x = this->getSize(); x < i_size; x++){
				PointerArrayStorageLog(ame_Log_Statement, "expandLocal", "println", "iteration:");
				PointerArrayStorageLog(ame_Log_Statement, "expandLocal", "println", x);
				nT[x] = nullptr;
			}
			if(this->m_values != nullptr){
				PointerArrayStorageLog(ame_Log_Statement, "expandLocal", "println", "this->m_values != nullptr");
				delete[] this->m_values;
			}
			this->m_values = nT;
			this->setSize(i_size);
			
			PointerArrayStorageLog(ame_Log_Statement, "expandLocal", "println", "List Size:");
			PointerArrayStorageLog(ame_Log_Statement, "expandLocal", "println", this->getSize());	
			PointerArrayStorageLog(ame_Log_EndMethod, "expandLocal", "println", "");
			return true;
		}
	
	protected:
		T** m_values = nullptr;
};

}

#endif