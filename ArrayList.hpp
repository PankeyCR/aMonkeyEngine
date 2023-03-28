
#ifndef ArrayList_hpp
#define ArrayList_hpp
#define ArrayList_AVAILABLE

#include "ListIterator.hpp"
#include "cppObject.hpp"
#include "List.hpp"
#include "Class.hpp"

#ifdef ArrayList_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"

	#define ArrayListLog(location,method,type,mns) ame_Log(this,location,"ArrayList",method,type,mns)
	#define const_ArrayListLog(location,method,type,mns)
#else
	#ifdef ArrayList_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"

		#define ArrayListLog(location,method,type,mns) ame_LogDebug(this,location,"ArrayList",method,type)
		#define const_ArrayListLog(location,method,type,mns)
	#else
		#define ArrayListLog(location,method,type,mns)
		#define const_ArrayListLog(location,method,type,mns)
	#endif
#endif

namespace ame{

template <class T,int t_size = 20>
class ArrayList : public List<T>{
	protected:
		T  m_values[t_size];

	public:

		ArrayList(){
			ArrayListLog(ame_Log_StartMethod, "Constructor", "println", "");
			this->setOwner(false);
			this->setSize(t_size);
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
		}
		
		ArrayList(const ArrayList<T,t_size>& c_list){
			ArrayListLog(ame_Log_StartMethod, "Constructor", "println", "");
			this->setOwner(false);
			this->setSize(t_size);
			for(int x=0; x < c_list.getPosition(); x++){
				this->addLValue(m_values[t_size]);
			}
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
		}

		ArrayList(T t[],int s){
			ArrayListLog(ame_Log_StartMethod, "Constructor", "println", "");
			this->setOwner(false);
			this->setSize(t_size);
			for(int x = 0; x < s; x++){
				this->addLValue(t[x]);
			}
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
		}
		virtual ~ArrayList(){
			ArrayListLog(ame_Log_StartMethod, "Destructor", "println", "");
			ArrayListLog(ame_Log_EndMethod, "Destructor", "println", "");
		}

		virtual bool isEmpty()const{
			const_ArrayListLog(ame_Log_StartMethod, "isEmpty", "println", "");
			const_ArrayListLog(ame_Log_EndMethod, "isEmpty", "println", "");
			return this->getPosition() == 0;
		}
		
		virtual bool replace(int i, int j){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			if(i >= this->getPosition() || j >= this->getPosition()){
				return false;
			}
			T it =  this->m_values[i];
			T jt =  this->m_values[j];
			this->m_values[i] = jt;
			this->m_values[j] = it;
			ArrayListLog(ame_Log_EndMethod, "replace", "println", "");
			return true;
		}

		virtual void addCopy(RawPointerList<T>* a_list){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			for(int x = 0; x < a_list->getPosition(); x++){
				T* f_value = a_list->getByPosition(x);
				this->addLValue(*f_value);
			}
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
		}
		
		virtual void addMove(RawPointerList<T>* a_list){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			for(int x = 0; x < a_list->getPosition(); x++){
				T* f_value = a_list->getByPosition(x);
				this->addLValue(*f_value);
			}
			a_list->resetDelete();
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
		}
		
		virtual void addDuplicate(RawPointerList<T>* a_list){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			for(int x = 0; x < a_list->getPosition(); x++){
				T* f_value = a_list->getByPosition(x);
				this->addLValue(*f_value);
			}
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
		}

		virtual T* addPointer(T* a_value){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			if(a_value != nullptr){
				return nullptr;
			}
			if(this->getPosition() >= t_size){
				delete a_value;
				return nullptr;
			}
			this->m_values[this->getPosition()] = *a_value;
			delete a_value;
			this->incrementPosition();
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
			return & this->m_values[this->getPosition()-1];
		}

		virtual T* setPointer(int a_position, T* a_value){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			if(a_position >= t_size || a_value == nullptr){
				return nullptr;
			}
			this->m_values[a_position] = *a_value;
			delete a_value;
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
			return & this->m_values[a_position];
		}

		virtual T* insertPointer(int a_position, T* value){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			if(a_position >= t_size){
				return nullptr;
			}
			if(a_position >= this->getPosition()+1){
				return nullptr;
			}
			if(value == nullptr){
				return nullptr;
			}
			T nVaule;
			T rVaule = *value;
			for(int x = a_position; x <= this->getPosition(); x++){
				nVaule =  this->m_values[x];
				this->m_values[x] = rVaule;
				rVaule = nVaule;
			}
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
			return & this->m_values[a_position];
		}

