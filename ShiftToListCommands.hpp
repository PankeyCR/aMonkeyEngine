
#ifndef ShiftToListCommands_hpp
#define ShiftToListCommands_hpp
#define ShiftToListCommands_AVAILABLE

#include "Command.hpp"
#include "PrimitiveList.hpp"
#include "Note.hpp"
#include "NoteHelper.hpp"
#include "SerialListenerState.hpp"

namespace ame{

class ShiftToListCommands : public Command<Note>{
    public:
		ShiftToListCommands(){}
		ShiftToListCommands(SerialListenerState<PrimitiveList<Note>>* c_listener){
			m_listener = c_listener;
		}
		virtual ~ShiftToListCommands(){}

		virtual void execute(const Note& a_message){
			if(m_listener == nullptr){
				return;
			}

			PrimitiveList<Note> commands = splitNote(a_message, ' ');

			m_listener->addInput(commands);
		}
		
		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(AbstractClass_AVAILABLE)
		virtual cppObjectClass* getClass(){return AbstractClass<ShiftToListCommands<C>>::getClass();}
		virtual bool instanceof(cppObjectClass* cls){return cls == AbstractClass<ShiftToListCommands<C>>::getClass();}
		#endif

	protected:
		SerialListenerState<PrimitiveList<Note>>* m_listener = nullptr;
};

}

#endif