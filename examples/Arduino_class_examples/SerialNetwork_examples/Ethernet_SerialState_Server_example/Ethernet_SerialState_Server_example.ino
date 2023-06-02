
#define ETHERNET_IP "192.168.5.140"
#define ETHERNET_MAC { 0x10, 15, 0x2C, 0x80, 2, 2 }

#include "DefaultApplication.hpp"

#include "FreeSerialNetwork.hpp"

#include "EthernetSerialServer.hpp"

#include "EthernetSerialPort.hpp"
#include "DefaultSerialPort.hpp"

#include "DefaultServerProtocol.hpp"
#include "DefaultPortProtocol.hpp"

#include "SerialListenerState.hpp"
#include "SerialDelivery.hpp"

#include "ame_ETHERNET.hpp"
#include "SerialStateCommands.hpp"

using namespace ame;

DefaultApplication app;

long prevNow = 0;

void setup() {
  Serial.begin(9600);

  delay(4000);
  
  Serial.println(ame_Enviroment_Name);
  Serial.println(ame_Hardware_Name);

  uint8_t mac[6] = ETHERNET_MAC;

  initializeETHERNET( ETHERNET_IP,
                      "192.168.5.1",    //gateway
                      "255.255.255.0",  //subnet
                      10,               //CS pin
                      mac);             //mac address
  
  auto manager = app.getStateManager();

  auto serial = manager->addState(new FreeSerialNetwork());

  auto note_listener = manager->addState(new SerialListenerState<Note>());

  auto server = new EthernetSerialServer(55);
  auto usb = new DefaultSerialPort(&Serial, "usb");

  serial->addSerialServer(server, new DefaultServerProtocol<DefaultPortProtocol>());
  serial->addSerialPort(usb, new DefaultPortProtocol());
  
  auto delivery = new SerialDelivery(note_listener);

  serial->setDelivery(delivery);
  
  note_listener->addListener(SerialMessage);
}

void loop() {
  ame_Debuging(ame_Log_StartLoop, "loop");
  app.update();
  ame_Debuging(ame_Log_EndLoop, "loop");
}

void SerialMessage(const Note& a_message){
  Serial.println(a_message);
}


//