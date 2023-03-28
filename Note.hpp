
/*
*	position = total of chars in the string
*	size = total size of the array
*	length = total of chars before the endValue()
*
*
*	position = length
*
*/

#ifndef CONFIGURATION_Note_hpp
#define CONFIGURATION_Note_hpp

#include "ame_Enviroment.hpp"

	#if defined(DISABLE_Note)
		#define Note_hpp

		#ifdef ame_Windows
			typedef std::string Note;
		#endif

		#ifdef ame_ArduinoIDE
			typedef String Note;
		#endif

		#define IMPLEMENTATION_Note
		#define IMPLEMENTING_Note
	#else
		#if defined(DISABLE_IMPLEMENTATION_Note)
			#define IMPLEMENTATION_Note
			#define IMPLEMENTING_Note
		#endif
	#endif
#endif

#ifndef Note_hpp
#define Note_hpp
#define Note_AVAILABLE 

#include "cppObject.hpp"

#ifndef DISABLE_IMPLEMENTATION_Note
	#define IMPLEMENTATION_Note IMPLEMENTATION(public Note)
	#define IMPLEMENTING_Note IMPLEMENTING(public Note)
#endif

#include "Array.hpp"

#ifdef ame_Windows
	#include "ame_Printable.hpp"
	#include "ame_Print.hpp"
#endif

#ifdef ame_ArduinoIDE
	#include "Arduino.h"
	#include "Printable.h"
	#include "IPAddress.h"
#endif

#include "NoteIterator.hpp"

#include "PrimitiveRawList.hpp"
#include "PrimitiveRawMap.hpp"

#include "ame_Byte.hpp"

#define ame_BINARY 0
#define ame_HEXADECIMAL 1
#define ame_DECIMAL 2

#ifdef Note_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"

	#define NoteLog(location,method,type,mns) ame_Log((void*)this,location,"Note",method,type,mns)
	#define const_NoteLog(location,method,type,mns) ame_Log((void*)this,location,"Note",method,type,mns)
	#define StaticNoteLog(pointer,location,method,type,mns) ame_Log(pointer,location,"Note",method,type,mns)
#else
	#ifdef Note_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"

		#define NoteLog(location,method,type,mns) ame_LogDebug((void*)this,location,"Note",method,type)
		#define const_NoteLog(location,method,type,mns) ame_LogDebug((void*)this,location,"Note",method,type)
		#define StaticNoteLog(pointer,location,method,type,mns) ame_LogDebug(pointer,location,"Note",method,type)
	#else
		#define NoteLog(location,method,type,mns)
		#define const_NoteLog(location,method,type,mns)
		#define StaticNoteLog(pointer,location,method,type,mns)
	#endif
#endif


namespace ame{

class Note : public Array<char>, public Printable{
    public:
		Note(){
			NoteLog(ame_Log_StartMethod, "Constructor", "println", "Default Constructor");
			NoteLog(ame_Log_EndMethod, "Constructor", "println", "");
		}

		Note(const char* c_value){
			NoteLog(ame_Log_StartMethod, "Constructor", "println", "const char* c_value");
			NoteLog(ame_Log_Statement, "Constructor", "println", "Char Array:");
			NoteLog(ame_Log_Statement, "Constructor", "println", c_value);

			this->insertLocalArrayPointer(0, c_value);

			NoteLog(ame_Log_Statement, "Constructor", "println", "Array Position:");
			NoteLog(ame_Log_Statement, "Constructor", "println", this->getPosition());
			NoteLog(ame_Log_Statement, "Constructor", "println", "Array Size:");
			NoteLog(ame_Log_Statement, "Constructor", "println", this->getSize());
				
			NoteLog(ame_Log_EndMethod, "Constructor", "println", "");
		}

		Note(const Array<char>& source){
			NoteLog(ame_Log_StartMethod, "Constructor", "println", "const Array<char>& source");
			int i_array_length = source.length();
			if(i_array_length > 0){
				this->createArray(i_array_length);
				this->copyPointer(source.pointer(), i_array_length);
				this->copyEndValue();
				NoteLog(ame_Log_Statement, "Constructor", "println", "Array Length:");
				NoteLog(ame_Log_Statement, "Constructor", "println", i_array_length);
				NoteLog(ame_Log_Statement, "Constructor", "println", "Array Position:");
				NoteLog(ame_Log_Statement, "Constructor", "println", this->getPosition());
				NoteLog(ame_Log_Statement, "Constructor", "println", "Array Size:");
				NoteLog(ame_Log_Statement, "Constructor", "println", this->getSize());
			}
			NoteLog(ame_Log_EndMethod, "Constructor", "println", "");
		}

		Note(const Note& source){
			NoteLog(ame_Log_StartMethod, "Constructor", "println", "const Note& val");
			NoteLog(ame_Log_Statement, "Constructor", "println", "Note:");
			NoteLog(ame_Log_Statement, "Constructor", "println", source.pointer());
			int i_array_length = source.length();
			NoteLog(ame_Log_Statement, "Constructor", "println", "Array Length:");
			NoteLog(ame_Log_Statement, "Constructor", "println", i_array_length);
			NoteLog(ame_Log_Statement, "Constructor", "println", "Array Position:");
			NoteLog(ame_Log_Statement, "Constructor", "println", this->getPosition());
			NoteLog(ame_Log_Statement, "Constructor", "println", "Array Size:");
			NoteLog(ame_Log_Statement, "Constructor", "println", this->getSize());
			if(i_array_length > 0){
				this->createArray(i_array_length);
				this->copyPointer(source.pointer(), i_array_length);
				this->copyEndValue();
				NoteLog(ame_Log_Statement, "Constructor", "println", "Array Position:");
				NoteLog(ame_Log_Statement, "Constructor", "println", this->getPosition());
				NoteLog(ame_Log_Statement, "Constructor", "println", "Array Size:");
				NoteLog(ame_Log_Statement, "Constructor", "println", this->getSize());
			}
			NoteLog(ame_Log_EndMethod, "Constructor", "println", "");
		}

		Note(Note&& source){
			NoteLog(ame_Log_StartMethod, "Constructor", "println", "Note&& source");
			int i_array_length = source.getPosition();
			if(i_array_length > 0){
				this->m_pos = source.m_pos;
				this->m_size = source.m_size;
				this->m_t_value = source.m_t_value;
				source.m_t_value = nullptr;
				source.m_pos = 0;
				source.m_size = 0;
				NoteLog(ame_Log_Statement, "Constructor", "println", "Array Length:");
				NoteLog(ame_Log_Statement, "Constructor", "println", i_array_length);
				NoteLog(ame_Log_Statement, "Constructor", "println", "Array Position:");
				NoteLog(ame_Log_Statement, "Constructor", "println", this->getPosition());
				NoteLog(ame_Log_Statement, "Constructor", "println", "Array Size:");
				NoteLog(ame_Log_Statement, "Constructor", "println", this->getSize());
			}
			NoteLog(ame_Log_EndMethod, "Constructor", "println", "");
		}

		Note(const char& c_char){
			NoteLog(ame_Log_StartMethod, "Constructor", "println", "const char& c_char");
			NoteLog(ame_Log_Statement, "Constructor", "println", "Char:");
			NoteLog(ame_Log_Statement, "Constructor", "println", c_char);
			this->createArray(1);
			this->copyValue(c_char);
			this->copyEndValue();
			NoteLog(ame_Log_Statement, "Constructor", "println", "Array Length:");
			NoteLog(ame_Log_Statement, "Constructor", "println", 1);
			NoteLog(ame_Log_Statement, "Constructor", "println", "Array Position:");
			NoteLog(ame_Log_Statement, "Constructor", "println", this->getPosition());
			NoteLog(ame_Log_Statement, "Constructor", "println", "Array Size:");
			NoteLog(ame_Log_Statement, "Constructor", "println", this->getSize());
			NoteLog(ame_Log_EndMethod, "Constructor", "println", "");
		}

		Note(const bool& c_value){
			NoteLog(ame_Log_StartMethod, "Constructor", "println", "const bool& i");
			NoteLog(ame_Log_Statement, "Constructor", "println", "bool:");
			NoteLog(ame_Log_Statement, "Constructor", "println", c_value);
			char* i_pointer = this->getBool(c_value);
			this->addLocalArrayPointer(i_pointer);
			delete i_pointer;
			NoteLog(ame_Log_Statement, "Constructor", "println", "Array Position:");
			NoteLog(ame_Log_Statement, "Constructor", "println", this->getPosition());
			NoteLog(ame_Log_Statement, "Constructor", "println", "Array Size:");
			NoteLog(ame_Log_Statement, "Constructor", "println", this->getSize());
			NoteLog(ame_Log_EndMethod, "Constructor", "println", "");
		}

