
#ifndef InputState_hpp
#define InputState_hpp
#define InputState_AVAILABLE

#ifdef ame_ArduinoIDE
	#include "Arduino.h"
#endif

#include "cppObject.hpp"
#include "BaseAppState.hpp"
#include "PrimitiveList.hpp"
#include "PrimitiveMap.hpp"
#include "Class.hpp"

#ifdef InputState_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"
	
	#define InputStateLog(location,method,type,mns) ame_Log(this,location,"InputState",method,type,mns)
	#define InputStateMethodLog(location,method,type,mns) ame_Log(nullptr,location,"InputState Free Function",method,type,mns)
	#define const_InputStateLog(location,method,type,mns) 
	#define StaticInputStateLog(pointer,location,method,type,mns) ame_Log(pointer,location,"InputState",method,type,mns)
#else
	#ifdef InputState_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"
		
		#define InputStateLog(location,method,type,mns) ame_LogDebug(this,location,"InputState",method,type)
		#define InputStateMethodLog(location,method,type,mns) ame_LogDebug(nullptr,location,"InputState Free Function",method,type,mns)
		#define const_InputStateLog(location,method,type,mns) 
		#define StaticInputStateLog(pointer,location,method,type,mns) ame_LogDebug(pointer,location,"InputState",method,type)
	#else
		#define InputStateLog(location,method,type,mns) 
		#define InputStateMethodLog(location,method,type,mns) 
		#define const_InputStateLog(location,method,type,mns) 
		#define StaticInputStateLog(pointer,location,method,type,mns) 
	#endif
#endif

namespace ame{

	using InputEventMethod = void (*)(int,long,bool);//Input,millis,state

	class Input IMPLEMENTATION_cppObject {
		public:
		int pin = 0;
		bool inverted = false;
		bool state = false;

		public:

		Input(){}
		Input(int c_pin, bool c_inveted, bool c_state){
			pin = c_pin;
			inverted = c_inveted;
			state = c_state;
		}
		Input(const Input& c_input){
			pin = c_input.pin;
			inverted = c_input.inverted;
			state = c_input.state;
		}

		virtual void operator=(const Input& o_i_events){
			pin = o_i_events.pin;
			inverted = o_i_events.inverted;
			state = o_i_events.state;
		}

		virtual bool operator==(const Input& o_i_events){
			return inverted == o_i_events.inverted || pin == o_i_events.pin || state == o_i_events.state;
		}

		virtual bool operator!=(const Input& o_i_events){
			return inverted != o_i_events.inverted || pin != o_i_events.pin || state != o_i_events.state;
		}

