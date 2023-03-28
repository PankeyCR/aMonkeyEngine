
#ifndef Listener_hpp
#define Listener_hpp
#define Listener_AVAILABLE

#define ListenerInput 0
#define ListenerDebounceInput 1
#define ListenerDebounceInterrupt 2
#define ListenerDebounceInterruptEvent 3
#define ListenerDebounceInterruptClassEvent 4
#define ListenerDebounceLoopInterrupt 5
#define ListenerInterrupt 6
#define ListenerThreadInterrupt 7
#define ListenerOutput 8
#define ListenerOutputInterrupt 9
#define ListenerOutputEvent 10
#define ListenerInputEvent 11
#define ListenerDebounceMultiInterruptEvent 12
#define ListenerDebounceMultiMultiInterruptEvent 13
#define ListenerDebounceMultiMultiInterruptEvent_v2 14
#define ListenerDebounceMultiMultiInterruptEvent_v3 15
#define ListenerClickInterrupt 16
#define ListenerMultiClickInterrupt 17
#define ListenerAnalogInput 18
#define ListenerAnalogInputController 19
#define ListenerAnalogOutput 20
#define ListenerAnalogOutputController 21

#include "ame_Enviroment.hpp"

#ifndef ame_Enviroment_Defined

#endif

#ifdef ame_Windows

#endif

#ifdef ame_ArduinoIDE
	#include "Arduino.h"
#endif

#include "cppObject.hpp"
#include "BaseAppState.hpp"
#include "ListenerEvent.hpp"
#include "ListenerAnalogEvent.hpp"
#include "PrimitiveList.hpp"
#include "PrimitiveMap.hpp"
#include "MonkeyExporter.hpp"
#include "MonkeyImporter.hpp"

#ifdef Listener_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"
	
	#define ListenerLog(location,method,type,mns) ame_Log(this,location,"Listener",method,type,mns)
	#define ListenerMethodLog(location,method,type,mns) ame_Log(nullptr,location,"RawMethod",method,type,mns)
	#define const_ListenerLog(location,method,type,mns) 
	#define StaticListenerLog(pointer,location,method,type,mns) ame_Log(pointer,location,"Listener",method,type,mns)
#else
	#ifdef Listener_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"
		
		#define ListenerLog(location,method,type,mns) ame_LogDebug(this,location,"Listener",method,type)
		#define ListenerMethodLog(location,method,type,mns) ame_LogDebug(nullptr,location,"RawMethod",method,type)
		#define const_ListenerLog(location,method,type,mns) 
		#define StaticListenerLog(pointer,location,method,type,mns) ame_LogDebug(pointer,location,"Listener",method,type)
	#else
		#define ListenerLog(location,method,type,mns) 
		#define ListenerMethodLog(location,method,type,mns) 
		#define const_ListenerLog(location,method,type,mns) 
		#define StaticListenerLog(pointer,location,method,type,mns) 
	#endif
#endif