		Note(const int& c_value){
			NoteLog(ame_Log_StartMethod, "Constructor", "println", "const int& c_value");
			NoteLog(ame_Log_Statement, "Constructor", "println", "Int:");
			NoteLog(ame_Log_Statement, "Constructor", "println", c_value);
			char* i_pointer = this->getInt(c_value);
			this->addLocalArrayPointer(i_pointer);
			delete i_pointer;
			NoteLog(ame_Log_Statement, "Constructor", "println", "Array Position:");
			NoteLog(ame_Log_Statement, "Constructor", "println", this->getPosition());
			NoteLog(ame_Log_Statement, "Constructor", "println", "Array Size:");
			NoteLog(ame_Log_Statement, "Constructor", "println", this->getSize());
			NoteLog(ame_Log_EndMethod, "Constructor", "println", "");
		}

		Note(const long& c_value){
			NoteLog(ame_Log_StartMethod, "Constructor", "println", "const long& c_value");
			NoteLog(ame_Log_Statement, "Constructor", "println", "Long:");
			NoteLog(ame_Log_Statement, "Constructor", "println", c_value);
			char* i_pointer = this->getLong(c_value);
			this->addLocalArrayPointer(i_pointer);
			delete i_pointer;
			NoteLog(ame_Log_Statement, "Constructor", "println", "Array Position:");
			NoteLog(ame_Log_Statement, "Constructor", "println", this->getPosition());
			NoteLog(ame_Log_Statement, "Constructor", "println", "Array Size:");
			NoteLog(ame_Log_Statement, "Constructor", "println", this->getSize());
			NoteLog(ame_Log_EndMethod, "Constructor", "println", "");
		}

		Note(const float& c_value){
			NoteLog(ame_Log_StartMethod, "Constructor", "println", "const float& c_value");
			NoteLog(ame_Log_Statement, "Constructor", "println", "Float:");
			NoteLog(ame_Log_Statement, "Constructor", "println", c_value);
			char* i_pointer = this->getFloat(c_value);
			this->addLocalArrayPointer(i_pointer);
			delete i_pointer;
			NoteLog(ame_Log_Statement, "Constructor", "println", "Array Position:");
			NoteLog(ame_Log_Statement, "Constructor", "println", this->getPosition());
			NoteLog(ame_Log_Statement, "Constructor", "println", "Array Size:");
			NoteLog(ame_Log_Statement, "Constructor", "println", this->getSize());
			NoteLog(ame_Log_EndMethod, "Constructor", "println", "");
		}

		#ifdef ame_ArduinoIDE
/*
		Note(const ame_Byte& c_byte){
			NoteLog(ame_Log_StartMethod, "Constructor", "println", "start");
			NoteLog(ame_Log_Statement, "Constructor", "println", "const byte& i");
			this->m_pos = byteCharSize(ame_DECIMAL, c_byte);
			this->m_size = getAvailableSize(this->getPosition());

			this->m_t_value = this->create(this->m_size);
			byteToCharPointer(c_byte, this->getPosition(), 0, this->m_t_value, ame_DECIMAL, true);
			NoteLog(ame_Log_Statement, "Constructor", "println", "Array Position:");
			NoteLog(ame_Log_Statement, "Constructor", "println", this->getPosition());
			NoteLog(ame_Log_Statement, "Constructor", "println", "Array Size:");
			NoteLog(ame_Log_Statement, "Constructor", "println", this->getSize());
			NoteLog(ame_Log_EndMethod, "Constructor", "println", "");
		}
/*
		Note(const ame_Byte& c_byte, int a_type){
			NoteLog(ame_Log_StartMethod, "Constructor", "println", "start");
			NoteLog(ame_Log_Statement, "Constructor", "println", "const byte& c_byte, int a_type");
			this->m_pos = byteCharSize(a_type, c_byte);
			this->m_size = getAvailableSize(this->getPosition());

			this->m_t_value = this->create(this->m_size);
			byteToCharPointer(c_byte, this->getPosition(), 0, this->m_t_value, a_type, true);
			NoteLog(ame_Log_Statement, "Constructor", "println", this->getPosition());
			NoteLog(ame_Log_Statement, "Constructor", "println", this->m_size);
			NoteLog(ame_Log_EndMethod, "Constructor", "println", "");
		}
*/
		Note(const String& source){
			NoteLog(ame_Log_StartMethod, "Constructor", "println", "const String& source");
			NoteLog(ame_Log_Statement, "Constructor", "println", "String:");
			NoteLog(ame_Log_Statement, "Constructor", "println", source);
			if(source != ""){
				int i_pos = source.length();
				this->createArray(i_pos);
				this->copyPointer(source.c_str(), i_pos);
				this->copyEndValue();
				NoteLog(ame_Log_Statement, "Constructor", "println", this->getPosition());
				NoteLog(ame_Log_Statement, "Constructor", "println", this->m_size);
				NoteLog(ame_Log_Statement, "Constructor", "println", this->m_t_value);
			}
			NoteLog(ame_Log_EndMethod, "Constructor", "println", "");
		}

		// Note(String&& source){
			// NoteLog(ame_Log_StartMethod, "Constructor", "println", "start");
			// NoteLog(ame_Log_Statement, "Constructor", "println", "String&& source");
			// if(!source.isEmpty()){
				// this->m_t_value = source.c_str();
				// source.c_str() = nullptr;
			// }
			// NoteLog(ame_Log_EndMethod, "Constructor", "println", "");
		// }
		
		virtual String toString() const{
			String i_string;
			for(int x = 0; x < this->getPosition(); x++){
				i_string += this->get(x);
			}
			return i_string;
		}

		#endif

		virtual ~Note(){
			NoteLog(ame_Log_StartMethod, "Destructor", "println", "");
			NoteLog(ame_Log_EndMethod, "Destructor", "println", "");
		}

		virtual char* pointer()const{
			NoteLog(ame_Log_StartMethod, "pointer", "println", "");
			ArrayLog(ame_Log_Statement, "pointer", "println", "Pointer: ");
			ArrayLog(ame_Log_Statement, "pointer", "println", this->m_t_value);
			ArrayLog(ame_Log_EndMethod, "pointer", "println", "");
			return this->m_t_value;
		}

		virtual bool hasEndValue()const{
			const_NoteLog(ame_Log_StartMethod, "hasEndValue", "println", "");
			const_NoteLog(ame_Log_EndMethod, "hasEndValue", "println", "");
			return true;
		}

		virtual char endValue()const{
			const_NoteLog(ame_Log_StartMethod, "endValue", "println", "");
			const_NoteLog(ame_Log_EndMethod, "endValue", "println", "");
            return '\0';
		}

		virtual size_t printTo(Print& p) const{
			const_NoteLog(ame_Log_StartMethod, "printTo", "println", "");
			if(this->isEmpty()){
                const_NoteLog(ame_Log_EndMethod, "printTo", "println", "");
				return 0;
			}
			size_t i_size = 0;
			char i_endValue = this->endValue();
			for(int x = 0; x < this->getPosition(); x++){
				char f_value = this->m_t_value[x];
                if(f_value == i_endValue){
					const_NoteLog(ame_Log_EndMethod, "printTo", "println", "f_value == i_endValue");
                    const_NoteLog(ame_Log_EndMethod, "printTo", "println", "index: ");
                    const_NoteLog(ame_Log_EndMethod, "printTo", "println", x);
                    break;
                }
				p.print(f_value);
				i_size += sizeof(f_value);
			}
			const_NoteLog(ame_Log_EndMethod, "printTo", "println", "");
			return i_size;
		}

		virtual int length(void) const{
			const_NoteLog(ame_Log_StartMethod, "length", "println", "");
			int i_length = this->arrayLength(this->m_t_value);
			if(i_length <= 0){
				const_NoteLog(ame_Log_EndMethod, "length", "println", "");
				return 0;
			}
			const_NoteLog(ame_Log_EndMethod, "length", "println", "");
			return i_length;
		}

		virtual int getAvailableSize(int a_pos){
			NoteLog(ame_Log_StartMethod, "getAvailableSize", "println", "");
			NoteLog(ame_Log_EndMethod, "getAvailableSize", "println", "");
			return a_pos + 1;
		}

		virtual char* create(int a_size){
			NoteLog(ame_Log_StartMethod, "create", "println", "");
			NoteLog(ame_Log_EndMethod, "create", "println", "");
			return new char[a_size];
		}

		virtual int boolCharSize(bool a_value){
			return 1;
		}

