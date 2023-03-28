
#ifndef PrimitiveRawList_hpp
#define PrimitiveRawList_hpp
#define PrimitiveRawList_AVAILABLE

#include "PrimitiveRawPointerList.hpp"
#include "RawList.hpp"
#include "ListIterator.hpp"

#ifdef PrimitiveRawList_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"

	#define PrimitiveRawListLog(location,method,type,mns) ame_Log(this,location,"PrimitiveRawList",method,type,mns)
	#define const_PrimitiveRawListLog(location,method,type,mns)
#else
	#ifdef PrimitiveRawList_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"

		#define PrimitiveRawListLog(location,method,type,mns) ame_LogDebug(this,location,"PrimitiveRawList",method,type)
		#define const_PrimitiveRawListLog(location,method,type,mns)
	#else
		#define PrimitiveRawListLog(location,method,type,mns)
		#define const_PrimitiveRawListLog(location,method,type,mns)
	#endif
#endif

namespace ame{

template<class T>
class PrimitiveRawList : public PrimitiveRawPointerList<T>, virtual public RawList<T>{
	public:
		PrimitiveRawList(){
			PrimitiveRawListLog(ame_Log_StartMethod, "Constructor", "println", "");
			PrimitiveRawListLog(ame_Log_EndMethod, "Constructor", "println", "");
		}
		
		PrimitiveRawList(const PrimitiveRawList<T>& a_list){
			PrimitiveRawListLog(ame_Log_StartMethod, "Constructor", "println", "");
			this->m_values = new T*[a_list.getSize()];
			this->setSize(a_list.getSize());
			for(int x = 0; x < a_list.getPosition(); x++){
				this->addLValue(*a_list.getByPosition(x));
			}
			PrimitiveRawListLog(ame_Log_EndMethod, "Constructor", "println", "");
		}
		
		PrimitiveRawList(int c_size, bool c_own, bool c_reordering) : PrimitiveRawPointerList<T>(c_size, c_own, c_reordering){
			PrimitiveRawListLog(ame_Log_StartMethod, "Constructor", "println", "");
			PrimitiveRawListLog(ame_Log_EndMethod, "Constructor", "println", "");
		}
		
		virtual ~PrimitiveRawList(){
			PrimitiveRawListLog(ame_Log_StartMethod, "Destructor", "println", "");
			PrimitiveRawListLog(ame_Log_EndMethod, "Destructor", "println", "");
		}
		
		virtual T* addLValue(T a_value){
			PrimitiveRawListLog(ame_Log_StartMethod, "addLValue", "println", "");
			T* i_value = new T();
			*i_value = a_value;
			PrimitiveRawListLog(ame_Log_EndMethod, "addLValue", "println", "");
			return this->addPointer(i_value);
		}
		
		virtual T* setLValue(int a_position, T a_value){
			PrimitiveRawListLog(ame_Log_StartMethod, "setLValue", "println", "");
			if(a_position >= this->getPosition()){
				return nullptr;			
			}
			if(this->m_values[a_position] == nullptr){
				this->m_values[a_position] = new T();
			}
			*this->m_values[a_position] = a_value;
			PrimitiveRawListLog(ame_Log_EndMethod, "setLValue", "println", "");
			return this->m_values[a_position];
		}
		
		virtual T* insertLValue(int a_position, T a_value){
			PrimitiveRawListLog(ame_Log_StartMethod, "insertLValue", "println", "");
            if(a_position >= this->getPosition() + 1){
				return nullptr;
            }
			if(this->getSize() <= this->getPosition()){
				this->expandLocal(this->m_expandSize);
			}
			T* nVaule;
			T* rVaule = new T();
			*rVaule = a_value;
			for(int x = a_position; x <= this->getPosition(); x++){
				nVaule = this->m_values[x];
				this->m_values[x] = rVaule;
				rVaule = nVaule;
			}
			this->incrementPosition();
			PrimitiveRawListLog(ame_Log_EndMethod, "insertLValue", "println", "");
			return this->m_values[a_position];
		}
		
