
#ifndef ame_Logger_config_hpp
#define ame_Logger_config_hpp


//logger

#define ame_LogApp
#define ame_LogPrint
#define ame_SystemFullLog
//#define ame_Arduino_Log

#define Reflection_LogApp

// #define FreeSerialNetwork_LogApp

#define PointerArrayStorage_LogApp
// #define ReferenceCount_LogApp

// #define RawPointer_LogApp
// #define RawPointerManager_LogApp

// #define GameManager_LogApp

// #define GameSystem_LogApp
// #define TimeEventGameSystem_LogApp
// #define MethodGameSystem_LogApp

// #define Lexer_LogApp

// #define InputState_LogApp
// #define DebounceInput_LogApp

// #define DataNetwork_LogApp

// #define LoRaNetwork_LogApp
// #define RadioNetwork_LogApp

// #define ame_WIFI_LogApp
// #define ame_ETHERNET_LogApp
// #define ame_LoRa_LogApp

// #define DefaultApplication_LogApp

// #define DefaultStateManager_LogApp

// #define RawList_LogApp
// #define LinkedRawPointerList_LogApp
// #define LinkedRawList_LogApp
// #define LinkedIterator_LogApp
// #define PrimitiveRawPointerList_LogApp
// #define PrimitiveRawList_LogApp
// #define PrimitiveList_LogApp

// #define MapEntry_LogApp
// #define RawPointerMap_LogApp
// #define PrimitiveRawPointerMap_LogApp
// #define RawMap_LogApp
// #define PrimitiveRawMap_LogApp
// #define PrimitiveMap_LogApp

// #define ArrayIterator_LogApp
#define PointerArray_LogApp
#define Array_LogApp
#define Note_LogApp
// #define ByteArray_LogApp

// #define MonkeyFile_LogApp
// #define WindowsFile_LogApp
// #define DefaultMonkeyFile_LogApp

// #define ElementId_LogApp

// #define BaseAppState_LogApp

// #define SerialPost_LogApp
// #define SerialNetwork_LogApp
// #define SerialState_LogApp
// #define SerialStateController_LogApp
// #define SerialDelivery_LogApp

// #define UDPNetwork_LogApp

// #define DefaultSerialPort_LogApp
// #define DefaultPortProtocol_LogApp
// #define ListenerDelivery_LogApp
// #define LoRaNetwork_LogApp
// #define SerialListenerState_LogApp
// #define AlwaysConnected_LogApp

// #define WIFISerialServer_LogApp
// #define WIFISerialPort_LogApp

// #define LinkedList_LogApp

// #define CSMS_LogApp
//#define Listener_LogApp
//#define DefaultPortProtocol_LogApp
//#define StartEndPortProtocol_LogApp
// #define DefaultServerProtocol_LogApp
//#define IOPortProtocol_LogApp
//#define IOServerProtocol_LogApp

// #define Note_LogDebugApp
//#define Listener_LogDebugApp
//#define SerialState_LogDebugApp
//#define DefaultPortProtocol_LogDebugApp
//#define StartEndPortProtocol_LogDebugApp
//#define DefaultServerProtocol_LogDebugApp
//#define IOPortProtocol_LogDebugApp
//#define IOServerProtocol_LogDebugApp
//#define SerialListenerState_LogDebugApp
//#define AlwaysConnected_LogDebugApp

#ifndef ame_Log
	// #include "ame_Simple_Logger.hpp"
	// #define ame_Log_Module(pointer,location,name,method,type,mns) Simple_LogPrint_(pointer,location,name,method,type,mns)

	#include "ame_Method_Stack_Logger.hpp"
	#define ame_Log(pointer,location,name,method,type,mns) Stack_LogPrint_(pointer,location,name,method,type,mns)
	
	// #include "ame_List_Logger.hpp"
	// #define ame_Log(pointer,location,name,method,type,mns) List_LogPrint_(pointer,location,name,method,type,mns)
#endif

//   addClassToLog("Note");
//   addClassMethodToLog("insertLocalArrayPointer");


// #ifndef ame_LogDebug
// 	#include "ame_debug.hpp"
// 	#define ame_LogDebug(pointer,location,name,method,type) debug(pointer,location,name,method,type)
// #endif

// #ifndef ame_LogDebug
// 	#include "ame_list_debug.hpp"
// 	#define ame_LogDebug(pointer,location,name,method,type) list_debug(pointer,location,name,method,type)
// #endif


namespace ame{

void ameLoggerConfig(){
	// addClassToLog("Reflection");
	// addClassToLog("Note");
	// addClassToLog("Array");
	// addClassMethodToLog("addFunction");
	// addClassMethodToLog("invokeFunction");
	// addClassMethodToLog("getFunctionClass");
	// addClassMethodToLog("clonePointer");
	// addClassMethodToLog("copyExternEndValue");
	// addClassMethodToLog("endValue");
	// addClassMethodToLog("insertLocalArrayPointer");

    addStackChecker(stackName("Reflection", "addFunction"));
    // addStackChecker(stackName("Array", "clonePointer"));
    addStackChecker(stackName("Reflection", "addFunction"), stackName("Array", "clonePointer"));
	
}

}

#endif 

