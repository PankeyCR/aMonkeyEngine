
#include "ame_Level.hpp"

#if defined(ame_untilLevel_7)

#ifndef DipSwitch_hpp
#define DipSwitch_hpp

#include "Arduino.h"
#include "List.hpp"
#include "ArrayList.hpp"
#include "cppObject.hpp"

namespace ame{

class DipSwitch : public cppObject{
    private:
		void readPins(){
			value = 0;
			for(int x =0; x < pinList->getPosition(); x++){
				value += digitalRead(*pinList->getByPosition(x)) * pow(2,x);
			}
		}
	
    public:
		int value;
		ArrayList<int,10> *pinList;
		
		DipSwitch(){
			pinList = new ArrayList<int,10>();
		}
	
		int getValue(){
			
			return value;
		}
		void addPin(int pin){
			pinList->addLValue(pin);
		}

        void onDelete(){
			pinList->onDelete();
			delete this;
		}
        int operator &(){
			return value;
		}
        void operator =(const DipSwitch& d){
			value = d.value;
		}
        void operator =(const int& t){
		value = t;
	}
        bool operator ==(const int& t){
			this->readPins();
			return this->value==t;
		}
        bool operator !=(const int& t){
			this->readPins();
			return this->value!=t;
		}
};

}

#endif 

#endif 