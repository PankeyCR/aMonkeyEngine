
#ifndef CONFIGURATION_Array_hpp
#define CONFIGURATION_Array_hpp

	#include "ame_Enviroment.hpp"

	#if defined(DISABLE_Array)
		#define Array_hpp

		#define IMPLEMENTATION_Array
		#define IMPLEMENTING_Array
	#else
		#if defined(DISABLE_IMPLEMENTATION_Array)
			#define IMPLEMENTATION_Array
			#define IMPLEMENTING_Array
		#endif
	#endif
#endif

#ifndef Array_hpp
#define Array_hpp
#define Array_AVAILABLE

#ifndef DISABLE_IMPLEMENTATION_Array
	#define IMPLEMENTATION_Array IMPLEMENTATION(public Array)
	#define IMPLEMENTING_Array IMPLEMENTING(public Array)
#endif

#include "cppObject.hpp"
#include "ArrayIterator.hpp"
#include "Class.hpp"

#ifdef Array_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"

	#define ArrayLog(location,method,type,mns) ame_Log((void*)this,location,"Array",method,type,mns)
#else
	#ifdef Array_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"

		#define ArrayLog(location,method,type,mns) ame_LogDebug((void*)this,location,"Array",method,type)
	#else
		#define ArrayLog(location,method,type,mns)
	#endif
#endif


namespace ame{

template<class T>
class Array IMPLEMENTATION_cppObject {

	protected:
		T* m_t_value = nullptr;
		int m_pos = 0;
		int m_size = 0;
		int m_expandSize = 0;

    public:
		Array(){
			ArrayLog(ame_Log_StartMethod, "Constructor", "println", "");
			ArrayLog(ame_Log_Statement, "Constructor", "println", "Default Constructor");
			ArrayLog(ame_Log_EndMethod, "Constructor", "println", "");
		}

		template<class... args>
		Array(args... xs){
			ArrayLog(ame_Log_StartMethod, "Constructor", "println", "args... xs");
			T array1[] = {xs...};
			int i_array_length = 0;
			ArrayLog(ame_Log_Statement, "Constructor", "println", "Array Length:");
			ArrayLog(ame_Log_Statement, "Constructor", "println", i_array_length);
			for(const T& a : array1){
			  i_array_length++;
			}
			if(i_array_length != 0){
				T* c_pointer = this->createFilledArray(i_array_length);
				int count = 0;
				if(c_pointer != nullptr){
					for(const T& a : array1){
						c_pointer[count] = a;
						count++;
					}
				}
			}
			ArrayLog(ame_Log_Statement, "Constructor", "println", "Array Position:");
			ArrayLog(ame_Log_Statement, "Constructor", "println", this->getPosition());
			ArrayLog(ame_Log_Statement, "Constructor", "println", "Array Size:");
			ArrayLog(ame_Log_Statement, "Constructor", "println", this->getSize());

			ArrayLog(ame_Log_EndMethod, "Constructor", "println", "");
		}

		Array(const Array<T>& c_array){
			ArrayLog(ame_Log_StartMethod, "Constructor", "println", "");
			ArrayLog(ame_Log_Statement, "Constructor", "println", "const Array& val");
			if(c_array.isEmpty()){
				ArrayLog(ame_Log_EndMethod, "Constructor", "println", "c_array.isEmpty()");
				return;
			}
			int i_array_length = c_array.getPosition();
			ArrayLog(ame_Log_Statement, "Constructor", "println", "Array Length:");
			ArrayLog(ame_Log_Statement, "Constructor", "println", i_array_length);
			this->createArray(i_array_length);
			this->copyPointer(c_array.pointer(), i_array_length);
			this->copyEndValue();
			ArrayLog(ame_Log_Statement, "Constructor", "println", "Array Position:");
			ArrayLog(ame_Log_Statement, "Constructor", "println", this->getPosition());
			ArrayLog(ame_Log_Statement, "Constructor", "println", "Array Size:");
			ArrayLog(ame_Log_Statement, "Constructor", "println", this->getSize());

			ArrayLog(ame_Log_EndMethod, "Constructor", "println", "");
		}

		Array(Array<T>&& c_array){
			ArrayLog(ame_Log_StartMethod, "Constructor", "println", "start");
			ArrayLog(ame_Log_Statement, "Constructor", "println", "Array&& c_array");
			if(c_array.isEmpty()){
				ArrayLog(ame_Log_EndMethod, "Constructor", "println", "c_array.isEmpty()");
				return;
			}
			int i_array_length = c_array.getPosition();
			ArrayLog(ame_Log_Statement, "Constructor", "println", "Array Length:");
			ArrayLog(ame_Log_Statement, "Constructor", "println", i_array_length);
			this->m_pos = c_array.m_pos;
			this->m_size = c_array.m_size;
			this->m_t_value = c_array.m_t_value;
			c_array.m_t_value = nullptr;
			c_array.m_pos = 0;
			c_array.m_size = 0;
			ArrayLog(ame_Log_Statement, "Constructor", "println", "Array Position:");
			ArrayLog(ame_Log_Statement, "Constructor", "println", this->getPosition());
			ArrayLog(ame_Log_Statement, "Constructor", "println", "Array Size:");
			ArrayLog(ame_Log_Statement, "Constructor", "println", this->getSize());

			ArrayLog(ame_Log_EndMethod, "Constructor", "println", "");
		}

		virtual ~Array(){
			ArrayLog(ame_Log_StartMethod, "Destructor", "println", "");
			ArrayLog(ame_Log_Statement, "Destructor", "println", "~Array");
			ArrayLog(ame_Log_Statement, "Destructor", "println", this->getPosition());
			ArrayLog(ame_Log_Statement, "Destructor", "println", this->getSize());
			this->fix();
			this->erase();
			ArrayLog(ame_Log_EndMethod, "Destructor", "println", "");
		}

		virtual int getFreeSpace(int a_position)const{
			ArrayLog(ame_Log_StartMethod, "getFreeSpace", "println", "int a_position");
			int i_addingEndValue = 0;
			if(this->hasEndValue()){
				ArrayLog(ame_Log_Statement, "getFreeSpace", "println", "this->hasEndValue()");
				i_addingEndValue = 1;
			}
			int i_availableSize = this->getSize() - a_position - i_addingEndValue;
			ArrayLog(ame_Log_EndMethod, "getFreeSpace", "println", i_availableSize);
			return i_availableSize;
		}

		virtual int getFreeSpace()const{
			ArrayLog(ame_Log_StartMethod, "getFreeSpace", "println", "");
			int i_addingEndValue = 0;
			if(this->hasEndValue()){
				ArrayLog(ame_Log_Statement, "getFreeSpace", "println", "this->hasEndValue()");
				i_addingEndValue = 1;
			}
			int i_availableSize = this->getSize() - this->getPosition() - i_addingEndValue;
			ArrayLog(ame_Log_EndMethod, "getFreeSpace", "println", i_availableSize);
			return i_availableSize;
		}

		virtual void expandIfNeeded(int a_array_length){
			ArrayLog(ame_Log_StartMethod, "expandIfNeeded", "println", "");
			ArrayLog(ame_Log_Statement, "hasAvailableSize", "println", "Array Position:");
			ArrayLog(ame_Log_Statement, "hasAvailableSize", "println", this->getPosition());
			ArrayLog(ame_Log_Statement, "hasAvailableSize", "println", "Array Size:");
			ArrayLog(ame_Log_Statement, "hasAvailableSize", "println", this->getSize());
			int i_availableSize = this->getFreeSpace();
			if(i_availableSize < a_array_length){
				this->expandLocal(a_array_length + m_expandSize);
			}
			ArrayLog(ame_Log_Statement, "hasAvailableSize", "println", "Array Position:");
			ArrayLog(ame_Log_Statement, "hasAvailableSize", "println", this->getPosition());
			ArrayLog(ame_Log_Statement, "hasAvailableSize", "println", "Array Size:");
			ArrayLog(ame_Log_Statement, "hasAvailableSize", "println", this->getSize());
			ArrayLog(ame_Log_EndMethod, "expandIfNeeded", "println", "");
		}

