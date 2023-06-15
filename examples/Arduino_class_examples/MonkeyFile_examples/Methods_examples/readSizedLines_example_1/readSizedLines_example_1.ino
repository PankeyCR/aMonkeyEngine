
#define ame_ArduinoIDE
#define ame_ESP32_POE_ETHERNET

#include "MonkeyFile.hpp"
#include "ArduinoSDFile.hpp"
#include "PrimitiveList.hpp"
#include "PrintableList.hpp"

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
  
  PrimitiveList<Note> lines = file.readSizedLines(12, "/memory.txt");
  Serial.println(PrintableList<PrimitiveList<Note>,Note>(lines, true));
  
  ame_Debuging(ame_Log_EndLoop, "loop");
}