
#ifndef CONFIGURATION_ame_Enviroment_define_hpp
#define CONFIGURATION_ame_Enviroment_define_hpp

	#if defined(DISABLE_ame_Enviroment_define)
		#define ame_Enviroment_define_hpp
	#endif
#endif

#ifndef ame_Enviroment_define_hpp
#define ame_Enviroment_define_hpp

///////////////////////////////////////////

#include "ame_Windows_Enviroment_define.hpp"
#include "ame_ArduinoIDE_Enviroment_define.hpp"

///////////////////////////////////////////

#ifndef ame_Hardware_Defined

	#if defined(__APPLE__)
		#ifndef ame_Level_Defined
			#define ame_Level_15
			#define ame_Level_Defined
		#endif
		#ifndef ame_Enviroment_Defined
			#define ame_Apple
			#define ame_Enviroment_Defined
		#endif
	#endif

	#if defined(__linux__)
		#ifndef ame_Level_Defined
			#define ame_Level_15
			#define ame_Level_Defined
		#endif
		#ifndef ame_Enviroment_Defined
			#define ame_Linux
			#define ame_Enviroment_Defined
		#endif
	#endif
	
#endif

///////////////////////////////////////////

#endif