
#define ame_Windows

#include "aMonkeyEngine/System.hpp"
#include "aMonkeyEngine/WindowsFile.hpp"

using namespace ame;

int main(){
    WindowsFile file;
    file.createFile("example.txt");

    Note text = "examples text";

    file.writeText(text, "example.txt");

    Note readText = file.readText("example.txt");

    System::console.println(readText);

    file.clearFile("example.txt");

    Note readText_2 = file.readText("example.txt");

    if(readText_2.isEmpty()){
        System::console.println("example.txt is empty");
    }else{
        System::console.println(readText_2);
    }
    return 0;
}