		virtual bool hasAvailableSize()const{
			ArrayLog(ame_Log_StartMethod, "hasAvailableSize", "println", "");
			ArrayLog(ame_Log_Statement, "hasAvailableSize", "println", "Array Position:");
			ArrayLog(ame_Log_Statement, "hasAvailableSize", "println", this->getPosition());
			ArrayLog(ame_Log_Statement, "hasAvailableSize", "println", "Array Size:");
			ArrayLog(ame_Log_Statement, "hasAvailableSize", "println", this->getSize());
			return this->getFreeSpace() > 0;
		}

		virtual bool hasAvailableSize(int a_size)const{
			ArrayLog(ame_Log_StartMethod, "hasAvailableSize", "println", "int a_size");
			ArrayLog(ame_Log_Statement, "hasAvailableSize", "println", "New Size:");
			ArrayLog(ame_Log_Statement, "hasAvailableSize", "println", a_size);
			ArrayLog(ame_Log_Statement, "hasAvailableSize", "println", "Array Size:");
			ArrayLog(ame_Log_Statement, "hasAvailableSize", "println", this->getSize());
			return this->getFreeSpace(a_size) > 0;
		}

		virtual bool set(int a_position, T a_value){
			ArrayLog(ame_Log_StartMethod, "set", "println", "");
			if(this->isEmpty()){
				return false;
			}
			if(!this->hasAvailableSize(a_position)){
				return false;
			}
			this->m_t_value[a_position] = a_value;
			ArrayLog(ame_Log_EndMethod, "set", "println", "");
			return true;
		}

		virtual bool hasEndValue()const{
			ArrayLog(ame_Log_StartMethod, "endValue", "println", "");
			ArrayLog(ame_Log_EndMethod, "endValue", "println", "");
			return false;
		}

		virtual T endValue()const{
			ArrayLog(ame_Log_StartMethod, "endValue", "println", "");
			ArrayLog(ame_Log_EndMethod, "endValue", "println", "");
			return T();
		}

		virtual void copyEndValue()const{
			ArrayLog(ame_Log_StartMethod, "copyEndValue", "println", "");
			if(this->isEmpty() || !this->hasEndValue()){
				ArrayLog(ame_Log_EndMethod, "copyEndValue", "println", "");
				return;
			}
			if(this->getPosition() >= this->getSize()){
				ArrayLog(ame_Log_EndMethod, "copyEndValue", "println", "");
				return;
			}
			this->m_t_value[this->getPosition()] = this->endValue();
			ArrayLog(ame_Log_EndMethod, "copyEndValue", "println", "");
		}

		virtual void copyEndValue(int a_position)const{
			ArrayLog(ame_Log_StartMethod, "copyEndValue", "println", "");
			if(this->isEmpty() || !this->hasEndValue()){
				ArrayLog(ame_Log_EndMethod, "copyEndValue", "println", "");
				return;
			}
			if(a_position >= this->getSize()){
				ArrayLog(ame_Log_EndMethod, "copyEndValue", "println", "");
				return;
			}
			this->m_t_value[a_position] = this->endValue();
			ArrayLog(ame_Log_EndMethod, "copyEndValue", "println", "");
		}

		virtual void copyExternEndValue(T* a_arrray, int a_position)const{
			ArrayLog(ame_Log_StartMethod, "copyEndValue", "println", "");
			if(a_arrray == nullptr || !this->hasEndValue()){
				ArrayLog(ame_Log_EndMethod, "copyEndValue", "println", "");
				return;
			}
			a_arrray[a_position] = this->endValue();
			ArrayLog(ame_Log_EndMethod, "copyEndValue", "println", "");
		}

		virtual void expandLocal(int a_size){
			ArrayLog(ame_Log_StartMethod, "expandLocal", "println", "");
			int nsize = this->getSize() + a_size;
			T *nT = new T[nsize];
			for(int x = 0; x < this->m_pos; x++){
				nT[x] = this->m_t_value[x];
			}
			if(this->m_t_value != nullptr){
				delete[] this->m_t_value;
			}
			this->m_t_value = nT;
			this->setSize(nsize);
			ArrayLog(ame_Log_EndMethod, "expandLocal", "println", "");
		}

		virtual void fix(){
			ArrayLog(ame_Log_StartMethod, "fix", "println", "");
			ArrayLog(ame_Log_EndMethod, "fix", "println", "");
		}

		virtual void erase(){
			ArrayLog(ame_Log_StartMethod, "erase", "println", "");
			if(this->m_t_value == nullptr){
				this->m_pos = 0;
				this->m_size = 0;
				ArrayLog(ame_Log_EndMethod, "erase", "println", "this->m_t_value == nullptr");
				return;
			}
			delete[] this->m_t_value;
			this->m_t_value = nullptr;
			this->m_pos = 0;
			this->m_size = 0;
			ArrayLog(ame_Log_EndMethod, "erase", "println", "");
		}

		virtual void eraseExtern(T* a_t_value){
			ArrayLog(ame_Log_StartMethod, "erase", "println", "");
			if(a_t_value == nullptr){
				return;
			}
			delete[] a_t_value;
			ArrayLog(ame_Log_EndMethod, "erase", "println", "");
		}

		virtual T* create(int a_size)const{
			ArrayLog(ame_Log_StartMethod, "create", "println", "");
			ArrayLog(ame_Log_EndMethod, "create", "println", "");
			return new T[a_size];
		}

		virtual T* createFilledArray(int a_size){
			ArrayLog(ame_Log_StartMethod, "createFilledArray", "println", "");
			this->fix();
			this->erase();
			this->m_pos = a_size;
			this->m_size = this->getAvailableSize(this->m_pos);
			this->m_t_value = this->create(this->m_size);
			ArrayLog(ame_Log_EndMethod, "createFilledArray", "println", "");
			return this->m_t_value;
		}

		virtual T* createArray(int a_size){
			ArrayLog(ame_Log_StartMethod, "createArray", "println", "");
			this->fix();
			this->erase();
			int i_pos = a_size;
			this->m_size = this->getAvailableSize(i_pos);
			this->m_t_value = this->create(this->m_size);
			ArrayLog(ame_Log_EndMethod, "createArray", "println", "");
			return this->m_t_value;
		}

		virtual T* createFilledArray(T* a_array, int a_position){
			ArrayLog(ame_Log_StartMethod, "createFilledArray", "println", "");
			this->fix();
			this->erase();
			this->m_pos = a_position;
			this->m_size = this->getAvailableSize(this->m_pos);
			this->m_t_value = a_array;
			ArrayLog(ame_Log_EndMethod, "createFilledArray", "println", "");
			return this->m_t_value;
		}

		virtual T* createArray(T* a_array, int a_size){
			ArrayLog(ame_Log_StartMethod, "createArray", "println", "");
			this->fix();
			this->erase();
			int i_pos = a_size;
			this->m_size = this->getAvailableSize(i_pos);
			this->m_t_value = a_array;
			ArrayLog(ame_Log_EndMethod, "createArray", "println", "");
			return this->m_t_value;
		}

