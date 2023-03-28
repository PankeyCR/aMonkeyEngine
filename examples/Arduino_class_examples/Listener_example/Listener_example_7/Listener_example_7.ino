
#include "Application.hpp"
#include "DefaultApplication.hpp"
#include "Listener.hpp"

using namespace ame;

Application* app;
Listener* listener;

void setup() {
  Serial.begin(9600);
  Serial.println("Listener example 7");
  
  app = new DefaultApplication();
  listener = app->getStateManager()->addState(new Listener());
  
  listener->createSingleDebounceMultiInterrupt<1,3,2>(10, 2);
  listener->createSingleDebounceMultiInterrupt<2,3,1>(10, 3);
  
  listener->addSingleEvent<1>(Sensor1);
  listener->addSingleEvent<2>(Sensor2);
  listener->addSingleMultiEvent<1>(End);
  listener->addSingleMultiEvent<2>(End);
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