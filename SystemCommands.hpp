
#ifndef SystemCommands_hpp
#define SystemCommands_hpp
#define SystemCommands_AVAILABLE

#include "Note.hpp"
#include "NoteHelper.hpp"
#include "PrimitiveList.hpp"
#include "System.hpp"
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

void SystemCommands(const PrimitiveList<Note>& a_commands){
	if(a_commands.getPosition() == 1){
		Note command_0 = a_commands[0];
		
		if (command_0 == "ram") {
			System::console.print("ram: ");
			System::console.println(getRamSize());
		}
	}

	if(a_commands.getPosition() == 2){
		Note command_0 = a_commands[0];
		Note command_1 = a_commands[1];
		
		if (command_0 == "broadcastSystem") {
			System::console.println(command_1);
		}
	}
}

}

#endif