namespace ame{
	
using EventMethod = void (*)(int,long,bool);//interrupt,millis,state

using AnalogInputMethod = void (*)(int,float,float);//interrupt,input,tpc
using AnalogOutputMethod = void (*)(int,float);//interrupt,tpc
using AnalogControllerMethod = float (*)(int,float,float,float,float);//interrupt,input,output,sum,tpc

using ClickMethod = void (*)(int);//interrupt
using MultiClickMethod = void (*)(int,int);//interrupt,clicks

void empty(int i_interrupt,long i_millis,bool i_state){}

void analog_input_empty(int i_interrupt,float i_input,float i_tpc){}
float analog_output_empty(int i_interrupt,float i_tpc){return 0.0f;}
float analog_controller_empty(int i_interrupt,float i_input,float i_output,float i_sum,float i_tpc){return 0.0f;}

void click_empty(int i_interrupt){}
void multi_click_empty(int i_interrupt,int i_clicks){}

class Application;

static PrimitiveList<void (*)()>* ThreadMap_m = nullptr;
static PrimitiveList<void (*)(float)>* LoopMap_m = nullptr;
static PrimitiveList<void (*)()>* OutputMap_m = nullptr;

#ifdef ame_ArduinoIDE
template<int interrupt>
struct Analog_Vars{
	static int m_type;
	static float m_value;
};

template<int interrupt>
struct Analog_Scale_Var{
	static float m_scale;
};

template<int interrupt>
struct Click_Vars{
	static int m_type;
	static bool m_state;
};

template<int interrupt>
struct Multi_Click_Vars{
	static int m_clicks;
};

template<int interrupt>
struct IO_Enable{
	static bool m_enable;
};

template<int interrupt>
struct IO_Consuming{
	static bool* m_consume;
};

template<int interrupt>
struct IO_Consume{
	static bool m_consume;
};

template<int interrupt>
struct IO_Vars{
	static int m_type;
	static bool m_state;
	static bool m_inverted;
	static bool m_safe;
};

template<int interrupt>
struct IO_Output_State{
	static Note m_name;
	static bool* m_state;
};

template<int interrupt>
struct IO_Output_Value{
	static PrimitiveMap<Note,bool>* m_output_values;
};

template<int interrupt>
struct IO_Multi_State{
	static bool m_state;
};

template<int interrupt>
struct IO_Pin{
	static int m_pin;
};

template<int interrupt>
struct IO_Millis{
	static long m_millis;
};

template<int interrupt>
struct IO_Long_Times{
	static long m_time;
	static long m_timelimit;
};

template<int interrupt>
struct IO_Float_Times{
	static float m_time;
	static float m_timelimit;
};

template<int interrupt>
struct IO_Map_Event{
	static PrimitiveMap<Note,EventMethod>* m_events;
};

template<int interrupt>
struct IO_Map_ClassEvent{
	static PrimitiveMap<Note,ListenerEvent>* m_events;
};

template<int interrupt>
struct IO_Event{
	static PrimitiveList<EventMethod>* m_events;
};

template<int interrupt>
struct IO_Single_Event{
	static EventMethod m_event;
};

template<int interrupt>
struct IO_Multi_Event{
	static PrimitiveList<EventMethod>* m_events;
};

template<int interrupt>
struct IO_Single_Multi_Event{
	static EventMethod m_event;
};

template<int interrupt>
struct IO_Named_Event{
	static PrimitiveMap<Note,EventMethod>* m_events;
};

template<int interrupt>
struct IO_ClassEvent{
	static PrimitiveList<ListenerEvent>* m_events;
};

template<int interrupt>
struct IO_Single_ClassEvent{
	static ListenerEvent* m_event;
};

template<int interrupt>
struct IO_Multi_ClassEvent{
	static PrimitiveList<ListenerEvent>* m_events;
};

template<int interrupt>
struct IO_Single_Multi_ClassEvent{
	static ListenerEvent* m_event;
};

template<int interrupt>
struct IO_Named_ClassEvent{
	static PrimitiveMap<Note,ListenerEvent>* m_events;
};

template<int interrupt>
struct IO_AnalogEvent{
	static PrimitiveList<AnalogInputMethod>* m_events;
};

template<int interrupt>
struct IO_AnalogClassEvent{
	static PrimitiveList<ListenerAnalogEvent>* m_events;
};

template<int interrupt>
struct IO_Single_AnalogEvent{
	static AnalogInputMethod m_event;
};

template<int interrupt>
struct IO_Single_AnalogClassEvent{
	static ListenerAnalogEvent* m_event;
};

template<int interrupt> int   Analog_Vars<interrupt>::m_type = -1;
template<int interrupt> float  Analog_Vars<interrupt>::m_value = 0.0f;

#if defined(ame_GENERIC_ARDUINO)
template<int interrupt> float  Analog_Scale_Var<interrupt>::m_scale = 5.0f/1023.0f;
#elif defined(ame_GENERIC_ADAFRUIT_FEATHER )
template<int interrupt> float  Analog_Scale_Var<interrupt>::m_scale = 3.6f/1023.0f;
#elif defined(ame_GENERIC_ESP8266)
template<int interrupt> float  Analog_Scale_Var<interrupt>::m_scale = 3.3f/1023.0f;
#elif defined(ame_GENERIC_ESP32)
template<int interrupt> float  Analog_Scale_Var<interrupt>::m_scale = 3.3f/4095.0f;
#endif

template<int interrupt> bool  IO_Enable<interrupt>::m_enable = true;

template<int interrupt> bool*  IO_Consuming<interrupt>::m_consume = nullptr;

template<int interrupt> bool  IO_Consume<interrupt>::m_consume = true;

template<int interrupt> int   IO_Vars<interrupt>::m_type = -1;
template<int interrupt> bool  IO_Vars<interrupt>::m_state = false;
template<int interrupt> bool  IO_Vars<interrupt>::m_inverted = false;
template<int interrupt> bool  IO_Vars<interrupt>::m_safe = false;

template<int interrupt> Note IO_Output_State<interrupt>::m_name = "output";
template<int interrupt> bool* IO_Output_State<interrupt>::m_state = nullptr;
template<int interrupt> PrimitiveMap<Note,bool>* IO_Output_Value<interrupt>::m_output_values = nullptr;

template<int interrupt> bool IO_Multi_State<interrupt>::m_state = false;

template<int interrupt> int IO_Pin<interrupt>::m_pin = -1;

template<int interrupt> long IO_Millis<interrupt>::m_millis = 0;

template<int interrupt> long IO_Long_Times<interrupt>::m_time = 0;
template<int interrupt> long IO_Long_Times<interrupt>::m_timelimit = 0;

template<int interrupt> float IO_Float_Times<interrupt>::m_time = 0.0f;
template<int interrupt> float  IO_Float_Times<interrupt>::m_timelimit = 0.1f;

template<int interrupt> PrimitiveList<EventMethod>* IO_Event<interrupt>::m_events = nullptr;

template<int interrupt> PrimitiveMap<Note,EventMethod>* IO_Map_Event<interrupt>::m_events = nullptr;

template<int interrupt> PrimitiveMap<Note,ListenerEvent>* IO_Map_ClassEvent<interrupt>::m_events = nullptr;

template<int interrupt> EventMethod IO_Single_Event<interrupt>::m_event = empty;

template<int interrupt> PrimitiveList<EventMethod>* IO_Multi_Event<interrupt>::m_events = nullptr;

template<int interrupt> EventMethod IO_Single_Multi_Event<interrupt>::m_event = empty;

template<int interrupt> PrimitiveMap<Note,EventMethod>* IO_Named_Event<interrupt>::m_events = nullptr;

template<int interrupt> PrimitiveList<ListenerEvent>* IO_ClassEvent<interrupt>::m_events = nullptr;

template<int interrupt> ListenerEvent* IO_Single_ClassEvent<interrupt>::m_event = nullptr;

template<int interrupt> PrimitiveList<ListenerEvent>* IO_Multi_ClassEvent<interrupt>::m_events = nullptr;

template<int interrupt> ListenerEvent* IO_Single_Multi_ClassEvent<interrupt>::m_event = nullptr;

template<int interrupt> PrimitiveMap<Note,ListenerEvent>* IO_Named_ClassEvent<interrupt>::m_events = nullptr;

template<int interrupt> PrimitiveList<AnalogInputMethod>* IO_AnalogEvent<interrupt>::m_events = nullptr;

template<int interrupt> PrimitiveList<ListenerAnalogEvent>* IO_AnalogClassEvent<interrupt>::m_events = nullptr;

template<int interrupt> AnalogInputMethod IO_Single_AnalogEvent<interrupt>::m_event = analog_input_empty;

template<int interrupt> ListenerAnalogEvent* IO_Single_AnalogClassEvent<interrupt>::m_event = nullptr;



template<int interrupt>
void AnalogInput(float tpc){
	int pin = IO_Pin<interrupt>::m_pin;
	List<AnalogInputMethod>* static_events = IO_AnalogEvent<interrupt>::m_events;
	List<ListenerAnalogEvent>* events = IO_AnalogClassEvent<interrupt>::m_events;
	if(pin == -1 || events == nullptr ||  static_events == nullptr){
		ListenerMethodLog(ame_Log_Statement, "AnalogInput",  "println", "pin == -1");
		return;
	}
	Analog_Vars<interrupt>::m_value = ((float)analogRead(pin)) * Analog_Scale_Var<interrupt>::m_scale;
	ListenerMethodLog(ame_Log_Statement, "AnalogInput",  "println", "start interrupt");
	for(int x = 0; x < static_events->getPosition(); x++){
		AnalogInputMethod event =  *static_events->getByPosition(x);
		event(interrupt, Analog_Vars<interrupt>::m_value, tpc);
	}
	for(int x = 0; x < events->getPosition(); x++){
		ListenerAnalogEvent* e =  events->getByPosition(x);
		e->event(interrupt, Analog_Vars<interrupt>::m_value, tpc);
	}
	ListenerMethodLog(ame_Log_Statement, "AnalogInput",  "println", "end interrupt");
}

template<int interrupt>
void Input(float tpc){
	IO_Millis<interrupt>::m_millis = millis();
	ListenerMethodLog(ame_Log_Statement, "Input",  "println", "");
	if(IO_Pin<interrupt>::m_pin == -1){
		ListenerMethodLog(ame_Log_Statement, "Input",  "println", "pin == -1");
		return;
	}
	IO_Vars<interrupt>::m_state = digitalRead(IO_Pin<interrupt>::m_pin);
	ListenerMethodLog(ame_Log_Statement, "Input",  "println", Note("pin: ") + Note(IO_Pin<interrupt>::m_pin));
	ListenerMethodLog(ame_Log_Statement, "Input",  "println", Note("state: ") + Note(IO_Vars<interrupt>::m_state));
}

template<int interrupt>
void DebounceInput(float tpc){
	IO_Millis<interrupt>::m_millis = millis();
	ListenerMethodLog(ame_Log_Statement, "DebounceInput",  "println", "");
	int pin = IO_Pin<interrupt>::m_pin;
	if(pin == -1){
		ListenerMethodLog(ame_Log_Statement, "DebounceInput",  "println", "pin == -1");
		return;
	}
	bool state = digitalRead(pin);
	if(state == IO_Vars<interrupt>::m_state){
		ListenerMethodLog(ame_Log_Statement, "DebounceInput",  "println", "state == IO_Vars<interrupt>::m_state");
		IO_Float_Times<interrupt>::m_time = 0.0f;
		return;
	}
	IO_Float_Times<interrupt>::m_time += tpc;
	if(IO_Float_Times<interrupt>::m_time < IO_Float_Times<interrupt>::m_timelimit){
		ListenerMethodLog(ame_Log_Statement, "DebounceInput",  "println", "m_time < m_timelimit");
		return;
	}
	IO_Float_Times<interrupt>::m_time = 0.0f;
	IO_Vars<interrupt>::m_state = state;
	ListenerMethodLog(ame_Log_Statement, "DebounceInput",  "println", Note("state: ") + Note(IO_Vars<interrupt>::m_state));
}

template<int interrupt>
void DebounceInterrupt_Event(){
	IO_Millis<interrupt>::m_millis = millis();
	ListenerMethodLog(ame_Log_Statement, "DebounceInterrupt_Event",  "println", "");
	int pin = IO_Pin<interrupt>::m_pin;
	List<EventMethod>* static_events = IO_Event<interrupt>::m_events;
	if(pin == -1 || static_events == nullptr){
		ListenerMethodLog(ame_Log_Statement, "DebounceInterrupt_Event",  "println", "pin == -1 || static_events == nullptr");
		return;
	}
	bool state = digitalRead(pin);
	if(state == IO_Vars<interrupt>::m_state){
		ListenerMethodLog(ame_Log_Statement, "DebounceInterrupt_Event",  "println", "state == IO_Vars<interrupt>::m_state");
		return;
	}
	if( (millis() - IO_Long_Times<interrupt>::m_time) < IO_Long_Times<interrupt>::m_timelimit){
		ListenerMethodLog(ame_Log_Statement, "DebounceInterrupt_Event",  "println", "time less then the limit");
		return;
	}
	IO_Long_Times<interrupt>::m_time = millis();
	IO_Vars<interrupt>::m_state = state;
	ListenerMethodLog(ame_Log_Statement, "DebounceInterrupt_Event",  "println", "start interrupt");
	for(int x = 0; x < static_events->getPosition(); x++){
		EventMethod event =  *static_events->getByPosition(x);
		if(IO_Vars<interrupt>::m_inverted){
			event(interrupt, IO_Millis<interrupt>::m_millis, !IO_Vars<interrupt>::m_state);
		}else{
			event(interrupt, IO_Millis<interrupt>::m_millis, IO_Vars<interrupt>::m_state);
		}
	}
	ListenerMethodLog(ame_Log_Statement, "DebounceInterrupt_Event",  "println", "end interrupt");
}

template<int interrupt>
void DebounceInterrupt_ClassEvent(){
	IO_Millis<interrupt>::m_millis = millis();
	ListenerMethodLog(ame_Log_Statement, "DebounceInterrupt_ClassEvent",  "println", "");
	int pin = IO_Pin<interrupt>::m_pin;
	List<ListenerEvent>* events = IO_ClassEvent<interrupt>::m_events;
	if(pin == -1 || events == nullptr){
		ListenerMethodLog(ame_Log_Statement, "DebounceInterrupt_ClassEvent",  "println", "pin == -1 || events == nullptr");
		return;
	}
	bool state = digitalRead(pin);
	if(state == IO_Vars<interrupt>::m_state){
		ListenerMethodLog(ame_Log_Statement, "DebounceInterrupt_ClassEvent",  "println", "state == IO_Vars<interrupt>::m_state");
		return;
	}
	if( (millis() - IO_Long_Times<interrupt>::m_time) < IO_Long_Times<interrupt>::m_timelimit){
		ListenerMethodLog(ame_Log_Statement, "DebounceInterrupt_ClassEvent",  "println", "time less then the limit");
		return;
	}
	IO_Long_Times<interrupt>::m_time = millis();
	IO_Vars<interrupt>::m_state = state;
	ListenerMethodLog(ame_Log_Statement, "DebounceInterrupt_ClassEvent",  "println", "start interrupt");
	for(int x = 0; x < events->getPosition(); x++){
		ListenerEvent* e =  events->getByPosition(x);
		if(!e->isEnable()){
			continue;
		}
		if(IO_Vars<interrupt>::m_inverted){
			e->event(interrupt, IO_Millis<interrupt>::m_millis, !IO_Vars<interrupt>::m_state);
		}else{
			e->event(interrupt, IO_Millis<interrupt>::m_millis, IO_Vars<interrupt>::m_state);
		}
	}
	ListenerMethodLog(ame_Log_Statement, "DebounceInterrupt_ClassEvent",  "println", "end interrupt");
}

template<int interrupt>
bool StatesChecker(bool state){
	return state == IO_Vars<interrupt>::m_state;
}

template<int interrupt, int interrupt_2, int... interrupts>
bool StatesChecker(bool state){
	return IO_Vars<interrupt>::m_state == state && StatesChecker<interrupt_2,interrupts...>(state);
}

template<int interrupt, int multiInterrupt, int... interrupts>
void DebounceMultiInterrupt(){
	IO_Millis<interrupt>::m_millis = millis();
	ListenerMethodLog(ame_Log_Statement, "DebounceMultiInterrupt",  "println", "");
	int pin = IO_Pin<interrupt>::m_pin;
	List<ListenerEvent>* events = IO_ClassEvent<interrupt>::m_events;
	List<EventMethod>* static_events = IO_Event<interrupt>::m_events;
	if(pin == -1 || events == nullptr || static_events == nullptr){
		ListenerMethodLog(ame_Log_Statement, "DebounceMultiInterrupt",  "println", "pin == -1 || events == nullptr || static_events == nullptr");
		return;
	}
	bool state = digitalRead(pin);
	if(state == IO_Vars<interrupt>::m_state){
		ListenerMethodLog(ame_Log_Statement, "DebounceMultiInterrupt",  "println", "state == IO_Vars<interrupt>::m_state");
		return;
	}
	if( (millis() - IO_Long_Times<interrupt>::m_time) < IO_Long_Times<interrupt>::m_timelimit){
		ListenerMethodLog(ame_Log_Statement, "DebounceMultiInterrupt",  "println", "time less then the limit");
		return;
	}
	IO_Long_Times<interrupt>::m_time = millis();
	IO_Vars<interrupt>::m_state = state;
	ListenerMethodLog(ame_Log_Statement, "DebounceMultiInterrupt",  "println", "start interrupt");
	for(int x = 0; x < static_events->getPosition(); x++){
		EventMethod event =  *static_events->getByPosition(x);
		if(IO_Vars<interrupt>::m_inverted){
			event(interrupt, IO_Millis<interrupt>::m_millis, !IO_Vars<interrupt>::m_state);
		}else{
			event(interrupt, IO_Millis<interrupt>::m_millis, IO_Vars<interrupt>::m_state);
		}
	}
	for(int x = 0; x < events->getPosition(); x++){
		ListenerEvent* e =  events->getByPosition(x);
		if(!e->isEnable()){
			continue;
		}
		if(IO_Vars<interrupt>::m_inverted){
			e->event(interrupt, IO_Millis<interrupt>::m_millis, !IO_Vars<interrupt>::m_state);
		}else{
			e->event(interrupt, IO_Millis<interrupt>::m_millis, IO_Vars<interrupt>::m_state);
		}
	}
	//// end part 1
	List<ListenerEvent>* multi_events = IO_Multi_ClassEvent<interrupt>::m_events;
	List<EventMethod>* multi_static_events = IO_Multi_Event<interrupt>::m_events;
	if(multi_static_events == nullptr || multi_events == nullptr){
		ListenerMethodLog(ame_Log_Statement, "DebounceMultiInterrupt",  "println", "multi_static_events == nullptr || multi_events == nullptr");
		return;
	}
	if(!StatesChecker<interrupt,interrupts...>(state)){
		return;
	}
	if(state == IO_Multi_State<multiInterrupt>::m_state){
		ListenerMethodLog(ame_Log_Statement, "DebounceMultiInterrupt",  "println", "state == IO_Vars<interrupt>::m_state");
		return;
	}
	IO_Multi_State<multiInterrupt>::m_state = state;
	for(int x = 0; x < multi_static_events->getPosition(); x++){
		EventMethod event =  *multi_static_events->getByPosition(x);
		if(IO_Vars<interrupt>::m_inverted){
			event(interrupt, IO_Millis<interrupt>::m_millis, !IO_Vars<interrupt>::m_state);
		}else{
			event(interrupt, IO_Millis<interrupt>::m_millis, IO_Vars<interrupt>::m_state);
		}
	}
	for(int x = 0; x < multi_events->getPosition(); x++){
		ListenerEvent* e =  multi_events->getByPosition(x);
		if(!e->isEnable()){
			continue;
		}
		if(IO_Vars<interrupt>::m_inverted){
			e->event(interrupt, IO_Millis<interrupt>::m_millis, !IO_Vars<interrupt>::m_state);
		}else{
			e->event(interrupt, IO_Millis<interrupt>::m_millis, IO_Vars<interrupt>::m_state);
		}
	}
	ListenerMethodLog(ame_Log_Statement, "DebounceMultiInterrupt",  "println", "end interrupt");
}

template<int interrupt, int multiInterrupt, int... interrupts>
void SingleDebounceMultiInterrupt(){
	IO_Millis<interrupt>::m_millis = millis();
	ListenerMethodLog(ame_Log_Statement, "DebounceMultiInterrupt",  "println", "");
	int pin = IO_Pin<interrupt>::m_pin;
	EventMethod static_events = IO_Single_Event<interrupt>::m_event;
	if(pin == -1){
		ListenerMethodLog(ame_Log_Statement, "SingleDebounceMultiInterrupt",  "println", "pin == -1 || events == nullptr || static_events == nullptr");
		return;
	}
	bool state = digitalRead(pin);
	if(state == IO_Vars<interrupt>::m_state){
		ListenerMethodLog(ame_Log_Statement, "SingleDebounceMultiInterrupt",  "println", "state == IO_Vars<interrupt>::m_state");
		return;
	}
	if( (millis() - IO_Long_Times<interrupt>::m_time) < IO_Long_Times<interrupt>::m_timelimit){
		ListenerMethodLog(ame_Log_Statement, "SingleDebounceMultiInterrupt",  "println", "time less then the limit");
		return;
	}
	IO_Long_Times<interrupt>::m_time = millis();
	IO_Vars<interrupt>::m_state = state;
	ListenerMethodLog(ame_Log_Statement, "SingleDebounceMultiInterrupt",  "println", "start interrupt");
	if(IO_Vars<interrupt>::m_inverted){
		static_events(interrupt, IO_Millis<interrupt>::m_millis, !state);
	}else{
		static_events(interrupt, IO_Millis<interrupt>::m_millis, state);
	}
	//// end part 1
	EventMethod static_events_multi = IO_Single_Multi_Event<interrupt>::m_event;
	if(!StatesChecker<interrupt,interrupts...>(state)){
		return;
	}
	if(state == IO_Multi_State<multiInterrupt>::m_state){
		ListenerMethodLog(ame_Log_Statement, "SingleDebounceMultiInterrupt",  "println", "state == IO_Vars<interrupt>::m_state");
		return;
	}
	IO_Multi_State<multiInterrupt>::m_state = state;
	if(IO_Vars<interrupt>::m_inverted){
		static_events_multi(interrupt, IO_Millis<interrupt>::m_millis, !state);
	}else{
		static_events_multi(interrupt, IO_Millis<interrupt>::m_millis, state);
	}
	ListenerMethodLog(ame_Log_Statement, "SingleDebounceMultiInterrupt",  "println", "end interrupt");
}

template<int interrupt>
void DebounceInterrupt(){
	IO_Millis<interrupt>::m_millis = millis();
	ListenerMethodLog(ame_Log_Statement, "DebounceInterrupt",  "println", "");
	int pin = IO_Pin<interrupt>::m_pin;
	List<ListenerEvent>* events = IO_ClassEvent<interrupt>::m_events;
	List<EventMethod>* static_events = IO_Event<interrupt>::m_events;
	if(pin == -1 || events == nullptr || static_events == nullptr){
		ListenerMethodLog(ame_Log_Statement, "DebounceInterrupt",  "println", "pin == -1 || events == nullptr || static_events == nullptr");
		return;
	}
	bool state = digitalRead(pin);
	if(state == IO_Vars<interrupt>::m_state){
		ListenerMethodLog(ame_Log_Statement, "DebounceInterrupt",  "println", "state == IO_Vars<interrupt>::m_state");
		return;
	}
	if( (millis() - IO_Long_Times<interrupt>::m_time) < IO_Long_Times<interrupt>::m_timelimit){
		ListenerMethodLog(ame_Log_Statement, "DebounceInterrupt",  "println", "time less then the limit");
		return;
	}
	IO_Long_Times<interrupt>::m_time = millis();
	IO_Vars<interrupt>::m_state = state;
	ListenerMethodLog(ame_Log_Statement, "DebounceInterrupt",  "println", "start interrupt");
	for(int x = 0; x < static_events->getPosition(); x++){
		EventMethod event =  *static_events->getByPosition(x);
		if(IO_Vars<interrupt>::m_inverted){
			event(interrupt, IO_Millis<interrupt>::m_millis, !IO_Vars<interrupt>::m_state);
		}else{
			event(interrupt, IO_Millis<interrupt>::m_millis, IO_Vars<interrupt>::m_state);
		}
	}
	for(int x = 0; x < events->getPosition(); x++){
		ListenerEvent* e =  events->getByPosition(x);
		if(!e->isEnable()){
			continue;
		}
		if(IO_Vars<interrupt>::m_inverted){
			e->event(interrupt, IO_Millis<interrupt>::m_millis, !IO_Vars<interrupt>::m_state);
		}else{
			e->event(interrupt, IO_Millis<interrupt>::m_millis, IO_Vars<interrupt>::m_state);
		}
	}
	ListenerMethodLog(ame_Log_Statement, "DebounceInterrupt",  "println", "end interrupt");
}

template<int interrupt>
void DebounceLoopInterrupt(float tpc){
	if(!IO_Enable<interrupt>::m_enable){
		return;
	}
	IO_Millis<interrupt>::m_millis = millis();
	// ListenerMethodLog(ame_Log_Statement, "DebounceLoopInterrupt",  "println", "");
	int pin = IO_Pin<interrupt>::m_pin;
	List<ListenerEvent>* events = IO_ClassEvent<interrupt>::m_events;
	List<EventMethod>* static_events = IO_Event<interrupt>::m_events;
	if(pin == -1 || events == nullptr || static_events == nullptr){
		ListenerMethodLog(ame_Log_Statement, "DebounceLoopInterrupt",  "println", "pin == -1 || events == nullptr || static_events == nullptr");
		return;
	}
	bool state = digitalRead(pin);
	if(state == IO_Vars<interrupt>::m_state){
		// ListenerMethodLog(ame_Log_Statement, "DebounceLoopInterrupt",  "println", "state == IO_Vars<interrupt>::m_state");
		return;
	}
	IO_Float_Times<interrupt>::m_time += tpc;
	if(IO_Float_Times<interrupt>::m_time < IO_Float_Times<interrupt>::m_timelimit){
		ListenerMethodLog(ame_Log_Statement, "DebounceLoopInterrupt",  "println", "m_time < m_timelimit");
		ListenerMethodLog(ame_Log_Statement, "DebounceLoopInterrupt",  "println", Note("m_time ") + Note(IO_Float_Times<interrupt>::m_time));
		ListenerMethodLog(ame_Log_Statement, "DebounceLoopInterrupt",  "println", Note("m_timelimit ") + Note(IO_Float_Times<interrupt>::m_timelimit));
		ListenerMethodLog(ame_Log_Statement, "DebounceLoopInterrupt",  "println", Note("tpc ") + Note(tpc));
		return;
	}
	IO_Float_Times<interrupt>::m_time = 0.0f;
	IO_Vars<interrupt>::m_state = state;
	ListenerMethodLog(ame_Log_Statement, "DebounceLoopInterrupt",  "println", Note("interrupt ") + Note(interrupt));
	ListenerMethodLog(ame_Log_Statement, "DebounceLoopInterrupt",  "println", Note("state ") + Note(state));
	ListenerMethodLog(ame_Log_Statement, "DebounceLoopInterrupt",  "println", "start interrupt");
	for(int x = 0; x < static_events->getPosition(); x++){
		EventMethod event =  *static_events->getByPosition(x);
		if(IO_Vars<interrupt>::m_inverted){
			event(interrupt, IO_Millis<interrupt>::m_millis, !IO_Vars<interrupt>::m_state);
		}else{
			event(interrupt, IO_Millis<interrupt>::m_millis, IO_Vars<interrupt>::m_state);
		}
	}
	for(int x = 0; x < events->getPosition(); x++){
		ListenerEvent* e =  events->getByPosition(x);
		if(!e->isEnable()){
			continue;
		}
		if(IO_Vars<interrupt>::m_inverted){
			e->event(interrupt, IO_Millis<interrupt>::m_millis, !IO_Vars<interrupt>::m_state);
		}else{
			e->event(interrupt, IO_Millis<interrupt>::m_millis, IO_Vars<interrupt>::m_state);
		}
	}
	ListenerMethodLog(ame_Log_Statement, "DebounceLoopInterrupt",  "println", "end interrupt");
}

template<int interrupt>
void DebounceLoopInterrupt(bool a_state, float tpc){
	IO_Millis<interrupt>::m_millis = millis();
	// ListenerMethodLog(ame_Log_Statement, "DebounceLoopInterrupt",  "println", "");
	int pin = IO_Pin<interrupt>::m_pin;
	List<ListenerEvent>* events = IO_ClassEvent<interrupt>::m_events;
	List<EventMethod>* static_events = IO_Event<interrupt>::m_events;
	if(pin == -1 || events == nullptr || static_events == nullptr){
		ListenerMethodLog(ame_Log_Statement, "DebounceLoopInterrupt",  "println", "pin == -1 || events == nullptr || static_events == nullptr");
		return;
	}
	bool state = a_state;
	if(state == IO_Vars<interrupt>::m_state){
		// ListenerMethodLog(ame_Log_Statement, "DebounceLoopInterrupt",  "println", "state == IO_Vars<interrupt>::m_state");
		return;
	}
	IO_Float_Times<interrupt>::m_time += tpc;
	if(IO_Float_Times<interrupt>::m_time < IO_Float_Times<interrupt>::m_timelimit){
		ListenerMethodLog(ame_Log_Statement, "DebounceLoopInterrupt",  "println", "m_time < m_timelimit");
		ListenerMethodLog(ame_Log_Statement, "DebounceLoopInterrupt",  "println", Note("m_time ") + Note(IO_Float_Times<interrupt>::m_time));
		ListenerMethodLog(ame_Log_Statement, "DebounceLoopInterrupt",  "println", Note("m_timelimit ") + Note(IO_Float_Times<interrupt>::m_timelimit));
		ListenerMethodLog(ame_Log_Statement, "DebounceLoopInterrupt",  "println", Note("tpc ") + Note(tpc));
		return;
	}
	IO_Float_Times<interrupt>::m_time = 0.0f;
	IO_Vars<interrupt>::m_state = state;
	ListenerMethodLog(ame_Log_Statement, "DebounceLoopInterrupt",  "println", "start interrupt");
	for(int x = 0; x < static_events->getPosition(); x++){
		EventMethod event =  *static_events->getByPosition(x);
		if(IO_Vars<interrupt>::m_inverted){
			event(interrupt, IO_Millis<interrupt>::m_millis, !IO_Vars<interrupt>::m_state);
		}else{
			event(interrupt, IO_Millis<interrupt>::m_millis, IO_Vars<interrupt>::m_state);
		}
	}
	for(int x = 0; x < events->getPosition(); x++){
		ListenerEvent* e =  events->getByPosition(x);
		if(!e->isEnable()){
			continue;
		}
		if(IO_Vars<interrupt>::m_inverted){
			e->event(interrupt, IO_Millis<interrupt>::m_millis, !IO_Vars<interrupt>::m_state);
		}else{
			e->event(interrupt, IO_Millis<interrupt>::m_millis, IO_Vars<interrupt>::m_state);
		}
	}
	ListenerMethodLog(ame_Log_Statement, "DebounceLoopInterrupt",  "println", "end interrupt");
}

template<int interrupt>
void OutputInterrupt(float tpc){
	IO_Millis<interrupt>::m_millis = millis();
	// ListenerMethodLog(ame_Log_Statement, "OutputInterrupt",  "println", "");
	int pin = IO_Pin<interrupt>::m_pin;
	List<ListenerEvent>* events = IO_ClassEvent<interrupt>::m_events;
	List<EventMethod>* static_events = IO_Event<interrupt>::m_events;
	if(pin == -1 || events == nullptr || static_events == nullptr){
		ListenerMethodLog(ame_Log_Statement, "OutputInterrupt",  "println", "pin == -1 || events == nullptr || static_events == nullptr");
		return;
	}
	if(IO_Output_State<interrupt>::m_state == nullptr || IO_Consuming<interrupt>::m_consume == nullptr){
		return;
	}
	if(IO_Vars<interrupt>::m_state != *IO_Output_State<interrupt>::m_state){
		*IO_Consuming<interrupt>::m_consume = true;
	}
	bool canConsume = *IO_Consuming<interrupt>::m_consume;
	if(!canConsume){
		return;
	}
	IO_Vars<interrupt>::m_state = *IO_Output_State<interrupt>::m_state;
	if(IO_Vars<interrupt>::m_inverted){
		digitalWrite(pin, !IO_Vars<interrupt>::m_state);
	}else{
		digitalWrite(pin, IO_Vars<interrupt>::m_state);
	}
	ListenerMethodLog(ame_Log_Statement, "OutputInterrupt",  "println", Note("interrupt ") + Note(interrupt));
	ListenerMethodLog(ame_Log_Statement, "OutputInterrupt",  "println", "start interrupt");
	for(int x = 0; x < static_events->getPosition(); x++){
		EventMethod event =  *static_events->getByPosition(x);
		if(IO_Vars<interrupt>::m_inverted){
			event(interrupt, IO_Millis<interrupt>::m_millis, !IO_Vars<interrupt>::m_state);
		}else{
			event(interrupt, IO_Millis<interrupt>::m_millis, IO_Vars<interrupt>::m_state);
		}
	}
	for(int x = 0; x < events->getPosition(); x++){
		ListenerEvent* e =  events->getByPosition(x);
		if(IO_Vars<interrupt>::m_inverted){
			e->event(interrupt, IO_Millis<interrupt>::m_millis, !IO_Vars<interrupt>::m_state);
		}else{
			e->event(interrupt, IO_Millis<interrupt>::m_millis, IO_Vars<interrupt>::m_state);
		}
	}
	ListenerMethodLog(ame_Log_Statement, "OutputInterrupt",  "println", "end interrupt");
}

#ifdef ARDUINO_ARCH_ESP8266

template<int interrupt>
void ICACHE_RAM_ATTR Interrupt(){
	
#elif defined(ARDUINO_ARCH_SAM)

template<int interrupt>
void Interrupt(){
	
#elif defined(ARDUINO_ARCH_AVR)

template<int interrupt>
void Interrupt(){

#elif defined(ARDUINO_SAMD_ZERO)

template<int interrupt>
void Interrupt(){

#else

template<int interrupt>
void Interrupt(){
	
#endif
	IO_Millis<interrupt>::m_millis = millis();
	using EventMethod = void (*)(int,long,bool);
	ListenerMethodLog(ame_Log_Statement, "Interrupt",  "println", "");
	int pin = IO_Pin<interrupt>::m_pin;
	bool state = IO_Vars<interrupt>::m_state;
	List<ListenerEvent>* events = IO_ClassEvent<interrupt>::m_events;
	List<EventMethod>* static_events = IO_Event<interrupt>::m_events;
	if(pin == -1 || events == nullptr || static_events == nullptr){
		ListenerMethodLog(ame_Log_Statement, "Interrupt",  "println", "pin == -1 || events == nullptr || static_events == nullptr");
		return;
	}
	if(IO_Vars<interrupt>::m_safe){
		IO_Vars<interrupt>::m_state = digitalRead(pin);
	}else{
		IO_Vars<interrupt>::m_state = !(state);
	}
	ListenerMethodLog(ame_Log_Statement, "Interrupt",  "println", "start interrupt");
	for(int x = 0; x < static_events->getPosition(); x++){
		EventMethod event =  *static_events->getByPosition(x);
		if(IO_Vars<interrupt>::m_inverted){
			event(interrupt, IO_Millis<interrupt>::m_millis, !IO_Vars<interrupt>::m_state);
		}else{
			event(interrupt, IO_Millis<interrupt>::m_millis, IO_Vars<interrupt>::m_state);
		}
	}
	for(int x = 0; x < events->getPosition(); x++){
		ListenerEvent* e =  events->getByPosition(x);
		if(IO_Vars<interrupt>::m_inverted){
			e->event(interrupt, IO_Millis<interrupt>::m_millis, !IO_Vars<interrupt>::m_state);
		}else{
			e->event(interrupt, IO_Millis<interrupt>::m_millis, IO_Vars<interrupt>::m_state);
		}
	}
	ListenerMethodLog(ame_Log_Statement, "Interrupt",  "println", "end interrupt");
}

#ifdef ARDUINO_ARCH_ESP8266

template<int interrupt>
void ICACHE_RAM_ATTR ThreadInterrupt(){
	
#elif defined(ARDUINO_ARCH_SAM)

template<int interrupt>
void ThreadInterrupt(){
	
#elif defined(ARDUINO_ARCH_AVR)

template<int interrupt>
void ThreadInterrupt(){

#elif defined(ARDUINO_SAMD_ZERO)

template<int interrupt>
void ThreadInterrupt(){

#else

template<int interrupt>
void ThreadInterrupt(){
	
#endif
	ListenerMethodLog(ame_Log_Statement, "ThreadInterrupt",  "println", "");
	if(IO_Vars<interrupt>::m_safe){
		ListenerMethodLog(ame_Log_Statement, "ThreadInterrupt",  "println", "safe interrupt");
		Interrupt<interrupt>();
	}else{
		if(ThreadMap_m != nullptr){
			ListenerMethodLog(ame_Log_Statement, "ThreadInterrupt",  "println", "adding unsafe interrupt");
			ThreadMap_m->addLValue(&Interrupt<interrupt>);
		}
	}
}

template<int interrupt>
void Interrupt(bool state){
	IO_Millis<interrupt>::m_millis = millis();
	using EventMethod = void (*)(int,long,bool);
	ListenerMethodLog(ame_Log_Statement, "Interrupt",  "println", "with parameter");
	int pin = IO_Pin<interrupt>::m_pin;
	List<ListenerEvent>* events = IO_ClassEvent<interrupt>::m_events;
	List<EventMethod>* static_events = IO_Event<interrupt>::m_events;
	if(pin == -1 || events == nullptr || static_events == nullptr){
		ListenerMethodLog(ame_Log_Statement, "Interrupt",  "println", "pin == -1 || events == nullptr || static_events == nullptr");
		return;
	}
	ListenerMethodLog(ame_Log_Statement, "Interrupt",  "println", "start interrupt");
	for(int x = 0; x < static_events->getPosition(); x++){
		EventMethod event =  *static_events->getByPosition(x);
		if(IO_Vars<interrupt>::m_inverted){
			event(interrupt, IO_Millis<interrupt>::m_millis, !state);
		}else{
			event(interrupt, IO_Millis<interrupt>::m_millis, state);
		}
	}
	for(int x = 0; x < events->getPosition(); x++){
		ListenerEvent* e =  events->getByPosition(x);
		if(IO_Vars<interrupt>::m_inverted){
			e->event(interrupt, IO_Millis<interrupt>::m_millis, !state);
		}else{
			e->event(interrupt, IO_Millis<interrupt>::m_millis, state);
		}
	}
	ListenerMethodLog(ame_Log_Statement, "Interrupt",  "println", "end interrupt");
}
#endif

class Listener IMPLEMENTATION_BaseAppState {
    public:
		using EventMethod = void (*)(int,long,bool);
		typedef void (*Method)();
		Listener(){
			ListenerLog(ame_Log_StartMethod, "Constructor",  "println", "");
			if(ThreadMap_m == nullptr){
				ThreadMap_m = new PrimitiveList<void (*)()>();
			}
			if(LoopMap_m == nullptr){
				LoopMap_m = new PrimitiveList<void (*)(float)>();
			}
			if(OutputMap_m == nullptr){
				OutputMap_m = new PrimitiveList<void (*)()>();
			}
			ListenerLog(ame_Log_EndMethod, "Constructor",  "println", "");
		}
		virtual ~Listener(){
			ListenerLog(ame_Log_StartMethod, "Destructor",  "println", "");
			if(ThreadMap_m != nullptr){
				delete ThreadMap_m;
			}
			if(LoopMap_m != nullptr){
				delete LoopMap_m;
			}
			if(OutputMap_m != nullptr){
				delete OutputMap_m;
			}
			ListenerLog(ame_Log_EndMethod, "Destructor",  "println", "");
		}
		
		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){return Class<Listener>::getClass();}
		virtual bool instanceof(cppObjectClass* cls){return cls == Class<Listener>::getClass();}
		#endif
		
#ifdef ame_ArduinoIDE
		template<int interrupt>
		void Secure(){
			ListenerLog(ame_Log_StartMethod, "Secure",  "println", "");
			IO_Vars<interrupt>::m_safe = true;
			ListenerLog(ame_Log_EndMethod, "Secure",  "println", "");
		}
		
		template<int interrupt>
		void UnSecure(){
			ListenerLog(ame_Log_StartMethod, "UnSecure",  "println", "");
			IO_Vars<interrupt>::m_safe = false;
			ListenerLog(ame_Log_EndMethod, "UnSecure",  "println", "");
		}
		virtual void updateState(float tpc){
			for(int x = 0; x < LoopMap_m->getPosition(); x++){
				(*LoopMap_m->getByPosition(x))(tpc);
			}
			for(int x = 0; x < ThreadMap_m->getPosition(); x++){
				(*ThreadMap_m->getByPosition(x))();
			}
			for(int x = 0; x < OutputMap_m->getPosition(); x++){
				(*OutputMap_m->getByPosition(x))();
			}
			OutputMap_m->resetDelete();
			ThreadMap_m->resetDelete();
		}
		
		template<int interrupt>
		void createInput(int pin, bool inv, bool state){
			ListenerLog(ame_Log_StartMethod, "createInput",  "println", "");
			IO_Pin<interrupt>::m_pin = pin;
			IO_Vars<interrupt>::m_type = ListenerInput;
			IO_Vars<interrupt>::m_state = state;
			IO_Vars<interrupt>::m_safe = true;
			IO_Vars<interrupt>::m_inverted = inv;
			pinMode(pin,INPUT);
			LoopMap_m->addLValue(&Input<interrupt>);
			ListenerLog(ame_Log_EndMethod, "createInput",  "println", "");
		}
		
		template<int interrupt>
		void createInput(int pin, bool inv){
			createInput<interrupt>(pin, inv, false);
		}
		
		template<int interrupt>
		void createInput(int pin){
			createInput<interrupt>(pin, false, false);
		}
		
		template<int interrupt>
		void createDebounceInput(float l, int pin, bool inv, bool state){
			IO_Pin<interrupt>::m_pin = pin;
			IO_Vars<interrupt>::m_type = ListenerDebounceInput;
			IO_Vars<interrupt>::m_state = state;
			IO_Float_Times<interrupt>::m_timelimit = l;
			IO_Vars<interrupt>::m_safe = true;
			IO_Vars<interrupt>::m_inverted = inv;
			pinMode(pin,INPUT);
			LoopMap_m->addLValue(&DebounceInput<interrupt>);
		}
		
		template<int interrupt>
		void createDebounceInput(float l, int pin, bool inv){
			createDebounceInput<interrupt>(l, pin, inv, false);
		}
		
		template<int interrupt>
		void createDebounceInput(float l, int pin){
			createDebounceInput<interrupt>(l, pin, false, false);
		}
		
		template<int interrupt>
		void createDebounceInput(int pin){
			createDebounceInput<interrupt>(0.1f, pin, false);
		}
		
		template<int interrupt>
		void createDebounceInput(int pin, bool inv){
			createDebounceInput<interrupt>(0.1f, pin, inv, false);
		}
		
		template<int interrupt>
		void createDebounceInterrupt(long l, int pin, bool inv, bool state, bool owner){
			IO_Pin<interrupt>::m_pin = pin;
			IO_Vars<interrupt>::m_type = ListenerDebounceInterrupt;
			IO_Vars<interrupt>::m_state = state;
			IO_Vars<interrupt>::m_safe = true;
			IO_Vars<interrupt>::m_inverted = inv;
			IO_Long_Times<interrupt>::m_timelimit = l;
			if(IO_Event<interrupt>::m_events == nullptr){
				IO_Event<interrupt>::m_events = new PrimitiveList<EventMethod>(5, owner, true);
			}
			if(IO_ClassEvent<interrupt>::m_events == nullptr){
				IO_ClassEvent<interrupt>::m_events = new PrimitiveList<ListenerEvent>(5, owner, true);
			}
			pinMode(pin,INPUT_PULLUP);
			attachInterrupt(digitalPinToInterrupt(pin), DebounceInterrupt<interrupt>, CHANGE);
		}
		
		template<int interrupt>
		void createDebounceInterrupt(long l, int pin){
			createDebounceInterrupt<interrupt>(l, pin, false, false, true);
		}
		
		template<int interrupt>
		void createDebounceInterrupt(long l, int pin, bool inv){
			createDebounceInterrupt<interrupt>(l, pin, inv, false, true);
		}
		
		template<int interrupt>
		void createDebounceInterrupt(long l, int pin, bool inv, bool state){
			createDebounceInterrupt<interrupt>(l, pin, inv, state, true);
		}
		
		template<int interrupt>
		void createDebounceInterruptEvent(long l, int pin, bool inv, bool state, bool owner){
			IO_Pin<interrupt>::m_pin = pin;
			IO_Vars<interrupt>::m_type = ListenerDebounceInterruptEvent;
			IO_Vars<interrupt>::m_state = state;
			IO_Vars<interrupt>::m_safe = true;
			IO_Vars<interrupt>::m_inverted = inv;
			IO_Long_Times<interrupt>::m_timelimit = l;
			if(IO_Event<interrupt>::m_events == nullptr){
				IO_Event<interrupt>::m_events = new PrimitiveList<EventMethod>(5, owner, true);
			}
			pinMode(pin,INPUT_PULLUP);
			attachInterrupt(digitalPinToInterrupt(pin), DebounceInterrupt_Event<interrupt>, CHANGE);
		}
		
		template<int interrupt>
		void createDebounceInterruptEvent(long l, int pin){
			createDebounceInterruptEvent<interrupt>(l, pin, false, false, true);
		}
		
		template<int interrupt>
		void createDebounceInterruptEvent(long l, int pin, bool inv, bool state){
			createDebounceInterruptEvent<interrupt>(l, pin, inv, state, true);
		}
		
		template<int interrupt>
		void createDebounceInterruptEvent(long l, int pin, bool inv){
			createDebounceInterruptEvent<interrupt>(l, pin, inv, false, true);
		}
		
		template<int interrupt>
		void createDebounceInterruptClassEvent(long l, int pin, bool inv, bool state, bool owner){
			IO_Pin<interrupt>::m_pin = pin;
			IO_Vars<interrupt>::m_type = ListenerDebounceInterruptClassEvent;
			IO_Vars<interrupt>::m_state = state;
			IO_Vars<interrupt>::m_safe = true;
			IO_Vars<interrupt>::m_inverted = inv;
			IO_Long_Times<interrupt>::m_timelimit = l;
			if(IO_ClassEvent<interrupt>::m_events == nullptr){
				IO_ClassEvent<interrupt>::m_events = new PrimitiveList<ListenerEvent>(5, owner, true);
			}
			pinMode(pin,INPUT_PULLUP);
			attachInterrupt(digitalPinToInterrupt(pin), DebounceInterrupt_ClassEvent<interrupt>, CHANGE);
		}
		
		template<int interrupt>
		void createDebounceInterruptClassEvent(long l, int pin){
			createDebounceInterruptClassEvent<interrupt>(l, pin, false, false, true);
		}
		
		template<int interrupt>
		void createDebounceInterruptClassEvent(long l, int pin, bool inv){
			createDebounceInterruptClassEvent<interrupt>(l, pin, inv, false, true);
		}
		
		template<int interrupt>
		void createDebounceInterruptClassEvent(long l, int pin, bool inv, bool state){
			createDebounceInterruptClassEvent<interrupt>(l, pin, inv, state, true);
		}
		
		template<int interrupt>
		void loadDebounceLoopInterrupt(float l, int pin,  bool inv, bool state, bool owner, MonkeyImporter* importer){
			ElementId parent = Note("Listener.") + Note(interrupt);
			if(importer !=  nullptr){
				IO_Pin<interrupt>::m_pin = importer->read(parent.child("pin"), pin);
				IO_Vars<interrupt>::m_type = importer->read(parent.child("type"), ListenerDebounceLoopInterrupt);
				IO_Vars<interrupt>::m_state = importer->read(parent.child("state"), state);
				IO_Vars<interrupt>::m_safe = importer->read(parent.child("safe"), true);
				IO_Vars<interrupt>::m_inverted = importer->read(parent.child("inv"), inv);
				IO_Float_Times<interrupt>::m_timelimit = importer->read(parent.child("timelimit"), l);
			}else{
				IO_Pin<interrupt>::m_pin = pin;
				IO_Vars<interrupt>::m_type = ListenerDebounceLoopInterrupt;
				IO_Vars<interrupt>::m_state = state;
				IO_Vars<interrupt>::m_safe = true;
				IO_Vars<interrupt>::m_inverted = inv;
				IO_Float_Times<interrupt>::m_timelimit = l;
			}
			if(IO_Event<interrupt>::m_events == nullptr){
				IO_Event<interrupt>::m_events = new PrimitiveList<EventMethod>(5, owner, true);
			}
			if(IO_ClassEvent<interrupt>::m_events == nullptr){
				IO_ClassEvent<interrupt>::m_events = new PrimitiveList<ListenerEvent>(5, owner, true);
			}
			pinMode(IO_Pin<interrupt>::m_pin,INPUT);
			LoopMap_m->addLValue(&DebounceLoopInterrupt<interrupt>);
			ListenerLog(ame_Log_Statement, "loadDebounceLoopInterrupt",  "println", Note("pin: ") + Note(IO_Pin<interrupt>::m_pin));
			ListenerLog(ame_Log_Statement, "loadDebounceLoopInterrupt",  "println", Note("type: ") + Note(IO_Vars<interrupt>::m_type));
			ListenerLog(ame_Log_Statement, "loadDebounceLoopInterrupt",  "println", Note("state: ") + Note(IO_Vars<interrupt>::m_state));
			ListenerLog(ame_Log_Statement, "loadDebounceLoopInterrupt",  "println", Note("safe: ") + Note(IO_Vars<interrupt>::m_safe));
			ListenerLog(ame_Log_Statement, "loadDebounceLoopInterrupt",  "println", Note("inverted: ") + Note(IO_Vars<interrupt>::m_inverted));
			ListenerLog(ame_Log_Statement, "loadDebounceLoopInterrupt",  "println", Note("timelimit: ") + Note(IO_Float_Times<interrupt>::m_timelimit));
		}
		
		template<int interrupt>
		void loadDebounceLoopInterrupt(float l, int pin, MonkeyImporter* importer){
			loadDebounceLoopInterrupt<interrupt>(l, pin, false, false, true, importer);
		}
		
		template<int interrupt>
		void loadDebounceLoopInterrupt(float l, int pin,  bool inv, MonkeyImporter* importer){
			loadDebounceLoopInterrupt<interrupt>(l, pin, inv, false, true, importer);
		}
		
		template<int interrupt>
		void loadDebounceLoopInterrupt(float l, int pin,  bool inv, bool state, MonkeyImporter* importer){
			loadDebounceLoopInterrupt<interrupt>(l, pin, inv, state, true, importer);
		}
		
		template<int interrupt>
		void saveDebounceLoopInterrupt(MonkeyExporter* exporter){
			ElementId parent = Note("Listener.") + Note(interrupt);
			if(exporter ==  nullptr){
				return;
			}
			exporter->write(parent.child("pin"), IO_Pin<interrupt>::m_pin);
			exporter->write(parent.child("type"), IO_Vars<interrupt>::m_type);
			exporter->write(parent.child("state"), IO_Vars<interrupt>::m_state);
			exporter->write(parent.child("safe"), IO_Vars<interrupt>::m_safe);
			exporter->write(parent.child("inv"), IO_Vars<interrupt>::m_inverted);
			exporter->write(parent.child("timelimit"), IO_Float_Times<interrupt>::m_timelimit);
			ListenerLog(ame_Log_Statement, "saveDebounceLoopInterrupt",  "println", Note("pin: ") + Note(IO_Pin<interrupt>::m_pin));
			ListenerLog(ame_Log_Statement, "saveDebounceLoopInterrupt",  "println", Note("type: ") + Note(IO_Vars<interrupt>::m_type));
			ListenerLog(ame_Log_Statement, "saveDebounceLoopInterrupt",  "println", Note("state: ") + Note(IO_Vars<interrupt>::m_state));
			ListenerLog(ame_Log_Statement, "saveDebounceLoopInterrupt",  "println", Note("safe: ") + Note(IO_Vars<interrupt>::m_safe));
			ListenerLog(ame_Log_Statement, "saveDebounceLoopInterrupt",  "println", Note("inverted: ") + Note(IO_Vars<interrupt>::m_inverted));
			ListenerLog(ame_Log_Statement, "saveDebounceLoopInterrupt",  "println", Note("timelimit: ") + Note(IO_Float_Times<interrupt>::m_timelimit));
		}
		
		template<int interrupt>
		void createDebounceLoopInterrupt(float l, int pin,  bool inv, bool state, bool owner){
			IO_Pin<interrupt>::m_pin = pin;
			IO_Vars<interrupt>::m_type = ListenerDebounceLoopInterrupt;
			IO_Vars<interrupt>::m_state = state;
			IO_Vars<interrupt>::m_safe = true;
			IO_Vars<interrupt>::m_inverted = inv;
			IO_Float_Times<interrupt>::m_timelimit = l;
			if(IO_Event<interrupt>::m_events == nullptr){
				IO_Event<interrupt>::m_events = new PrimitiveList<EventMethod>(5, owner, true);
			}
			if(IO_ClassEvent<interrupt>::m_events == nullptr){
				IO_ClassEvent<interrupt>::m_events = new PrimitiveList<ListenerEvent>(5, owner, true);
			}
			pinMode(pin,INPUT);
			LoopMap_m->addLValue(&DebounceLoopInterrupt<interrupt>);
			ListenerLog(ame_Log_Statement, "createDebounceLoopInterrupt",  "println", Note("interrupt: ") + Note(interrupt));
			ListenerLog(ame_Log_Statement, "createDebounceLoopInterrupt",  "println", Note("pin: ") + Note(IO_Pin<interrupt>::m_pin));
			ListenerLog(ame_Log_Statement, "createDebounceLoopInterrupt",  "println", Note("type: ") + Note(IO_Vars<interrupt>::m_type));
			ListenerLog(ame_Log_Statement, "createDebounceLoopInterrupt",  "println", Note("state: ") + Note(IO_Vars<interrupt>::m_state));
			ListenerLog(ame_Log_Statement, "createDebounceLoopInterrupt",  "println", Note("safe: ") + Note(IO_Vars<interrupt>::m_safe));
			ListenerLog(ame_Log_Statement, "createDebounceLoopInterrupt",  "println", Note("invert: ") + Note(IO_Vars<interrupt>::m_inverted));
		}
		
		template<int interrupt>
		void createDebounceLoopInterrupt(float l, int pin){
			createDebounceLoopInterrupt<interrupt>(l, pin, false, false, true);
		}
		
		template<int interrupt>
		void createDebounceLoopInterrupt(float l, int pin,  bool inv){
			createDebounceLoopInterrupt<interrupt>(l, pin, inv, false, true);
		}
		
		template<int interrupt>
		void createDebounceLoopInterrupt(float l, int pin,  bool inv, bool state){
			createDebounceLoopInterrupt<interrupt>(l, pin, inv, state, true);
		}
		
		template<int interrupt, int multiInterrupt, int... interrupts>
		void createDebounceMultiInterrupt(long l, int pin,  bool inv, bool state, bool owner){
			IO_Pin<interrupt>::m_pin = pin;
			IO_Vars<interrupt>::m_type = ListenerDebounceMultiMultiInterruptEvent_v3;
			IO_Vars<interrupt>::m_state = state;
			IO_Vars<interrupt>::m_safe = true;
			IO_Vars<interrupt>::m_inverted = inv;
			IO_Multi_State<multiInterrupt>::m_state = state;
			IO_Long_Times<interrupt>::m_timelimit = l;
			if(IO_Event<interrupt>::m_events == nullptr){
				IO_Event<interrupt>::m_events = new PrimitiveList<EventMethod>(5, owner, true);
			}
			if(IO_ClassEvent<interrupt>::m_events == nullptr){
				IO_ClassEvent<interrupt>::m_events = new PrimitiveList<ListenerEvent>(5, owner, true);
			}
			if(IO_Multi_Event<interrupt>::m_events == nullptr){
				IO_Multi_Event<interrupt>::m_events = new PrimitiveList<EventMethod>(5, owner, true);
			}
			if(IO_Multi_ClassEvent<interrupt>::m_events == nullptr){
				IO_Multi_ClassEvent<interrupt>::m_events = new PrimitiveList<ListenerEvent>(5, owner, true);
			}
			pinMode(pin,INPUT_PULLUP);
			attachInterrupt(digitalPinToInterrupt(pin), DebounceMultiInterrupt<interrupt,multiInterrupt,interrupts...>, CHANGE);
		}
		
		template<int interrupt, int multiInterrupt, int... interrupts>
		void createDebounceMultiInterrupt(float l, int pin){
			createDebounceMultiInterrupt<interrupt,multiInterrupt,interrupts...>(l, pin, false, false, true);
		}
		
		template<int interrupt>
		void createDebounceMultiInterrupt(float l, int pin,  bool inv){
			createDebounceMultiInterrupt<interrupt>(l, pin, inv, false, true);
		}
		
		template<int interrupt>
		void createDebounceMultiInterrupt(float l, int pin,  bool inv, bool state){
			createDebounceMultiInterrupt<interrupt>(l, pin, inv, state, true);
		}
		
		template<int interrupt, int multiInterrupt, int... interrupts>
		void createSingleDebounceMultiInterrupt(long l, int pin,  bool inv, bool state, bool owner){
			IO_Pin<interrupt>::m_pin = pin;
			IO_Vars<interrupt>::m_type = ListenerDebounceMultiMultiInterruptEvent_v3;
			IO_Vars<interrupt>::m_state = state;
			IO_Vars<interrupt>::m_safe = true;
			IO_Vars<interrupt>::m_inverted = inv;
			IO_Multi_State<multiInterrupt>::m_state = state;
			IO_Long_Times<interrupt>::m_timelimit = l;
			pinMode(pin,INPUT_PULLUP);
			attachInterrupt(digitalPinToInterrupt(pin), SingleDebounceMultiInterrupt<interrupt,multiInterrupt,interrupts...>, CHANGE);
		}
		
		template<int interrupt, int multiInterrupt, int... interrupts>
		void createSingleDebounceMultiInterrupt(float l, int pin){
			createSingleDebounceMultiInterrupt<interrupt,multiInterrupt,interrupts...>(l, pin, false, false, true);
		}
		
		template<int interrupt>
		void createSingleDebounceMultiInterrupt(float l, int pin,  bool inv){
			createSingleDebounceMultiInterrupt<interrupt>(l, pin, inv, false, true);
		}
		
		template<int interrupt>
		void createSingleDebounceMultiInterrupt(float l, int pin,  bool inv, bool state){
			createSingleDebounceMultiInterrupt<interrupt>(l, pin, inv, state, true);
		}
		
		template<int interrupt>
		void createInterrupt(int pin, bool state, bool safe, bool owner){
			IO_Pin<interrupt>::m_pin = pin;
			IO_Vars<interrupt>::m_type = ListenerInterrupt;
			IO_Vars<interrupt>::m_state = state;
			IO_Vars<interrupt>::m_safe = safe;
			if(IO_Event<interrupt>::m_events == nullptr){
				IO_Event<interrupt>::m_events = new PrimitiveList<EventMethod>(5, owner, true);
			}
			if(IO_ClassEvent<interrupt>::m_events == nullptr){
				IO_ClassEvent<interrupt>::m_events = new PrimitiveList<ListenerEvent>(5, owner, true);
			}
			pinMode(pin,INPUT_PULLUP);
			attachInterrupt(digitalPinToInterrupt(pin), Interrupt<interrupt>, CHANGE);
		}
		
		template<int interrupt>
		void createInterrupt(int pin, bool state, bool safe){
			createInterrupt<interrupt>(pin, state, safe, true);
		}
		
		template<int interrupt>
		void createInterrupt(int pin, bool state){
			createInterrupt<interrupt>(pin, state, true, true);
		}
		
		template<int interrupt>
		void createThreadInterrupt(int pin, bool state, bool owner){
			IO_Pin<interrupt>::m_pin = pin;
			IO_Vars<interrupt>::m_type = ListenerThreadInterrupt;
			IO_Vars<interrupt>::m_state = state;
			IO_Vars<interrupt>::m_safe = true;
			if(IO_Event<interrupt>::m_events == nullptr){
				IO_Event<interrupt>::m_events = new PrimitiveList<EventMethod>(5, owner, true);
			}
			if(IO_ClassEvent<interrupt>::m_events == nullptr){
				IO_ClassEvent<interrupt>::m_events = new PrimitiveList<ListenerEvent>(5, owner, true);
			}
			pinMode(pin,INPUT);
			attachInterrupt(digitalPinToInterrupt(pin), ThreadInterrupt<interrupt>, CHANGE);
		}
		
		template<int interrupt>
		void createThreadInterrupt(int pin, bool state){
			createThreadInterrupt<interrupt>(pin, state, true);
		}
		
		template<int interrupt>
		void createOutput(int pin, bool state){
			IO_Pin<interrupt>::m_pin = pin;
			IO_Vars<interrupt>::m_type = ListenerOutput;
			IO_Vars<interrupt>::m_state = state;
			IO_Vars<interrupt>::m_safe = true;
			pinMode(pin,OUTPUT);
		}
		
		template<int interrupt>
		void createOutput(int pin){
			createOutput<interrupt>(pin, false);
		}
		
		template<int interrupt>
		void loadOutputInterrupt(int pin, bool inv, bool state, bool owner, MonkeyImporter* importer){
			if(importer != nullptr){
				ElementId parent = Note("Listener.output.") + Note(interrupt);
				
				IO_Pin<interrupt>::m_pin = importer->read(parent.child("pin"), pin);
				IO_Vars<interrupt>::m_type = importer->read(parent.child("type"), ListenerOutputInterrupt);
				IO_Vars<interrupt>::m_state = importer->read(parent.child("state"), state);
				IO_Vars<interrupt>::m_safe = importer->read(parent.child("safe"), true);
				IO_Vars<interrupt>::m_inverted = importer->read(parent.child("invert"), inv);
			}else{
				IO_Pin<interrupt>::m_pin = pin;
				IO_Vars<interrupt>::m_type = ListenerOutputInterrupt;
				IO_Vars<interrupt>::m_state = state;
				IO_Vars<interrupt>::m_safe = true;
				IO_Vars<interrupt>::m_inverted = inv;
			}
			if(IO_Event<interrupt>::m_events == nullptr){
				IO_Event<interrupt>::m_events = new PrimitiveList<EventMethod>(5, owner, true);
			}
			if(IO_ClassEvent<interrupt>::m_events == nullptr){
				IO_ClassEvent<interrupt>::m_events = new PrimitiveList<ListenerEvent>(5, owner, true);
			}
			pinMode(IO_Pin<interrupt>::m_pin,OUTPUT);
			digitalWrite(IO_Pin<interrupt>::m_pin, IO_Vars<interrupt>::m_state);
			LoopMap_m->addLValue(&OutputInterrupt<interrupt>);
			ListenerLog(ame_Log_Statement, "loadOutputInterrupt",  "println", Note("pin: ") + Note(IO_Pin<interrupt>::m_pin));
			ListenerLog(ame_Log_Statement, "loadOutputInterrupt",  "println", Note("type: ") + Note(IO_Vars<interrupt>::m_type));
			ListenerLog(ame_Log_Statement, "loadOutputInterrupt",  "println", Note("state: ") + Note(IO_Vars<interrupt>::m_state));
			ListenerLog(ame_Log_Statement, "loadOutputInterrupt",  "println", Note("safe: ") + Note(IO_Vars<interrupt>::m_safe));
			
		}
		
		template<int interrupt>
		void loadOutputInterrupt(int pin, MonkeyImporter* importer){
			loadOutputInterrupt<interrupt>(pin, false, false, true, importer);
		}
		
		template<int interrupt>
		void loadOutputInterrupt(int pin, bool inv, bool state, MonkeyImporter* importer){
			loadOutputInterrupt<interrupt>(pin, false, state, true, importer);
		}
		
		template<int interrupt>
		void loadOutputInterrupt(int pin, bool state, MonkeyImporter* importer){
			loadOutputInterrupt<interrupt>(pin, false, state, true, importer);
		}
		
		template<int interrupt>
		void saveOutputInterrupt(MonkeyExporter* exporter){
			if(exporter == nullptr){
				return;
			}
			ElementId parent = Note("Listener.output.") + Note(interrupt);
			exporter->write(parent.child("pin"), IO_Pin<interrupt>::m_pin);
			exporter->write(parent.child("type"), IO_Vars<interrupt>::m_type);
			exporter->write(parent.child("state"), IO_Vars<interrupt>::m_state);
			exporter->write(parent.child("safe"), IO_Vars<interrupt>::m_safe);
			exporter->write(parent.child("invert"), IO_Vars<interrupt>::m_inverted);
			ListenerLog(ame_Log_Statement, "saveOutputInterrupt",  "println", Note("interrupt: ") + Note(interrupt));
			ListenerLog(ame_Log_Statement, "saveOutputInterrupt",  "println", Note("pin: ") + Note(IO_Pin<interrupt>::m_pin));
			ListenerLog(ame_Log_Statement, "saveOutputInterrupt",  "println", Note("type: ") + Note(IO_Vars<interrupt>::m_type));
			ListenerLog(ame_Log_Statement, "saveOutputInterrupt",  "println", Note("state: ") + Note(IO_Vars<interrupt>::m_state));
			ListenerLog(ame_Log_Statement, "saveOutputInterrupt",  "println", Note("safe: ") + Note(IO_Vars<interrupt>::m_safe));
			ListenerLog(ame_Log_Statement, "saveOutputInterrupt",  "println", Note("invert: ") + Note(IO_Vars<interrupt>::m_inverted));
		}
		
		template<int interrupt>
		void createOutputInterrupt(int pin, bool inv, bool state, bool owner){
			IO_Pin<interrupt>::m_pin = pin;
			IO_Vars<interrupt>::m_type = ListenerOutputInterrupt;
			IO_Vars<interrupt>::m_state = state;
			IO_Vars<interrupt>::m_safe = true;
			IO_Vars<interrupt>::m_inverted = inv;
			if(IO_Event<interrupt>::m_events == nullptr){
				IO_Event<interrupt>::m_events = new PrimitiveList<EventMethod>(5, owner, true);
			}
			if(IO_ClassEvent<interrupt>::m_events == nullptr){
				IO_ClassEvent<interrupt>::m_events = new PrimitiveList<ListenerEvent>(5, owner, true);
			}
			pinMode(pin,OUTPUT);
			digitalWrite(pin, state);
			LoopMap_m->addLValue(&OutputInterrupt<interrupt>);
			ListenerLog(ame_Log_Statement, "createOutputInterrupt",  "println", Note("interrupt: ") + Note(interrupt));
			ListenerLog(ame_Log_Statement, "createOutputInterrupt",  "println", Note("pin: ") + Note(IO_Pin<interrupt>::m_pin));
			ListenerLog(ame_Log_Statement, "createOutputInterrupt",  "println", Note("type: ") + Note(IO_Vars<interrupt>::m_type));
			ListenerLog(ame_Log_Statement, "createOutputInterrupt",  "println", Note("state: ") + Note(IO_Vars<interrupt>::m_state));
			ListenerLog(ame_Log_Statement, "createOutputInterrupt",  "println", Note("safe: ") + Note(IO_Vars<interrupt>::m_safe));
			ListenerLog(ame_Log_Statement, "createOutputInterrupt",  "println", Note("invert: ") + Note(IO_Vars<interrupt>::m_inverted));
		}
		
		template<int interrupt>
		void createOutputInterrupt(int pin){
			createOutputInterrupt<interrupt>(pin, false, false, true);
		}
		
		template<int interrupt>
		void createOutputInterrupt(int pin, bool inv){
			createOutputInterrupt<interrupt>(pin, inv, false, true);
		}
		
		template<int interrupt>
		void createOutputInterrupt(int pin, bool inv, bool state){
			createOutputInterrupt<interrupt>(pin, inv, state, true);
		}
		
		template<int interrupt>
		void loadOutputValue(Note name, bool state, bool owner, MonkeyImporter* importer){
			if(IO_Output_Value<interrupt>::m_output_values == nullptr){
				IO_Output_Value<interrupt>::m_output_values = new PrimitiveMap<Note,bool>(owner);
				
				ElementId parent = Note("Listener.output.") + Note(interrupt);
				*IO_Output_Value<interrupt>::m_output_values = importer->read(parent.child("output_values"), PrimitiveMap<Note,bool>());
			}
			if(IO_Output_Value<interrupt>::m_output_values->containKeyByLValue(name)){
				return;
			}
			IO_Output_Value<interrupt>::m_output_values->addLValues(name,state);
			ListenerLog(ame_Log_Statement, "loadOutputValue",  "println", Note("name: ") + name);
			ListenerLog(ame_Log_Statement, "loadOutputValue",  "println", Note("state: ") + Note(state));
		}
		
		template<int interrupt>
		void loadOutputValue(Note name, bool state, MonkeyImporter* importer){
			loadOutputValue<interrupt>(name, state, true, importer);
		}
		
		template<int interrupt>
		void saveOutputValue(MonkeyExporter* exporter){
			if(IO_Output_Value<interrupt>::m_output_values == nullptr || exporter == nullptr){
				return;
			}
			ElementId parent = Note("Listener.output.") + Note(interrupt);
			exporter->write(parent.child("output_values"), *IO_Output_Value<interrupt>::m_output_values);
		}
		
		template<int interrupt>
		void createOutputValue(Note name, bool state, bool owner){
			if(IO_Output_Value<interrupt>::m_output_values == nullptr){
				IO_Output_Value<interrupt>::m_output_values = new PrimitiveMap<Note,bool>(owner);
			}
			IO_Output_Value<interrupt>::m_output_values->addLValues(name,state);
		}
		
		template<int interrupt>
		void createOutputValue(Note name, bool state){
			createOutputValue<interrupt>(name, state, true);
		}
		
		template<int interrupt>
		void createOutputValue(Note name){
			createOutputValue<interrupt>(name, false, true);
		}
		
		template<int interrupt>
		void setOutputValue(Note name, bool state){
			if(IO_Output_Value<interrupt>::m_output_values == nullptr){
				return;
			}
			ListenerLog(ame_Log_Statement, "setOutputValue",  "println", Note("name: ") + name);
			ListenerLog(ame_Log_Statement, "setOutputValue",  "println", Note("state: ") + Note(state));
			IO_Output_Value<interrupt>::m_output_values->setLValues(name, state);
		}
		
		template<int interrupt,int interrupt_2>
		void applyOutputValue(Note name, bool state){
			if(IO_Output_Value<interrupt_2>::m_output_values == nullptr){
				return;
			}
			IO_Output_Value<interrupt_2>::m_output_values->setLValues(name, state);
			bool* statePointer = IO_Output_Value<interrupt_2>::m_output_values->getValueByLValue(name);
			if(statePointer == nullptr){
				return;
			}
			IO_Output_State<interrupt>::m_name = name;
			IO_Output_State<interrupt>::m_state = statePointer;
			if(IO_Vars<interrupt>::m_state == *statePointer){
				return;
			}
			IO_Vars<interrupt>::m_state = *statePointer;
			digitalWrite(IO_Pin<interrupt>::m_pin, *statePointer);
		}
		
		template<int interrupt,int interrupt_2>
		void loadLinkOutputValue(Note name, MonkeyImporter* importer){
			if(IO_Output_Value<interrupt_2>::m_output_values == nullptr || importer == nullptr){
				return;
			}
			ElementId parent = Note("Listener.output.") + Note(interrupt_2);
			Note loadName = importer->read(parent.child(Note(interrupt)).child("output_values").child("link"), name);
			bool* state = IO_Output_Value<interrupt_2>::m_output_values->getByLValue(loadName);
			IO_Output_State<interrupt>::m_name = name;
			IO_Output_State<interrupt>::m_state = state;
			IO_Consume<interrupt>::m_consume = true;
			IO_Consuming<interrupt>::m_consume = &IO_Consume<interrupt>::m_consume;
			ListenerLog(ame_Log_Statement, "loadLinkOutputValue",  "println", Note("loadName: ") + loadName);
		}
		
		template<int interrupt,int interrupt_2>
		void saveLinkOutputValue(Note name, MonkeyExporter* exporter){
			if(IO_Output_Value<interrupt_2>::m_output_values == nullptr || exporter == nullptr){
				return;
			}
			ElementId parent = Note("Listener.output.") + Note(interrupt_2);
			exporter->write(parent.child(Note(interrupt)).child("output_values").child("link"), name);
			
			bool* state = IO_Output_Value<interrupt_2>::m_output_values->getByLValue(name);
			IO_Output_State<interrupt>::m_name = name;
			IO_Output_State<interrupt>::m_state = state;
			IO_Consume<interrupt>::m_consume = true;
			IO_Consuming<interrupt>::m_consume = &IO_Consume<interrupt>::m_consume;
			ListenerLog(ame_Log_Statement, "saveLinkOutputValue",  "println", Note("loadName: ") + name);
		}
		
		template<int interrupt,int interrupt_2>
		void linkOutputValue(Note name){
			if(IO_Output_Value<interrupt_2>::m_output_values == nullptr){
				return;
			}
			bool* state = IO_Output_Value<interrupt_2>::m_output_values->getValueByLValue(name);
			IO_Output_State<interrupt>::m_name = name;
			IO_Output_State<interrupt>::m_state = state;
			IO_Consume<interrupt>::m_consume = true;
			IO_Consuming<interrupt>::m_consume = &IO_Consume<interrupt>::m_consume;
		}
		
		template<int interrupt,int interrupt_2>
		void syncOutputValue(Note name){
			if(IO_Output_Value<interrupt_2>::m_output_values == nullptr){
				return;
			}
			bool* state = IO_Output_Value<interrupt_2>::m_output_values->getValueByLValue(name);
			if(state == nullptr){
				return;
			}
			IO_Output_State<interrupt>::m_name = name;
			IO_Output_State<interrupt>::m_state = state;
			IO_Consume<interrupt>::m_consume = true;
			IO_Consuming<interrupt>::m_consume = &IO_Consume<interrupt>::m_consume;
		}
		
		template<int interrupt>
		bool getOutputValue(Note name){
			if(IO_Output_Value<interrupt>::m_output_values == nullptr){
				return false;
			}
			bool* state = IO_Output_Value<interrupt>::m_output_values->getByLValue(name);
			if(state == nullptr){
				return false;
			}
			return *state;
		}
		
		template<int interrupt>
		Note getOutputName(){
			return IO_Output_State<interrupt>::m_name;
		}
		
		template<int interrupt>
		void createOutputEvent(int pin, bool state, bool owner){
			IO_Pin<interrupt>::m_pin = pin;
			IO_Vars<interrupt>::m_type = ListenerOutputEvent;
			IO_Vars<interrupt>::m_state = state;
			IO_Vars<interrupt>::m_safe = true;
			if(IO_Event<interrupt>::m_events == nullptr){
				IO_Event<interrupt>::m_events = new PrimitiveList<EventMethod>(5, owner, true);
			}
			if(IO_ClassEvent<interrupt>::m_events == nullptr){
				IO_ClassEvent<interrupt>::m_events = new PrimitiveList<ListenerEvent>(5, owner, true);
			}
			pinMode(pin,OUTPUT);
		}
		
		template<int interrupt>
		void createOutputEvent(int pin, bool state){
			createOutputEvent<interrupt>(pin, state, true);
		}
		
		template<int interrupt>
		void createAnalogInput(int pin, bool owner){
			IO_Pin<interrupt>::m_pin = pin;
			Analog_Vars<interrupt>::m_type = ListenerAnalogInput;
			if(IO_AnalogEvent<interrupt>::m_events == nullptr){
				IO_AnalogEvent<interrupt>::m_events = new PrimitiveList<AnalogInputMethod>(5, owner, true);
			}
			if(IO_AnalogClassEvent<interrupt>::m_events == nullptr){
				IO_AnalogClassEvent<interrupt>::m_events = new PrimitiveList<ListenerAnalogEvent>(5, owner, true);
			}
			pinMode(pin,INPUT);
			LoopMap_m->addLValue(&AnalogInput<interrupt>);
		}
		
		template<int interrupt>
		void createAnalogInput(int pin){
			createAnalogInput<interrupt>(pin, true);
		}
		
		template<int interrupt>
		int Type(){
			return IO_Vars<interrupt>::m_type;
		}
		
		template<int interrupt>
		int Pin(){
			return IO_Pin<interrupt>::m_pin;
		}
		
		//template<int interrupt, int pinSize>
		//int Pin(int x){
			//if(pinSize <= x){
				//return -1;
			//}
			//return IO_Multi_Pins<interrupt>::m_pin[x];
		//}
		
		template<int interrupt>
		bool isInverted(){
			return IO_Vars<interrupt>::m_inverted;
		}
		
		template<int interrupt>
		void invert(bool s){
			IO_Vars<interrupt>::m_inverted = s;
		}
		
		template<int interrupt>
		void invert(){
			IO_Vars<interrupt>::m_inverted = !IO_Vars<interrupt>::m_inverted;
		}
		
		template<int interrupt>
		void setPin(int pin){
			if(IO_Vars<interrupt>::m_type == -1){
				return;
			}
			if(IO_Vars<interrupt>::m_type == ListenerInput){
				pinMode(pin,INPUT);
			}
			if(IO_Vars<interrupt>::m_type == ListenerInputEvent){
				pinMode(pin,INPUT);
			}
			if(IO_Vars<interrupt>::m_type == ListenerDebounceInput){
				pinMode(pin,INPUT);
			}
			if(IO_Vars<interrupt>::m_type == ListenerDebounceInterrupt){
				pinMode(pin,INPUT);
			}
			if(IO_Vars<interrupt>::m_type == ListenerInterrupt){
				pinMode(pin,INPUT);
				attachInterrupt(digitalPinToInterrupt(pin), Interrupt<interrupt>, CHANGE);
			}
			if(IO_Vars<interrupt>::m_type == ListenerThreadInterrupt){
				pinMode(pin,INPUT);
				attachInterrupt(digitalPinToInterrupt(pin), ThreadInterrupt<interrupt>, CHANGE);
			}
			if(IO_Vars<interrupt>::m_type == ListenerOutput){
				pinMode(pin,OUTPUT);
			}
			if(IO_Vars<interrupt>::m_type == ListenerOutputInterrupt){
				pinMode(pin,OUTPUT);
			}
			if(IO_Vars<interrupt>::m_type == ListenerOutputEvent){
				pinMode(pin,OUTPUT);
			}
			IO_Pin<interrupt>::m_pin = pin;
		}
		
		template<int interrupt>
		void setTimeLimit(float t){
			IO_Vars<interrupt>::m_timelimit = t;
		}
		
		template<int interrupt>
		int TimeLimit(){
			return IO_Vars<interrupt>::m_timelimit;
		}
		
		template<int interrupt>
		long Millis(){
			return IO_Millis<interrupt>::m_millis;
		}
		
		template<int interrupt>
		void setConsume(bool a_consume){
			IO_Consume<interrupt>::m_consume = a_consume;
		}
		
		template<int interrupt>
		bool getState(){
			if(IO_Vars<interrupt>::m_inverted){
				return !IO_Vars<interrupt>::m_state;
			}
			return IO_Vars<interrupt>::m_state;
		}
		
		template<int interrupt>
		Note getRawStateNote(){
			if(IO_Vars<interrupt>::m_state){
				return Note("true");
			}else{
				return Note("false");
			}
			return "false";
		}
		
		template<int interrupt>
		Note getStateNote(){
			if(IO_Vars<interrupt>::m_inverted){
				if(IO_Vars<interrupt>::m_state){
					return Note("false");
				}else{
					return Note("true");
				}
			}
			if(IO_Vars<interrupt>::m_state){
				return Note("true");
			}else{
				return Note("false");
			}
			return "false";
		}
		
		template<int interrupt>
		bool PinState(){
			return IO_Vars<interrupt>::m_state;
		}
		
		template<int interrupt>
		void setState(bool state){
			if(IO_Vars<interrupt>::m_inverted){
				setPinState<interrupt>(!state);
			}
			setPinState<interrupt>(state);
		}
		
		template<int interrupt>
		void setPinState(bool state){
			ListenerLog(ame_Log_Statement, "setPinState",  "println", Note("interrupt ") + Note(interrupt));
			ListenerLog(ame_Log_Statement, "setPinState",  "println", Note("state ") + Note(state));
			ListenerLog(ame_Log_Statement, "setPinState",  "println", Note("IO_Vars<interrupt>::m_type ") + Note(IO_Vars<interrupt>::m_type));
			IO_Vars<interrupt>::m_state = state;
			if(IO_Vars<interrupt>::m_type == ListenerOutput){
				digitalWrite(IO_Pin<interrupt>::m_pin, state);
			}
			if(IO_Vars<interrupt>::m_type == ListenerOutputInterrupt){
				int pin = IO_Pin<interrupt>::m_pin;
				if(pin == -1){
					return;
				}
				if(IO_Output_State<interrupt>::m_state == nullptr){
					return;
				}
				*IO_Output_State<interrupt>::m_state = state;
				digitalWrite(pin, state);
			}
			if(IO_Vars<interrupt>::m_type == ListenerOutputEvent){
				digitalWrite(IO_Pin<interrupt>::m_pin, state);
				// OutputInterrupt<interrupt>(0.5f);
			}
		}
		
		template<int interrupt>
		bool PinSafe(){
			return IO_Vars<interrupt>::m_safe;
		}
		
		//////////////////Adding single static events////////////////////////
		
		template<int interrupt>
		void addSingleEvent(EventMethod e){
			IO_Single_Event<interrupt>::m_event = e;
		}
		
		template<int interrupt>
		void addSingleMultiEvent(EventMethod e){
			IO_Single_Multi_Event<interrupt>::m_event = e;
		}
		
		template<int interrupt>
		bool containSingleEvent(EventMethod e){
			return IO_Single_Event<interrupt>::m_event == e;
		}
		
		template<int interrupt>
		void removeSingleEvent(EventMethod e){
			if(IO_Single_Event<interrupt>::m_event != e){
				return;
			}
			IO_Single_Event<interrupt>::m_event == nullptr;
		}
		
		//////////////////Adding single class events////////////////////////
		
		template<int interrupt>
		void addSingleEvent(ListenerEvent* e){
			IO_Single_ClassEvent<interrupt>::m_event = e;
		}
		
		template<int interrupt>
		void addSingleMultiEvent(ListenerEvent* e){
			IO_Single_ClassEvent<interrupt>::m_event = e;
		}
		
		template<int interrupt>
		bool containSingleEvent(ListenerEvent* e){
			return IO_Single_ClassEvent<interrupt>::m_event == e;
		}
		
		template<int interrupt>
		void removeSingleEvent(ListenerEvent* e){
			if(IO_Single_ClassEvent<interrupt>::m_event != e){
				return;
			}
			IO_Single_ClassEvent<interrupt>::m_event == nullptr;
		}
		
		template<int interrupt>
		void deleteSingleEvent(ListenerEvent* e){
			if(IO_Single_ClassEvent<interrupt>::m_event != e){
				return;
			}
			IO_Single_ClassEvent<interrupt>::m_event == nullptr;
		}
		
		//////////////////Adding static named events////////////////////////
		
		// template<int interrupt>
		// void addEventMap(Note name, EventMethod e, bool owner){
			// if(IO_Named_Event<interrupt>::m_events == nullptr){
				// IO_Named_Event<interrupt>::m_events = new PrimitiveMap<Note,EventMethod>(owner);
			// }
			// IO_Named_Event<interrupt>::m_events->addLValue(name, e);
		// }
		
		// template<int interrupt>
		// void addEventMap(Note name, EventMethod e){
			// if(IO_Named_Event<interrupt>::m_events == nullptr){
				// IO_Named_Event<interrupt>::m_events = new PrimitiveMap<Note,EventMethod>(owner);
			// }
			// IO_Named_Event<interrupt>::m_events->addLValue(name, e);
		// }
		
		// template<int interrupt>
		// void addMultiEvent(EventMethod e){
			// if(IO_Multi_Event<interrupt>::m_events == nullptr){
				// IO_Multi_Event<interrupt>::m_events = new PrimitiveList<EventMethod>();
			// }
			// IO_Multi_Event<interrupt>::m_events->addLValue(e);
		// }
		
		// template<int interrupt>
		// bool containEvent(EventMethod e){
			// if(IO_Event<interrupt>::m_events == nullptr){
				// return false;
			// }
			// return IO_Event<interrupt>::m_events->containByLValue(e);
		// }
		
		// template<int interrupt>
		// void removeEvent(EventMethod e){
			// if(IO_Event<interrupt>::m_events == nullptr){
				// return;
			// }
			// IO_Event<interrupt>::m_events->removeByLValue(e);
		// }
		
		// template<int interrupt>
		// void deleteEvent(EventMethod e){
			// if(IO_Event<interrupt>::m_events == nullptr){
				// return;
			// }
			// IO_Event<interrupt>::m_events->removeDeleteByLValue(e);
		// }
		
		//////////////////Adding Map static events////////////////////////
		
		template<int interrupt>
		void addEvent(Note a_name, EventMethod e, bool owner){
			if(IO_Map_Event<interrupt>::m_events == nullptr){
				IO_Map_Event<interrupt>::m_events = new PrimitiveMap<Note,EventMethod>(owner);
			}
			IO_Map_Event<interrupt>::m_events->addLValues(a_name, e);
		}
		
		template<int interrupt>
		void addEvent(Note a_name, EventMethod e){
			if(IO_Map_Event<interrupt>::m_events == nullptr){
				IO_Map_Event<interrupt>::m_events = new PrimitiveMap<Note,EventMethod>();
			}
			IO_Map_Event<interrupt>::m_events->addLValues(a_name, e);
		}
		
		template<int interrupt>
		bool containMethodEvent(Note a_name){
			if(IO_Map_Event<interrupt>::m_events == nullptr){
				return false;
			}
			return IO_Map_Event<interrupt>::m_events->containByLValue(a_name);
		}
		
		template<int interrupt>
		void removeMethodEvent(Note a_name){
			if(IO_Map_Event<interrupt>::m_events == nullptr){
				return;
			}
			IO_Map_Event<interrupt>::m_events->removeByLValue(a_name);
		}
		
		template<int interrupt>
		void deleteMethodEvent(Note a_name){
			if(IO_Map_Event<interrupt>::m_events == nullptr){
				return;
			}
			IO_Map_Event<interrupt>::m_events->removeDeleteByLValue(a_name);
		}
		
		template<int interrupt>
		void clearMethodEvent(Note a_name){
			if(IO_Map_Event<interrupt>::m_events == nullptr){
				return;
			}
			IO_Map_Event<interrupt>::m_events->removeDeleteByLValue(a_name);
		}
		
		//////////////////Adding Map class events////////////////////////
		
		template<int interrupt>
		void addEvent(Note a_name, ListenerEvent* e, bool owner){
			if(IO_Map_ClassEvent<interrupt>::m_events == nullptr){
				IO_Map_ClassEvent<interrupt>::m_events = new PrimitiveMap<Note,ListenerEvent>(owner);
			}
			IO_Map_ClassEvent<interrupt>::m_events->addPointer(a_name,e);
		}
		
		template<int interrupt>
		void addEvent(Note a_name, ListenerEvent* e){
			if(IO_Map_ClassEvent<interrupt>::m_events == nullptr){
				IO_Map_ClassEvent<interrupt>::m_events = new PrimitiveMap<Note,ListenerEvent>();
			}
			IO_Map_ClassEvent<interrupt>::m_events->addPointer(a_name,e);
		}
		
		template<int interrupt>
		bool containClassEvent(Note a_name){
			if(IO_Map_ClassEvent<interrupt>::m_events == nullptr){
				return false;
			}
			return IO_Map_ClassEvent<interrupt>::m_events->containByLValue(a_name);
		}
		
		template<int interrupt>
		ListenerEvent* removeClassEvent(Note a_name){
			if(IO_Map_ClassEvent<interrupt>::m_events == nullptr){
				return nullptr;
			}
			return IO_Map_ClassEvent<interrupt>::m_events->removeByLValue(a_name);
		}
		
		template<int interrupt>
		void deleteClassEvent(Note a_name){
			if(IO_Map_ClassEvent<interrupt>::m_events == nullptr){
				return;
			}
			IO_Map_ClassEvent<interrupt>::m_events->removeDeleteByLValue(a_name);
		}
		
		template<int interrupt>
		void clearClassEvent(Note a_name){
			if(IO_Map_ClassEvent<interrupt>::m_events == nullptr){
				return;
			}
			IO_Map_ClassEvent<interrupt>::m_events->removeDeleteByLValue(a_name);
		}
		
		//////////////////class and method - contain,remove and delete ////////////////////////
		
		template<int interrupt>
		bool containEvent(Note a_name){
			if(IO_Map_Event<interrupt>::m_events != nullptr){
				return IO_Map_Event<interrupt>::m_events->containByLValue(a_name);
			}
			if(IO_Map_ClassEvent<interrupt>::m_events != nullptr){
				return IO_Map_ClassEvent<interrupt>::m_events->containByLValue(a_name);
			}
			return false;
		}
		
		template<int interrupt>
		ListenerEvent* removeEvent(Note a_name){
			if(IO_Map_Event<interrupt>::m_events != nullptr){
				return IO_Map_Event<interrupt>::m_events->removeByLValue(a_name);
			}
			if(IO_Map_ClassEvent<interrupt>::m_events != nullptr){
				return IO_Map_ClassEvent<interrupt>::m_events->removeByLValue(a_name);
			}
			return nullptr;
		}
		
		template<int interrupt>
		void deleteEvent(Note a_name){
			if(IO_Map_Event<interrupt>::m_events != nullptr){
				IO_Map_Event<interrupt>::m_events->removeDeleteByLValue(a_name);
			}
			if(IO_Map_ClassEvent<interrupt>::m_events != nullptr){
				IO_Map_ClassEvent<interrupt>::m_events->removeDeleteByLValue(a_name);
			}
		}
		
		template<int interrupt>
		void clearMapEvents(){
			if(IO_Map_Event<interrupt>::m_events != nullptr){
				IO_Map_Event<interrupt>::m_events->resetDelete();
			}
			if(IO_Map_ClassEvent<interrupt>::m_events != nullptr){
				IO_Map_ClassEvent<interrupt>::m_events->resetDelete();
			}
		}
		
		//////////////////linking map events////////////////////////
		
		template<int interrupt_1, int interrupt_2>
		void linkEvent(Note a_name){
			if(IO_Map_Event<interrupt_2>::m_events != nullptr){
				EventMethod* event = IO_Map_Event<interrupt_2>::m_events->getValueByLValue(a_name);
				if(event != nullptr){
					if(!IO_Event<interrupt_1>::m_events->containByPointer(event)){
						IO_Event<interrupt_1>::m_events->addPointer(event);
					}
				}
			}
			if(IO_Map_ClassEvent<interrupt_2>::m_events != nullptr && IO_ClassEvent<interrupt_2>::m_events != nullptr){
				ListenerEvent* event = IO_Map_ClassEvent<interrupt_2>::m_events->getValueByLValue(a_name);
				if(event != nullptr){
					if(!IO_ClassEvent<interrupt_1>::m_events->containByPointer(event)){
						IO_ClassEvent<interrupt_1>::m_events->addPointer(event);
					}
				}
			}
		}
		
		template<int interrupt_1, int interrupt_2>
		void removeLinkEvent(Note a_name){
			if(IO_Map_Event<interrupt_2>::m_events != nullptr){
				EventMethod* event = IO_Map_Event<interrupt_2>::m_events->getByLValue(a_name);
				if(event != nullptr){
					if(!IO_Event<interrupt_1>::m_events->containByPointer(event)){
						IO_Event<interrupt_1>::m_events->removeByPointer(event);
					}
				}
			}
			if(IO_Map_ClassEvent<interrupt_2>::m_events != nullptr && IO_ClassEvent<interrupt_2>::m_events != nullptr){
				ListenerEvent* event = IO_Map_ClassEvent<interrupt_2>::m_events->getByLValue(a_name);
				if(event != nullptr){
					if(!IO_ClassEvent<interrupt_1>::m_events->containByPointer(event)){
						IO_ClassEvent<interrupt_1>::m_events->removeByPointer(event);
					}
				}
			}
		}
		
		template<int interrupt_1, int interrupt_2>
		void deleteLinkEvent(Note a_name){
			if(IO_Map_Event<interrupt_2>::m_events != nullptr){
				EventMethod* event = IO_Map_Event<interrupt_2>::m_events->getByLValue(a_name);
				if(event != nullptr){
					if(!IO_Event<interrupt_1>::m_events->containByPointer(event)){
						IO_Event<interrupt_1>::m_events->removeDeleteByPointer(event);
					}
				}
			}
			if(IO_Map_ClassEvent<interrupt_2>::m_events != nullptr && IO_ClassEvent<interrupt_2>::m_events != nullptr){
				ListenerEvent* event = IO_Map_ClassEvent<interrupt_2>::m_events->getByLValue(a_name);
				if(event != nullptr){
					if(!IO_ClassEvent<interrupt_1>::m_events->containByPointer(event)){
						IO_ClassEvent<interrupt_1>::m_events->removeDeleteByPointer(event);
					}
				}
			}
		}
		
		template<int interrupt_1, int interrupt_2>
		PrimitiveList<Note> getLinkEvents(){
			ListenerLog(ame_Log_Statement, "getLinkEvents",  "println", Note("interrupt_1 ") + Note(interrupt_1));
			ListenerLog(ame_Log_Statement, "getLinkEvents",  "println", Note("interrupt_2 ") + Note(interrupt_2));
			PrimitiveList<Note> i_names;
			if(IO_Map_Event<interrupt_2>::m_events != nullptr && IO_Event<interrupt_1>::m_events != nullptr){
				ListenerLog(ame_Log_Statement, "getLinkEvents",  "println", Note("EventMethods"));
				PrimitiveList<EventMethod>*  list = IO_Event<interrupt_1>::m_events;
				for(int x = 0; x < list->getPosition(); x++){
					EventMethod* event = list->getByPosition(x);
					PrimitiveMap<Note,EventMethod>* f_map = IO_Map_Event<interrupt_2>::m_events;
					if(f_map->containValueByPointer(event) &&
						f_map->getKeyByPointer(event) != nullptr){
						Note fi_name = *f_map->getKeyByPointer(event);
						i_names.add(fi_name);
						ListenerLog(ame_Log_Statement, "getLinkEvents",  "println", Note("iteration: ") + Note(x));
						ListenerLog(ame_Log_Statement, "getLinkEvents",  "println", Note("LinkedEvents: ") + Note(fi_name));
					}
				}
			}
			if(IO_Map_ClassEvent<interrupt_2>::m_events != nullptr && IO_ClassEvent<interrupt_1>::m_events != nullptr){
				ListenerLog(ame_Log_Statement, "getLinkEvents",  "println", Note("ListenerEvents"));
				PrimitiveList<ListenerEvent>*  list = IO_ClassEvent<interrupt_1>::m_events;
				for(int x = 0; x < list->getPosition(); x++){
					ListenerEvent* event = list->getByPosition(x);
					PrimitiveMap<Note,ListenerEvent>* f_map = IO_Map_ClassEvent<interrupt_2>::m_events;
					if(!f_map->containValueByPointer(event) &&
						f_map->getKeyByPointer(event) != nullptr){
						Note fi_name = *f_map->getKeyByPointer(event);
						i_names.add(fi_name);
						ListenerLog(ame_Log_Statement, "getLinkEvents",  "println", Note("iteration: ") + Note(x));
						ListenerLog(ame_Log_Statement, "getLinkEvents",  "println", Note("LinkedEvents: ") + Note(fi_name));
					}
				}
			}
			return i_names;
		}
		
		//////////////////Adding static events////////////////////////
		
		template<int interrupt>
		void addEvent(EventMethod e, bool owner){
			if(IO_Event<interrupt>::m_events == nullptr){
				IO_Event<interrupt>::m_events = new PrimitiveList<EventMethod>(5, owner, true);
			}
			IO_Event<interrupt>::m_events->addLValue(e);
		}
		
		template<int interrupt>
		void addEvent(EventMethod e){
			if(IO_Event<interrupt>::m_events == nullptr){
				IO_Event<interrupt>::m_events = new PrimitiveList<EventMethod>();
			}
			IO_Event<interrupt>::m_events->addLValue(e);
		}
		
		template<int interrupt>
		void addMultiEvent(EventMethod e){
			if(IO_Multi_Event<interrupt>::m_events == nullptr){
				IO_Multi_Event<interrupt>::m_events = new PrimitiveList<EventMethod>();
			}
			IO_Multi_Event<interrupt>::m_events->addLValue(e);
		}
		
		template<int interrupt>
		bool containEvent(EventMethod e){
			if(IO_Event<interrupt>::m_events == nullptr){
				return false;
			}
			return IO_Event<interrupt>::m_events->containByLValue(e);
		}
		
		template<int interrupt>
		void removeEvent(EventMethod e){
			if(IO_Event<interrupt>::m_events == nullptr){
				return;
			}
			IO_Event<interrupt>::m_events->removeByLValue(e);
		}
		
		template<int interrupt>
		void deleteEvent(EventMethod e){
			if(IO_Event<interrupt>::m_events == nullptr){
				return;
			}
			IO_Event<interrupt>::m_events->removeDeleteByLValue(e);
		}
		
		template<int interrupt>
		void clearEvents(){
			if(IO_Event<interrupt>::m_events != nullptr){
				IO_Event<interrupt>::m_events->reset();
			}
			if(IO_ClassEvent<interrupt>::m_events != nullptr){
				IO_ClassEvent<interrupt>::m_events->resetDelete();
			}
		}
		
		//////////////////Adding class events////////////////////////
		
		template<int interrupt>
		void addEvent(ListenerEvent* e, bool owner){
			if(IO_ClassEvent<interrupt>::m_events == nullptr){
				IO_ClassEvent<interrupt>::m_events = new PrimitiveList<ListenerEvent>(5, owner, true);
			}
			IO_ClassEvent<interrupt>::m_events->addPointer(e);
		}
		
		template<int interrupt>
		void addEvent(ListenerEvent* e){
			if(IO_ClassEvent<interrupt>::m_events == nullptr){
				IO_ClassEvent<interrupt>::m_events = new PrimitiveList<ListenerEvent>();
			}
			IO_ClassEvent<interrupt>::m_events->addPointer(e);
		}
		
		template<int interrupt>
		bool containEvent(ListenerEvent* e){
			if(IO_ClassEvent<interrupt>::m_events == nullptr){
				return false;
			}
			return IO_ClassEvent<interrupt>::m_events->containByPointer(e);
		}
		
		template<int interrupt>
		ListenerEvent* removeEvent(ListenerEvent* e){
			if(IO_ClassEvent<interrupt>::m_events == nullptr){
				return nullptr;
			}
			return IO_ClassEvent<interrupt>::m_events->removeByPointer(e);
		}
		
		template<int interrupt>
		void deleteEvent(ListenerEvent* e){
			if(IO_ClassEvent<interrupt>::m_events == nullptr){
				return;
			}
			IO_ClassEvent<interrupt>::m_events->removeDeleteByPointer(e);
		}
		
		template<int interrupt>
		void runEvents(bool state_e){
			Interrupt<interrupt>(state_e);
		}
		
		template<int interrupt>
		void simulateEvents(bool state_e){
			ListenerLog(ame_Log_StartMethod, "simulateEvents",  "println", "");
			List<ListenerEvent>* events = IO_ClassEvent<interrupt>::m_events;
			List<EventMethod>* static_events = IO_Event<interrupt>::m_events;
			if(events == nullptr || static_events == nullptr){
				ListenerLog(ame_Log_Statement, "simulateEvents",  "println", "pin == -1 || events == nullptr || static_events == nullptr");
				return;
			}
			ListenerLog(ame_Log_Statement, "simulateEvents",  "println", "start events");
			for(int x = 0; x < static_events->getPosition(); x++){
				EventMethod event =  *static_events->getByPosition(x);
				if(IO_Vars<interrupt>::m_inverted){
					event(interrupt, millis(), !state_e);
				}else{
					event(interrupt, millis(), state_e);
				}
			}
			for(int x = 0; x < events->getPosition(); x++){
				ListenerEvent* e =  events->getByPosition(x);
				if(!e->isEnable()){
					continue;
				}
				if(IO_Vars<interrupt>::m_inverted){
					e->event(interrupt, millis(), !state_e);
				}else{
					e->event(interrupt, millis(), state_e);
				}
			}
			ListenerLog(ame_Log_Statement, "simulateEvents",  "println", "end events");
			ListenerLog(ame_Log_EndMethod, "simulateEvents",  "println", "");
		}
		
		
		//////////////////Adding static events////////////////////////
		
		template<int interrupt>
		void addEvent(AnalogInputMethod e, bool owner){
			if(IO_AnalogEvent<interrupt>::m_events == nullptr){
				IO_AnalogEvent<interrupt>::m_events = new PrimitiveList<AnalogInputMethod>(5, owner, true);
			}
			IO_AnalogEvent<interrupt>::m_events->addLValue(e);
		}
		
		template<int interrupt>
		void addEvent(AnalogInputMethod e){
			if(IO_AnalogEvent<interrupt>::m_events == nullptr){
				IO_AnalogEvent<interrupt>::m_events = new PrimitiveList<AnalogInputMethod>();
			}
			IO_AnalogEvent<interrupt>::m_events->addLValue(e);
		}
		
		template<int interrupt>
		bool containEvent(AnalogInputMethod e){
			if(IO_AnalogEvent<interrupt>::m_events == nullptr){
				return false;
			}
			return IO_AnalogEvent<interrupt>::m_events->containByLValue(e);
		}
		
		template<int interrupt>
		void removeEvent(AnalogInputMethod e){
			if(IO_AnalogEvent<interrupt>::m_events == nullptr){
				return;
			}
			IO_AnalogEvent<interrupt>::m_events->removeByLValue(e);
		}
		
		template<int interrupt>
		void deleteEvent(AnalogInputMethod e){
			if(IO_AnalogEvent<interrupt>::m_events == nullptr){
				return;
			}
			IO_AnalogEvent<interrupt>::m_events->removeDeleteByLValue(e);
		}
		
		//////////////////Adding class events////////////////////////
		
		template<int interrupt>
		void addEvent(ListenerAnalogEvent* e, bool owner){
			if(IO_AnalogClassEvent<interrupt>::m_events == nullptr){
				IO_AnalogClassEvent<interrupt>::m_events = new PrimitiveList<ListenerAnalogEvent>(5, owner, true);
			}
			IO_AnalogClassEvent<interrupt>::m_events->addPointer(e);
		}
		
		template<int interrupt>
		void addEvent(ListenerAnalogEvent* e){
			if(IO_AnalogClassEvent<interrupt>::m_events == nullptr){
				IO_AnalogClassEvent<interrupt>::m_events = new PrimitiveList<ListenerAnalogEvent>();
			}
			IO_AnalogClassEvent<interrupt>::m_events->addPointer(e);
		}
		
		template<int interrupt>
		bool containEvent(ListenerAnalogEvent* e){
			if(IO_AnalogClassEvent<interrupt>::m_events == nullptr){
				return false;
			}
			return IO_AnalogClassEvent<interrupt>::m_events->containByPointer(e);
		}
		
		template<int interrupt>
		ListenerAnalogEvent* removeEvent(ListenerAnalogEvent* e){
			if(IO_AnalogClassEvent<interrupt>::m_events == nullptr){
				return nullptr;
			}
			return IO_AnalogClassEvent<interrupt>::m_events->removeByPointer(e);
		}
		
		template<int interrupt>
		void deleteEvent(ListenerAnalogEvent* e){
			if(IO_AnalogClassEvent<interrupt>::m_events == nullptr){
				return;
			}
			IO_AnalogClassEvent<interrupt>::m_events->removeDeleteByPointer(e);
		}
		
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		
		template<int interrupt>
		void enableEvents(){
			IO_Enable<interrupt>::m_enable = true;
		}
		
		template<int interrupt>
		void disableEvents(){
			IO_Enable<interrupt>::m_enable = false;
		}
#endif
		
	protected:
	Application* app = nullptr;
};

}

#endif