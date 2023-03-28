
#include "Random.hpp"

using namespace ame;

void setup() {
  Serial.begin(9600);
}

void loop() {
  ame_Debuging(ame_Log_StartLoop, "loop");
  
  Random random;
  random.setMax(10);
  random.setMin(0);
  random.setSeed(7768);
  Serial.println(random.getRandom());

  ame_Debuging(ame_Log_EndLoop, "loop");
}