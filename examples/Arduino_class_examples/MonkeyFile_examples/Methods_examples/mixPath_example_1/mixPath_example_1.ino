
#include "MonkeyFile.hpp"

using namespace ame;

void setup() {
  Serial.begin(9600);
}

void loop() {
  ame_Debuging(ame_Log_StartLoop, "loop");

  MonkeyFile file;
  Note path = file.mixPath("Pokemon", "memory.txt");
  Serial.println(path);
  
  ame_Debuging(ame_Log_EndLoop, "loop");
}