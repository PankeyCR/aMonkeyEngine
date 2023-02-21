
#ifndef PrimitiveRawPointerList_hpp
#define PrimitiveRawPointerList_hpp
#define PrimitiveRawPointerList_AVAILABLE

#include "RawPointerList.hpp"

#ifdef PrimitiveRawPointerList_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"

	#define PrimitiveRawPointerListLog(location,method,type,mns) ame_Log((void*)this,location,"PrimitiveRawPointerList",method,type,mns)
	#define const_PrimitiveRawPointerListLog(location,method,type,mns)
#else
	#ifdef PrimitiveRawPointerList_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"

		#define PrimitiveRawPointerListLog(location,method,type,mns) ame_LogDebug((void*)this,location,"PrimitiveRawPointerList",method,type)
		#define const_PrimitiveRawPointerListLog(location,method,type,mns)
	#else
		#define PrimitiveRawPointerListLog(location,method,type,mns)
		#define const_PrimitiveRawPointerListLog(location,method,type,mns)
	#endif
#endif

namespace ame{

template<class T>
class PrimitiveRawPointerList : virtual public RawPointerList<T>{
	public:
		PrimitiveRawPointerList(){
			PrimitiveRawPointerListLog(ame_Log_StartMethod, "Constructor", "println", "");
			PrimitiveRawPointerListLog(ame_Log_EndMethod, "Constructor", "println", "");
		}
		
		PrimitiveRawPointerList(const PrimitiveRawPointerList<T>& a_list){
			PrimitiveRawPointerListLog(ame_Log_StartMethod, "Constructor", "println", "");
			this->expandLocal(a_list.getSize());
			for(int x = 0; x < a_list.getPosition(); x++){
				this->addPointer(a_list.getByPosition(x));
			}
			PrimitiveRawPointerListLog(ame_Log_EndMethod, "Constructor", "println", "");
		}
		
		PrimitiveRawPointerList(int c_size){
			PrimitiveRawPointerListLog(ame_Log_StartMethod, "Constructor", "println", "");
			this->expandLocal(c_size);
			PrimitiveRawPointerListLog(ame_Log_EndMethod, "Constructor", "println", "");
		}
		
		PrimitiveRawPointerList(int c_size, bool c_own, int c_reordering){
			PrimitiveRawPointerListLog(ame_Log_StartMethod, "Constructor", "println", "");
			this->m_owner = c_own;
			this->m_reorder = c_reordering;
			this->expandLocal(c_size);
			PrimitiveRawPointerListLog(ame_Log_EndMethod, "Constructor", "println", "");
		}
		
		virtual ~PrimitiveRawPointerList(){
			PrimitiveRawPointerListLog(ame_Log_StartMethod, "Destructor", "println", "");
			if(this->m_values != nullptr){
				if(this->m_owner){
					for(int x=0; x < this->getPosition() ; x++){
						delete this->m_values[x];
					}
				}
				this->setPosition(0);
				this->setSize(0);
				delete[] this->m_values;
				this->m_values = nullptr;
			}
			PrimitiveRawPointerListLog(ame_Log_EndMethod, "Destructor", "println", "");
		}
		

		virtual bool isEmpty()const{
			PrimitiveRawPointerListLog(ame_Log_Statement, "isEmpty", "println", "List Position:");
			PrimitiveRawPointerListLog(ame_Log_Statement, "isEmpty", "println", this->getPosition());
			PrimitiveRawPointerListLog(ame_Log_Statement, "isEmpty", "println", "List Size:");
			PrimitiveRawPointerListLog(ame_Log_Statement, "isEmpty", "println", this->getSize());
			return this->getPosition() == 0 || this->m_values == nullptr;
		}
	
		virtual bool replace(int i, int j){
			PrimitiveRawPointerListLog(ame_Log_StartMethod, "replace", "println", "");
			if(i >= this->getPosition() || j >= this->getPosition()){
				return false;
			}
			T* it = this->m_values[i];
			T* jt = this->m_values[j];
			this->m_values[i] = jt;
			this->m_values[j] = it;
			PrimitiveRawPointerListLog(ame_Log_EndMethod, "replace", "println", "");
			return true;
		}
		
		virtual void addMove(RawPointerList<T>* a_list){
			PrimitiveRawPointerListLog(ame_Log_StartMethod, "addMove", "println", "");
			for(int x = 0; x < a_list->getPosition(); x++){
				T* f_value = a_list->getByPosition(x);
				this->addPointer(f_value);
			}
			PrimitiveRawPointerListLog(ame_Log_EndMethod, "addMove", "println", "");
		}
		