		virtual void copyExternBool(char* a_array, bool a_position, bool a_value, int a_size){
			NoteLog(ame_Log_StartMethod, "copyExternBool", "println", "");

			NoteLog(ame_Log_Statement, "copyExternBool", "println", "a_value");
			NoteLog(ame_Log_Statement, "copyExternBool", "println", a_value);
			NoteLog(ame_Log_Statement, "copyExternBool", "println", "Array Length:");
			NoteLog(ame_Log_Statement, "copyExternBool", "println", a_size);

			if(a_array == nullptr){
				NoteLog(ame_Log_EndMethod, "copyExternBool", "println", "a_array == nullptr");
				return;
			}

			if(a_size == 1){
				if(a_value){
					a_array[a_position] = 1 + 48;
				}else{
					a_array[a_position] = 0 + 48;
				}
				NoteLog(ame_Log_EndMethod, "copyExternBool", "println", "a_size == 1");
				return;
			}

			if(a_size == 4){//true
				if(!a_value){
					a_array[a_position] = 't';
					a_array[a_position + 1] = 'r';
					a_array[a_position + 2] = 'u';
					a_array[a_position + 3] = 'e';
				}
			}

			if(a_size == 5){//false
				if(!a_value){
					a_array[a_position] = 'f';
					a_array[a_position + 1] = 'a';
					a_array[a_position + 2] = 'l';
					a_array[a_position + 3] = 's';
					a_array[a_position + 4] = 'e';
				}
			}

			NoteLog(ame_Log_Statement, "copyExternBool", "println", "Array Length:");
			NoteLog(ame_Log_Statement, "copyExternBool", "println", a_size);

			NoteLog(ame_Log_EndMethod, "copyExternBool", "println", "");
		}
		
		virtual char* getBool(bool a_value){
			NoteLog(ame_Log_StartMethod, "getBool", "println", "");
			int i_array_length = boolCharSize(a_value);
			char* i_pointer = this->createArrayClone(i_array_length);
			this->copyExternBool(i_pointer, 0, a_value, i_array_length);
			this->copyExternEndValue(i_pointer, i_array_length);
			NoteLog(ame_Log_EndMethod, "getBool", "println", "");
			return i_pointer;
		}

		virtual bool isBool() const{
			NoteLog(ame_Log_StartMethod, "isBool", "println", "");
			if(this->getPosition() != 1){
				NoteLog(ame_Log_EndMethod, "isBool", "println", "Not a bool");
				return false;
			}
			NoteLog(ame_Log_EndMethod, "isBool", "println", "Is a bool");
			return this->get(0) == '0' || this->get(0) == '1';
		}

		virtual int intCharSize(int a_value)const{
			const_NoteLog(ame_Log_StartMethod, "intCharSize", "println", "");
			const_NoteLog(ame_Log_Statement, "intCharSize", "println", "");
			int i_size_val = 0;
			int x = 1;
			int add_x = 0;
			if(a_value < 0){
				a_value *= -1;
				add_x++;
			}
			for( ; x < 100; x++){
				int expn = 1;
				for(int y = 0; y < x; y++){
					expn *= 10;
				}
				if(a_value/expn < 1){
					i_size_val = x;
					break;
				}
			}
			const_NoteLog(ame_Log_EndMethod, "intCharSize", "println", "");
			return i_size_val + add_x;
		}
		
		virtual void copyExternInt(char* a_array, bool a_position, int a_value, int a_size){
			NoteLog(ame_Log_StartMethod, "intToCharPointer", "println", "");
			NoteLog(ame_Log_Statement, "intToCharPointer", "println", "");
			if(a_array == nullptr){
				NoteLog(ame_Log_EndMethod, "intToCharPointer", "println", "");
				return;
			}
			int position = a_position;
			bool isNegative = false;
			if(a_value < 0){
				NoteLog(ame_Log_Statement, "intToCharPointer", "println", "negative value");
				NoteLog(ame_Log_Statement, "intToCharPointer", "println", "Position: ");
				NoteLog(ame_Log_Statement, "intToCharPointer", "println", position);
				isNegative = true;
				a_value *= -1;
				a_size--;
				a_array[position] = 45;
				position++;
			}
			int i_value_reduction = 1;
			int i_reduce_value = 1;
			int i_output_value = 1;
			for(int x = 0; x < a_size; x++){
				int exponent = 1;
				for(int y = 0; y < a_size - x - 1; y++){
					exponent *= 10;
				}
				i_value_reduction = a_value / exponent;
				if(x == 0){
					i_output_value = i_value_reduction;
				}else{
					i_output_value = i_value_reduction - i_reduce_value;
				}
				i_reduce_value = i_value_reduction * 10;
				NoteLog(ame_Log_Statement, "intToCharPointer", "println", "exponent: ");
				NoteLog(ame_Log_Statement, "intToCharPointer", "println", exponent);
				NoteLog(ame_Log_Statement, "intToCharPointer", "println", "value reduction: ");
				NoteLog(ame_Log_Statement, "intToCharPointer", "println", i_value_reduction);
				NoteLog(ame_Log_Statement, "intToCharPointer", "println", "reduce value: ");
				NoteLog(ame_Log_Statement, "intToCharPointer", "println", i_reduce_value);
				NoteLog(ame_Log_Statement, "intToCharPointer", "println", "output value: ");
				NoteLog(ame_Log_Statement, "intToCharPointer", "println", i_output_value);
				NoteLog(ame_Log_Statement, "intToCharPointer", "println", "Position: ");
				NoteLog(ame_Log_Statement, "intToCharPointer", "println", position);
				a_array[position] = i_output_value + 48;
				position++;
			}

			NoteLog(ame_Log_EndMethod, "intToCharPointer", "println", "");
		}
		
		virtual char* getInt(int a_value){
			NoteLog(ame_Log_StartMethod, "getInt", "println", "");
			int i_array_length = intCharSize(a_value);
			char* i_pointer = this->createArrayClone(i_array_length);
			this->copyExternInt(i_pointer, 0, a_value, i_array_length);
			this->copyExternEndValue(i_pointer, i_array_length);
			NoteLog(ame_Log_EndMethod, "getInt", "println", "");
			return i_pointer;
		}
		
		virtual bool isInt() const{ 
			NoteLog(ame_Log_StartMethod, "isInt", "println", "");
			if(this->isEmpty()){
				NoteLog(ame_Log_EndMethod, "isInt", "println", "Not a float");
				return false;
			}
			for(int i = 0; i < this->length(); i++){
				char f_char = this->get(i);
				if(!this->isNumber(f_char)){
					NoteLog(ame_Log_EndMethod, "isInt", "println", "Not a float");
					return false;
				}
			}
			NoteLog(ame_Log_EndMethod, "isInt", "println", "Is a float");
			return true;
		}

		virtual int longCharSize(long value)const{
			NoteLog(ame_Log_StartMethod, "longCharSize", "println", "");
			NoteLog(ame_Log_Statement, "longCharSize", "println", "");
			int i_size_val = 0;
			int x = 1;
			int add_x = 0;
			if(value < 0){
				value *= -1;
				add_x++;
			}
			for( ; x < 100; x++){
				long expn = 1;
				for(int y = 0; y < x; y++){
					expn *= 10;
				}
				if(value/expn < 1){
					i_size_val = x;
					break;
				}
			}
			NoteLog(ame_Log_EndMethod, "longCharSize", "println", "");
			return i_size_val + add_x;
		}

		virtual void copyExternLong(char* a_array, bool a_position, long a_value, int a_size){
			NoteLog(ame_Log_StartMethod, "copyExternLong", "println", "");
			NoteLog(ame_Log_Statement, "copyExternLong", "println", "a_value");
			NoteLog(ame_Log_Statement, "copyExternLong", "println", a_value);
			NoteLog(ame_Log_Statement, "copyExternLong", "println", "a_size");
			NoteLog(ame_Log_Statement, "copyExternLong", "println", a_size);
			if(a_array == nullptr){
				NoteLog(ame_Log_EndMethod, "copyExternLong", "println", "chr == nullptr");
				return;
			}
			int position = a_position;
			bool isNegative = false;
			if(a_value < 0){
				isNegative = true;
				a_value *= -1;
				a_size--;
				a_array[position] = 45;
				position++;
			}
			long n_value = 1;
			long r_value = 1;
			long s_value = 1;
			for(int x = 0; x < a_size; x++){
				long expn = 1;
				for(int y = 0; y < a_size - x - 1; y++){
					expn *= 10;
				}
				n_value = a_value / expn;
				if(x == 0){
					s_value = n_value;
				}else{
					s_value = n_value - r_value;
				}
				r_value = n_value * 10;
				a_array[position] = s_value + 48;
				position++;
			}
			
			NoteLog(ame_Log_EndMethod, "copyExternLong", "println", "");
		}
		
		virtual char* getLong(long a_value){
			NoteLog(ame_Log_StartMethod, "getLong", "println", "");
			int i_array_length = intCharSize(a_value);
			char* i_pointer = this->createArrayClone(i_array_length);
			this->copyExternInt(i_pointer, 0, a_value, i_array_length);
			this->copyExternEndValue(i_pointer, i_array_length);
			NoteLog(ame_Log_EndMethod, "getLong", "println", "");
			return i_pointer;
		}

