
#include "ame_Enviroment.hpp"
#include "System.hpp"

#include "RawPointer.hpp"
#include "MemoryStorage.hpp"
#include "PointerArrayStorage.hpp"
#include "ReferenceCount.hpp"

#include "MemoryRam.hpp"

using namespace ame;

MemoryStorage<RawPointer>* i_storage;

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