		virtual T* createFilledArray(T* a_array, int a_position, int a_size){
			ArrayLog(ame_Log_StartMethod, "createFilledArray", "println", "");
			this->fix();
			this->erase();
			this->m_pos = a_position;
			this->m_size = a_size;
			this->m_t_value = a_array;
			ArrayLog(ame_Log_EndMethod, "createFilledArray", "println", "");
			return this->m_t_value;
		}

		virtual T* createArrayClone(int a_size)const{
			ArrayLog(ame_Log_StartMethod, "createArrayClone", "println", "");
			int i_pos = a_size;
			int i_size = this->getAvailableSize(i_pos);
			T* i_t_value = this->create(i_size);
			ArrayLog(ame_Log_EndMethod, "createArrayClone", "println", "");
			return i_t_value;
		}

		virtual void fill(T a_fill){
			ArrayLog(ame_Log_StartMethod, "fill", "println", "");
			if(this->isEmpty()){
				return;
			}
			for(int x = 0; x < this->getPosition(); x++){
				this->m_t_value[x] = a_fill;
			}
			ArrayLog(ame_Log_EndMethod, "fill", "println", "");
		}

		//
		virtual void clear(){
			ArrayLog(ame_Log_StartMethod, "clear", "println", "");
			if(this->m_t_value == nullptr){
				this->m_pos = 0;
				this->m_size = 0;
				return;
			}
			delete[] this->m_t_value;
			this->m_t_value = nullptr;
			this->m_pos = 0;
			this->m_size = 0;
			ArrayLog(ame_Log_EndMethod, "clear", "println", "");
		}

		virtual void copyToExternPointer(T* a_array, T a_value, int a_size){
			ArrayLog(ame_Log_StartMethod, "copyPointer", "println", "");
			if(a_array == nullptr || m_t_value == nullptr){
				return;
			}
			for(int x = 0; x < a_size; x++){
				a_array[x] = a_value;
			}
			int i_full_size = a_size;
			if(this->hasEndValue()){
				i_full_size--;
			}
			if(this->getPosition() < a_size){
				i_full_size = this->getPosition();
			}
			for(int x = 0; x < i_full_size; x++){
				a_array[x] = m_t_value[x];
			}
			if(this->hasEndValue()){
				a_array[i_full_size] = this->endValue();
			}
			ArrayLog(ame_Log_EndMethod, "copyPointer", "println", "");
		}

		virtual void copyExternPointer(T* a_array, const T* a_copy, int a_size){
			ArrayLog(ame_Log_StartMethod, "copyPointer", "println", "");
			if(a_array == nullptr || a_copy == nullptr ){
				return;
			}
			for(int x = 0; x < a_size; x++){
				a_array[x] = a_copy[x];
			}
			ArrayLog(ame_Log_EndMethod, "copyPointer", "println", "");
		}

		//Method Functionality: utility - polimorfic - reductive - unit - contruct
		virtual void copyExternPointer(T* a_array, const T* a_copy, int a_start, int a_size){
			ArrayLog(ame_Log_StartMethod, "copyPointer", "println", "");
			if(a_array == nullptr || a_copy == nullptr ){
				return;
			}
			for(int x = 0; x < a_size; x++){
				a_array[x] = a_copy[x + a_start];
			}
			ArrayLog(ame_Log_EndMethod, "copyPointer", "println", "");
		}

		//Method Functionality: utility - polimorfic - reductive - unit - contruct
		virtual void copyExternPointer(T* a_array, const T* a_copy, int a_start_1, int a_start_2, int a_size){
			ArrayLog(ame_Log_StartMethod, "copyPointer", "println", "");
			if(a_array == nullptr || a_copy == nullptr ){
				return;
			}
			for(int x = 0; x < a_size; x++){
				a_array[x + a_start_1] = a_copy[x + a_start_2];
			}
			ArrayLog(ame_Log_EndMethod, "copyPointer", "println", "");
		}

		virtual void copyPointer(const T* a_copy, int a_size){
			ArrayLog(ame_Log_StartMethod, "copyPointer", "println", "");
			if(this->m_t_value == nullptr || a_copy == nullptr ){
				return;
			}
			if(this->getPosition() + a_size > this->getSize()){
				ArrayLog(ame_Log_EndMethod, "copyPointer", "println", "this->getPosition() + a_size > this->getSize()");
				return;
			}
			for(int x = 0; x < a_size; x++){
				this->m_t_value[this->m_pos] = a_copy[x];
				this->m_pos++;
			}
			ArrayLog(ame_Log_EndMethod, "copyPointer", "println", "");
		}

		virtual void copyPointer(const T* a_copy, int a_start, int a_size){
			ArrayLog(ame_Log_StartMethod, "copyPointer", "println", "");
			if(this->m_t_value == nullptr || a_copy == nullptr ){
				return;
			}
			if(this->getPosition() + a_size > this->getSize()){
				return;
			}
			for(int x = 0; x < a_size; x++){
				this->m_t_value[this->m_pos] = a_copy[x + a_start];
				this->m_pos++;
			}
			ArrayLog(ame_Log_EndMethod, "copyPointer", "println", "");
		}

		virtual void copyPointer(const T* a_copy, int a_start_1, int a_start_2, int a_size){
			ArrayLog(ame_Log_StartMethod, "copyPointer", "println", "");
			if(this->m_t_value == nullptr || a_copy == nullptr ){
				return;
			}
			if(a_size + a_start_1 > this->getSize()){
				return;
			}
			for(int x = 0; x < a_size; x++){
				this->m_t_value[x + a_start_1] = a_copy[x + a_start_2];
			}
			ArrayLog(ame_Log_EndMethod, "copyPointer", "println", "");
		}

		//Method Functionality: utility - polimorfic - reductive - unit - contruct
		virtual void copyExternValue(T* a_array, T a_copy, int a_position){
			ArrayLog(ame_Log_StartMethod, "copyValue", "println", "");
			if(a_array == nullptr){
				return;
			}
			a_array[a_position] = a_copy;
			ArrayLog(ame_Log_EndMethod, "copyValue", "println", "");
		}

		virtual void copyValue(T a_value){
			ArrayLog(ame_Log_StartMethod, "copyValue", "println", "");
			if(this->m_t_value == nullptr){
				ArrayLog(ame_Log_EndMethod, "copyValue", "println", "this->m_t_value == nullptr");
				return;
			}
			if(!this->hasAvailableSize()){
				ArrayLog(ame_Log_EndMethod, "copyValue", "println", "!this->hasAvailableSize()");
				return;
			}
			this->m_t_value[this->m_pos] = a_value;
			this->m_pos++;
			ArrayLog(ame_Log_Statement, "copyValue", "println", "Position: ");
			ArrayLog(ame_Log_Statement, "copyValue", "println", this->getPosition());
			ArrayLog(ame_Log_Statement, "copyValue", "println", "Size: ");
			ArrayLog(ame_Log_Statement, "copyValue", "println", this->getSize());
			// ArrayLog(ame_Log_Statement, "copyValue", "println", "value copied");
			// ArrayLog(ame_Log_Statement, "copyValue", "println", this->m_t_value[this->m_pos]);

			ArrayLog(ame_Log_EndMethod, "copyValue", "println", "");
		}

		virtual int getAvailableSize(int a_pos)const{
			ArrayLog(ame_Log_StartMethod, "getAvailableSize", "println", "");
			ArrayLog(ame_Log_EndMethod, "getAvailableSize", "println", "");
			return a_pos;
		}

		virtual T* pointer()const{
			ArrayLog(ame_Log_EndMethod, "pointer", "println", "");
			return this->m_t_value;
		}