		virtual bool getState(){
			return inverted ? !state : state;
		}

		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){return Class<Input>::getClass();}
		virtual bool instanceof(cppObjectClass* cls){return cls == Class<Input>::getClass();}
		#endif
	};

	template<class t_Input = Input>
	using InputActionMethod = bool (*)(int a_interrupt, long a_milli, t_Input& a_input);

	template<class t_Input = Input>
	class InputEvent IMPLEMENTATION_cppObject {
		public:
		t_Input input;
		InputActionMethod<t_Input> action;
		PrimitiveList<InputEventMethod> events;

		public:
		InputEvent(){}

		InputEvent(const InputEvent& c_input_event){
			input = c_input_event.input;
			action = c_input_event.action;
			events = c_input_event.events;
		}
		virtual ~InputEvent(){}

		virtual void operator=(const InputEvent& o_i_events){
			input = o_i_events.input;
			action = o_i_events.action;
			events = o_i_events.events;
		}
		virtual bool operator==(const InputEvent& o_i_events){
			return input == o_i_events.input && action == o_i_events.action;
		}

		virtual bool operator!=(const InputEvent& o_i_events){
			return input != o_i_events.input || action != o_i_events.action;
		}

		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){return Class<InputEvent>::getClass();}
		virtual bool instanceof(cppObjectClass* cls){return cls == Class<InputEvent>::getClass();}
		#endif

		virtual void runEvents(int a_interrupt, long a_millis){
			if(action(a_interrupt, a_millis, input)){
				for(int x = 0; x < events.getPosition(); x++){
					InputEventMethod* ff_event_method = events.getByPosition(x);
					(**ff_event_method)(a_interrupt, a_millis, input.getState());
				}
			}
		}
	};
	/*
	template<int Input_Interrupt, class t_Input>
	struct Input_List{
		static PrimitiveList<InputEvent<t_Input>> m_Inputs;
	};

	template<int Input_Interrupt, class t_Input> PrimitiveList<InputEvent<t_Input>>  Input_List<Input_Interrupt,t_Input>::m_Inputs;
	
	template<int Input_Interrupt, class t_Input = Input>
	void IRAM_ATTR updateInputEvent(){
		InputStateMethodLog(ame_Log_StartMethod, "updateInputEvent", "println", "");
		long i_millis = millis();
		PrimitiveList<InputEvent<t_Input>>& i_Inputs = Input_List<Input_Interrupt,t_Input>::m_Inputs;
		for(int x = 0; x < i_Inputs.getPosition(); x++){
			InputEvent<t_Input>* f_i_event = i_Inputs.getByPosition(x);
			if(f_i_event == nullptr){
				continue;
			}
			t_Input& f_input = f_i_event->input;
			InputActionMethod<t_Input>& f_action = f_i_event->action;
			PrimitiveList<InputEventMethod>& f_events = f_i_event->events;
			
			if((*f_action)(Input_Interrupt, i_millis, f_input)){
				for(int y = 0; y < f_events.getPosition(); y++){
					InputEventMethod* ff_event_method = f_events.getByPosition(y);
					(**ff_event_method)(Input_Interrupt, i_millis, f_input->state);
				}
			}
		}
		InputStateMethodLog(ame_Log_EndMethod, "updateInputEvent", "println", "");
	}
	
	template<int Input_Interrupt, class t_Input = Input>
	InputEvent<t_Input>& createInputEvent(){
		PrimitiveList<InputEvent<t_Input>>& i_Inputs = Input_List<Input_Interrupt,t_Input>::m_Inputs;
		return *i_Inputs.addPointer(new InputEvent<t_Input>());
	}
	
	template<int Input_Interrupt, class t_Input = Input>
	InputEvent<t_Input>* createInputEvent(t_Input a_input, InputActionMethod<t_Input> a_action){
		PrimitiveList<InputEvent<t_Input>>& i_Inputs = Input_List<Input_Interrupt,t_Input>::m_Inputs;
		InputEvent<t_Input>* i_event = new InputEvent<t_Input>();
		i_event->input = a_input;
		i_event->action = a_action;
		return i_Inputs.addPointer(i_event);
	}
	
	template<int Input_Interrupt, class t_Input = Input>
	void attachInputEventInterrupt(int a_pin){
		pinMode(a_pin,INPUT_PULLUP);
		attachInterrupt(a_pin, updateInputEvent<Input_Interrupt,t_Input>, CHANGE);
	}
	
	template<int Input_Interrupt>
	void attachInputEvent(int a_pin){
		pinMode(a_pin,INPUT);
	}*/
/*
class InputState IMPLEMENTATION_BaseAppState {
    public:
		InputState(){}
		virtual ~InputState(){}
			
		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){
			return Class<InputState>::classType;
		}
		
		virtual bool instanceof(cppObjectClass* cls){
			return cls == Class<InputState>::getClass()
			#if defined(BaseAppState_AVAILABLE)
			|| BaseAppState::instanceof(cls)
			#endif
			;
		}
		#endif
		
		virtual void createInput(int a_Input){
			m_update_Inputs.putPointer(a_Input, new InputEvent());
		}
		
		virtual void addEvent(int a_Input, InputEventMethod a_events){
			InputEvent* i_events = m_update_Inputs.getValueByLValue(a_Input);
			if(i_events == nullptr){
				return;
			}
			
			i_events->events.add(a_events);
		}
		
		virtual void addAction(int a_Input, InputAction* a_runner){
			InputEvent* i_events = m_update_Inputs.getValueByLValue(a_Input);
			if(i_events == nullptr){
				return;
			}

			i_events->action = a_runner;
		}
		
		virtual void updateState(float tpc){
			long i_millis = millis();
			for(auto f_entry : m_update_Inputs){
				int f_Input = f_entry.getKey();
				InputEvent* f_i_event = f_entry.getValuePointer();
				if(f_i_event == nullptr){
					return;
				}
				PrimitiveList<InputEventMethod>& f_events = f_i_event->events;
				InputAction* f_action = f_i_event->action;
				if(f_action == nullptr){
					return;
				}

				runInput(f_Input, f_action, f_events, i_millis, tpc);
			}
		}
		
	protected:
		PrimitiveMap<int,InputEvent> m_update_Inputs;
};
*/
}

#endif