		virtual bool isLong() const{
			NoteLog(ame_Log_StartMethod, "isLong", "println", "");
			if(this->isEmpty()){
				NoteLog(ame_Log_EndMethod, "isLong", "println", "Not a long");
				return false;
			}
			if(this->getLastChar() != 'l'){
				NoteLog(ame_Log_EndMethod, "isLong", "println", "Not a long");
				return false;
			}
			for(int i = 0; i < this->length() - 1; i++){
				char f_char = this->get(i);
				if(!this->isNumber(f_char)){
					NoteLog(ame_Log_EndMethod, "isLong", "println", "Not a long");
					return false;
				}
			}
			NoteLog(ame_Log_EndMethod, "isLong", "println", "Is a long");
			return true;
		}
		
		virtual int floatCharSize(float a_value, int extra){
			NoteLog(ame_Log_StartMethod, "floatCharSize", "println", "");
			NoteLog(ame_Log_Statement, "floatCharSize", "println", "");
			int i_size_val = 0;
			int x = 1;
			int add_x = 0;
			if(a_value < 0){
				a_value *= -1;
				add_x++;
			}
			for( ; x < 100; x++){
				int expn = 1;
				for(int y = 0; y < x; y++){
					expn *= 10;
				}
				if(a_value/expn < 1){
					i_size_val = x;
					break;
				}
			}
			NoteLog(ame_Log_EndMethod, "floatCharSize", "println", "");
			return i_size_val + add_x + extra + 1;
		}

		virtual void copyExternFloat(char* a_array, bool a_position, float a_value, int a_size, int decimal_size){
			NoteLog(ame_Log_StartMethod, "copyFloat", "println", "");

			NoteLog(ame_Log_Statement, "copyFloat", "println", "a_value");
			NoteLog(ame_Log_Statement, "copyFloat", "println", a_value);
			NoteLog(ame_Log_Statement, "copyFloat", "println", "a_size");
			NoteLog(ame_Log_Statement, "copyFloat", "println", a_size);
			NoteLog(ame_Log_Statement, "copyFloat", "println", "decimal_size");
			NoteLog(ame_Log_Statement, "copyFloat", "println", decimal_size);

			if(a_array == nullptr){
				NoteLog(ame_Log_EndMethod, "copyFloat", "println", "");
				return;
			}
			int position = a_position;
			bool isNegative = false;
			NoteLog(ame_Log_Statement, "copyFloat", "println", "position");
			NoteLog(ame_Log_Statement, "copyFloat", "println", position);
			if(a_value < 0){
				NoteLog(ame_Log_EndMethod, "copyFloat", "println", "a_value < 0");
				isNegative = true;
				a_value *= -1;
				a_size--;
				a_array[position] = 45;
				position++;
			}
			NoteLog(ame_Log_Statement, "copyFloat", "println", "position");
			NoteLog(ame_Log_Statement, "copyFloat", "println", position);
			int n_value = 1;
			int r_value = 1;
			int s_value = 1;
			int i_size = a_size - decimal_size - 1;
			NoteLog(ame_Log_Statement, "copyFloat", "println", "i_size");
			NoteLog(ame_Log_Statement, "copyFloat", "println", i_size);
			for(int x = 0; x < i_size; x++){
				int expn = 1;
				for(int y = 0; y < i_size - x - 1; y++){
					expn *= 10;
				}
				n_value = a_value / expn;
				if(x == 0){
					s_value = n_value;
				}else{
					s_value = n_value - r_value;
				}
				r_value = n_value * 10;
				a_array[position] = s_value + 48;
				position++;
			}
			NoteLog(ame_Log_Statement, "copyFloat", "println", "position");
			NoteLog(ame_Log_Statement, "copyFloat", "println", position);

			a_array[position] = 46;
			position++;
			
			NoteLog(ame_Log_Statement, "copyFloat", "println", "position");
			NoteLog(ame_Log_Statement, "copyFloat", "println", position);

			n_value = 1;
			r_value = 1;
			s_value = 1;
			float i_value = a_value - (int)a_value;
			NoteLog(ame_Log_Statement, "copyFloat", "println", "i_value");
			NoteLog(ame_Log_Statement, "copyFloat", "println", i_value);
			for(int x = 0; x < decimal_size; x++){
				int expn = 10;
				for(int y = 0; y < x; y++){
					expn *= 10;
				}
				n_value = i_value * expn;
				if(x == 0){
					s_value = n_value;
				}else{
					s_value = n_value - r_value;
				}
				r_value = n_value * 10;
				a_array[position] = s_value + 48;
				position++;
			}
			NoteLog(ame_Log_Statement, "copyFloat", "println", "position");
			NoteLog(ame_Log_Statement, "copyFloat", "println", position);

			NoteLog(ame_Log_Statement, "copyFloat", "println", "Array Length:");
			NoteLog(ame_Log_Statement, "copyFloat", "println", a_size);

			NoteLog(ame_Log_EndMethod, "copyFloat", "println", "");
		}
		
		virtual char* getFloat(float a_value){
			NoteLog(ame_Log_StartMethod, "getFloat", "println", "");
			int i_array_length = floatCharSize(a_value, 4);
			char* i_pointer = this->createArrayClone(i_array_length);
			this->copyExternFloat(i_pointer, 0, a_value, i_array_length, 4);
			this->copyExternEndValue(i_pointer, i_array_length);
			NoteLog(ame_Log_EndMethod, "getFloat", "println", "");
			return i_pointer;
		}
		
		virtual bool isFloat() const{ 
			NoteLog(ame_Log_StartMethod, "isFloat", "println", "");
			if(this->isEmpty()){
				NoteLog(ame_Log_EndMethod, "isFloat", "println", "Not a float");
				return false;
			}
			if(this->getLastChar() != 'f'){
				NoteLog(ame_Log_EndMethod, "isFloat", "println", "Not a float");
				return false;
			}
			bool i_has_decimal_point = false;
			for(int i = 0; i < this->length() - 1; i++){
				char f_char = this->get(i);
				if(!this->isNumber(f_char) && f_char != '.'){
					NoteLog(ame_Log_EndMethod, "isFloat", "println", "Not a float");
					return false;
				}
				if(f_char == '.'){
					if(i_has_decimal_point){
						NoteLog(ame_Log_EndMethod, "isFloat", "println", "Not a float");
						return false;
					}else{
						i_has_decimal_point = true;
					}
				}
			}
			NoteLog(ame_Log_EndMethod, "isFloat", "println", "Is a float");
			return true;
		}
		
		virtual bool isNote() const{
			if(this->isEmpty()){
				return false;
			}
			if(this->get(0) != '"' && this->getLastChar() != '"'){
				return false;
			}
			for(int i = 0; i < this->length(); i++){
				if(i != 0 && i != this->length() - 1){
					if(this->get(i) == '"'){
						return false;
					}
				}
			}
			return true;
		}
		
		virtual Note extractNote(){//   \"Hellow\"
			if(this->isEmpty()){
				return Note();
			}
			if(this->get(0) != '"' && this->getLastChar() != '"'){
				return Note();
			}
			Note i_extract = *this;
			i_extract.removeFirstIndex();
			i_extract.removeLastIndex();
			return i_extract;
		}
		
		virtual bool isNumber() const{
			if(this->isEmpty()){
				return false;
			}
			char lastChar = this->getLastChar();
			int c_size = this->length();
			if(lastChar == 'f' || lastChar == 'l'){
				c_size = this->length() - 1;
			}
			bool i_has_decimal_point = false;
			for(int i = 0; i < c_size; i++){
				char f_char = this->get(i);
				if(!this->isNumber(f_char) && f_char != '.'){
					NoteLog(ame_Log_EndMethod, "isFloat", "println", "Not a float");
					return false;
				}
				if(f_char == '.'){
					if(i_has_decimal_point){
						NoteLog(ame_Log_EndMethod, "isFloat", "println", "Not a float");
						return false;
					}else{
						i_has_decimal_point = true;
					}
				}
			}
			return true;
		}

		virtual void fix(){
			if(this->m_pos == this->getSize()){
				return;
			}
			for(int x = this->getPosition(); x < this->getSize(); x++){
				if(x == this->getSize() - 1){
					this->set(x, this->endValue());
				}else{
					this->set(x, ' ');
				}
			}
		}

		virtual Note addNote(const Note& a_note){
			NoteLog(ame_Log_StartMethod, "addNote", "println", "const Note& a_note");
			Note i_note = *this;
			NoteLog(ame_Log_EndMethod, "addNote", "println", "");
			return i_note.addLocalNote(a_note);
		}

		virtual Note addLocalNote(const Note& a_note){
			NoteLog(ame_Log_StartMethod, "addLocalNote", "println", "const Note& a_note");
			NoteLog(ame_Log_EndMethod, "addLocalNote", "println", "");
			return this->insertLocalNote(this->getPosition(), a_note);
		}

