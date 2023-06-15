
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

  Note text = "Line 1\n";
  text.addLocalNote("Line 2\n");
  text.addLocalNote("Line 3\n");
  text.addLocalNote("Line 4\n");
  
  file.writeText(text, "/memory.txt");
}

void loop() {
  ame_Debuging(ame_Log_StartLoop, "loop");
  
  Note line = file.readLine(2, "/memory.txt");
  Serial.println(line);
  
  ame_Debuging(ame_Log_EndLoop, "loop");
}