		virtual T* getByPointer(T* a_key){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			for(int x=0; x < this->getPosition(); x++){
				if(this->m_values[x] == *a_key){
					return & this->m_values[x];
				}
			}
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
			return nullptr;
		}

		virtual T *getByPosition(int x)const{
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			if(x >= this->getPosition()){
				return nullptr;
			}
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
			return const_cast<T*>(& this->m_values[x]);
		}

		virtual bool containByPointer(T* a_key){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			for(int x = 0; x < this->getPosition(); x++){
				if(this->m_values[x] == *a_key){
					return true;
				}
			}
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
			return false;
		}

		virtual int getIndexByPointer(T* a_key){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			for(int x=0; x < this->getPosition(); x++){
				if( this->m_values[x] == *a_key ){
					return x;
				}
			}
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
			return -1;
		}

		virtual void reset(){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			this->setPosition(0);
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
		}

		virtual void resetDelete(){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			this->setPosition(0);
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
		}

		virtual T* removeByPointer(T* key){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			T *t = nullptr;
			bool is=false;
			for(int x=0; x < this->getPosition(); x++){
				if( this->m_values[x] == *key ){
					is = true;
				}
			}
			if(is){
				int nv =0;
				for(int x=0; x < this->getPosition(); x++){
					if( this->m_values[x] != *key ){
						 this->m_values[nv] =  this->m_values[x];
						nv++;
					}else{
						t = & this->m_values[x];
					}
				}
				this->setPosition(nv);
			}
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
			return t;
		}

		virtual T* removeByPosition(int a_position){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			if(a_position >= this->getPosition()){
				return nullptr;
			}
			T* t = nullptr;
			for(int x=0; x < this->getPosition(); x++){
				if(x == a_position){
					t = & this->m_values[x];
				}
				if(x > a_position){
					 this->m_values[x-1] =  this->m_values[x];
				}
			}
			this->decrementPosition();
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
			return t;
		}
			
		virtual bool removeFirstIndex(int a_amount){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
			return false;
		}

		virtual bool removeLastIndex(int a_amount){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
			return false;
		}

		virtual T* addLValue(T a_value){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			if(this->getPosition() >= t_size){
				return nullptr;
			}
			 this->m_values[this->getPosition()] = a_value;
			this->incrementPosition();
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
			return & this->m_values[this->getPosition()-1];
		}

		virtual T* setLValue(int a_position,T a_value){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			if(a_position >= t_size){
				return nullptr;
			}
			this->m_values[a_position] = a_value;
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
			return &this->m_values[a_position];
		}

		virtual T* insertLValue(int a_position, T a_value){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			if(a_position >= t_size){
				return nullptr;
			}
			if(a_position >= this->getPosition()+1){
				return nullptr;
			}
			T nVaule;
			T rVaule = a_value;
			for(int x = 0; x <= this->getPosition(); x++){
				if(x >= a_position){
					nVaule =  this->m_values[x];
					 this->m_values[x] = rVaule;
					rVaule = nVaule;
				}
			}
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
			return &this->m_values[a_position];
		}

		virtual T* getByLValue(T key){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			for(int x=0; x < this->getPosition(); x++){
				if( this->m_values[x] == key ){
					return & this->m_values[x];
				}
			}
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
			return nullptr;
		}

		virtual bool containByLValue(T key){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			for(int x=0; x < this->getPosition(); x++){
				if( this->m_values[x] == key ){
					return true;
				}
			}
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
			return false;
		}

		virtual int getIndexByLValue(T key){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			for(int x=0; x < this->getPosition(); x++){
				if( this->m_values[x] == key ){
					return x;
				}
			}
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
			return -1;
		}

		virtual T* removeByLValue(T key){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			T *t = nullptr;
			bool is=false;
			for(int x = 0; x < this->getPosition(); x++){
				if(this->m_values[x] == key ){
					is = true;
				}
			}
			if(is){
				int nv =0;
				for(int x=0; x < this->getPosition(); x++){
					if(this->m_values[x] != key ){
						this->m_values[nv] =  this->m_values[x];
						nv++;
					}else{
						t = & this->m_values[x];
					}
				}
				this->setPosition(nv);
			}
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
			return t;
		}
		
		////////////////////////////////////////////special removes part///////////////////////////////////////////////
		virtual bool removeAll(T value){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			bool r_val = false;
			int p_x = 0;
			// Serial.println(pos);
			for(int x = 0; x < this->getPosition(); x++){
				if(value ==  this->m_values[x]){
					r_val = true;
				}else{
					 this->m_values[p_x] =  this->m_values[x];
					p_x++;
				}
			}
			this->setPosition(p_x);
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
			return r_val;
		}
		