		virtual Note insertLocalNote(int a_position, const Note& a_note){
			NoteLog(ame_Log_StartMethod, "insertLocalNote", "println", "const Note& a_note");
			
			this->insertLocalArrayPointer(a_position, a_note.pointer());
			
			NoteLog(ame_Log_EndMethod, "insertLocalNote", "println", "");
			return *this;
		}
		
		virtual Note addInt(const int& a_number){
			NoteLog(ame_Log_StartMethod, "addInt", "println", "const int& a_number");
			Note i_note = *this;
			NoteLog(ame_Log_EndMethod, "addInt", "println", "");
			return i_note.addLocalInt(a_number);
		}

		virtual Note addLocalInt(const int& a_number){
			NoteLog(ame_Log_StartMethod, "addLocalInt", "println", "const int& a_number");
			NoteLog(ame_Log_EndMethod, "addLocalInt", "println", "");
			return this->insertLocalInt(this->getPosition(), a_number);
		}

		virtual Note insertLocalInt(int a_position, const int& a_number){
			NoteLog(ame_Log_StartMethod, "insertLocalInt", "println", "const int& a_number");

			char* i_pointer = this->getInt(a_number);
			this->insertLocalArrayPointer(a_position, i_pointer);
			delete i_pointer;
			
			NoteLog(ame_Log_EndMethod, "insertLocalInt", "println", "");
			return *this;
		}
		
		virtual Note addFloat(const float& a_number){
			NoteLog(ame_Log_StartMethod, "addFloat", "println", "const float& a_number");
			Note i_note = *this;
			NoteLog(ame_Log_EndMethod, "addFloat", "println", "");
			return i_note.addLocalFloat(a_number);
		}

		virtual Note addLocalFloat(const float& a_number){
			NoteLog(ame_Log_StartMethod, "addLocalFloat", "println", "const float& a_number");
			NoteLog(ame_Log_EndMethod, "addLocalFloat", "println", "");
			return this->insertLocalFloat(this->getPosition(), a_number);
		}

		virtual Note insertLocalFloat(int a_position, const float& a_number){
			NoteLog(ame_Log_StartMethod, "insertLocalFloat", "println", "const float& a_note");

			char* i_pointer = this->getFloat(a_number);
			this->insertLocalArrayPointer(a_position, i_pointer);
			delete i_pointer;

			NoteLog(ame_Log_EndMethod, "insertLocalFloat", "println", "");
			return *this;
		}
		
		virtual Note addLong(const long& a_number){
			NoteLog(ame_Log_StartMethod, "addLong", "println", "const long& a_number");
			Note i_note = *this;
			NoteLog(ame_Log_EndMethod, "addLong", "println", "");
			return i_note.addLocalLong(a_number);
		}

		virtual Note addLocalLong(const long& a_number){
			NoteLog(ame_Log_StartMethod, "addLocalLong", "println", "const long& a_number");
			NoteLog(ame_Log_EndMethod, "addLocalLong", "println", "");
			return this->insertLocalLong(this->getPosition(), a_number);
		}

		virtual Note insertLocalLong(int a_position, const long& a_number){
			NoteLog(ame_Log_StartMethod, "insertLocalLong", "println", "const long& a_note");

			char* i_pointer = this->getLong(a_number);
			this->insertLocalArrayPointer(a_position, i_pointer);
			delete i_pointer;

			NoteLog(ame_Log_EndMethod, "insertLocalLong", "println", "");
			return *this;
		}
		
		virtual Note addBool(const bool& a_number){
			NoteLog(ame_Log_StartMethod, "addBool", "println", "const bool& a_number");
			Note i_note = *this;
			NoteLog(ame_Log_EndMethod, "addBool", "println", "");
			return i_note.addLocalBool(a_number);
		}

		virtual Note addLocalBool(const bool& a_number){
			NoteLog(ame_Log_StartMethod, "addLocalBool", "println", "const bool& a_number");
			NoteLog(ame_Log_EndMethod, "addLocalBool", "println", "");
			return this->insertLocalBool(this->getPosition(), a_number);
		}

		virtual Note insertLocalBool(int a_position, const bool& a_number){
			NoteLog(ame_Log_StartMethod, "insertLocalBool", "println", "const bool& a_note");

			char* i_pointer = this->getBool(a_number);
			this->insertLocalArrayPointer(a_position, i_pointer);
			delete i_pointer;
			
			NoteLog(ame_Log_EndMethod, "insertLocalBool", "println", "");
			return *this;
		}

		virtual bool isNumber(char a_char) const{
			NoteLog(ame_Log_StartMethod, "isNumber", "println", "");
			NoteLog(ame_Log_EndMethod, "isNumber", "println", "");
			return a_char > 47 && a_char < 58;
		}

		virtual int getNumber(char a_char) const{
			NoteLog(ame_Log_StartMethod, "isNumber", "println", "");
			NoteLog(ame_Log_EndMethod, "isNumber", "println", "");
			return a_char - 48;
		}

		virtual bool isDecimalPoint(char a_char) const{
			NoteLog(ame_Log_StartMethod, "isNumber", "println", "");
			NoteLog(ame_Log_EndMethod, "isNumber", "println", "");
			return a_char == 46;
		}

		bool toBool()const{
			NoteLog(ame_Log_StartMethod, "toBool", "println", "");
			if(this->m_pos == 1){
				if(this->get(0) == '1'){
					NoteLog(ame_Log_EndMethod, "toInt", "println", "true");
					return true;
				}
				if(this->get(0) == '0'){
					NoteLog(ame_Log_EndMethod, "toInt", "println", "false");
					return false;
				}
			}
			NoteLog(ame_Log_EndMethod, "toInt", "println", "false");
			return false;
		}

		int toInt()const{
			NoteLog(ame_Log_StartMethod, "toInt", "println", "");
			if(this->isEmpty()){
				NoteLog(ame_Log_EndMethod, "toInt", "println", "this->isEmpty()");
				return 0;
			}
			int i_start = 0;
			if(this->get(0) == '-'){
				i_start = 1;
			}
			int output = 0;
			int c_size = this->length();
			bool lastDecimals = false;
			for(int x = i_start; x < c_size; x++){
				char f_char = this->m_t_value[x];
				NoteLog(ame_Log_StartMethod, "toInt", "println", "f_char");
				NoteLog(ame_Log_StartMethod, "toInt", "println", f_char);
				if(this->isDecimalPoint(f_char)){
					if(lastDecimals){
						NoteLog(ame_Log_EndMethod, "toInt", "println", "allready has a decimal point");
						return 0;
					}
					lastDecimals = true;
					continue;
				}
				if(this->isNumber(f_char)){
					if(lastDecimals){
						
					}else{
						NoteLog(ame_Log_Statement, "toInt", "println", "int part");
						if(x != i_start){
							output *= 10;
						}
						output += (f_char - 48);
						NoteLog(ame_Log_Statement, "toInt", "println", "output");
						NoteLog(ame_Log_Statement, "toInt", "println", output);
					}
				}else{
					NoteLog(ame_Log_EndMethod, "toInt", "println", "");
					return 0;
				}
			}
			if(i_start == 1){
				output *= -1;
			}
			NoteLog(ame_Log_EndMethod, "toInt", "println", "");
			return output;
		}
		
		long toLong()const{
			NoteLog(ame_Log_StartMethod, "toLong", "println", "");
			if(this->isEmpty()){
				NoteLog(ame_Log_EndMethod, "toLong", "println", "this->isEmpty()");
				return 0;
			}
			int i_start = 0;
			if(this->get(0) == '-'){
				i_start = 1;
			}
			long output = 0;
			int c_size = this->length();
			if(this->getLastChar() == 'l'){
				c_size -= 1;
			}
			bool lastDecimals = false;
			for(int x = i_start; x < c_size; x++){
				char f_char = this->m_t_value[x];
				NoteLog(ame_Log_StartMethod, "toLong", "println", "f_char");
				NoteLog(ame_Log_StartMethod, "toLong", "println", f_char);
				if(this->isDecimalPoint(f_char)){
					if(lastDecimals){
						NoteLog(ame_Log_EndMethod, "toLong", "println", "allready has a decimal point");
						return 0;
					}
					lastDecimals = true;
					continue;
				}
				if(this->isNumber(f_char)){
					if(lastDecimals){
						
					}else{
						NoteLog(ame_Log_Statement, "toLong", "println", "int part");
						if(x != i_start){
							output *= 10;
						}
						output += (f_char - 48);
						NoteLog(ame_Log_Statement, "toLong", "println", "output");
						NoteLog(ame_Log_Statement, "toLong", "println", output);
					}
				}else{
					NoteLog(ame_Log_EndMethod, "toLong", "println", "");
					return 0;
				}
			}
			if(i_start == 1){
				output *= -1;
			}
			NoteLog(ame_Log_EndMethod, "toLong", "println", "");
			return output;
		}
		