		virtual void addDuplicate(RawPointerList<T>* a_list){
			PrimitiveRawPointerListLog(ame_Log_StartMethod, "addDuplicate", "println", "");
			for(int x = 0; x < a_list->getPosition(); x++){
				T* f_value = a_list->getByPosition(x);
				this->addPointer(f_value);
			}
			PrimitiveRawPointerListLog(ame_Log_EndMethod, "addDuplicate", "println", "");
		}
		
		virtual T* addPointer(T* a_value){
			PrimitiveRawPointerListLog(ame_Log_StartMethod, "addPointer", "println", "");
			PrimitiveRawPointerListLog(ame_Log_Statement, "addPointer", "println", "List Position Before adding:");
			PrimitiveRawPointerListLog(ame_Log_Statement, "addPointer", "println", this->getPosition());
			PrimitiveRawPointerListLog(ame_Log_Statement, "addPointer", "println", "List Size Before adding:");
			PrimitiveRawPointerListLog(ame_Log_Statement, "addPointer", "println", this->getSize());
			if(this->getPosition() >= this->getSize()){
				PrimitiveRawPointerListLog(ame_Log_Statement, "addPointer", "println", "this->getPosition() >= this->getSize()");
				this->expandLocal(this->m_expandSize);
			}
			if(this->getPosition() >= this->getSize()){
				PrimitiveRawPointerListLog(ame_Log_Statement, "addPointer", "println", "this->getPosition() >= this->getSize()");
				if(a_value != nullptr){
					PrimitiveRawPointerListLog(ame_Log_Statement, "addPointer", "println", "deleting pointer");
					delete a_value;
				}
				return nullptr;
			}
			this->m_values[this->getPosition()] = a_value;
			this->incrementPosition();
			
			PrimitiveRawPointerListLog(ame_Log_Statement, "addPointer", "println", "List Position After adding:");
			PrimitiveRawPointerListLog(ame_Log_Statement, "addPointer", "println", this->getPosition());
			PrimitiveRawPointerListLog(ame_Log_Statement, "addPointer", "println", "List Size After adding:");
			PrimitiveRawPointerListLog(ame_Log_Statement, "addPointer", "println", this->getSize());	
			PrimitiveRawPointerListLog(ame_Log_EndMethod, "addPointer", "println", "");
			return a_value;
		}
		
		virtual T* setPointer(int a_position, T* a_value){
			PrimitiveRawPointerListLog(ame_Log_StartMethod, "setPointer", "println", "");
			if(this->isEmpty() || a_position >= this->getPosition()){
				if(a_value != nullptr){
					delete a_value;
				}
				return nullptr;			
			}
			T* i_value = this->getByPosition(a_position);
			if(a_value == i_value){
				return a_value;
			}
			if(this->isOwner() && i_value != nullptr){
				delete i_value;
			}
			this->m_values[a_position] = a_value;
			PrimitiveRawPointerListLog(ame_Log_EndMethod, "setPointer", "println", "");
			return a_value;
		}
		
		virtual T* insertPointer(int a_position, T* a_value){
			PrimitiveRawPointerListLog(ame_Log_StartMethod, "insertPointer", "println", "");
			if(a_position >= this->getPosition()){
				PrimitiveRawPointerListLog(ame_Log_EndMethod, "insertPointer", "println", "a_position >= this->getPosition()");
				return this->addPointer(a_value);
            }
			if(this->getPosition() >= this->getSize()){
				this->expandLocal(this->m_expandSize);
            }
			if(this->getPosition() >= this->getSize()){
				if(a_value != nullptr){
					delete a_value;
				}
				return nullptr;
			}
			T* nVaule;
			T* rVaule = a_value;
			for(int x = a_position; x <= this->getPosition(); x++){
				nVaule = this->m_values[x];
				this->m_values[x] = rVaule;
				rVaule = nVaule;
			}
			this->incrementPosition();
			PrimitiveRawPointerListLog(ame_Log_EndMethod, "insertPointer", "println", "");
			return a_value;
		}
		
		virtual T* getByPointer(T* a_key){
			PrimitiveRawPointerListLog(ame_Log_StartMethod, "getByPointer", "println", "");
			if(this->isEmpty()){
				return nullptr;
			}
			for(int x = 0; x < this->getPosition(); x++){
				if(a_key == this->m_values[x]){
					return a_key;
				}
			}
			PrimitiveRawPointerListLog(ame_Log_EndMethod, "getByPointer", "println", "");
			return nullptr;
		}
		
		virtual T* getByPosition(int x)const{
			PrimitiveRawPointerListLog(ame_Log_StartMethod, "getByPosition", "println", "");
			if(this->isEmpty() || x >= this->getPosition()){
				return nullptr;
			}
			PrimitiveRawPointerListLog(ame_Log_EndMethod, "getByPosition", "println", "");
			return this->m_values[x];
		}
		
