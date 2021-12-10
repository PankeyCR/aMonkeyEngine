
#include "ame_Level.hpp"

#if defined(ame_untilLevel_1)

#ifndef ArrayList_hpp
#define ArrayList_hpp

#include "ListIterator.hpp"
#include "cppObject.hpp"
#include "List.hpp"

namespace ame{

template <class T,int size=20>
class ArrayList : public List<T>{
	private:

	public:
	// typedef const_ArrayIterator const_iterator;
	
	int pos;
	T values[size];

	ArrayList(){
		pos=0;
	}
	
	ArrayList(const ArrayList<T,size>& l){
		pos=0;
		for(int x=0; x < l.getPosition(); x++){
			this->addLValue(l.values[x]);
		}
	}

	ArrayList(T t[],int s){
		pos=0;
		for(int x=0; x<s; x++){
			this->addLValue(t[x]);
		}
	}
	virtual ~ArrayList(){}

	bool isEmpty()const{
		return pos==0;
	}

	void setPosition(int p){
		pos=p;
	}

	int getPosition()const{
		return pos;
	}

	int getSize()const{
		return size;
	}

	T *getByPosition(int x)const{
		if(x >= pos){
			return nullptr;
		}
		return const_cast<T*>(&values[x]);
	}
	
	virtual bool replace(int i, int j){
		if(i >= pos || j >= pos){
			return false;
		}
		T it = values[i];
		T jt = values[j];
		values[i] = jt;
		values[j] = it;
		return true;
	}

	void addList(RawList<T> *list){
		if(list == nullptr){
			return;
		}
		for(int x=0; x < list->getPosition() ; x++){
			values[pos] = *list->getByPosition(x);
			pos++;
		}
	}
	
	template<class... args>
	void addPack(args... x){
		T array[] = {x...};
		//for(const T &a : array){
		for(T a : array){
			addLValue(a);
		}
	}

	template<class... Args>
	T* addParameters(Args... args){
		if(pos >= size){
			return nullptr;
		}
		values[pos] = T(args...);
		pos++;
		return &values[pos-1];
	}

	T* addPointer(T *value){
		if(pos >= size){
			delete value;
			return nullptr;
		}
		values[pos] = *value;
		delete value;
		pos++;
		return &values[pos-1];
	}

	T* addLValue(T value){
		if(pos >= size){
			return nullptr;
		}
		values[pos] = value;
		pos++;
		return &values[pos-1];
	}

	T* setLValue(int position,T value){
		if(position >= size){
			return nullptr;
		}
		values[position] = value;
		return &values[position];
	}

	T* setPointer(int position,T* value){
		if(position >= size){
			return nullptr;
		}
		if(value == nullptr){
			return nullptr;
		}
		values[position] = *value;
		delete value;
		return &values[position];
	}

	T* insertLValue(int position, T value){
		if(position >= size){
			return nullptr;
		}
		if(position >= pos+1){
			return nullptr;
		}
		T nVaule;
		T rVaule = value;
		for(int x = 0; x <= pos; x++){
			if(x >= position){
				nVaule = values[x];
				values[x] = rVaule;
				rVaule = nVaule;
			}
		}
		return &values[position];
	}

	T* insertPointer(int position, T* value){
		if(position >= size){
			return nullptr;
		}
		if(position >= pos+1){
			return nullptr;
		}
		if(value == nullptr){
			return nullptr;
		}
		T nVaule;
		T rVaule = *value;
		for(int x = 0; x <= pos; x++){
			if(x >= position){
				nVaule = values[x];
				values[x] = rVaule;
				rVaule = nVaule;
			}
		}
		return &values[position];
	}

	T *getByPointer(T *key){
		for(int x=0; x < pos; x++){
			if(values[x] == *key ){
				return &values[x];
			}
		}
		return nullptr;
	}

	T* getByLValue(T key){
		for(int x=0; x < pos; x++){
			if(values[x] == key ){
				return &values[x];
			}
		}
		return nullptr;
	}

	bool containByPointer(T* key){
		for(int x=0; x < pos; x++){
			if(values[x] == *key ){
				return true;
			}
		}
		return false;
	}

	bool containByLValue(T key){
		for(int x=0; x < pos; x++){
			if(values[x] == key ){
				return true;
			}
		}
		return false;
	}