		float toFloat()const{
			NoteLog(ame_Log_StartMethod, "toFloat", "println", "");
			if(this->isEmpty()){
				NoteLog(ame_Log_EndMethod, "toFloat", "println", "this->isEmpty()");
				return 0;
			}
			int i_start = 0;
			if(this->get(0) == '-'){
				i_start = 1;
			}
			float output = 0;
			int c_size = this->length();
			if(this->getLastChar() == 'f'){
				c_size -= 1;
			}
			bool lastDecimals = false;
			int lastDecimalPosition= 0;
			for(int x = i_start; x < c_size; x++){
				char f_char = this->m_t_value[x];
				NoteLog(ame_Log_Statement, "toFloat", "println", "f_char");
				NoteLog(ame_Log_Statement, "toFloat", "println", f_char);
				if(this->isDecimalPoint(f_char)){
					if(lastDecimals){
						NoteLog(ame_Log_EndMethod, "toFloat", "println", "allready has a decimal point");
						return 0;
					}
					lastDecimals = true;
					lastDecimalPosition= x;
					continue;
				}
				if(this->isNumber(f_char)){
					if(lastDecimals){
						NoteLog(ame_Log_Statement, "toFloat", "println", "has Decimal point");
						float expn = 1;
						for(int y = 0; y < x - lastDecimalPosition; y++){
							expn *= 10;
						}
						NoteLog(ame_Log_Statement, "toFloat", "println", "expn");
						NoteLog(ame_Log_Statement, "toFloat", "println", expn);
						output += ((float)(f_char - 48) / expn);
						NoteLog(ame_Log_Statement, "toFloat", "println", "output");
						NoteLog(ame_Log_Statement, "toFloat", "println", output);
					}else{
						NoteLog(ame_Log_Statement, "toFloat", "println", "int part");
						if(x != i_start){
							output *= 10;
						}
						output += (f_char - 48);
						NoteLog(ame_Log_Statement, "toFloat", "println", "output");
						NoteLog(ame_Log_Statement, "toFloat", "println", output);
					}
				}else{
					NoteLog(ame_Log_EndMethod, "toFloat", "println", "");
					return 0;
				}
			}
			if(i_start == 1){
				output *= -1;
			}
			NoteLog(ame_Log_EndMethod, "toFloat", "println", "");
			return output;
		}

		Note split(int a_position, char a_char) const{
			const_NoteLog(ame_Log_StartMethod, "split", "println", "");
			Note i_note;
			int i_position = 0;

			for(int x = 0; x < this->getPosition(); x++){
				const_NoteLog(ame_Log_Statement, "split", "println", "iteration: ");
				const_NoteLog(ame_Log_Statement, "split", "println", x);
				const char f_char = this->m_t_value[x];
				const_NoteLog(ame_Log_Statement, "split", "println", "char: ");
				const_NoteLog(ame_Log_Statement, "split", "println", f_char);
				const_NoteLog(ame_Log_Statement, "split", "println", "i_note: ");
				const_NoteLog(ame_Log_Statement, "split", "println", i_note);
				if(f_char == a_char){
					const_NoteLog(ame_Log_Statement, "split", "println", "f_char == a_char");
					i_position++;
					const_NoteLog(ame_Log_Statement, "split", "println", "end for loop");
					continue;
				}
				if(i_position == a_position){
					const_NoteLog(ame_Log_Statement, "split", "println", "f_char == a_char");
					i_note.addLocalValue(f_char);
					const_NoteLog(ame_Log_Statement, "split", "println", "i_note: ");
					const_NoteLog(ame_Log_Statement, "split", "println", i_note);
					const_NoteLog(ame_Log_Statement, "split", "println", "end for loop");
					continue;
				}
				if(i_position > a_position){
					const_NoteLog(ame_Log_Statement, "split", "println", "i_position > a_position");
					const_NoteLog(ame_Log_Statement, "split", "println", "end for loop");
					break;
				}
				const_NoteLog(ame_Log_Statement, "split", "println", "end for loop");
			}
			const_NoteLog(ame_Log_EndMethod, "split", "println", "");
			return i_note;
		}

		RawList<Note>* split(char a_char, RawList<Note>* a_list) const{
			const_NoteLog(ame_Log_StartMethod, "split", "println", "");
			if(a_list == nullptr){
				return nullptr;
			}
			Note i_note;
			for(int x = 0; x < this->getPosition(); x++){
				const_NoteLog(ame_Log_Statement, "split", "println", "iteration: ");
				const_NoteLog(ame_Log_Statement, "split", "println", x);
				const char f_char = this->m_t_value[x];
				const_NoteLog(ame_Log_Statement, "split", "println", "char: ");
				const_NoteLog(ame_Log_Statement, "split", "println", f_char);
				const_NoteLog(ame_Log_Statement, "split", "println", "i_note: ");
				const_NoteLog(ame_Log_Statement, "split", "println", i_note);
				if(f_char == a_char){
					const_NoteLog(ame_Log_Statement, "split", "println", "f_char == a_char");
					const_NoteLog(ame_Log_Statement, "split", "println", "i_note: ");
					const_NoteLog(ame_Log_Statement, "split", "println", i_note);
					if(i_note.isEmpty()){
						continue;
					}
					a_list->add(i_note);
					i_note.clear();
					const_NoteLog(ame_Log_Statement, "split", "println", "end for loop");
					continue;
				}
				i_note.addLocalValue(f_char);
				const_NoteLog(ame_Log_Statement, "split", "println", "i_note: ");
				const_NoteLog(ame_Log_Statement, "split", "println", i_note);
				if(x == this->getPosition() - 1){
					const_NoteLog(ame_Log_Statement, "split", "println", "x == this->getPosition() - 1");
					const_NoteLog(ame_Log_Statement, "split", "println", "i_note: ");
					const_NoteLog(ame_Log_Statement, "split", "println", i_note);
					if(i_note.isEmpty()){
						continue;
					}
					a_list->add(i_note);
				}
				const_NoteLog(ame_Log_Statement, "split", "println", "end for loop");
			}
			const_NoteLog(ame_Log_EndMethod, "split", "println", "");
			return a_list;
		}

		virtual char getLastChar() const{
			NoteLog(ame_Log_StartMethod, "getLastChar", "println", "");
			NoteLog(ame_Log_Statement, "getLastChar", "println", "");
			if(this->isEmpty()){
				return this->endValue();
			}
			NoteLog(ame_Log_EndMethod, "getLastChar", "println", "");
			return this->get(this->getPosition() - 1);
		}

		virtual void addLine(){
			NoteLog(ame_Log_StartMethod, "addLine", "println", "");
			this->addLocalValue('\n');
			NoteLog(ame_Log_EndMethod, "addLine", "println", "");
		}

		virtual bool isEndLine(const char& a_char) const{
			NoteLog(ame_Log_StartMethod, "isEndLine", "println", "");
			NoteLog(ame_Log_EndMethod, "isEndLine", "println", "");
			return a_char == '\n';
		}

		virtual int getOrder(Note a_note, char a_split, char a_end){
			NoteLog(ame_Log_StartMethod, "getOrder", "println", "");
			NoteLog(ame_Log_Statement, "getOrder", "println", "");
			Note i_note = "";
			int split_position = 0;
			bool addToNote = true;
			for(int x = 0; x < this->getPosition(); x++){
				// const_NoteLog(ame_Log_Statement, "getOrder", "println", "iteration: ");
				// const_NoteLog(ame_Log_Statement, "getOrder", "println", x);
				const char f_char = this->get(x);
				// const_NoteLog(ame_Log_Statement, "getOrder", "println", "char: ");
				// const_NoteLog(ame_Log_Statement, "getOrder", "println", f_char);
				// const_NoteLog(ame_Log_Statement, "getOrder", "println", "i_note: ");
				// const_NoteLog(ame_Log_Statement, "getOrder", "println", i_note);
				if(f_char == a_end){
					const_NoteLog(ame_Log_Statement, "getOrder", "println", "f_char == a_end");
					const_NoteLog(ame_Log_Statement, "getOrder", "println", "i_note: ");
					const_NoteLog(ame_Log_Statement, "getOrder", "println", i_note);
					i_note = "";
					addToNote = true;
					const_NoteLog(ame_Log_Statement, "getOrder", "println", "end for loop");
					continue;
				}
				if(f_char == a_split){
					const_NoteLog(ame_Log_Statement, "getOrder", "println", "f_char == a_split");
					const_NoteLog(ame_Log_Statement, "getOrder", "println", "i_note: ");
					const_NoteLog(ame_Log_Statement, "getOrder", "println", i_note);
					const_NoteLog(ame_Log_Statement, "getOrder", "println", "split_position: ");
					const_NoteLog(ame_Log_Statement, "getOrder", "println", split_position);
					if(a_note == i_note){
						const_NoteLog(ame_Log_Statement, "getOrder", "println", "a_note == i_note");
						return split_position;
					}
					split_position++;
					i_note = "";
					addToNote = false;
					const_NoteLog(ame_Log_Statement, "getOrder", "println", "end for loop");
					continue;
				}
				if(addToNote){
					i_note.addLocalValue(f_char);
				}
				// const_NoteLog(ame_Log_Statement, "getOrder", "println", "i_note: ");
				// const_NoteLog(ame_Log_Statement, "getOrder", "println", i_note);
				// const_NoteLog(ame_Log_Statement, "getOrder", "println", "end for loop");
			}
			NoteLog(ame_Log_EndMethod, "getOrder", "println", "");
			return -1;
		}

