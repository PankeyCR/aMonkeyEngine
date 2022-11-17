
#include "ByteArray.hpp"
#include "MonkeyFile.hpp"
#include "DefaultMonkeyFile.hpp"

using namespace ame;

DefaultMonkeyFile<SDFileSystemClass> file = SD;

void setup() {
  Serial.begin(9600);

  file.setRootPathFile("monkey");
  
  file.deleteFile("memory.txt");
  file.deleteRootFile("memory.txt");
  file.createFile("memory.txt");
  ByteArray array = 0b01010101;
  file.writeByteArray(array, "memory.txt");
  
  file.createRootFile("memory.txt");
  file.writeRootByteArray(array, "memory.txt");
}

void loop() {
  ame_Debuging(ame_Log_StartLoop, "loop");
  
  ByteArray array = file.readByteArray("memory.txt");
  Serial.println(array.toNote());
  ByteArray arrayRoot = file.readRootByteArray("memory.txt");
  Serial.println(arrayRoot.toNote());
  
  ame_Debuging(ame_Log_EndLoop, "loop");
}