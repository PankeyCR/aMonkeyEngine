
#include "RealRandom.hpp"

using namespace ame;

void setup() {
  Serial.begin(9600);
}

void loop() {
  ame_Debuging(ame_Log_StartLoop, "loop");
  
  RealRandom function;
  Serial.println(function.f(10, 0, 557599.9893f));

  ame_Debuging(ame_Log_EndLoop, "loop");
}