	int getIndexByPointer(T* key){
		for(int x=0; x < pos; x++){
			if(values[x] == *key ){
				return x;
			}
		}
		return -1;
	}

	int getIndexByLValue(T key){
		for(int x=0; x < pos; x++){
			if(values[x] == key ){
				return x;
			}
		}
		return -1;
	}

	void reset(){
		pos=0;
	}

	void resetDelete(){
		pos=0;
	}

	T* removeByPointer(T* key){
		T *t = nullptr;
		bool is=false;
		for(int x=0; x < pos; x++){
			if(values[x] == *key ){
				is = true;
			}
		}
		if(is){
			int nv =0;
			for(int x=0; x < pos; x++){
				if(values[x] != *key ){
					values[nv] = values[x];
					nv++;
				}else{
					t = &values[x];
				}
			}
			pos = nv;
		}
		return t;
	}

	T* removeByLValue(T key){
		T *t = nullptr;
		bool is=false;
		for(int x=0; x < pos; x++){
			if(values[x] == key ){
				is = true;
			}
		}
		if(is){
			int nv =0;
			for(int x=0; x < pos; x++){
				if(values[x] != key ){
					values[nv] = values[x];
					nv++;
				}else{
					t = &values[x];
				}
			}
			pos = nv;
		}
		return t;
	}

	T* removeByPosition(int p){
		if(p >= pos){
			return nullptr;
		}
		T* t = nullptr;
		for(int x=0; x < pos; x++){
			if(x == p ){
				t = &values[x];
			}
			if(x > p ){
				values[x-1] = values[x];
			}
		}
		pos--;
		return t;
	}

	void removeDeleteByPointer(T* key){
		bool is=false;
		for(int x=0; x < pos; x++){
			if(values[x] == *key ){
				is = true;
			}
		}
		if(is){
			int nv =0;
			for(int x=0; x < pos; x++){
				if(values[x] != *key ){
					values[nv] = values[x];
					nv++;
				}
			}
			pos = nv;
		}
	}

	void removeDeleteByLValue(T key){
		bool is=false;
		for(int x=0; x < pos; x++){
			if(values[x] == key ){
				is = true;
			}
		}
		if(is){
			int nv =0;
			for(int x=0; x < pos; x++){
				if(values[x] != key ){
					values[nv] = values[x];
					nv++;
				}
			}
			pos = nv;
		}
	}

	void removeDeleteByPosition(int p){
		if(p >= pos){
			return;
		}
		for(int x=0; x < pos; x++){
			if(x > p ){
				values[x-1] = values[x];
			}
		}
		pos--;
	}

	T& operator[](int x){
		if(x >= size){
			return values[size-1];
		}
		if(pos == x){
			pos++;
		}
		return values[x];
	}

	cppObjectClass* getClass(){
		return Class<ArrayList<T,size>>::classType;
	}

	List<T>* clone(){
		List<T>* list = new ArrayList<T,size>();
		for(int xl=0; xl < this->pos; xl++){
			list->addLValue(values[xl]);
		}
		return list;
	}

	List<T>* clone(bool owningMemory){
		List<T>* list = new ArrayList<T,size>();
		for(int xl=0; xl < this->pos; xl++){
			list->addLValue(values[xl]);
		}
		return list;
	}

	ArrayList<T,size>& operator =(const ArrayList<T,size>& t){
		this->reset();
		for(int x=0; x < t.getPosition(); x++){
			this->addLValue(*t.getByPosition(x));
		}
		return *this;
	}

	void operator =(const T a[size]){
		this->reset();
		for(int xtst=0; xtst<size; xtst++){
			this->addLValue(a[xtst]);
		}
	}

	bool operator ==(const ArrayList<T,size>& t){
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
		return true;
	}

	bool operator !=(const ArrayList<T,size>& t){
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
		return false;
	}
	
	////////////////////////////////////////////Iterator part///////////////////////////////////////////////
	
	ListIterator<T> begin(){
	  return ListIterator<T>(this, 0, this->getPosition());
	}
	// const_iterator begin()const;
	
	ListIterator<T> end(){
	  return ListIterator<T>(this, this->getPosition(), this->getPosition());
	}
	// const_iterator end()const;
	
};

}//namespace ame ends

#endif 

#endif 