		int getSplitSize(char a_split) const{
			NoteLog(ame_Log_StartMethod, "getSplitSize", "println", "");
			NoteLog(ame_Log_Statement, "getSplitSize", "println", "~Note");
			if(this->isEmpty()){
				return 0;
			}
			int i_size = 1;
			for(int x = 0; x < this->getPosition(); x++){
				char f_char = this->get(x);
				if(f_char == a_split){
					i_size++;
				}
			}

			NoteLog(ame_Log_EndMethod, "getSplitSize", "println", "");
			return i_size;
		}

		int getSizeNoStartNoEnd(char a_split){
			NoteLog(ame_Log_StartMethod, "getSizeNoStartNoEnd", "println", "");
			NoteLog(ame_Log_Statement, "getSizeNoStartNoEnd", "println", "~Note");
			int i_size = 0;
			for(int x = 0; x < length(); x++){
				char f_char = this->get(x);
				if(f_char == a_split){
					i_size++;
					continue;
				}
			}

			NoteLog(ame_Log_EndMethod, "getSizeNoStartNoEnd", "println", "");
			return i_size + 1;
		}

		int getLineSize(){
			NoteLog(ame_Log_StartMethod, "getLineSize", "println", "");
			NoteLog(ame_Log_Statement, "getLineSize", "println", "");
			int i_size = 0;
			int x_c = 0;
			for(int x = 0; x < getPosition(); x++){
				char f_char = this->get(x);
				if(f_char == '\n'){
					i_size++;
					x_c = 0;
					continue;
				}
				x_c++;
			}
			if(x_c == 0){
				return i_size;
			}
			if(x_c > 0){
				return i_size + 1;
			}
			NoteLog(ame_Log_EndMethod, "getLineSize", "println", "");
			return i_size;
		}

		Note getLine(int l, char end){
			NoteLog(ame_Log_StartMethod, "getLine", "println", "");
			NoteLog(ame_Log_Statement, "getLine", "println", "");
			Note c = "";
			int i_size = 0;
			for(int x = 0; x < length(); x++){
				char f_char = this->get(x);
				if(f_char == end){
					if(i_size == l){
						NoteLog(ame_Log_EndMethod, "getLine", "println", "");
						return c;
					}
					c = "";
					i_size++;
					continue;
				}
				c.addLocalValue(f_char);
			}

			NoteLog(ame_Log_EndMethod, "getLine", "println", "");
			return Note();
		}

		void removeLine(int a_line, char a_end){
			NoteLog(ame_Log_StartMethod, "removeLine", "println", "");
			NoteLog(ame_Log_Statement, "removeLine", "println", "");
			if(a_line == -1){
				NoteLog(ame_Log_EndMethod, "removeLine", "println", "");
				return;
			}
			Note i_newTxt;
			int xLine = 0;
			for(int x = 0; x < length(); x++){
				char f_char = this->get(x);
				if(f_char == a_end){
					xLine++;
					if(i_newTxt == ""){
						continue;
					}
					char cnewTxt = i_newTxt.get(i_newTxt.length()-1);
					if(!i_newTxt.isEmpty() && cnewTxt != a_end){
						i_newTxt.addLocalValue(a_end);
					}
					continue;
				}
				if(xLine != a_line){
					i_newTxt.addLocalValue(f_char);
				}
			}

			NoteLog(ame_Log_EndMethod, "removeLine", "println", "");
			this->clear();
			this->addLocalNote(i_newTxt);
		}

		void removeLine(Note a_txt, char a_split, char a_end){
			NoteLog(ame_Log_StartMethod, "removeLine", "println", "");
			NoteLog(ame_Log_Statement, "removeLine", "println", "~Note");
			int i_order = getOrder(a_txt, a_split, a_end);
			if(i_order == -1){
				NoteLog(ame_Log_EndMethod, "removeLine", "println", "");
				return;
			}
			removeLine(i_order, a_end);

			NoteLog(ame_Log_EndMethod, "removeLine", "println", "");
		}

		void writeLine(int line, Note txt, char end){
			NoteLog(ame_Log_StartMethod, "writeLine", "println", "");
			NoteLog(ame_Log_Statement, "writeLine", "println", "");
			Note newTxt = "";
			int xLine = 0;
			int xTxt = 0;
			int xText = 0;
			for(int x = 0; x < length() + txt.length(); x++){
				char ctext = get(xText);
				char ctxt = txt.get(xTxt);
				if(ctext == end){
					xLine++;
					xText++;
					newTxt.addLocalValue(end);
					continue;
				}
				if((xLine == line || xText >= length())){
					newTxt.addLocalValue(ctxt);
					xTxt++;
					if(xTxt == txt.length()){
						newTxt.addLocalValue('\n');
						xLine++;
					}
				}else{
					newTxt.addLocalValue(ctext);
					xText++;
				}
			}
			
			this->clear();
			this->addLocalNote(newTxt);

			NoteLog(ame_Log_EndMethod, "writeLine", "println", "");
		}

		void writeLine(Note cmdt, Note txt, char split, char end){
			NoteLog(ame_Log_StartMethod, "writeLine", "println", "");
			NoteLog(ame_Log_Statement, "writeLine", "println", "~Note");
			int line = getOrder(cmdt, split, end);
			if(line == -1){
				NoteLog(ame_Log_EndMethod, "writeLine", "println", "");
				return;
			}
			writeLine(line, txt, end);
			removeLine(line + 1, end);

			NoteLog(ame_Log_EndMethod, "writeLine", "println", "");
		}

		Note getCommand(int l, char split, char end){
			NoteLog(ame_Log_StartMethod, "getCommand", "println", "");
			NoteLog(ame_Log_Statement, "getCommand", "println", "~Note");
			Note c = "";
			bool init = true;
			int gcmd = 0;
			for(int x = 0; x < length(); x++){
				char cr = get(x);
				if(cr == end){
					if(gcmd == l){
						NoteLog(ame_Log_EndMethod, "getCommand", "println", "");
						return c;
					}
					init = true;
					gcmd++;
					c = "";
					continue;
				}
				if(init){
					if(cr == split){
						if(gcmd == l){
							NoteLog(ame_Log_EndMethod, "getCommand", "println", "");
							return c;
						}
						init = false;
						c = "";
						continue;
					}
					c.addLocalValue(cr);
				}
			}

			NoteLog(ame_Log_EndMethod, "getCommand", "println", "");
			return "";
		}

		Note getArgument(int l, char split, char end){
			NoteLog(ame_Log_StartMethod, "getArgument", "println", "");
			NoteLog(ame_Log_Statement, "getArgument", "println", "~Note");
			Note c = "";
			bool init = false;
			int gcmd = 0;
			for(int x = 0; x < length(); x++){
				char cr = get(x);
				if(cr == end){
					if(gcmd == l){
						NoteLog(ame_Log_EndMethod, "getArgument", "println", "");
						return c;
					}
					gcmd++;
					c = "";
					init = false;
					continue;
				}
				if(cr == split && !init){
					init = true;
					continue;
				}
				if(init && gcmd == l){
					c.addLocalValue(cr);
				}
			}
			if(gcmd == l){
				NoteLog(ame_Log_EndMethod, "getArgument", "println", "");
				return c;
			}

			NoteLog(ame_Log_EndMethod, "getArgument", "println", "");
			return Note();
		}
		
		virtual int getIndex(Note a_search){
			NoteLog(ame_Log_StartMethod, "getIndex", "println", "");
			Note i_note;
			int i_index = 0;
			int i_note_count = 0;
			for(int x = 0; x < this->getPosition(); x++){
				char f_char = this->get(x);
				NoteLog(ame_Log_StartMethod, "getIndex", "println", "f_char");
				NoteLog(ame_Log_StartMethod, "getIndex", "println", f_char);
				i_note.addLocalValue(f_char);
				char f_char_search = a_search.get(i_note_count);
				char f_char_record = i_note.get(i_note_count);
				if(f_char_search == f_char_record){
					NoteLog(ame_Log_StartMethod, "getIndex", "println", "f_char_search == f_char_record");
					if(i_note_count == 0){
						i_index = x;
					}
					i_note_count++;
				}else{
					i_note_count = 0;
					i_note.clear();
					continue;
				}
				if(a_search == i_note){
					NoteLog(ame_Log_StartMethod, "getIndex", "println", "a_search == i_note");
					return i_index;
				}
			}
			NoteLog(ame_Log_EndMethod, "getIndex", "println", "-1");
			return -1;
		}
		
