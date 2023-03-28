
#include "Note.hpp"
#include "PrimitiveList.hpp"
#include "System.hpp"

#include "DefaultApplication.hpp"

#include "SerialListenerState.hpp"

#include "ShiftToListCommands.hpp"
#include "SystemCommands.hpp"

#include "PrintableList.hpp"

using namespace ame;

float g_time = 0;

Application* app;
SerialListenerState<Note>* note_listener;
SerialListenerState<PrimitiveList<Note>>* list_listener;

void setup() {
  Serial.begin(9600);

  System::startEngine();
  
  app = new DefaultApplication();
  
  note_listener = app->getStateManager()->addState(new SerialListenerState<Note>());
  list_listener = app->getStateManager()->addState(new SerialListenerState<PrimitiveList<Note>>());
  
  note_listener->addListener(new ShiftToListCommands(list_listener));
  list_listener->addListener(SystemCommands);
  
  note_listener->addListener(Event);
  list_listener->addListener(Event);
}

void loop() {
  ame_Debuging(ame_Log_StartLoop, "loop");
  float tpc = app->update();
  g_time += tpc;

  if(g_time >= 3){
    g_time = 0;
    System::console.println("adding note to listener");
    note_listener->addInput("println system_enviroment");
  }
  ame_Debuging(ame_Log_EndLoop, "loop");
}

void Event(const Note& message) {
  System::console.println("Note Event");
  System::console.println(message);
}

void Event(const PrimitiveList<Note>& message) {
  System::console.println("PrimitiveList Note Event");
  System::console.println(PrintableList<PrimitiveList<Note>,Note>(message));
}


//