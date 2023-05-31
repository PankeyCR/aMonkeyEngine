# 1 "C:\\Users\\ManuelSánchezBadilla\\Documents\\Arduino\\libraries\\aMonkeyEngine\\examples\\Arduino_class_examples\\MemoryStorage_examples\\MemoryStorage_example_2\\MemoryStorage_example_2.ino"

# 3 "C:\\Users\\ManuelSánchezBadilla\\Documents\\Arduino\\libraries\\aMonkeyEngine\\examples\\Arduino_class_examples\\MemoryStorage_examples\\MemoryStorage_example_2\\MemoryStorage_example_2.ino" 2
# 4 "C:\\Users\\ManuelSánchezBadilla\\Documents\\Arduino\\libraries\\aMonkeyEngine\\examples\\Arduino_class_examples\\MemoryStorage_examples\\MemoryStorage_example_2\\MemoryStorage_example_2.ino" 2

# 6 "C:\\Users\\ManuelSánchezBadilla\\Documents\\Arduino\\libraries\\aMonkeyEngine\\examples\\Arduino_class_examples\\MemoryStorage_examples\\MemoryStorage_example_2\\MemoryStorage_example_2.ino" 2
# 7 "C:\\Users\\ManuelSánchezBadilla\\Documents\\Arduino\\libraries\\aMonkeyEngine\\examples\\Arduino_class_examples\\MemoryStorage_examples\\MemoryStorage_example_2\\MemoryStorage_example_2.ino" 2
# 8 "C:\\Users\\ManuelSánchezBadilla\\Documents\\Arduino\\libraries\\aMonkeyEngine\\examples\\Arduino_class_examples\\MemoryStorage_examples\\MemoryStorage_example_2\\MemoryStorage_example_2.ino" 2
# 9 "C:\\Users\\ManuelSánchezBadilla\\Documents\\Arduino\\libraries\\aMonkeyEngine\\examples\\Arduino_class_examples\\MemoryStorage_examples\\MemoryStorage_example_2\\MemoryStorage_example_2.ino" 2
# 10 "C:\\Users\\ManuelSánchezBadilla\\Documents\\Arduino\\libraries\\aMonkeyEngine\\examples\\Arduino_class_examples\\MemoryStorage_examples\\MemoryStorage_example_2\\MemoryStorage_example_2.ino" 2

# 12 "C:\\Users\\ManuelSánchezBadilla\\Documents\\Arduino\\libraries\\aMonkeyEngine\\examples\\Arduino_class_examples\\MemoryStorage_examples\\MemoryStorage_example_2\\MemoryStorage_example_2.ino" 2

using namespace ame;

MemoryStorage<MemoryStorage<RawPointer>>* i_storage;

void setup(){
    Serial.begin(9600);
    i_storage = new PointerArrayStorage<MemoryStorage<RawPointer>>();
    i_storage->setManager( new ReferenceCount<MemoryStorage<RawPointer>>() );
    i_storage->expandLocal(5);
}

void loop(){
    debug(nullptr,2,"raw","loop","println");

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

    debug(nullptr,3,"raw","loop","println");
}
