
#ifndef System_hpp
#define System_hpp
#define System_AVAILABLE

#ifndef ame_Enviroment_Defined

#endif

#ifdef ame_Windows
	#include <stdio.h>
	#include "ame_Print.hpp"
	#include "ame_Printable.hpp"
	#include "ConsolePrint.hpp"
#endif

#ifdef ame_ArduinoIDE
	#include "Arduino.h"
	#include "Printable.h"
#endif

#include "ame_String.hpp"

namespace ame{

class System{
    public:
		static Print& console;
		virtual ~System(){}

		static long milliSeconds(){
		#ifdef ame_Windows
			return 0;
		#elif defined(ame_ArduinoIDE)
			return millis();
		#else
			return 0;
		#endif
		}

		static long microSeconds(){
		#ifdef ame_Windows
			return 0;
		#elif defined(ame_ArduinoIDE)
			return micros();
		#else
			return 0;
		#endif
		}

		static void sleep(long a_time){
		#ifdef ame_Windows
			
		#elif defined(ame_ArduinoIDE)
			delay(a_time);
		#else
			
		#endif
		}

		static void startEngine(){
			bool i_halt = true;

			#ifdef ame_Enviroment_Name
			System::console.println(ame_Enviroment_Name);
			i_halt = false;
			#endif

			while(i_halt){
				System::console.println("No Engine detected");
				
				#ifndef ame_Enviroment_Name
				System::console.println("No Enviroment detected");
				#endif

				System::sleep(1000);
			}
		}

	protected:

		System(){}

};
#ifdef ame_Windows

ConsolePrint PConsole;
Print& System::console = PConsole;

#endif

#ifdef ame_ArduinoIDE
Print& System::console = Serial;
#endif


}

#endif
