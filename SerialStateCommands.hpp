
#ifndef SerialStateCommands_hpp
#define SerialStateCommands_hpp
#define SerialStateCommands_AVAILABLE

#include "Note.hpp"
#include "SerialState.hpp"
#include "NoteHelper.hpp"
#include "MemoryRam.hpp"

#ifdef SerialStateCommands_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"
	
	#define SerialStateCommandsLog(location,method,type,mns) ame_Log(nullptr,location,"SerialStateCommands",method,type,mns)
#else
	#ifdef SerialStateCommands_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"
		
		#define SerialStateCommandsLog(location,method,type,mns) ame_LogDebug(nullptr,location,"SerialStateCommands",method,type)
	#else
		#define SerialStateCommandsLog(location,method,type,mns) 
	#endif
#endif

namespace ame{

SerialState* g_serialState = nullptr;

void setSerialState(SerialState* a_state){
	g_serialState = a_state;
}

void SerialStateCommands(const Note& message){
	if(g_serialState == nullptr) {
		System::console.println("message == nullptr || g_serialState == nullptr");
		return;
	}
	System::console.println("SerialStateCommands");
	
	PrimitiveList<Note> commands = splitNote(message, ' ');

	if(commands.getPosition() == 1){
		Note command_0 = commands[0];

		if (command_0 == "getSerialPortSize") {
			g_serialState->instantSend("SerialPort Size");
			g_serialState->instantSend(Note(g_serialState->getSerialPortSize()));
		}
	}

	if(commands.getPosition() == 2){
		Note command_0 = commands[0];
		Note command_1 = commands[1];

		if (command_0 == "broadcastSerialState") {
			g_serialState->instantSend(command_1);
		}
	}
}

}

#endif