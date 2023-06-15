
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

  file.setRootPathFile("/monkey");
  
  file.deleteRootFile("memory.txt");
  file.createRootFile("memory.txt");

  Note text = "Line 1\n";
  text.addLocalNote("Line 2\n");
  text.addLocalNote("Line 3\n");
  text.addLocalNote("Line 4\n");
  
  file.writeRootText(text, "memory.txt");
}

void loop() {
  ame_Debuging(ame_Log_StartLoop, "loop");
  
  PrimitiveList<Note> lines = file.readRootSizedLines(12, "memory.txt");
  Serial.println(PrintableList<PrimitiveList<Note>,Note>(lines, true));
  
  ame_Debuging(ame_Log_EndLoop, "loop");
}