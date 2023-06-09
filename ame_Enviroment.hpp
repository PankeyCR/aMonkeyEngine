
#ifndef CONFIGURATION_ame_Enviroment_hpp
#define CONFIGURATION_ame_Enviroment_hpp

	#if defined(DISABLE_ame_Enviroment)
		#define ame_Enviroment_hpp
	#endif
#endif

#ifndef ame_Enviroment_hpp
#define ame_Enviroment_hpp

#include "ame_Enviroment_config.hpp"

#include "ame_config.hpp"

#include "ame_Class_Implementation.hpp"

#include "ame_Enviroment_config.hpp"
#include "ame_Enviroment_define.hpp"
//at this point the enviroment is defined

#include "ame_Render_config.hpp"

#include "ame_Level.hpp"

#include "ame_Logger_config.hpp"
#include "ame_Logger.hpp"

#include "ame_Context.hpp"

namespace ame{

void initializeEngine(){
	ameConfig();
	ameLoggerConfig();
}

}

#endif