		virtual T* clonePointer(){
			ArrayLog(ame_Log_StartMethod, "clonePointer", "println", "");
			if(this->isEmpty()){
				ArrayLog(ame_Log_EndMethod, "clonePointer", "println", "this->isEmpty()");
				return nullptr;
			}
			int n_size = this->getPosition();
			ArrayLog(ame_Log_Statement, "clonePointer", "println", n_size);
			int availableSize = this->getAvailableSize(n_size);
			ArrayLog(ame_Log_Statement, "clonePointer", "println", this->m_size);
			T* cloneArray = this->create(availableSize);
			this->copyExternPointer(cloneArray, this->m_t_value, n_size);
			ArrayLog(ame_Log_EndMethod, "clonePointer", "println", "");
			return cloneArray;
		}

		virtual T* clonePointer(int a_start, int a_size){
			ArrayLog(ame_Log_StartMethod, "clonePointer", "println", "start and end");
			if(a_start < 0 || a_start >= this->getPosition() || a_size < 1){
				return nullptr;
			}
			ArrayLog(ame_Log_Statement, "clonePointer", "println", "new size: ");
			ArrayLog(ame_Log_Statement, "clonePointer", "println", a_size);
			T* cloneArray = this->createArrayClone(a_size);
			this->copyExternPointer(cloneArray, this->m_t_value, a_start, a_size);
			return cloneArray;
		}

		virtual int length(void) const{
			return this->m_pos;
		}

		virtual int arrayLength(const T* a_array) const{
			return this->arrayLength(a_array, this->endValue());
		}

		virtual int arrayLength(const T* a_array, T a_end) const{
			if(a_array == nullptr){
				return -1;
			}
			for(int x = 0; x < 10000; x++){
				if(a_array[x] == a_end){
					return x;
				}
			}
			return -2;
		}

		virtual void setPosition(int a_position){
			ArrayLog(ame_Log_StartMethod, "setPosition", "println", "");
			this->m_pos = a_position;
			ArrayLog(ame_Log_EndMethod, "setPosition", "println", "");
		}

		virtual int getPosition() const{
			return this->m_pos;
		}

		virtual void setSize(int a_size){
			ArrayLog(ame_Log_StartMethod, "setSize", "println", "");
			this->m_size = a_size;
			ArrayLog(ame_Log_EndMethod, "setSize", "println", "");
		}

		virtual int getSize() const{
			return this->m_size;
		}

		virtual bool isEmpty() const{
			ArrayLog(ame_Log_StartMethod, "isEmpty", "println", "");
			ArrayLog(ame_Log_Statement, "isEmpty", "println", "this->m_pos == 0");
			ArrayLog(ame_Log_Statement, "isEmpty", "println", this->m_pos == 0);
			ArrayLog(ame_Log_Statement, "isEmpty", "println", "this->m_t_value == nullptr");
			ArrayLog(ame_Log_Statement, "isEmpty", "println", this->m_t_value == nullptr);
			ArrayLog(ame_Log_EndMethod, "isEmpty", "println", "");
			return this->m_pos == 0 || this->m_t_value == nullptr;
		}

		virtual T get(int x) const{
			if(this->m_t_value == nullptr){
				return T();
			}
			if(x >= this->m_pos && this->m_pos > 0){
				return this->m_t_value[this->m_pos - 1];
			}
			if(x < this->m_pos && x >= 0){
				return this->m_t_value[x];
			}
			return T();
		}

		virtual T* getPointer(int x) const{
			if(this->m_t_value == nullptr){
				return nullptr;
			}
			if(x < this->m_pos && x >= 0 && this->m_pos > 0){
				return &this->m_t_value[x];
			}
			return nullptr;
		}

		Array<T> getArrayPart(int start)const{
			ArrayLog(ame_Log_StartMethod, "getArrayPart", "println", "");
			
			if(this->isEmpty()){
				ArrayLog(ame_Log_StartMethod, "getArrayPart", "println", "this->isEmpty()");
				return Array<T>();
			}
			
			int t_size = this->length();
			int s_size = t_size - start;
			ArrayLog(ame_Log_StartMethod, "getArrayPart", "println", "getArrayPart size");
			ArrayLog(ame_Log_StartMethod, "getArrayPart", "println", s_size);
			T* buff = this->createArrayClone(s_size);
			
			T* i_arrayPointer = this->pointer();

			if(i_arrayPointer == nullptr || buff == nullptr){
				return Array<T>();
			}

			for(int x = start; x < t_size; x++){
				buff[x - start] = i_arrayPointer[x];
			}
			this->copyExternEndValue(buff, s_size);

			Array<T> i_array;
			i_array.addLocalArrayPointer(buff);
			delete[] buff;

			ArrayLog(ame_Log_EndMethod, "getArrayPart", "println", "");
			return i_array;
		}

		Array<T> getArrayPartBySize(int a_start, int a_size){//subNote
			return this->getArrayPart(a_start, a_start + a_size);
		}

		Array<T> getArrayPartByExtraSpace(int a_start, int a_size){//subNote
			return this->getArrayPart(a_start, this->getPosition() - a_size);
		}

		Array<T> getArrayPartByLastExtraSpace(int a_size){//subNote
			return this->getArrayPart(0, this->getPosition() - a_size);
		}

		Array<T> getArrayPart(int a_start, int a_end){//subNote
			ArrayLog(ame_Log_StartMethod, "getArrayPart", "println", "");
			
			if(this->isEmpty()){
				ArrayLog(ame_Log_StartMethod, "getArrayPart", "println", "this->isEmpty()");
				return Array<T>();
			}
			
			// if(a_end > this->getPosition()){
			// 	ArrayLog(ame_Log_StartMethod, "getArrayPart", "println", "this->isEmpty()");
			// 	return Array<T>();
			// }
			
			int t_size = this->getPosition();
			int s_size = t_size - a_start;
			
			if(a_end < t_size){
				s_size -= this->getPosition() - a_end;
				t_size = a_end;
			}
			
			ArrayLog(ame_Log_StartMethod, "getArrayPart", "println", "subNote size");
			ArrayLog(ame_Log_StartMethod, "getArrayPart", "println", s_size);
			T* buff = this->createArrayClone(s_size);
			
			T* i_arrayPointer = this->pointer();

			if(i_arrayPointer == nullptr || buff == nullptr){
				return Array<T>();
			}

			for(int x = a_start; x < t_size; x++){
				buff[x - a_start] = i_arrayPointer[x];
			}
			this->copyExternEndValue(buff, s_size);

			Array<T> i_array;
			i_array.addLocalArrayPointer(buff);
			delete[] buff;
			
			ArrayLog(ame_Log_EndMethod, "getArrayPart", "println", "");
			return i_array;
		}

		virtual T& operator[](int x){
			ArrayLog(ame_Log_StartMethod, "operator[]", "println", "");
			if(x > this->m_pos && this->m_pos > 0){
				return this->m_t_value[this->m_pos - 1];
			}
			if(x < this->m_pos && x >= 0){
				return this->m_t_value[x];
			}
			if(x >= this->m_size){
				expandLocal((x - this->m_size + 1) + this->m_expandSize);
			}
			if(this->m_pos == x){
				this->m_pos++;
			}
			ArrayLog(ame_Log_EndMethod, "operator[]", "println", "");
			return this->m_t_value[x];
		}

		virtual T operator[](int x) const{
			if(this->m_t_value == nullptr){
				return T();
			}
			if(x >= this->m_pos && this->m_pos > 0){
				return this->m_t_value[this->m_pos - 1];
			}
			if(x < this->m_pos && x >= 0){
				return this->m_t_value[x];
			}
			return T();
		}

