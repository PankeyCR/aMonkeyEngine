
#include "Application.hpp"
#include "DefaultApplication.hpp"
#include "Listener.hpp"

using namespace ame;

Application* app;
Listener* listener;

void setup() {
  Serial.begin(9600);
  Serial.println("Listener example 4");
  
  app = new DefaultApplication();
  listener = app->getStateManager()->addState(new Listener());
  
  listener->createDebounceInterruptEvent<1>(10, 2);//debounce time, pin
  listener->createDebounceInterruptEvent<2>(10, 3, true);//debounce time, pin, inverted
  
  listener->addEvent<1>(Sensor1);
  listener->addEvent<2>(Sensor2);
}

void loop() {
  app->update();
}

void Sensor1(int interrupt, long milli, bool state){
  Serial.print("method Event ");
  Serial.print("interrupt ");Serial.print(interrupt);
  Serial.print(" milli ");Serial.print(milli);
  Serial.print(" state ");Serial.println(state);
}

void Sensor2(int interrupt, long milli, bool state){
  Serial.print("method Event ");
  Serial.print("interrupt ");Serial.print(interrupt);
  Serial.print(" milli ");Serial.print(milli);
  Serial.print(" state ");Serial.println(state);
}