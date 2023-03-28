
#include "Application.hpp"
#include "DefaultApplication.hpp"
#include "Listener.hpp"
#include "SerialConnection.hpp"

using namespace ame;

Application* app;
Listener* listener;
SerialConnection* serialConnection;

void setup() {
  Serial.begin(9600);
  Serial.println("Listener example 10");

  app = new DefaultApplication();
  listener = app->getStateManager()->addState(new Listener());
  
  listener->createDebounceLoopInterrupt<1>(0.1f, 2);
  listener->createDebounceLoopInterrupt<2>(0.1f, 3);

  listener->addEvent<1>(Input_1);
  listener->addEvent<2>(Input_2);

  listener->createOutputInterrupt<3>(4);
  listener->createOutputInterrupt<4>(5);
  
  listener->createOutputValue<5>("light", false);
  listener->createOutputValue<5>("door", false);
  listener->createOutputValue<5>("stairs", false);
  
  listener->linkOutputValue<3,5>("light");
  listener->linkOutputValue<4,5>("stairs");

  serialConnection = new SerialConnection();
  serialConnection->setPort(&Serial);
}

void Input_1(int interrupt, long milli, bool state){
  Serial.print("interrupt ");Serial.print(interrupt);
  Serial.print(" milli ");Serial.print(milli);
  Serial.print(" state ");Serial.println(state);
}

void Input_2(int interrupt, long milli, bool state){
  Serial.print("interrupt ");Serial.print(interrupt);
  Serial.print(" milli ");Serial.print(milli);
  Serial.print(" state ");Serial.println(state);
}

void loop() {
  app->update();
  Note mns = serialConnection->safeReceive('\n');
  if(mns != ""){
    Serial.println(mns);
    if(mns == "lightHigh"){
      listener->setOutputValue<5>("light", true);
    }
    if(mns == "lightLow"){
      listener->setOutputValue<5>("light", false);
    }
    if(mns == "doorHigh"){
      listener->setOutputValue<5>("door", true);
    }
    if(mns == "doorLow"){
      listener->setOutputValue<5>("door", false);
    }
    if(mns == "stairsHigh"){
      listener->setOutputValue<5>("stairs", true);
    }
    if(mns == "stairsLow"){
      listener->setOutputValue<5>("stairs", false);
    }
    if(mns == "link_light_3_5"){
      listener->linkOutputValue<3,5>("light");
    }
    if(mns == "link_light_4_5"){
      listener->linkOutputValue<4,5>("light");
    }
    if(mns == "link_door_3_5"){
      listener->linkOutputValue<3,5>("door");
    }
    if(mns == "link_door_4_5"){
      listener->linkOutputValue<4,5>("door");
    }
    if(mns == "link_stairs_3_5"){
      listener->linkOutputValue<3,5>("stairs");
    }
    if(mns == "link_stairs_4_5"){
      listener->linkOutputValue<4,5>("stairs");
    }
    if(mns == "sync_light_3_5"){
      listener->syncOutputValue<3,5>("light");
    }
    if(mns == "sync_light_4_5"){
      listener->syncOutputValue<4,5>("light");
    }
    if(mns == "sync_door_3_5"){
      listener->syncOutputValue<3,5>("door");
    }
    if(mns == "sync_door_4_5"){
      listener->syncOutputValue<4,5>("door");
    }
    if(mns == "sync_stairs_3_5"){
      listener->syncOutputValue<3,5>("stairs");
    }
    if(mns == "sync_stairs_4_5"){
      listener->syncOutputValue<4,5>("stairs");
    }
    if(mns == "apply_light_high_3_5"){
      listener->applyOutputValue<3,5>("light", true);
    }
    if(mns == "apply_light_low_3_5"){
      listener->applyOutputValue<3,5>("light", false);
    }
    if(mns == "apply_door_high_3_5"){
      listener->applyOutputValue<3,5>("door", true);
    }
    if(mns == "apply_door_low_3_5"){
      listener->applyOutputValue<3,5>("door", false);
    }
    if(mns == "apply_stairs_high_3_5"){
      listener->applyOutputValue<3,5>("stairs", true);
    }
    if(mns == "apply_stairs_low_3_5"){
      listener->applyOutputValue<3,5>("stairs", false);
    }
    if(mns == "apply_light_high_4_5"){
      listener->applyOutputValue<4,5>("light", true);
    }
    if(mns == "apply_light_low_4_5"){
      listener->applyOutputValue<4,5>("light", false);
    }
    if(mns == "apply_door_high_4_5"){
      listener->applyOutputValue<4,5>("door", true);
    }
    if(mns == "apply_door_low_4_5"){
      listener->applyOutputValue<4,5>("door", false);
    }
    if(mns == "apply_stairs_high_4_5"){
      listener->applyOutputValue<4,5>("stairs", true);
    }
    if(mns == "apply_stairs_low_4_5"){
      listener->applyOutputValue<4,5>("stairs", false);
    }
  }
}