		virtual Array<T> addValue(T a_value)const{
			ArrayLog(ame_Log_StartMethod, "addValue", "println", "const T& a_value");
			Array<T> i_array = *this;
			ArrayLog(ame_Log_EndMethod, "addValue", "println", "");
			return i_array.addLocalValue(a_value);
		}

		virtual Array<T> addLocalValue(T a_value){
			ArrayLog(ame_Log_StartMethod, "addLocalValue", "println", "const T& a_value");
			ArrayLog(ame_Log_EndMethod, "addLocalValue", "println", "");
			return this->insertLocalValue(this->getPosition(), a_value);
		}

		virtual Array<T> insertLocalValue(int a_position, T a_value){
			ArrayLog(ame_Log_StartMethod, "insertLocalValue", "println", "const T& a_value");
			int i_array_length = 1;
			ArrayLog(ame_Log_Statement, "insertLocalValue", "println", "Array Length:");
			ArrayLog(ame_Log_Statement, "insertLocalValue", "println", i_array_length);
			ArrayLog(ame_Log_Statement, "insertLocalValue", "println", "Array Position:");
			ArrayLog(ame_Log_Statement, "insertLocalValue", "println", this->getPosition());
			ArrayLog(ame_Log_Statement, "insertLocalValue", "println", "Array Size:");
			ArrayLog(ame_Log_Statement, "insertLocalValue", "println", this->getSize());
			if(this->isEmpty()){
				ArrayLog(ame_Log_Statement, "insertLocalValue", "println", "this->isEmpty()");
				this->createArray(i_array_length);
				this->copyValue(a_value);
				this->copyEndValue();
				ArrayLog(ame_Log_EndMethod, "insertLocalValue", "println", "");
				return *this;
			}

			this->expandIfNeeded(i_array_length);

			if(a_position >= this->getPosition()){
				this->copyValue(a_value);
				this->copyEndValue();
				ArrayLog(ame_Log_EndMethod, "insertLocalValue", "println", "");
				return *this;
			}

			T* i_pointer = this->createArrayClone(i_array_length + this->getPosition());

			this->copyExternPointer(i_pointer, this->pointer(), a_position);
			this->copyExternValue(i_pointer, a_value, a_position);
			this->copyExternPointer(i_pointer, this->pointer(), a_position + i_array_length, a_position, this->getPosition() - a_position);
			this->copyExternEndValue(i_pointer, this->getPosition() + i_array_length);

			this->createFilledArray(i_pointer, this->getPosition() + i_array_length);

			ArrayLog(ame_Log_Statement, "insertLocalValue", "println", "Array Position:");
			ArrayLog(ame_Log_Statement, "insertLocalValue", "println", this->getPosition());
			ArrayLog(ame_Log_Statement, "insertLocalValue", "println", "Array Size:");
			ArrayLog(ame_Log_Statement, "insertLocalValue", "println", this->getSize());

			ArrayLog(ame_Log_EndMethod, "insertLocalValue", "println", "");
			return *this;
		}

		virtual Array<T> addArray(const Array<T>& a_array){
			ArrayLog(ame_Log_StartMethod, "addArray", "println", "");
			Array<T> i_array = *this;
			ArrayLog(ame_Log_EndMethod, "addArray", "println", "");
			return i_array.addLocalArray(a_array);
		}

		virtual Array<T> addLocalArray(const Array<T>& a_array){
			ArrayLog(ame_Log_StartMethod, "addLocalArray", "println", "const Array<T>& a_array");
			ArrayLog(ame_Log_EndMethod, "addLocalArray", "println", "");
			return this->insertLocalArray(this->getPosition(), a_array);
		}

		virtual Array<T> insertLocalArray(int a_position, const Array<T>& a_array){
			ArrayLog(ame_Log_StartMethod, "insertLocalArray", "println", "const Array<T>& a_array");
			int i_array_length = a_array.getPosition();
			ArrayLog(ame_Log_Statement, "insertLocalArray", "println", "Array Length:");
			ArrayLog(ame_Log_Statement, "insertLocalArray", "println", i_array_length);
			ArrayLog(ame_Log_Statement, "insertLocalArray", "println", "Array Position:");
			ArrayLog(ame_Log_Statement, "insertLocalArray", "println", this->getPosition());
			ArrayLog(ame_Log_Statement, "insertLocalArray", "println", "Array Size:");
			ArrayLog(ame_Log_Statement, "insertLocalArray", "println", this->getSize());
			if(this->isEmpty()){
				this->createArray(i_array_length);
				this->copyPointer(a_array.pointer(), i_array_length);
				this->copyEndValue();
				return *this;
			}
			this->expandIfNeeded(i_array_length);

			if(a_position >= this->getPosition()){
				this->copyPointer(a_array.pointer(), i_array_length);
				this->copyEndValue();
				ArrayLog(ame_Log_EndMethod, "insertLocalArray", "println", "");
				return *this;
			}

			T* i_pointer = this->createArrayClone(i_array_length + this->getPosition());

			this->copyExternPointer(i_pointer, this->pointer(), a_position);
			this->copyExternPointer(i_pointer, a_array.pointer(), a_position, 0, i_array_length);
			this->copyExternPointer(i_pointer, this->pointer(), a_position + i_array_length, a_position, this->getPosition() - a_position);
			this->copyExternEndValue(i_pointer, this->getPosition() + i_array_length);

			this->createFilledArray(i_pointer, this->getPosition() + i_array_length);

			ArrayLog(ame_Log_Statement, "insertLocalArray", "println", "Array Position:");
			ArrayLog(ame_Log_Statement, "insertLocalArray", "println", this->getPosition());
			ArrayLog(ame_Log_Statement, "insertLocalArray", "println", "Array Size:");
			ArrayLog(ame_Log_Statement, "insertLocalArray", "println", this->getSize());

			ArrayLog(ame_Log_EndMethod, "insertLocalArray", "println", "");
			return *this;
		}
		
		virtual Array<T> addArrayPointer(const T* a_pointer){
			ArrayLog(ame_Log_StartMethod, "addArrayPointer", "println", "const char* a_pointer");
			ArrayLog(ame_Log_Statement, "addArrayPointer", "println", "Pointer Array:");
			//ArrayLog(ame_Log_Statement, "addArrayPointer", "println", a_pointer);
			Array i_array = *this;
			ArrayLog(ame_Log_EndMethod, "addArrayPointer", "println", "");
			return i_array.addLocalArrayPointer(a_pointer);
		}

		virtual Array<T> addLocalArrayPointer(const T* a_pointer){
			ArrayLog(ame_Log_StartMethod, "addLocalArrayPointer", "println", "const char* a_pointer");
			ArrayLog(ame_Log_Statement, "addLocalArrayPointer", "println", "Pointer Array:");
			//ArrayLog(ame_Log_Statement, "addLocalArrayPointer", "println", a_pointer);
			ArrayLog(ame_Log_EndMethod, "addLocalArrayPointer", "println", "");
			return this->insertLocalArrayPointer(this->getPosition(), a_pointer);
		}

		virtual Array<T> addLocalArrayPointer(const T* a_pointer, int a_size){
			ArrayLog(ame_Log_StartMethod, "addLocalArrayPointer", "println", "const char* a_pointer");
			ArrayLog(ame_Log_Statement, "addLocalArrayPointer", "println", "Pointer Array:");
			//ArrayLog(ame_Log_Statement, "addLocalArrayPointer", "println", a_pointer);
			ArrayLog(ame_Log_EndMethod, "addLocalArrayPointer", "println", "");
			return this->insertLocalArrayPointer(this->getPosition(), a_pointer, a_size);
		}

