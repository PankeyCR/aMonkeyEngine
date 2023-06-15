
#define ame_ArduinoIDE
#define ame_ESP32_POE_ETHERNET

#include "MonkeyFile.hpp"
#include "ArduinoSDFile.hpp"

using namespace ame;

ArduinoSDFile<SDFileSystemClass> file = SD;

void setup() {
  delay(4000);
  
  Serial.begin(9600);
  
  initializeEngine();
  
  file.initialize();
  
  file.deleteFile("/memory.txt");
  file.createFile("/memory.txt");
  file.writeText("saving memory", "/memory.txt");
}

void loop() {
  ame_Debuging(ame_Log_StartLoop, "loop");
  
  Note text = file.readSizedText(6, "/memory.txt");
  Serial.println(text);
  
  ame_Debuging(ame_Log_EndLoop, "loop");
}