
#include "RealRandom.h"
#include "MemoryFree.h"

RealRandom *r;

int deletememory;
int startmemory;
int instancememory;
  
void setup() {
  Serial.begin(9600);
  startmemory = freeMemory();
  r = new RealRandom();
  instancememory = freeMemory();
  r->setMax(10);
  r->setMin(0);
  r->setSeed(3521);
  Serial.println(r->getRandom());
  
  delete r;
  deletememory = freeMemory();
  Serial.print("startmemory ");Serial.println(startmemory);
  Serial.print("instancememory ");Serial.println(instancememory);
  Serial.print("instance ");Serial.println(startmemory-instancememory);
  Serial.print("delete ");Serial.println(startmemory-deletememory); 
}

void loop() {
  
}