		virtual Array<T> insertLocalArrayPointer(int a_position, const T* a_pointer){
			ArrayLog(ame_Log_StartMethod, "insertLocalArrayPointer", "println", "const char* a_pointer");
			ArrayLog(ame_Log_EndMethod, "insertLocalArrayPointer", "println", "");
			return this->insertLocalArrayPointer(a_position, a_pointer, this->arrayLength(a_pointer));
		}

		virtual Array<T> insertLocalArrayPointer(int a_position, const T* a_pointer, int a_size){
			ArrayLog(ame_Log_StartMethod, "insertLocalArrayPointer", "println", "const char* a_pointer");
			ArrayLog(ame_Log_Statement, "insertLocalArrayPointer", "println", "Pointer Array:");
			//ArrayLog(ame_Log_Statement, "insertLocalArrayPointer", "println", a_pointer);
			if(a_pointer == nullptr){
				return *this;
			}
			int i_array_length = this->arrayLength(a_pointer);
			if(i_array_length > a_size){
				i_array_length = a_size;
			}
			ArrayLog(ame_Log_Statement, "insertLocalArrayPointer", "println", "Array Length:");
			ArrayLog(ame_Log_Statement, "insertLocalArrayPointer", "println", i_array_length);
			ArrayLog(ame_Log_Statement, "insertLocalArrayPointer", "println", "Array Position:");
			ArrayLog(ame_Log_Statement, "insertLocalArrayPointer", "println", this->getPosition());
			ArrayLog(ame_Log_Statement, "insertLocalArrayPointer", "println", "Array Size:");
			ArrayLog(ame_Log_Statement, "insertLocalArrayPointer", "println", this->getSize());
			if(this->isEmpty()){
				ArrayLog(ame_Log_Statement, "insertLocalArrayPointer", "println", "this->isEmpty()");
				this->createArray(i_array_length);
				this->copyPointer(a_pointer, i_array_length);
				this->copyEndValue();
				ArrayLog(ame_Log_Statement, "insertLocalArrayPointer", "println", "Array Position:");
				ArrayLog(ame_Log_Statement, "insertLocalArrayPointer", "println", this->getPosition());
				ArrayLog(ame_Log_Statement, "insertLocalArrayPointer", "println", "Array Size:");
				ArrayLog(ame_Log_Statement, "insertLocalArrayPointer", "println", this->getSize());
				ArrayLog(ame_Log_EndMethod, "insertLocalArrayPointer", "println", "");
				return *this;
			}
			this->expandIfNeeded(i_array_length);
			
			if(a_position >= this->getPosition()){
				ArrayLog(ame_Log_Statement, "insertLocalArrayPointer", "println", "a_position >= this->getPosition()");
				this->copyPointer(a_pointer, i_array_length);
				this->copyEndValue();
				ArrayLog(ame_Log_Statement, "insertLocalArrayPointer", "println", "Array Position:");
				ArrayLog(ame_Log_Statement, "insertLocalArrayPointer", "println", this->getPosition());
				ArrayLog(ame_Log_Statement, "insertLocalArrayPointer", "println", "Array Size:");
				ArrayLog(ame_Log_Statement, "insertLocalArrayPointer", "println", this->getSize());
				ArrayLog(ame_Log_EndMethod, "insertLocalArrayPointer", "println", "");
				return *this;
			}

			T* i_pointer = this->createArrayClone(i_array_length + this->getPosition());

			this->copyExternPointer(i_pointer, this->pointer(), a_position);
			this->copyExternPointer(i_pointer, a_pointer, a_position, 0, i_array_length);
			this->copyExternPointer(i_pointer, this->pointer(), a_position + i_array_length, a_position, this->getPosition() - a_position);
			this->copyExternEndValue(i_pointer, this->getPosition() + i_array_length);

			this->createFilledArray(i_pointer, this->getPosition() + i_array_length);
			
			ArrayLog(ame_Log_Statement, "insertLocalArrayPointer", "println", "a_position < this->getPosition()");
			ArrayLog(ame_Log_Statement, "insertLocalArrayPointer", "println", "Array Position:");
			ArrayLog(ame_Log_Statement, "insertLocalArrayPointer", "println", this->getPosition());
			ArrayLog(ame_Log_Statement, "insertLocalArrayPointer", "println", "Array Size:");
			ArrayLog(ame_Log_Statement, "insertLocalArrayPointer", "println", this->getSize());
			
			ArrayLog(ame_Log_EndMethod, "insertLocalArrayPointer", "println", "");
			return *this;
		}

		virtual Array<T> addLocal(){
			ArrayLog(ame_Log_StartMethod, "addLocal", "println", "");
			if(this->isEmpty()){
				return *this;
			}
			int i_size = this->getPosition();
			T* i_t_value = this->clonePointer();
			if(this->m_size - this->m_pos < 1){
				expandLocal(i_size + this->m_expandSize);
			}
			this->copyPointer(i_t_value, i_size);
			this->eraseExtern(i_t_value);
			ArrayLog(ame_Log_EndMethod, "addLocal", "println", "");
			return *this;
		}

		virtual ArrayIterator<T> begin() const{
			return ArrayIterator<T>(this->m_t_value,0);
		}
		virtual ArrayIterator<T> end() const{
			return ArrayIterator<T>(this->m_t_value, this->m_pos);
		}

		virtual bool contain(const T& a_value){
			ArrayLog(ame_Log_StartMethod, "contain", "println", "");
			if(this->m_t_value == nullptr || this->m_pos == 0){
				return false;
			}

			ArrayLog(ame_Log_Statement, "contain", "println", "Array Position:");
			ArrayLog(ame_Log_Statement, "contain", "println", this->getPosition());
			ArrayLog(ame_Log_Statement, "contain", "println", "Array Size:");
			ArrayLog(ame_Log_Statement, "contain", "println", this->getSize());

			for(int x = 0; x < this->m_pos; x++){
				if(this->m_t_value[x] == a_value){
					ArrayLog(ame_Log_EndMethod, "contain", "println", "return true");
					return true;
				}
			}
			ArrayLog(ame_Log_EndMethod, "contain", "println", "return false");
			return false;
		}

		virtual int getFirstIndex(const T& a_value){
			ArrayLog(ame_Log_StartMethod, "getFirstIndex", "println", "");
			if(this->isEmpty()){
				ArrayLog(ame_Log_EndMethod, "getFirstIndex", "println", "");
				return -1;
			}
			for(int x = 0; x < this->m_pos; x++){
				if(this->m_t_value[x] == a_value){
					return x;
				}
			}
			return -1;
			ArrayLog(ame_Log_EndMethod, "getFirstIndex", "println", "");
		}

		virtual int getLastIndex(const T& a_value){
			ArrayLog(ame_Log_StartMethod, "getLastIndex", "println", "");
			if(this->isEmpty()){
				ArrayLog(ame_Log_EndMethod, "getLastIndex", "println", "");
				return -1;
			}
			for(int x = this->m_pos - 1; x >= 0; x--){
				if(this->m_t_value[x] == a_value){
					return x;
				}
			}
			return -1;
			ArrayLog(ame_Log_EndMethod, "getLastIndex", "println", "");
		}

