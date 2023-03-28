
/*
*
*	Macros for all types of enviroments:
*
*	ame_Windows
*	ame_Linux
*	ame_Apple
*	ame_RaspberryPiOS
*	ame_ArduinoIDE
*	ame_Expressif
*
*
*	Macros for all supported hardwares and its level:
*	
*	ame_GENERIC_ARDUINO					ame_Level_7
*	ame_ARDUINO_MEGA					ame_Level_6
*	ame_ARDUINO_UNO						ame_Level_4
*	ame_ARDUINO_NANO					ame_Level_1
*	ame_ARDUINO_LEONARDO				ame_Level_5
*	
*	ame_GENERIC_ESP8266					ame_Level_10
*
*	ame_GENERIC_ESP32_S3				ame_Level_12
*	ame_GENERIC_ESP32					ame_Level_12
*	ame_ESP32_T2						ame_Level_12
*	ame_ESP32_DEV						ame_Level_12
*	ame_TTGO_T7							ame_Level_12
*	ame_ESP32_LILYGO_CAMERA_PLUS		ame_Level_12
*	ame_ESP32_AUDIO_KIT					ame_Level_12
*	ame_ESP32_LORA_V1					ame_Level_15
*	ame_LILYGO_WATCH_2020_V1			ame_Level_15
*	ame_LILYGO_WATCH_2020_V2			ame_Level_15
*	ame_LILYGO_WATCH_2020_V3			ame_Level_15
*	ame_ESP32_POE_ETHERNET				ame_Level_15
*
*	ame_GENERIC_ADAFRUIT_FEATHER		ame_Level_8
*	ame_ADAFRUIT_FEATHER_M0				ame_Level_8
*
*	ame_RaspberryPi_3					ame_Level_15
*	ame_RaspberryPi_4					ame_Level_15
*	
*	If a board is defined, the generic macro will be defined
*	
*	If a level is defined, the macro ame_Level_Defined is defined
*	
*	If a board is defined, the macro ame_Hardware_Defined is defined
*	
*	
*	char* enviroment_name = ame_Enviroment_Name;
*	
*	
*	
*	
*	
*/

///////////////////////////////////////////

#include "ame_Windows_Enviroment_config.hpp"
#include "ame_Linux_Enviroment_config.hpp"
#include "ame_RaspberryPiOS_Enviroment_config.hpp"
#include "ame_ArduinoIDE_Enviroment_config.hpp"
#include "ame_Expressif_Enviroment_config.hpp"

///////////////////////////////////////////