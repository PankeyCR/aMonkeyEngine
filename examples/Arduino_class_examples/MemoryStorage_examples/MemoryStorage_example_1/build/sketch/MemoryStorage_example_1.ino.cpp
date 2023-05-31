#include <Arduino.h>
#line 1 "C:\\Users\\ManuelSánchezBadilla\\Documents\\Arduino\\libraries\\aMonkeyEngine\\examples\\Arduino_class_examples\\MemoryStorage_examples\\MemoryStorage_example_1\\MemoryStorage_example_1.ino"

#include "ame_Enviroment.hpp"
#include "System.hpp"

#include "RawPointer.hpp"
#include "MemoryStorage.hpp"
#include "PointerArrayStorage.hpp"
#include "ReferenceCount.hpp"

#include "MemoryRam.hpp"

using namespace ame;

MemoryStorage<RawPointer>* i_storage;

#line 16 "C:\\Users\\ManuelSánchezBadilla\\Documents\\Arduino\\libraries\\aMonkeyEngine\\examples\\Arduino_class_examples\\MemoryStorage_examples\\MemoryStorage_example_1\\MemoryStorage_example_1.ino"
void setup();
#line 24 "C:\\Users\\ManuelSánchezBadilla\\Documents\\Arduino\\libraries\\aMonkeyEngine\\examples\\Arduino_class_examples\\MemoryStorage_examples\\MemoryStorage_example_1\\MemoryStorage_example_1.ino"
void loop();
#line 16 "C:\\Users\\ManuelSánchezBadilla\\Documents\\Arduino\\libraries\\aMonkeyEngine\\examples\\Arduino_class_examples\\MemoryStorage_examples\\MemoryStorage_example_1\\MemoryStorage_example_1.ino"
void setup(){
    Serial.begin(9600);
    i_storage = new PointerArrayStorage<RawPointer>();
    i_storage->setManager( new ReferenceCount<RawPointer>() );

    i_storage->expandLocal(3);
}

void loop(){
    i_storage->set(0, new RawPointer(new int(5)));
    i_storage->set(1, new RawPointer(new int(7)));
    i_storage->set(2, new RawPointer(new int(9)));
    
    for(int x = 0; x < i_storage->getSize(); x++){
        RawPointer* f_pointer = i_storage->get(x);
        if(f_pointer == nullptr){
            continue;
        }
        int f_value = f_pointer->cast<int>();
        System::console.println(f_value);
    }

    System::console.print("ram: ");
    System::console.println(getRamSize());
}

