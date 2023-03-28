
#include "DefaultApplication.hpp"
#include "MessageList.hpp"
#include "UDPNetwork.hpp"
#include "SerialListenerState.hpp"
#include "ListDelivery.hpp"

#include "Note.hpp"
#include "ame_ETHERNET.hpp"

byte mac[] = {0xA2, 0xB2, 0xC2, 0xD2, 0xE2, 0xF2};

using namespace ame;

Application* app;
UDPNetwork* udp;
Note ip = "192.168.1.140";

void setup() {

  delay(4000);

  Serial.begin(9600);
  
  initializeETHERNET( ip,
                      "192.168.1.1",    //gateway
                      "255.255.255.0",  //subnet
                      10,               //CS pin
                      mac);             //mac address

  app = new DefaultApplication();
  
  udp = app->getStateManager()->addState(new UDPNetwork(55));
  udp->addPort("Scpyd", IPAddress(192,168,1,112), 155);

  auto listener = app->getStateManager()->addState(new SerialListenerState<MessageList>());
  listener->addListener(UdpMessage);

  ListDelivery* delivery = new ListDelivery(listener);

  udp->setDelivery(delivery);
}

void loop() {
  app->update();
}

void UdpMessage(const MessageList& a_message){
  PrimitiveList<Note> i_list = a_message.list();
  if(i_list.isEmpty()){
    return;
  }
  if(i_list[0] == "hola"){
    System::console.println("enviando a java");
    udp->instantSend("hola java");
  }
}




//