		virtual bool remove(int a_index){
			ArrayLog(ame_Log_StartMethod, "remove", "println", "");
			if(a_index == -1 || a_index >= this->m_pos || this->isEmpty()){
				return false;
			}
			if(this->removeShrink){
				int i_pos = this->m_pos - 1;
				T* i_copy = this->createArrayClone(i_pos);
				int x_count = 0;
				for(int x = 0; x < this->m_pos; x++){
					if(a_index != x){
						i_copy[x_count] = this->m_t_value[x];
						x_count++;
					}
				}
				this->createFilledArray(i_copy, i_pos);
				this->copyEndValue();
			}else{

			}
			return true;
			ArrayLog(ame_Log_EndMethod, "remove", "println", "");
		}

		virtual bool remove(int a_index, int a_size){
			ArrayLog(ame_Log_StartMethod, "remove", "println", "");
			if(a_index == -1 || a_index >= this->m_pos || this->isEmpty()){
				return false;
			}
			if(this->removeShrink){
				int i_pos = this->m_pos - a_size;
				T* i_copy = this->createArrayClone(i_pos);
				int x_count = 0;
				for(int x = 0; x < a_index; x++){
					i_copy[x_count] = this->m_t_value[x];
					x_count++;
				}
				for(int x = a_index + a_size; x < this->getPosition(); x++){
					i_copy[x_count] = this->m_t_value[x];
					x_count++;
				}
				this->createFilledArray(i_copy, x_count);
				this->copyEndValue();
			}else{

			}
			return true;
			ArrayLog(ame_Log_EndMethod, "remove", "println", "");
		}

		virtual void removeFirst(const T& a_value){
			ArrayLog(ame_Log_StartMethod, "removeFirst", "println", "");
			int index = getFirstIndex(a_value);
			if(index == -1){
				return;
			}
			this->remove(index);
			ArrayLog(ame_Log_EndMethod, "removeFirst", "println", "");
		}

		virtual void removeLast(const T& a_value){
			ArrayLog(ame_Log_StartMethod, "removeLast", "println", "");
			int index = getLastIndex(a_value);
			if(index == -1){
				return;
			}
			this->remove(index);
			ArrayLog(ame_Log_EndMethod, "removeLast", "println", "");
		}

		virtual void removeFirstIndex(){
			ArrayLog(ame_Log_StartMethod, "removeFirstIndex", "println", "");
			if(this->isEmpty()){
				return;
			}
			this->remove(0);
			ArrayLog(ame_Log_EndMethod, "removeFirstIndex", "println", "");
		}

		virtual void removeLastIndex(){
			ArrayLog(ame_Log_StartMethod, "removeLastIndex", "println", "");
			if(this->isEmpty()){
				return;
			}
			this->remove(this->getPosition() - 1);
			ArrayLog(ame_Log_EndMethod, "removeLastIndex", "println", "");
		}
/*
		Array<Array<T>> split(const T& divide){

		}

		Array<T> split(const T& divide, int parte){

		}

		int splitLenght(const T& divide){

		}*/

		virtual Array<T>& operator=(const Array<T>& a_array){
			ArrayLog(ame_Log_StartMethod, "operator=", "println", "operator= const Array<T>&");
			this->fix();
			this->erase();

			if(a_array.isEmpty()){
				ArrayLog(ame_Log_EndMethod, "operator=", "println", "a_array.isEmpty()");
				return *this;
			}
			int i_array_length = a_array.getPosition();
			this->createArray(i_array_length);
			this->copyPointer(a_array.pointer(), i_array_length);
			this->copyEndValue();
			ArrayLog(ame_Log_EndMethod, "operator=", "println", "");
			return *this;
		}

		virtual Array<T> operator=(T a_value){
			ArrayLog(ame_Log_StartMethod, "operator=", "println", "operator= const T&");
			this->fix();
			this->erase();
			this->createArray(1);
			this->copyValue(a_value);
			this->copyEndValue();
			//ArrayLog(ame_Log_Statement, "operator=", "println", a_value);
			ArrayLog(ame_Log_EndMethod, "operator=", "println", "");
			return *this;
		}

		virtual Array<T> operator+=(const Array<T>& a_value){
			ArrayLog(ame_Log_StartMethod, "operator+=", "println", "const Array<T>& a_value");
			ArrayLog(ame_Log_EndMethod, "operator+=", "println", "");
			return this->addLocalArray(a_value);
		}

		virtual Array<T> operator+(const Array<T>& a_value){
			ArrayLog(ame_Log_StartMethod, "operator+", "println", "const Array<T>& a_value");
			Array<T> i_array = *this;
			ArrayLog(ame_Log_EndMethod, "operator+", "println", "");
			return i_array.addArray(a_value);
		}

		virtual Array<T> operator+=(T a_value){
			ArrayLog(ame_Log_StartMethod, "operator+=", "println", "T a_value");
			ArrayLog(ame_Log_EndMethod, "operator+=", "println", "");
			return this->addLocalValue(a_value);
		}

		virtual Array<T> operator+(T a_value){
			ArrayLog(ame_Log_StartMethod, "operator+", "println", "T a_value");
			Array<T> i_array = *this;
			ArrayLog(ame_Log_EndMethod, "operator+", "println", "");
			return i_array.addValue(a_value);
		}

		virtual bool operator==(const Array<T>& o_array){
			ArrayLog(ame_Log_StartMethod, "operator==", "println", "const Array<T>& o_array");
			
			if(o_array.getPosition() != this->getPosition()){
				return false;
			}
			for(int x = 0; x < this->getPosition(); x++){
				if(o_array.get(x) != this->get(x)){
					return false;
				}
			}

			ArrayLog(ame_Log_EndMethod, "operator==", "println", "");
			return true;
		}

		virtual bool operator!=(const Array<T>& o_array){
			ArrayLog(ame_Log_StartMethod, "operator!=", "println", "const Array<T>& o_array");
			
			if(o_array.getPosition() != this->getPosition()){
				return true;
			}
			for(int x = 0; x < this->getPosition(); x++){
				if(o_array.get(x) != this->get(x)){
					return true;
				}
			}

			ArrayLog(ame_Log_EndMethod, "operator!=", "println", "");
			return false;
		}

		virtual bool operator==(const T& a_value){
			ArrayLog(ame_Log_StartMethod, "operator==", "println", "const T& a_value");
			
			if(this->getPosition() != 1){
				return false;
			}

			ArrayLog(ame_Log_EndMethod, "operator==", "println", "");
			return this->get(0) == a_value;
		}
		
		virtual bool operator!=(const T& a_value){
			ArrayLog(ame_Log_StartMethod, "operator!=", "println", "const T& a_value");
			
			if(this->getPosition() != 1){
				return true;
			}

			ArrayLog(ame_Log_EndMethod, "operator!=", "println", "");
			return this->get(0) != a_value;
		}
/*
		void replace(Array a_search, Array a_change){
			ArrayLog(ame_Log_StartMethod, "replace", "println", "");
			ArrayLog(ame_Log_Statement, "replace", "println", "");
			Array i_Array;
			Array i_search;
			int i_search_index = 0;

			if(isEmpty()){
				return;
			}

			ArrayLog(ame_Log_Statement, "replace", "println", "start for");
			for(int x = 0; x < this->m_pos; x++){
				ArrayLog(ame_Log_Statement, "replace", "println", ame_String("iteration ") + ame_String(x));
				char cr = charAt(x);
				char schr = a_search.charAt(i_search_index);
				ArrayLog(ame_Log_Statement, "replace", "println", ame_String("Arrays char: ") + ame_String((char)cr));
				ArrayLog(ame_Log_Statement, "replace", "println", ame_String("searche char: ") + ame_String((char)schr));
				if(schr == cr){
					ArrayLog(ame_Log_Statement, "replace", "println", "schr == cr");
					i_search_index++;
					i_search += schr;
				}else{
					ArrayLog(ame_Log_Statement, "replace", "println", "schr != cr");
					if(i_search_index > 0){
						ArrayLog(ame_Log_Statement, "replace", "println", "i_search_index > 0");
						i_search_index = 0;
						i_Array += i_search;
						i_search = "";
					}
					i_Array += cr;
				}
				if(i_search_index == a_search.getPosition()){
					ArrayLog(ame_Log_Statement, "replace", "println", "i_search_index == a_search.getPosition() - 1");
					i_search_index = 0;
					i_search = "";
					i_Array += a_change;
				}
			}
			ArrayLog(ame_Log_Statement, "replace", "println", "end for");

			fix(this->m_t_value, this->m_pos, this->m_size);
			erase(this->m_t_value);
			this->m_t_value = i_Array.this->m_t_value;
			this->m_pos = i_Array.this->m_pos;
			this->m_size = i_Array.this->m_size;
			i_Array.this->m_t_value = nullptr;
			i_Array.this->m_pos = 0;
			i_Array.this->m_size = 0;
			return;
		}
*/

