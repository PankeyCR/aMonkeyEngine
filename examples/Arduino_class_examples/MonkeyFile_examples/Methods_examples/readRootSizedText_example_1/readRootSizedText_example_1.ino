
#include "MonkeyFile.hpp"
#include "ArduinoSDFile.hpp"

using namespace ame;

ArduinoSDFile<SDFileSystemClass> file = SD;

void setup() {
  delay(4000);
  
  Serial.begin(9600);
  
  initializeEngine();
  
  file.initialize();

  file.setRootPathFile("/monkey");
  
  file.deleteRootFile("memory.txt");
  file.createRootFile("memory.txt");
  file.writeRootText("saving root memory", "memory.txt");
}

void loop() {
  ame_Debuging(ame_Log_StartLoop, "loop");
  
  Note textRoot = file.readRootSizedText(6, "memory.txt");
  Serial.println(textRoot);
  
  ame_Debuging(ame_Log_EndLoop, "loop");
}