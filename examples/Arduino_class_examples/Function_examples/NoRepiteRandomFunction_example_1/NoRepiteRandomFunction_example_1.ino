
#include "NoRepiteRandom.hpp"

using namespace ame;

void setup() {
  Serial.begin(9600);
}

void loop() {
  ame_Debuging(ame_Log_StartLoop, "loop");
  
  NoRepiteRandom function;
  Serial.println(function.f(10, 0, 9599.98f));

  ame_Debuging(ame_Log_EndLoop, "loop");
}