		virtual bool removeFirst(T value){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			bool r_val = false;
			bool r_once = true;
			int p_x = 0;
			for(int x = 0; x < this->getPosition(); x++){
				if(value ==  this->m_values[x] && r_once){
					r_once = false;
					r_val = true;
				}else{
					 this->m_values[p_x] =  this->m_values[x];
					p_x++;
				}
			}
			this->setPosition(p_x);
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
			return r_val;
		}
		
		virtual bool removeLast(T value){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			int r_pos = this->getPosition();
			for(int x = this->getPosition() - 1; x >= 0; x--){
				if(value ==  this->m_values[x]){
					r_pos = x;
					break;
				}
			}
			
			bool r_val = false;
			bool r_once = true;
			int p_x = r_pos;
			for(int x = p_x; x < this->getPosition(); x++){
				if(value ==  this->m_values[x] && r_once){
					r_once = false;
					r_val = true;
				}else{
					 this->m_values[p_x] =  this->m_values[x];
					p_x++;
				}
			}
			this->setPosition(p_x);
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
			return r_val;
		}

		virtual T& operator[](int x){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			if(x > this->getPosition()){
				return  this->m_values[this->getPosition()-1];
			}
			if(this->getPosition() == x){
				this->incrementPosition();
			}
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
			return  this->m_values[x];
		}

		virtual T operator[](int x) const{
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			if(x >= this->getPosition()){
				return  this->m_values[this->getPosition() - 1];
			}
			if(x < this->getPosition()){
				return  this->m_values[x];
			}
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
			return T();
		}
		
		////////////////////////////////////////////cppObject part///////////////////////////////////////////////

		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
			return Class<ArrayList<T,t_size>>::classType;
		}
		#endif

		virtual List<T>* clone(){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			List<T>* list = new ArrayList<T,t_size>();
			for(int x = 0; x < this->getPosition(); x++){
				list->addLValue(this->m_values[x]);
			}
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
			return list;
		}

		virtual List<T>* clone(bool owningMemory){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			List<T>* list = new ArrayList<T,t_size>();
			for(int x = 0; x < this->getPosition(); x++){
				list->addLValue(this->m_values[x]);
			}
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
			return list;
		}
		
		

		////////////////////////////////////////////operator part///////////////////////////////////////////////

		virtual ArrayList<T,t_size>& operator =(const ArrayList<T,t_size>& t){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			this->reset();
			for(int x=0; x < t.getPosition(); x++){
				this->addLValue(*t.getByPosition(x));
			}
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
			return *this;
		}

		virtual void operator=(const T a_array[t_size]){
			ArrayListLog(ame_Log_StartMethod, "replace", "println", "");
			this->reset();
			for(int x = 0; x < t_size; x++){
				this->addLValue(a_array[x]);
			}
			ArrayListLog(ame_Log_EndMethod, "Constructor", "println", "");
		}

		virtual bool operator ==(const ArrayList<T,t_size>& t){
			ArrayListLog(ame_Log_StartMethod, "operator ==", "println", "");
			if(t.getPosition() != this->getPosition()){
				return false;
			}
			for(int x = 0; x < this->getPosition(); x++){
				T v = *this->getByPosition(x);
				T v2 = *t.getByPosition(x);
				if(v != v2){
					return false;
				}
			}
			ArrayListLog(ame_Log_EndMethod, "operator ==", "println", "");
			return true;
		}

		virtual bool operator !=(const ArrayList<T,t_size>& t){
			ArrayListLog(ame_Log_StartMethod, "operator !=", "println", "");
			if(t.getPosition() != this->getPosition()){
				return true;
			}
			for(int x = 0; x < this->getPosition(); x++){
				T v = *this->getByPosition(x);
				T v2 = *t.getByPosition(x);
				if(v != v2){
					return true;
				}
			}
			ArrayListLog(ame_Log_EndMethod, "operator !=", "println", "");
			return false;
		}
		
		////////////////////////////////////////////Iterator part///////////////////////////////////////////////
		
		virtual ListIterator<T> begin(){
			ArrayListLog(ame_Log_StartMethod, "begin", "println", "");
			ArrayListLog(ame_Log_EndMethod, "begin", "println", "");
			return ListIterator<T>(this, 0, this->getPosition());
		}
		
		virtual ListIterator<T> end(){
			ArrayListLog(ame_Log_StartMethod, "end", "println", "");
			ArrayListLog(ame_Log_EndMethod, "end", "println", "");
			return ListIterator<T>(this, this->getPosition(), this->getPosition());
		}
	
};

}

#endif
