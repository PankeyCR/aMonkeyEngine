
#define ame_Windows

#include "aMonkeyEngine/System.hpp"
#include "aMonkeyEngine/WindowsFile.hpp"

using namespace ame;

int main(){
    WindowsFile file;
    file.createFile("example.txt");

    file.writeLine("Hellow", "example.txt");
    file.writeLine("World", "example.txt");

    PrimitiveList<Note> readLines = file.readLines("example.txt");
    PrimitiveList<Note> readSizedLines = file.readSizedLines(13, "example.txt");

    System::console.println("Printing readLines");
    System::console.println(PrintableList<PrimitiveList<Note>,Note>(readLines));
    System::console.println("Printing readSizedLines");
    System::console.println(PrintableList<PrimitiveList<Note>,Note>(readSizedLines));

    System::console.println("Printing read line 1");
    System::console.println(file.readLine(1, "example.txt"));
    return 0;
}