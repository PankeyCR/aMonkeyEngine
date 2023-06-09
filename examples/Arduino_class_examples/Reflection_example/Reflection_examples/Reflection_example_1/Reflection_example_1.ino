
#include "Reflection.hpp"
#include "System.hpp"

using namespace ame;

void Function(){
    System::console.println("Class Function");
}

void Function_2(Note a_name){
    System::console.println(Note("Class ") + a_name);
}
 
void setup() {
  Serial.begin(9600);
  initializeEngine();
}

void loop() {
  ame_Debuging(ame_Log_StartLoop, "loop");
    
  Reflection reflection;

  reflection.addFunction("Function", Function);
  reflection.addFunction("Function_2", Function_2);
  
  reflection.invokeFunction("Function");
  reflection.invokeFunction("Function 2", Note("f2 invoke"));
  
  ame_Debuging(ame_Log_EndLoop, "loop");
}





//