		virtual T* getByLValue(T a_key){
			PrimitiveRawListLog(ame_Log_StartMethod, "getByLValue", "println", "");
			if(this->m_values == nullptr){
				return nullptr;
			}
			for(int x = 0; x < this->getPosition(); x++){
				if(this->m_values[x] == nullptr){
					continue;
				}
				if(a_key == *this->m_values[x]){
					return this->m_values[x];
				}
			}
			PrimitiveRawListLog(ame_Log_EndMethod, "getByLValue", "println", "");
			return nullptr;
		}
		
		virtual bool containByLValue(T a_key){
			PrimitiveRawListLog(ame_Log_StartMethod, "containByLValue", "println", "");
			if(this->m_values == nullptr){
				return false;
			}
			for(int x = 0; x < this->getPosition(); x++){
				if(this->m_values[x] == nullptr){
					continue;
				}
				if(a_key == *this->m_values[x]){
					return true;
				}
			}
			PrimitiveRawListLog(ame_Log_EndMethod, "containByLValue", "println", "");
			return false;
		}
		
		virtual int getIndexByLValue(T a_key){
			PrimitiveRawListLog(ame_Log_StartMethod, "getIndexByLValue", "println", "");
			if(this->isEmpty()){
				return -1;
			}
			for(int x = 0; x < this->getPosition(); x++){
				if(this->m_values[x] == nullptr){
					continue;
				}
				if(a_key == *this->m_values[x]){
					return x;
				}
			}
			PrimitiveRawListLog(ame_Log_EndMethod, "getIndexByLValue", "println", "");
			return -1;
		}
		
		virtual T* removeByLValue(T a_key){
			PrimitiveRawListLog(ame_Log_StartMethod, "removeByLValue", "println", "");
			if(this->isEmpty()){
				PrimitiveRawListLog(ame_Log_EndMethod, "removeByLValue", "println", "");
				return nullptr;
			}
			int i_position = -1;
			for(int x = 0; x < this->getPosition(); x++){
				if(this->m_values[x] == nullptr){
					continue;
				}
				if(a_key == *this->m_values[x]){
					i_position = x;
					break;
				}
			}
			PrimitiveRawListLog(ame_Log_EndMethod, "removeByLValue", "println", "");
			return this->removeByPosition(i_position);
		}
	
		////////////////////////////////////////////special removes part///////////////////////////////////////////////
		virtual bool removeAll(T a_value){
			PrimitiveRawListLog(ame_Log_StartMethod, "removeAll", "println", "");
			if(this->isEmpty()){
				PrimitiveRawListLog(ame_Log_EndMethod, "removeAll", "println", "");
				return false;
			}
			bool r_val = false;
			int p_x = 0;
			for(int x = 0; x < this->getPosition(); x++){
				if(a_value == *this->m_values[x]){
					if(this->isOwner()){
						delete this->m_values[x];
					}
					r_val = true;
					this->m_values[x] = nullptr;
				}else{
					if(!this->isInOrder()){
						continue;
					}
					this->m_values[p_x] = this->m_values[x];
					p_x++;
				}
			}
			if(!this->isInOrder()){
				PrimitiveRawListLog(ame_Log_EndMethod, "removeAll", "println", "!this->isInOrder()");
				return r_val;
			}
			this->setPosition(p_x);
			PrimitiveRawListLog(ame_Log_EndMethod, "removeAll", "println", "");
			return r_val;
		}
		
		virtual bool removeFirst(T a_value){
			PrimitiveRawListLog(ame_Log_StartMethod, "removeFirst", "println", "");
			PrimitiveRawListLog(ame_Log_EndMethod, "removeFirst", "println", "");
			return this->removeDeleteByLValue(a_value);
		}
		
		virtual bool removeLast(T a_value){
			PrimitiveRawListLog(ame_Log_StartMethod, "removeLast", "println", "");
			if(this->isEmpty()){
				PrimitiveRawListLog(ame_Log_EndMethod, "removeLast", "println", "");
				return false;
			}
			int i_position = -1;
			for(int x = this->getPosition() - 1; x >= 0; x--){
				if(this->m_values[x] == nullptr){
					continue;
				}
				if(a_value == *this->m_values[x]){
					i_position = x;
					break;
				}
			}
			PrimitiveRawListLog(ame_Log_EndMethod, "removeLast", "println", "");
			return this->removeByPosition(i_position);
		}
		