		virtual Array<T> getArray(){
			return *this;
		}

		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){return Class<Array<T>>::getClass();}
		virtual bool instanceof(cppObjectClass* cls){
			return cls == Class<Array<T>>::getClass();
		}
		#endif

		#if defined(cppObject_AVAILABLE)
		virtual Array<T>* clone(){
			ArrayLog(ame_Log_StartMethod, "clone", "println", "");
			Array<T>* array = new Array<T>(*this);
			array->copy(this);
			ArrayLog(ame_Log_EndMethod, "clone", "println", "");
			return array;
		}

		virtual Array<T>* clone(bool owningMemory){
			ArrayLog(ame_Log_StartMethod, "clone", "println", "");
			Array<T>* array = new Array<T>(*this);
			array->copy(this);
			ArrayLog(ame_Log_EndMethod, "clone", "println", "");
			return array;
		}

		virtual bool equal(cppObject *obj){
			ArrayLog(ame_Log_StartMethod, "equal", "println", "");
			if(obj == nullptr){
				ArrayLog(ame_Log_EndMethod, "equal", "println", "");
				return false;
			}
			if(!obj->instanceof(getClass())){
				ArrayLog(ame_Log_EndMethod, "equal", "println", "");
				return false;
			}
			Array<T>* e_array = (Array<T>*)obj;
			if(e_array->getPosition() != this->getPosition()){
				ArrayLog(ame_Log_EndMethod, "equal", "println", "");
				return false;
			}
			for(int x = 0; x < this->getPosition(); x++){
				if(e_array->get(x) != this->get(x)){
					ArrayLog(ame_Log_EndMethod, "equal", "println", "");
					return false;
				}
			}
			ArrayLog(ame_Log_EndMethod, "equal", "println", "");
			return true;
		}

		virtual bool copy(cppObject* obj){
			ArrayLog(ame_Log_StartMethod, "copy", "println", "");
			if(obj == nullptr){
				ArrayLog(ame_Log_EndMethod, "copy", "println", "");
				return false;
			}
			if(!obj->instanceof(getClass())){
				ArrayLog(ame_Log_EndMethod, "copy", "println", "");
				return false;
			}
			Array<T>* source = (Array<T>*)obj;
			this->fix();
			this->erase();
			if(source->isEmpty()){
				ArrayLog(ame_Log_EndMethod, "copy", "println", "source.isEmpty()");
				return true;
			}
			this->m_size = this->getAvailableSize(source->m_pos);
			this->m_t_value = this->create(this->m_size);
			this->copyPointer(source->m_t_value, source->m_pos);
			ArrayLog(ame_Log_EndMethod, "copy", "println", "");
			return true;
		}

		virtual bool move(cppObject* obj){
			ArrayLog(ame_Log_StartMethod, "move", "println", "");
			if(obj == nullptr){
				ArrayLog(ame_Log_EndMethod, "move", "println", "");
				return false;
			}
			if(!obj->instanceof(getClass())){
				ArrayLog(ame_Log_EndMethod, "move", "println", "");
				return false;
			}
			Array<T>* source = (Array<T>*)obj;
			fix();
			erase();
			if(source->isEmpty()){
				ArrayLog(ame_Log_EndMethod, "move", "println", "source.isEmpty()");
				return true;
			}
			this->m_pos = source->m_pos;
			this->m_size = source->m_size;
			this->m_t_value = source->m_t_value;
			source->m_t_value = nullptr;
			source->m_pos = 0;
			source->m_size = 0;
			ArrayLog(ame_Log_EndMethod, "move", "println", "");
			return true;
		}

		virtual bool duplicate(cppObject* obj){
			ArrayLog(ame_Log_StartMethod, "duplicate", "println", "");
			if(obj == nullptr){
				ArrayLog(ame_Log_EndMethod, "duplicate", "println", "");
				return false;
			}
			if(!obj->instanceof(getClass())){
				ArrayLog(ame_Log_EndMethod, "duplicate", "println", "");
				return false;
			}
			Array<T>* source = (Array<T>*)obj;
			this->fix();
			this->erase();
			if(source->isEmpty()){
				ArrayLog(ame_Log_EndMethod, "duplicate", "println", "source.isEmpty()");
				return true;
			}
			this->m_size = this->getAvailableSize(source->m_pos);
			this->m_t_value = this->create(this->m_size);
			this->copyPointer(source->m_t_value, source->m_pos);
			ArrayLog(ame_Log_EndMethod, "duplicate", "println", "");
			return true;
		}

		virtual cppObject* move(){
			ArrayLog(ame_Log_StartMethod, "move", "println", "");
			Array<T>* source = new Array<T>();
			if(this->isEmpty()){
				ArrayLog(ame_Log_EndMethod, "move", "println", "this.isEmpty()");
				return source;
			}
			source->m_pos = this->m_pos;
			source->m_size = this->m_size;
			source->m_t_value = this->m_t_value;
			this->m_t_value = nullptr;
			this->m_pos = 0;
			this->m_size = 0;
			ArrayLog(ame_Log_EndMethod, "move", "println", "");
			return source;
		}

		virtual cppObject* duplicate(){
			ArrayLog(ame_Log_StartMethod, "duplicate", "println", "");
			Array<T>* source = new Array<T>();
			if(this->isEmpty()){
				ArrayLog(ame_Log_EndMethod, "duplicate", "println", "this.isEmpty()");
				return source;
			}
			source->m_pos = this->m_pos;
			source->m_size = getAvailableSize(this->m_pos);
			source->m_t_value = create(this->m_size);
			source->copyPointer(this->m_t_value, this->m_pos);
			ArrayLog(ame_Log_EndMethod, "duplicate", "println", "");
			return source;
		}
		#endif

	protected:

		virtual void incrementPosition(){this->m_pos++;}
		virtual void decrementPosition(){
			this->m_pos--;
			if(this->m_pos < 0){
				this->m_pos = 0;
			}
		}

		virtual void incrementPosition(int a_size){this->m_pos += a_size;}
		virtual void decrementPosition(int a_size){
			this->m_pos -= a_size;
			if(this->m_pos < 0){
				this->m_pos = 0;
			}
		}

		virtual void incrementSize(){this->m_size++;}
		virtual void decrementSize(){
			this->m_size--;
			if(this->m_size < 0){
				this->m_size = 0;
			}
		}

		virtual void incrementSize(int a_size){this->m_size += a_size;}
		virtual void decrementSize(int a_size){
			this->m_size -= a_size;
			if(this->m_size < 0){
				this->m_size = 0;
			}
		}

	protected:
		bool removeShrink = true;
};

}

#endif








