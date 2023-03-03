
#define ame_Windows

#include "aMonkeyEngine/System.hpp"
#include "aMonkeyEngine/WindowsFile.hpp"

using namespace ame;

int main(){
    WindowsFile file;
    file.createFile("example.txt");
    if(file.exist("example.txt")){
        System::console.println("File found");
    }else{
        System::console.println("No file found");
    }
    
    if(file.deleteFile("example.txt")){
        System::console.println("File deleted");
    }else{
        System::console.println("No file deleted");
    }

    if(file.exist("example.txt")){
        System::console.println("File found");
    }else{
        System::console.println("No file found");
    }
    return 0;
}