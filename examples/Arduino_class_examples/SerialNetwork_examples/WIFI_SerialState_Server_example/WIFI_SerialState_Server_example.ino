
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
#include "ListDelivery.hpp"
#include "MessageList.hpp"

#include "ame_WIFI.hpp"
#include "PrintableList.hpp"
//#include "ApplicationCommands.hpp"

using namespace ame;

DefaultApplication app;

void setup() {
  Serial.begin(9600);
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

  auto list_listener = manager->addState(new SerialListenerState<MessageList>());
  auto note_listener = manager->addState(new SerialListenerState<PrimitiveList<Note>>());

  auto server = new WIFISerialServer(55);
  auto usb = new DefaultSerialPort(&Serial, "usb");

  serial->addSerialServer(server, new DefaultServerProtocol<DefaultPortProtocol>());
  serial->addSerialPort(usb, new DefaultPortProtocol());
  
  auto delivery = new ListDelivery(note_listener);// note_listener list_listener

  serial->setDelivery(delivery);
  
  list_listener->addListener(SerialMessage);
  note_listener->addListener(NoteToListListener);
}

void loop() {
  ame_Debuging(ame_Log_StartLoop, "loop");
  app.update();
  ame_Debuging(ame_Log_EndLoop, "loop");
}

void NoteToListListener(const PrimitiveList<Note>& a_message){
  Serial.println("NoteToListListener");
  Serial.println(PrintableList<PrimitiveList<Note>,Note>(a_message));
}

void SerialMessage(const MessageList& a_message) {
  Serial.println("SerialMessage");
  Serial.println(PrintableList<PrimitiveList<Note>,Note>(a_message.list()));
}


//