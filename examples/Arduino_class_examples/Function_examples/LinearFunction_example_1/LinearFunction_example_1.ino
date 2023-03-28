
#include "LinearFunction.hpp"

using namespace ame;

void setup() {
  Serial.begin(9600);
}

void loop() {
  ame_Debuging(ame_Log_StartLoop, "loop");
  
  LinearFunction function;
  function.setConstante(0, 0.5f);
  function.setConstante(1, 2.0f);
  Serial.println(function.f(55.5f));

  ame_Debuging(ame_Log_EndLoop, "loop");
}