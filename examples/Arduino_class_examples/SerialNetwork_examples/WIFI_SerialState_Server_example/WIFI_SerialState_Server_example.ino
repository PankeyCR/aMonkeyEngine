
#define WIFI_IP "192.168.1.140"
#define WIFI_MAC { 0x10, 15, 0x2C, 0x80, 0, 2 }

#include "DefaultApplication.hpp"

#include "SerialState.hpp"

#include "WIFISerialServer.hpp"

#include "WIFISerialPort.hpp"
#include "DefaultSerialPort.hpp"

#include "DefaultServerProtocol.hpp"
#include "DefaultPortProtocol.hpp"

#include "LoRaNetwork.hpp"
#include "SerialListenerState.hpp"
#include "SerialDelivery.hpp"

#include "ame_WIFI.hpp"
#include "SerialStateCommands.hpp"

using namespace ame;

Application* app;
SerialState* serialState;

long prevNow = 0;

void setup() {
  Serial.begin(9600);

  uint8_t mac[6] = WIFI_MAC;

  initializeWIFI( WIFI_IP,                //ip
                  "192.168.1.1" ,         //gateway
                  "192.168.1.1" ,         //subnet
                  "255, 255, 255, 0" ,    //dns
                  mac ,                   //mac
                  "Cristo" ,       //router name
                  "Jesucristo#1");            //router password

                  //router name MERCUSYS_6541 - pokemon
                  //router password 57924106 - tania1919

  haltUntilWIFIConnection();

  app = new DefaultApplication();

  serialState = app->getStateManager()->addState(new SerialState());
  setSerialState(serialState);

  serialState->setIP(WIFI_IP);
  serialState->addSerialServer(new WIFISerialServer(55), new DefaultServerProtocol<DefaultPortProtocol>());
  serialState->addSerialPort(new DefaultSerialPort(&Serial, "usb"), new DefaultPortProtocol());

  auto listener = app->getStateManager()->addState(new SerialListenerState<PrimitiveList<Note>>());
  listener->addListener(WIFICommands);
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

void SerialMessage(const PrimitiveList<Note>& messages) {
  Serial.println("SerialMessage");
  Serial.println(PrintableList<PrimitiveList<Note>,Note>(messages));
  if(messages[0] == "hola") {
    Serial.println("broadcast ethernet");
    serialState->instantSend("Mensaje recivido");
  }
}


//