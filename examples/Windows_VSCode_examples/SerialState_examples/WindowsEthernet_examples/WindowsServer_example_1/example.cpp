
#define ame_Windows

#include "aMonkeyEngine/System.hpp"
#include "aMonkeyEngine/Application.hpp"
#include "aMonkeyEngine/DefaultApplication.hpp"
#include "aMonkeyEngine/SerialState.hpp"
//#include "aMonkeyEngine/WindowsEthernetSerialPort.hpp"
//#include "aMonkeyEngine/WindowsEthernetSerialServer.hpp"

using namespace ame;

Application* app;
SerialState* serialState;

int main(){

    app = new DefaultApplication();

    serialState = app->getStateManager()->addState(new SerialState());
    serialState->addSerialPort();

    while(true){
        app->update();
        //System::console.println("update");
    }
    return 0;
}