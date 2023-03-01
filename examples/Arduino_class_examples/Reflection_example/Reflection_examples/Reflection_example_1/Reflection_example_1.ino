
#include "Reflection.hpp"
#include "System.hpp"

using namespace ame;

void runEvent(){System::console.println("runEvent");}
 
void setup() {
  Serial.begin(9600);
}

void loop() {
  ame_Debuging(ame_Log_StartLoop, "loop");
  
  Reflection reflection;
  reflection.addClass("Example");
  reflection.addMethod("Example", "runEvent", runEvent);

  cppObject* obj = reflection.newInstance("Example");

  reflection.invoke(obj, "runEvent");

  delete obj;
  
  ame_Debuging(ame_Log_EndLoop, "loop");
}





//