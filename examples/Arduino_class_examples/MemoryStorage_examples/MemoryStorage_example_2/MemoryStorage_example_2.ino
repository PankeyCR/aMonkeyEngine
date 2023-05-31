
#include "ame_Enviroment.hpp"
#include "System.hpp"

#include "RawPointer.hpp"
#include "Pointer.hpp"
#include "MemoryStorage.hpp"
#include "PointerArrayStorage.hpp"
#include "ReferenceCount.hpp"

#include "MemoryRam.hpp"

using namespace ame;

MemoryStorage<MemoryStorage<RawPointer>>* i_storage;

void setup(){
    Serial.begin(9600);
    i_storage = new PointerArrayStorage<MemoryStorage<RawPointer>>();
    i_storage->setManager( new ReferenceCount<MemoryStorage<RawPointer>>() );
    i_storage->expandLocal(5);
}

void loop(){
    ame_Debuging(ame_Log_StartLoop, "loop");

    for(int x = 0; x < i_storage->getSize(); x++){
        MemoryStorage<RawPointer>* f_storage = new PointerArrayStorage<RawPointer>();
        f_storage->setManager( new ReferenceCount<RawPointer>() );
        f_storage->expandLocal(3);

        i_storage->set(x, f_storage);
    }

    MemoryStorage<RawPointer>* i_storage_1 = i_storage->get(0);

    if(i_storage_1 == nullptr){
        return;
    }

    i_storage_1->set(0, new RawPointer(new int(5)));
    i_storage_1->set(1, new RawPointer(new int(7)));
    i_storage_1->set(2, new RawPointer(new int(9)));
    
    for(int x = 0; x < i_storage->getSize(); x++){
        MemoryStorage<RawPointer>* f_pointer = i_storage->get(x);
        if(f_pointer == nullptr){
            continue;
        }
        for(int x = 0; x < i_storage_1->getSize(); x++){
            Pointer<RawPointer> f_pointer_1 = i_storage_1->get(x);
            Pointer<RawPointer> f_pointer_2 = f_pointer->get(2 - x);//x , 2 - x
            if(f_pointer_1 == nullptr || f_pointer_2 == nullptr){
                continue;
            }
            i_storage_1->set(x, f_pointer_2);
            f_pointer->set(2 - x, f_pointer_1);
            int f_value_1 = f_pointer_1->cast<int>();
            System::console.println(f_value_1);
            int f_value_2 = f_pointer_2->cast<int>();
            System::console.println(f_value_2);
        }
    }

    ame_Debuging(ame_Log_EndLoop, "loop");
}

