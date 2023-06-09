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
#define DISABLE_AppSettings
#define DISABLE_TimeControl
// #define DISABLE_AppStateManager

#define DISABLE_DefaultSettings
#define DISABLE_SimpleTimer
// #define DISABLE_DefaultStateManager

// #define DISABLE_AppState
// #define DISABLE_BaseAppState

// #define DISABLE_SerialServer
// #define DISABLE_ServerProtocol

// #define DISABLE_SerialPort
// #define DISABLE_PortProtocol

// #define DISABLE_LinkedList


#define ame_ErrorWarning

namespace ame{

void ameConfig(){
	
}

}

//////////////////////////////////////////////////////////////

#endif