		virtual T& operator[](int x){
			PrimitiveRawListLog(ame_Log_StartMethod, "operator[]", "println", "");
			// if(this->m_values == nullptr){
				// ame_ErrorHandler(App_Crash_ERROR, "PrimitiveRawList", "operator[]", "null m_values");
			// }
			if(x > this->getPosition() && this->getPosition() > 0){
				return *this->m_values[this->getPosition() - 1];
			}
			if(x < this->getPosition()){
				return *this->m_values[x];
			}
			if(x >= this->getSize()){
				this->expandLocal(this->m_expandSize);
			}
			if(this->getPosition() == x){
				this->incrementPosition();
			}
			this->m_values[x] = new T();
			PrimitiveRawListLog(ame_Log_EndMethod, "operator[]", "println", "");
			return *this->m_values[x];
		}
		
		virtual T operator[](int x) const{
			const_PrimitiveRawListLog(ame_Log_StartMethod, "operator[]", "println", "");
			if(x >= this->getPosition() && this->getPosition() != 0){
				return *this->m_values[this->getPosition() - 1];
			}
			if(x < this->getPosition() && x >= 0){
				return *this->m_values[x];
			}
			const_PrimitiveRawListLog(ame_Log_EndMethod, "operator[]", "println", "");
			return T();
		}
	
		////////////////////////////////////////////operator part///////////////////////////////////////////////
		
		
		virtual PrimitiveRawList<T>& operator=(const PrimitiveRawList<T>& a_list){
			PrimitiveRawListLog(ame_Log_StartMethod, "operator=", "println", "");
			this->resetDelete();
			for(int x = 0; x < a_list.getPosition(); x++){
				this->addLValue(*a_list.getByPosition(x));
			}
			PrimitiveRawListLog(ame_Log_EndMethod, "operator=", "println", "");
			return *this;
		}
		
		virtual bool operator==(const PrimitiveRawList<T>& a_list){
			PrimitiveRawListLog(ame_Log_StartMethod, "operator==", "println", "");
			if(this->getPosition() != a_list.getPosition()){
				return false;
			}
			for(int x = 0; x < a_list.getPosition(); x++){
				T* t_value = this->getByPosition(x);
				T* f_value = a_list.getByPosition(x);
				if(t_value == f_value){
					continue;
				}
				if(t_value != nullptr && t_value != nullptr){
					if(*t_value != *f_value){
						return false;
					}
				}
				this->addLValue(*a_list.getByPosition(x));
			}
			PrimitiveRawListLog(ame_Log_EndMethod, "operator==", "println", "");
			return true;
		}
		
		virtual bool operator!=(const PrimitiveRawList<T>& a_list){
			PrimitiveRawListLog(ame_Log_StartMethod, "operator!=", "println", "");
			if(this->getPosition() != a_list.getPosition()){
				return true;
			}
			for(int x = 0; x < a_list.getPosition(); x++){
				T* t_value = this->getByPosition(x);
				T* f_value = a_list.getByPosition(x);
				if(t_value == f_value){
					continue;
				}
				if(t_value != nullptr && t_value != nullptr){
					if(*t_value == *f_value){
						return false;
					}
				}
				this->addLValue(*a_list.getByPosition(x));
			}
			PrimitiveRawListLog(ame_Log_EndMethod, "operator!=", "println", "");
			return true;
		}
	
		////////////////////////////////////////////Iterator part///////////////////////////////////////////////
		
		ListIterator<T> begin(){
			PrimitiveRawListLog(ame_Log_StartMethod, "begin", "println", "");
			PrimitiveRawListLog(ame_Log_EndMethod, "begin", "println", "");
			return ListIterator<T>(this, 0, this->getPosition());
		}
		
		ListIterator<T> end(){
			PrimitiveRawListLog(ame_Log_StartMethod, "end", "println", "");
			PrimitiveRawListLog(ame_Log_EndMethod, "end", "println", "");
			return ListIterator<T>(this, this->getPosition(), this->getPosition());
		}
		
	protected:
};

}

#endif