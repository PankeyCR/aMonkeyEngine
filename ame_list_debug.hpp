
#if defined(DISABLE_ame_list_debug)
	#define ame_list_debug_hpp
#endif

#ifndef ame_list_debug_hpp
#define ame_list_debug_hpp
#define ame_list_debug_AVAILABLE

//////////////////////////////////////////////////////////////

#include "ame_Logger_config.hpp"
#include "MemoryRam.hpp"
#include "ame_String.hpp"
#include "System.hpp"
#include "PrimitiveList.hpp"
#include "Note.hpp"

using namespace ame;

long ram_size = -1;
PrimitiveList<Note> debug_list;

void list_debug(void* pointer, int location, ame_String name, ame_String method, ame_String type){
	// Serial.println("Name");
	// Serial.println(name);
	// Serial.println("Method");
	// Serial.println(method);
	// Serial.println("Type");
	// Serial.println(type);
	if(location == ame_Log_StartLoop){
        // System::console.println("start loop -------------------------------------------");
		long n_ram_size = getRamSize();
		// long n_ram_size = 0;
		if(ram_size == -1){
			ram_size = n_ram_size;
		}
		if(n_ram_size < ram_size){
            System::console.println("WARNING, memory is dropping: ");
            System::console.println(ram_size - n_ram_size);
			ram_size = n_ram_size;
            System::console.println("ram size: ");
            System::console.println(ram_size);
			
		   System::console.print("Loggin class: ");
		   System::console.print(name);
		   System::console.print(" - Method: ");
		   System::console.println(method);

		}
		// ram_size = n_ram_size;
		// System::console.println("ram size: ");
		// System::console.println(ram_size);
	}
	if(location == ame_Log_EndLoop){
        // System::console.println("end loop --------------------------------------------");
	}
	// if(method == "Constructor" && location == ame_Log_StartMethod){
		// System::console.println("new instance");
	// }
	// System::console.println("debugging");
}

//////////////////////////////////////////////////////////////

#endif
