
#include "Reflection.hpp"
#include "System.hpp"

using namespace ame;

class Example : cppObject{
  public:
    Example(){}

    void runClassEvent(){System::console.println("runClassEvent");}
    
    cppObjectClass* getClass(){return Class<Example>::getClass();}
    bool instanceof(cppObjectoClass* cls){return cls == Class<Example>::getClass();}
};
 
void setup() {
  Serial.begin(9600);
}

void loop() {
  ame_Debuging(ame_Log_StartLoop, "loop");
  
  Reflection reflection;
  reflection.addClass("Example", Class<Example>::getClass());
  reflection.addClassMethod("Example", "runClassEvent", Example::runClassEvent);

  cppObject* obj = reflection.newInstance("Example");

  reflection.invoke(obj, "runClassEvent");

  delete obj;
  
  ame_Debuging(ame_Log_EndLoop, "loop");
}





//