		virtual bool containByPointer(T* a_key){
			PrimitiveRawPointerListLog(ame_Log_StartMethod, "containByPointer", "println", "");
			if(this->isEmpty()){
				return false;
			}
			for(int x = 0; x < this->getPosition(); x++){
				if(a_key == this->m_values[x]){
					return true;
				}
			}
			PrimitiveRawPointerListLog(ame_Log_EndMethod, "containByPointer", "println", "");
			return false;
		}
		
		virtual int getIndexByPointer(T* a_key){
			PrimitiveRawPointerListLog(ame_Log_StartMethod, "getIndexByPointer", "println", "");
			if(this->isEmpty()){
				return -1;
			}
			for(int x = 0; x < this->getPosition(); x++){
				if(a_key == this->m_values[x]){
					return x;
				}
			}
			PrimitiveRawPointerListLog(ame_Log_EndMethod, "getIndexByPointer", "println", "");
			return -1;
		}
		
		virtual void reset(){
			PrimitiveRawPointerListLog(ame_Log_StartMethod, "reset", "println", "");
			this->setPosition(0);
			PrimitiveRawPointerListLog(ame_Log_EndMethod, "reset", "println", "");
		}
		
		virtual void resetDelete(){
			PrimitiveRawPointerListLog(ame_Log_StartMethod, "resetDelete", "println", "");
			for(int x = 0; x < this->getPosition(); x++){
				T* f_value = this->m_values[x];
				if(f_value == nullptr){
					PrimitiveRawPointerListLog(ame_Log_Statement, "resetDelete", "println", "this->m_values[x] == nullptr");
					continue;
				}
				if(this->isOwner()){
					PrimitiveRawPointerListLog(ame_Log_Statement, "resetDelete", "println", "this->isOwner()");
					delete f_value;
				}
				this->m_values[x] = nullptr;
			}
			this->setPosition(0);
			PrimitiveRawPointerListLog(ame_Log_EndMethod, "resetDelete", "println", "");
		}
		
		virtual T* removeByPointer(T* a_key){
			PrimitiveRawPointerListLog(ame_Log_StartMethod, "removeByPointer", "println", "");
			int i_position = this->getIndexByPointer(a_key);
			PrimitiveRawPointerListLog(ame_Log_EndMethod, "removeByPointer", "println", "");
			return this->removeByPosition(i_position);
		}
		
		virtual T* removeByPosition(int a_position){
			PrimitiveRawPointerListLog(ame_Log_StartMethod, "removeByPosition", "println", "");
			if(this->isEmpty() || a_position >= this->getPosition()){
				return nullptr;
			}
			T* i_value = this->m_values[a_position];
			this->m_values[a_position] = nullptr;
			if(!this->isInOrder()){
				PrimitiveRawPointerListLog(ame_Log_EndMethod, "removeByPosition", "println", "!this->isInOrder()");
				return i_value;
			}
			int i_iteration = this->getPosition();
			this->decrementPosition();
			for(int x = a_position + 1; x < i_iteration; x++){
				this->m_values[x - 1] = this->m_values[x];
			}
			PrimitiveRawPointerListLog(ame_Log_EndMethod, "removeByPosition", "println", "");
			return i_value;
		}
		
		virtual bool removeFirstIndex(int a_amount){
			PrimitiveRawPointerListLog(ame_Log_StartMethod, "removeFirstIndex", "println", "");
			if(this->isEmpty()){
				return false;
			}
			int i_iteration = 0;
			for(int x = 0; x < a_amount && x < this->getPosition(); x++){
				if(this->isOwner() && this->m_values[x] != nullptr){
					delete this->m_values[x];
				}
				this->m_values[x] = nullptr;
				i_iteration++;
			}
			if(!this->isInOrder()){
				PrimitiveRawPointerListLog(ame_Log_EndMethod, "removeFirstIndex", "println", "!this->isInOrder()");
				return true;
			}
			for(int x = i_iteration; x < this->getPosition(); x++){
				this->m_values[x - i_iteration] = this->m_values[x];
			}
			this->decrementPosition(i_iteration);
			PrimitiveRawPointerListLog(ame_Log_EndMethod, "removeFirstIndex", "println", "");
			return true;
		}
	
		virtual bool removeLastIndex(int a_amount){
			PrimitiveRawPointerListLog(ame_Log_StartMethod, "removeLastIndex", "println", "");
			if(this->isEmpty()){
				return false;
			}
			int i_iteration = 0;
			for(int x = this->getPosition() - 1; x >= this->getPosition() - a_amount && x >= 0; x--){
				if(this->isOwner() && this->m_values[x] != nullptr){
					delete this->m_values[x];
				}
				this->m_values[x] = nullptr;
				i_iteration++;
			}
			if(!this->isInOrder()){
				PrimitiveRawPointerListLog(ame_Log_EndMethod, "removeLastIndex", "println", "!this->isInOrder()");
				return true;
			}
			this->decrementPosition(i_iteration);
			PrimitiveRawPointerListLog(ame_Log_EndMethod, "removeLastIndex", "println", "");
			return true;
		}
		
