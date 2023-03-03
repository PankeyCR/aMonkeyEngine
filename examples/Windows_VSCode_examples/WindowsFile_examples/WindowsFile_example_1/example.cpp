
#define ame_Windows

#include "aMonkeyEngine/System.hpp"
#include "aMonkeyEngine/WindowsFile.hpp"

using namespace ame;

int main(){
    WindowsFile file;
    file.createDir("Engine");
    if(file.exist("Engine")){
        System::console.println("Folder found");
    }else{
        System::console.println("No folder found");
    }
    
    if(file.deleteDir("Engine")){
        System::console.println("Folder deleted");
    }else{
        System::console.println("No Folder deleted");
    }

    if(file.exist("Engine")){
        System::console.println("Folder found");
    }else{
        System::console.println("No Folder found");
    }
    return 0;
}