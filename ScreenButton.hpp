
#ifndef ScreenButton_hpp
#define ScreenButton_hpp

#include "Button.hpp"
#include "Vector2f.hpp"

namespace ame{

class ScreenButton : public Button{
    private:
	
    public:
		virtual Vector2f getCursor()=0;
		virtual int getPressure()=0;
};

}

#endif 