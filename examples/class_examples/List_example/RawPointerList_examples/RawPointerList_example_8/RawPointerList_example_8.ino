
#include "ame_Enviroment.hpp"

#include "RawPointerList.hpp"
#include "PrimitiveRawPointerList.hpp"
#include "LinkedRawPointerList.hpp"

using namespace ame;

void setup() {
  Serial.begin(9600);
}

void loop() {
  ame_Debuging(ame_Log_StartLoop, "loop");
  
  PrimitiveRawPointerList<int> list;
  //LinkedRawPointerList<int> list;
  
  list.addPointer(new int(1));
  list.addPointer(new int(2));
  int* value = list.addPointer(new int(3));
  list.addPointer(new int(4));
  list.addPointer(new int(5));

  list.removeDeleteByPointer(value);

  for(int x = 0; x < list.getPosition(); x++){
    int* number = list.getByPosition(x);
    if(number != nullptr){
      Serial.println(*number);
    }
  }

  ame_Debuging(ame_Log_EndLoop, "loop");
}