		virtual bool removeNote(Note a_note){
			NoteLog(ame_Log_StartMethod, "removeNote", "println", "");
			int i_index = this->getIndex(a_note);
			if(i_index == -1){
				return false;
			}
			this->remove(i_index, a_note.getPosition());
			NoteLog(ame_Log_EndMethod, "removeNote", "println", "");
			return false;
		}

		virtual bool replace(Note a_search, Note a_change){
			NoteLog(ame_Log_StartMethod, "replace", "println", "");
			NoteLog(ame_Log_Statement, "replace", "println", "a_search");
			NoteLog(ame_Log_Statement, "replace", "println", a_search);
			NoteLog(ame_Log_Statement, "replace", "println", "a_change");
			NoteLog(ame_Log_Statement, "replace", "println", a_change);
			Note i_note;
			Note i_search;
			int i_search_index = 0;

			if(this->isEmpty()){
				NoteLog(ame_Log_EndMethod, "replace", "println", "this->isEmpty()");
				return false;
			}
			int i_index = this->getIndex(a_search);
			NoteLog(ame_Log_Statement, "replace", "println", "i_index");
			NoteLog(ame_Log_Statement, "replace", "println", i_index);
			if(i_index == -1){
				NoteLog(ame_Log_EndMethod, "replace", "println", "i_index == -1");
				return false;
			}
			this->remove(i_index, a_change.getPosition());
			this->insertLocalNote(i_index, a_change);
			NoteLog(ame_Log_EndMethod, "replace", "println", "");
			return true;
		}

		virtual Note& operator=(const Note& source){
			NoteLog(ame_Log_StartMethod, "operator=", "println", "");
			this->clear();
			NoteLog(ame_Log_Statement, "operator=", "println", "const Note& val");
			int i_array_length = source.length();
			if(i_array_length > 0){
				this->m_size = this->getAvailableSize(i_array_length);
				this->m_t_value = this->create(this->m_size);
				this->copyPointer(source.m_t_value, i_array_length);
				this->copyEndValue(this->getPosition());
				NoteLog(ame_Log_Statement, "operator=", "println", "Array Length:");
				NoteLog(ame_Log_Statement, "operator=", "println", i_array_length);
				NoteLog(ame_Log_Statement, "operator=", "println", "Array Position:");
				NoteLog(ame_Log_Statement, "operator=", "println", this->getPosition());
				NoteLog(ame_Log_Statement, "operator=", "println", "Array Size:");
				NoteLog(ame_Log_Statement, "operator=", "println", this->getSize());
			}
			NoteLog(ame_Log_EndMethod, "operator=", "println", "");
			return *this;
		}

		virtual Note& operator=(Note&& source){
			this->clear();
			NoteLog(ame_Log_StartMethod, "operator=", "println", "");
			NoteLog(ame_Log_Statement, "operator=", "println", "const Note& val");
			int i_array_length = source.length();
			if(i_array_length > 0){
				this->m_pos = source.m_pos;
				this->m_size = source.m_size;
				this->m_t_value = source.m_t_value;
				source.m_t_value = nullptr;
				source.m_pos = 0;
				source.m_size = 0;
				NoteLog(ame_Log_Statement, "operator=", "println", "Array Length:");
				NoteLog(ame_Log_Statement, "operator=", "println", i_array_length);
				NoteLog(ame_Log_Statement, "operator=", "println", "Array Position:");
				NoteLog(ame_Log_Statement, "operator=", "println", this->getPosition());
				NoteLog(ame_Log_Statement, "operator=", "println", "Array Size:");
				NoteLog(ame_Log_Statement, "operator=", "println", this->getSize());
			}
			NoteLog(ame_Log_EndMethod, "operator=", "println", "");
			return *this;
		}

		virtual Note operator+=(const Note& a_note){
			NoteLog(ame_Log_StartMethod, "operator+=", "println", "");
			NoteLog(ame_Log_EndMethod, "operator+=", "println", "");
			return this->addLocalNote(a_note);
		}

		virtual Note operator+=(const char* a_char){
			NoteLog(ame_Log_StartMethod, "operator+=", "println", "");
			NoteLog(ame_Log_EndMethod, "operator+=", "println", "");
			return this->addLocalArrayPointer(a_char);
		}
/*
		virtual Note operator+=(const char& a_char){
			NoteLog(ame_Log_StartMethod, "operator+=", "println", "");
			NoteLog(ame_Log_EndMethod, "operator+=", "println", "");
			return this->addLocalValue(a_char);
		}
*/
		virtual Note operator+=(const bool& a_value){
			NoteLog(ame_Log_StartMethod, "operator+=", "println", "");
			NoteLog(ame_Log_EndMethod, "operator+=", "println", "");
			return this->addLocalBool(a_value);
		}

		virtual Note operator+=(const int& a_value){
			NoteLog(ame_Log_StartMethod, "operator+=", "println", "");
			NoteLog(ame_Log_EndMethod, "operator+=", "println", "");
			return this->addLocalInt(a_value);
		}

		virtual Note operator+=(const long& a_value){
			NoteLog(ame_Log_StartMethod, "operator+=", "println", "");
			NoteLog(ame_Log_EndMethod, "operator+=", "println", "");
			return this->addLocalLong(a_value);
		}

		virtual Note operator+=(const float& a_value){
			NoteLog(ame_Log_StartMethod, "operator+=", "println", "");
			NoteLog(ame_Log_EndMethod, "operator+=", "println", "");
			return this->addLocalFloat(a_value);
		}

		virtual Note operator+(const Note& a_note){
			NoteLog(ame_Log_StartMethod, "operator+", "println", "");
			NoteLog(ame_Log_EndMethod, "operator+", "println", "");
			return this->addNote(a_note);
		}

		virtual Note operator+(char* a_note){
			NoteLog(ame_Log_StartMethod, "operator+", "println", "");
			NoteLog(ame_Log_EndMethod, "operator+", "println", "");
			return this->addArrayPointer(a_note);
		}
/*
		virtual Note operator+(const char& a_note){
			NoteLog(ame_Log_StartMethod, "operator+", "println", "");
			NoteLog(ame_Log_EndMethod, "operator+", "println", "");
			return this->addValue(a_note);
		}
*/
		virtual Note operator+(const bool& a_value){
			NoteLog(ame_Log_StartMethod, "operator+", "println", "");
			NoteLog(ame_Log_EndMethod, "operator+", "println", "");
			return this->addBool(a_value);
		}

		virtual Note operator+(const int& a_value){
			NoteLog(ame_Log_StartMethod, "operator+", "println", "");
			NoteLog(ame_Log_EndMethod, "operator+", "println", "");
			return this->addInt(a_value);
		}

		virtual Note operator+(const long& a_value){
			NoteLog(ame_Log_StartMethod, "operator+", "println", "");
			NoteLog(ame_Log_EndMethod, "operator+", "println", "");
			return this->addLong(a_value);
		}

		virtual Note operator+(const float& a_value){
			NoteLog(ame_Log_StartMethod, "operator+", "println", "");
			NoteLog(ame_Log_EndMethod, "operator+", "println", "");
			return this->addFloat(a_value);
		}

		virtual Note operator-=(const int& a_remove){
			if(this->isEmpty()){
				return *this;
			}

			return *this;
		}

		virtual Note operator-(const int& a_remove){
			Note i_value = *this;
			i_value-=(a_remove);
			return i_value;
		}

		virtual Note operator--(){

			return *this;
		}

		virtual bool operator==(const Note& a_note) const{
			if(a_note.getPosition() != this->getPosition()){
				return false;
			}
			for(int x = 0; x < this->getPosition(); x++){
				char f_char_1 = this->get(x);
				char f_char_2 = a_note.get(x);
				if(f_char_1 != f_char_2){
					return false;
				}
			}
			return true;
		}

		virtual bool operator!=(const Note& a_note){
			if(a_note.getPosition() != this->getPosition()){
				return true;
			}
			for(int x = 0; x < this->getPosition(); x++){
				char f_char_1 = this->get(x);
				char f_char_2 = a_note.get(x);
				if(f_char_1 == f_char_2){
					return false;
				}
			}
			return true;
		}
		
		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){return Class<Note>::getClass();}
		virtual bool instanceof(cppObjectClass* cls){
			return cls == Class<Note>::getClass() || Array<char>::instanceof(cls);
		}
		#endif

};

}

#endif