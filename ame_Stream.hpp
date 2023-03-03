
#ifndef ame_Stream_hpp
#define ame_Stream_hpp

//#include "ame_Streamable.hpp"
#include "ame_String.hpp"

#ifdef ame_Windows
	#include <string.h>
	#include "ame_Print.hpp"
#endif

#ifdef ame_ArduinoIDE
	#include "Print.h"
#endif

class Stream : public Print{
    public:
        Stream() {}
        virtual ~Stream() {}
		
        virtual int available() = 0;
        virtual int read() = 0;
        virtual int peek() = 0;
};

#endif