		//resize length by adding more space
		//bug unkown for template = char on feather m0
		virtual void expandLocal(int a_size){
			PrimitiveRawPointerListLog(ame_Log_StartMethod, "expandLocal", "println", "");
			
			int i_size = this->getSize() + a_size;
			PrimitiveRawPointerListLog(ame_Log_Statement, "expandLocal", "println", "List Position:");
			PrimitiveRawPointerListLog(ame_Log_Statement, "expandLocal", "println", this->getPosition());
			PrimitiveRawPointerListLog(ame_Log_Statement, "expandLocal", "println", "List Size:");
			PrimitiveRawPointerListLog(ame_Log_Statement, "expandLocal", "println", this->getSize());	
			PrimitiveRawPointerListLog(ame_Log_Statement, "expandLocal", "println", "List extra size added:");
			PrimitiveRawPointerListLog(ame_Log_Statement, "expandLocal", "println", a_size);
			PrimitiveRawPointerListLog(ame_Log_Statement, "expandLocal", "println", "List new size:");
			PrimitiveRawPointerListLog(ame_Log_Statement, "expandLocal", "println", i_size);
			if(i_size <= 1){
				PrimitiveRawPointerListLog(ame_Log_EndMethod, "expandLocal", "println", "new size is too small");
				return;
			}
			T **nT;
			nT = new T*[i_size];
			for(int x = 0; x < this->getPosition(); x++){
				PrimitiveRawPointerListLog(ame_Log_Statement, "expandLocal", "println", "iteration:");
				PrimitiveRawPointerListLog(ame_Log_Statement, "expandLocal", "println", x);
				nT[x] = this->m_values[x];
			}
			if(this->m_values != nullptr){
				PrimitiveRawPointerListLog(ame_Log_Statement, "expandLocal", "println", "this->m_values != nullptr");
				delete[] this->m_values;
			}
			this->m_values = nT;
			this->setSize(i_size);
			
			PrimitiveRawPointerListLog(ame_Log_Statement, "expandLocal", "println", "List Position:");
			PrimitiveRawPointerListLog(ame_Log_Statement, "expandLocal", "println", this->getPosition());
			PrimitiveRawPointerListLog(ame_Log_Statement, "expandLocal", "println", "List Size:");
			PrimitiveRawPointerListLog(ame_Log_Statement, "expandLocal", "println", this->getSize());	
			PrimitiveRawPointerListLog(ame_Log_EndMethod, "expandLocal", "println", "");
		}
		
		virtual PrimitiveRawPointerList<T>* expand(int a_size){
			PrimitiveRawPointerListLog(ame_Log_StartMethod, "expand", "println", "");
			int i_size = this->getSize() + a_size;
			PrimitiveRawPointerList<T> *i_list = new PrimitiveRawPointerList<T>(i_size);	
			for(int x = 0; x < this->getPosition(); x++){
				T* f_value = this->getByPosition(x);
				i_list->addPointer(f_value);
			}
			PrimitiveRawPointerListLog(ame_Log_EndMethod, "expand", "println", "");
			return i_list;
		}
	
		////////////////////////////////////////////operator part///////////////////////////////////////////////
		
		
		virtual PrimitiveRawPointerList& operator=(const PrimitiveRawPointerList<T>& a_list){
			PrimitiveRawPointerListLog(ame_Log_StartMethod, "operator=", "println", "");
			this->resetDelete();
			for(int x = 0; x < a_list.getPosition(); x++){
				T* f_value = a_list.getByPosition(x);
				this->addPointer(f_value);
			}
			PrimitiveRawPointerListLog(ame_Log_EndMethod, "operator=", "println", "");
			return *this;
		}

		virtual void reoder(){
			PrimitiveRawPointerListLog(ame_Log_StartMethod, "reoder", "println", "");
			int i_offset = 0;
			for(int x = 0; x < this->getPosition(); x++){
				T* f_value = this->getByPosition(x);
				if(f_value == nullptr){
					continue;
				}
				this->m_values[i_offset] = f_value;
				i_offset++;
			}
			this->setPosition(i_offset);
			PrimitiveRawPointerListLog(ame_Log_EndMethod, "reoder", "println", "");
		}
		
	protected:
		T** m_values = nullptr;
		int m_expandSize = 5;
};

}

#endif