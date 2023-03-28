
#include "Application.hpp"
#include "DefaultApplication.hpp"
#include "Listener.hpp"

using namespace ame;

Application* app;
Listener* listener;

void setup() {
  Serial.begin(9600);
  Serial.println("Listener example 2");
  
  app = new DefaultApplication();
  listener = app->getStateManager()->addState(new Listener());
  
  listener->createDebounceInput<1>(0.1f, 2);//debounce time, pin
  listener->createDebounceInput<2>(0.1f, 3, true);//debounce time, pin, inverted
}

void loop() {
  app->update();
  if(listener->PinState<1>()){
    if(!listener->isInverted<1>()){
      Sensor1(1, listener->Millis<1>(), listener->PinState<1>());
    }else{
      Sensor2(1, listener->Millis<1>(), !listener->PinState<1>());
    }
  }
  if(listener->PinState<2>()){
    if(!listener->isInverted<2>()){
      Sensor2(2, listener->Millis<2>(), listener->PinState<2>());
    }else{
      Sensor2(2, listener->Millis<2>(), !listener->PinState<2>());
    }
  }
}

void Sensor1(int interrupt, long milli, bool state){
  Serial.print("interrupt ");Serial.print(interrupt);
  Serial.print(" milli ");Serial.print(milli);
  Serial.print(" state ");Serial.println(state);
}

void Sensor2(int interrupt, long milli, bool state){
  Serial.print("interrupt ");Serial.print(interrupt);
  Serial.print(" milli ");Serial.print(milli);
  Serial.print(" state ");Serial.println(state);
}