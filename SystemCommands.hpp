
#ifndef SystemCommands_hpp
#define SystemCommands_hpp
#define SystemCommands_AVAILABLE

#include "Note.hpp"
#include "SerialState.hpp"
#include "NoteHelper.hpp"
#include "MemoryRam.hpp"

#ifdef SystemCommands_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"
	
	#define SystemCommandsLog(location,method,type,mns) ame_Log(nullptr,location,"SystemCommands",method,type,mns)
#else
	#ifdef SystemCommands_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"
		
		#define SystemCommandsLog(location,method,type,mns) ame_LogDebug(nullptr,location,"SystemCommands",method,type)
	#else
		#define SystemCommandsLog(location,method,type,mns) 
	#endif
#endif

namespace ame{

Application* g_app = nullptr;

void setApplication(Application* a_app){
	g_app = a_app;
}

Application* getApplication(){
	return g_app;
}

void SystemCommands(Note* message){
	if (message == nullptr || g_app == nullptr) {
		System::console.println("message == nullptr || g_app == nullptr");
		return;
	}
	System::console.println("SystemCommands");
	
	PrimitiveList<Note> commands = splitNote(*message, ' ');

	if(commands.getPosition() == 1){
		Note command_0 = commands[0];
		
		if (command_0 == "ram") {
			System::console.print("ram: ");
			System::console.println(getRamSize());
		}
	}

	if(commands.getPosition() == 2){
		Note command_0 = commands[0];
		Note command_1 = commands[1];
		
		if (command_0 == "broadcastSystem") {
			System::console.println(command_1);
		}
	}
}

}

#endif