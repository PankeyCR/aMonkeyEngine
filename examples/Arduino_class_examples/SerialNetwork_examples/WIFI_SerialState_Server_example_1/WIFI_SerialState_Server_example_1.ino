
#define WIFI_IP "192.168.1.140"
#define WIFI_MAC { 0x10, 15, 0x2C, 0x80, 0, 2 }

#include "DefaultApplication.hpp"

#include "FreeSerialNetwork.hpp"

#include "WIFISerialServer.hpp"

#include "WIFISerialPort.hpp"
#include "DefaultSerialPort.hpp"

#include "DefaultServerProtocol.hpp"
#include "DefaultPortProtocol.hpp"

#include "SerialListenerState.hpp"
#include "SerialDelivery.hpp"

#include "ame_WIFI.hpp"

using namespace ame;

DefaultApplication app;

void setup() {
  Serial.begin(9600);

  delay(4000);
  
  Serial.println(ame_Enviroment_Name);
  Serial.println(ame_Hardware_Name);

  uint8_t mac[6] = WIFI_MAC;

  initializeWIFI( WIFI_IP,                //ip
                  "192.168.1.1" ,         //gateway
                  "192.168.1.1" ,         //subnet
                  "255, 255, 255, 0" ,    //dns
                  mac ,                   //mac
                  "MERCUSYS_6541" ,       //router name
                  "57924106");            //router password

                  //router name MERCUSYS_6541 - pokemon - Cristo
                  //router password 57924106 - tania1919 - Jesucristo#1

  haltUntilWIFIConnection();
  
  auto manager = app.getStateManager();

  auto serial = manager->addState(new FreeSerialNetwork());

  auto note_listener = manager->addState(new SerialListenerState<Note>());

  auto server = new WIFISerialServer(55);
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