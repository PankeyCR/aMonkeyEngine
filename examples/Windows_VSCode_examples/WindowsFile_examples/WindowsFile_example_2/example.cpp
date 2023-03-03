
#define ame_Windows

#include "aMonkeyEngine/System.hpp"
#include "aMonkeyEngine/WindowsFile.hpp"

using namespace ame;

int main(){
    WindowsFile file;
    file.createPath("Engine", "System", "Win32");
    if(file.existPath("Engine", "System", "Win32")){
        System::console.println("Path found");
    }else{
        System::console.println("No Path found");
    }
    
    if(file.deletePath("Engine", "System", "Win32")){
        System::console.println("Path deleted");
    }else{
        System::console.println("No Path deleted");
    }

    if(file.existPath("Engine", "System", "Win32")){
        System::console.println("Path found");
    }else{
        System::console.println("No Path found");
    }
    return 0;
}