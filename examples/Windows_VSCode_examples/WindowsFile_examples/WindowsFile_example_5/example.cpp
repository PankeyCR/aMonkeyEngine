
#define ame_Windows

#include "aMonkeyEngine/System.hpp"
#include "aMonkeyEngine/WindowsFile.hpp"

using namespace ame;

int main(){
    WindowsFile file;
    file.createFile("example.txt");

    file.writeLine("Hellow", "example.txt");
    file.writeLine("World", "example.txt");

    Note readText = file.readText("example.txt");
    Note readSizedText = file.readSizedText(13, "example.txt");

    System::console.println("printing readText");
    System::console.println(readText.getPosition());
    System::console.println(readText);

    System::console.println("printing readSizedText");
    System::console.println(readSizedText.getPosition());
    System::console.println(readSizedText);
    return 0;
}