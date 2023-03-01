/*
*	
*
*/
#if defined(DISABLE_ame_config)
	#define ame_config_hpp
#endif

#ifndef ame_config_hpp
#define ame_config_hpp
#define ame_config_AVAILABLE 

//////////////////////////////////////////////////////////////

//enviroments

#ifndef ame_Enviroment_Defined
	// #define ame_Windows 
	// #define ame_Ubuntu 
	// #define ame_RaspberryPiOS 
	// #define ame_ArduinoIDE 
	// #define ame_Expressif 
#endif

//hardwares

#ifndef ame_Hardware_Defined
	// #define ame_GENERIC_ARDUINO 
	// #define ame_ARDUINO_MEGA 
	// #define ame_ARDUINO_UNO 
	// #define ame_ARDUINO_NANO 
	// #define ame_ARDUINO_LEONARDO 

	// #define ame_GENERIC_ESP32_S3 
	// #define ame_GENERIC_ESP8266 
	// #define ame_GENERIC_ESP32 
	// #define ame_ESP32_T2 
	// #define ame_ESP32_LILYGO_CAMERA_PLUS 
	// #define ame_ESP32_AUDIO_KIT 
	// #define ame_ESP32_LORA_V1  
	// #define ame_LILYGO_WATCH_2020_V1 
	// #define ame_LILYGO_WATCH_2020_V2 
	// #define ame_LILYGO_WATCH_2020_V3 
	// #define ame_ESP32_POE_ETHERNET 

	// #define ame_GENERIC_ADAFRUIT_FEATHER 
	// #define ame_ADAFRUIT_FEATHER_M0 

	// #define ame_RaspberryPi_3 
	// #define ame_RaspberryPi_4 
#endif


//logger

#define ame_LogApp
#define ame_LogPrint
#define ame_SystemFullLog
//#define ame_Arduino_Log

#define GameManager_LogApp

// #define GameSystem_LogApp
#define TimeEventGameSystem_LogApp
#define MethodGameSystem_LogApp

// #define Lexer_LogApp

// #define InputState_LogApp
// #define DebounceInput_LogApp

// #define DataNetwork_LogApp

// #define LoRaNetwork_LogApp
// #define RadioNetwork_LogApp

// #define ame_WIFI_LogApp
// #define ame_ETHERNET_LogApp
// #define ame_LoRa_LogApp

// #define SerialNetwork_LogApp
// #define SerialState_LogApp

// #define SerialDelivery_LogApp

#define DefaultApplication_LogApp

#define DefaultStateManager_LogApp

// #define RawList_LogApp
// #define LinkedRawPointerList_LogApp
// #define LinkedRawList_LogApp
// #define LinkedIterator_LogApp
#define PrimitiveRawPointerList_LogApp
#define PrimitiveRawList_LogApp
#define PrimitiveList_LogApp

// #define MapEntry_LogApp
// #define RawPointerMap_LogApp
// #define PrimitiveRawPointerMap_LogApp
// #define RawMap_LogApp
// #define PrimitiveRawMap_LogApp
// #define PrimitiveMap_LogApp

// #define ArrayIterator_LogApp
// #define Array_LogApp
// #define Note_LogApp
// #define ByteArray_LogApp

// #define DefaultMonkeyFile_LogApp

// #define ElementId_LogApp

// #define BaseAppState_LogApp

// #define SerialController_LogApp

// #define SerialPost_LogApp
// #define SerialNetwork_LogApp
// #define SerialState_LogApp
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
//#define DefaultServerProtocol_LogApp
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

// #define DISABLE_ame_Enviroment

// #define DISABLE_Note
// #define DISABLE_ByteArray

#define DISABLE_Memory
#define DISABLE_MemoryManager
#define DISABLE_MemoryPool
#define DISABLE_MemoryChunk
#define DISABLE_Chunk

// #define DISABLE_cppObjectClass
// #define DISABLE_Annotation
// #define DISABLE_Method

// #define DISABLE_cppObject

// #define DISABLE_AbstractClass
// #define DISABLE_Class

// #define DISABLE_Application
// #define DISABLE_DefaultApplication

#define DISABLE_RenderManager
// #define DISABLE_AppSettings
// #define DISABLE_TimeControl
// #define DISABLE_AppStateManager

// #define DISABLE_DefaultSettings
// #define DISABLE_SimpleTimer
// #define DISABLE_DefaultStateManager

// #define DISABLE_AppState
// #define DISABLE_BaseAppState

// #define DISABLE_SerialServer
// #define DISABLE_ServerProtocol

// #define DISABLE_SerialPort
// #define DISABLE_PortProtocol

// #define DISABLE_LinkedList


#define ame_ErrorWarning

// #ifndef ame_Log
// 	#include "ame_List_Logger.hpp"
// 	#define ame_Log(pointer,location,name,method,type,mns) List_LogPrint_(pointer,location,name,method,type,mns)
// #endif

//   addClassToLog("Note");
//   addClassMethodToLog("toLong");


#ifndef ame_LogDebug
	#include "ame_debug.hpp"
	#define ame_LogDebug(pointer,location,name,method,type) debug(pointer,location,name,method,type)
#endif

// #ifndef ame_LogDebug
// 	#include "ame_list_debug.hpp"
// 	#define ame_LogDebug(pointer,location,name,method,type) list_debug(pointer,location,name,method,type)
// #endif



//////////////////////////////////////////////////////////////

#endif