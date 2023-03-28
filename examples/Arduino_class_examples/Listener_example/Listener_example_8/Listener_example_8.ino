
#include "Application.hpp"
#include "DefaultApplication.hpp"
#include "Listener.hpp"

using namespace ame;

Application* app;
Listener* listener;

void setup() {
  Serial.begin(9600);
  Serial.println("Listener example 8");
  
  app = new DefaultApplication();
  listener = app->getStateManager()->addState(new Listener());
  
  listener->createDebounceMultiInterrupt<1,3,2>(10, 2);
  listener->createDebounceMultiInterrupt<2,3,1>(10, 3);
  
  listener->addEvent<1>(Sensor1);
  listener->addEvent<2>(Sensor2);
  listener->addMultiEvent<1>(End);
  listener->addMultiEvent<2>(End);
}

void loop() {
  app->update();
}

void Sensor1(int interrupt, long milli, bool state){
  Serial.print("Sensor1 ");
  Serial.print("interrupt ");Serial.print(interrupt);
  Serial.print(" state ");Serial.println(state);
}

void Sensor2(int interrupt, long milli, bool state){
  Serial.print("Sensor2 ");
  Serial.print("interrupt ");Serial.print(interrupt);
  Serial.print(" state ");Serial.println(state);
}

void End(int interrupt, long milli, bool state){
  Serial.print("End ");
  Serial.print("interrupt ");Serial.print(interrupt);
  Serial.print(" state ");Serial.println(state);
}