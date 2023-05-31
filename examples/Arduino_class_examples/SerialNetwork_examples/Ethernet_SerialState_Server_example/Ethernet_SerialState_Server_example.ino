
#define ETHERNET_IP "192.168.5.140"
#define ETHERNET_MAC { 0x10, 15, 0x2C, 0x80, 2, 2 }

#include "DefaultApplication.hpp"

#include "SerialState.hpp"

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

Application* app;
SerialState* serialState;
SerialListenerState<Note>* listener;

long prevNow = 0;

void setup() {
  Serial.begin(9600);

  uint8_t mac[6] = ETHERNET_MAC;

  initializeETHERNET( ETHERNET_IP,
                      "192.168.5.1",    //gateway
                      "255.255.255.0",  //subnet
                      10,               //CS pin
                      mac);             //mac address

  app = new DefaultApplication();
  
  serialState = app->getStateManager()->addState(new SerialState());
  setSerialState(serialState);

  serialState->setIP(ETHERNET_IP);
  serialState->addSerialServer(new EthernetSerialServer(55), new DefaultServerProtocol<DefaultPortProtocol>());
  serialState->addSerialPort(new DefaultSerialPort(&Serial, "usb"), new DefaultPortProtocol());

  listener = app->getStateManager()->addState(new SerialListenerState<Note>());
  listener->addListener(SerialMessage);
  listener->addListener(SerialStateCommands);

  SerialDelivery* delivery = new SerialDelivery(listener);

  serialState->setDelivery(delivery);
}

void loop() {
  ame_Debuging(ame_Log_StartLoop, "loop");
  app->update();
  ame_Debuging(ame_Log_EndLoop, "loop");
}

void SerialMessage(const Note& message) {
  Serial.println("SerialMessage");
  Serial.println(message);
  if (message == "hola") {
    Serial.println("broadcast ethernet");
    serialState->instantSend("Mensaje recivido");
  }
}


//