
#ifndef ame_Hardware_Defined

	#if defined(__AVR_ATmega2560__)
		#ifndef ame_ARDUINO_MEGA
			#define ame_ARDUINO_MEGA
		#endif
		#ifndef ame_GENERIC_ARDUINO
			#define ame_GENERIC_ARDUINO
		#endif
		#ifndef ame_Hardware_Defined
			#define ame_Hardware_Defined
		#endif
		#ifndef ame_Level_Defined
			#define ame_Level_6
			#define ame_Level_Defined
		#endif
		#ifndef ame_Enviroment_Defined
			#define ame_ArduinoIDE
			#define ame_Enviroment_Defined
			#define ame_Enviroment_Name "ArduinoIDE"
		#endif
		#ifndef ame_Hardware_Name
			#define ame_Hardware_Name "__AVR_ATmega2560__"
		#endif
	#endif

	#if defined(ARDUINO_ARCH_AVR)
		#ifndef ame_GENERIC_ARDUINO
			#define ame_GENERIC_ARDUINO
		#endif
		#ifndef ame_Hardware_Defined
			#define ame_Hardware_Defined
		#endif
		#ifndef ame_Level_Defined
			#define ame_Level_6
			#define ame_Level_Defined
		#endif
		#ifndef ame_Enviroment_Defined
			#define ame_ArduinoIDE
			#define ame_Enviroment_Defined
			#define ame_Enviroment_Name "ArduinoIDE"
		#endif
		#ifndef ame_Hardware_Name
			#define ame_Hardware_Name "ARDUINO_ARCH_AVR"
		#endif
	#endif

	#if defined(ARDUINO_ARCH_ESP8266)
		#ifndef ame_GENERIC_ESP8266
			#define ame_GENERIC_ESP8266
		#endif
		#ifndef ame_Hardware_Defined
			#define ame_Hardware_Defined
		#endif
		#ifndef ame_Level_Defined
			#define ame_Level_9
			#define ame_Level_Defined
		#endif
		#ifndef ame_Enviroment_Defined
			#define ame_ArduinoIDE
			#define ame_Enviroment_Defined
			#define ame_Enviroment_Name "ArduinoIDE"
		#endif
		#ifndef ame_Hardware_Name
			#define ame_Hardware_Name "ARDUINO_ARCH_ESP8266"
		#endif
	#endif

	#if defined(ARDUINO_ESP32S3_DEV)
		#ifndef ame_GENERIC_ESP32_S3
			#define ame_GENERIC_ESP32_S3
		#endif
		#ifndef ame_Hardware_Defined
			#define ame_Hardware_Defined
		#endif
		#ifndef ame_Level_Defined
			#define ame_Level_15
			#define ame_Level_Defined
		#endif
		#ifndef ame_Enviroment_Defined
			#define ame_ArduinoIDE
			#define ame_Enviroment_Defined
			#define ame_Enviroment_Name "ArduinoIDE"
		#endif
		#ifndef ame_Hardware_Name
			#define ame_Hardware_Name "ARDUINO_ESP32S3_DEV"
		#endif
	#endif

	#if defined(ARDUINO_ESP32_DEV)
		#ifndef ame_ESP32_DEV
			#define ame_ESP32_DEV
		#endif
		#ifndef ame_GENERIC_ESP32
			#define ame_GENERIC_ESP32
		#endif
		#ifndef ame_Hardware_Defined
			#define ame_Hardware_Defined
		#endif
		#ifndef ame_Level_Defined
			#define ame_Level_10
			#define ame_Level_Defined
		#endif
		#ifndef ame_Enviroment_Defined
			#define ame_ArduinoIDE
			#define ame_Enviroment_Defined
			#define ame_Enviroment_Name "ArduinoIDE"
		#endif
		#ifndef ame_Hardware_Name
			#define ame_Hardware_Name "ARDUINO_ESP32_DEV"
		#endif
	#endif

	#if defined(ARDUINO_ARCH_ESP32)
		#ifndef ame_GENERIC_ESP32
			#define ame_GENERIC_ESP32
		#endif
		#ifndef ame_Hardware_Defined
			#define ame_Hardware_Defined
		#endif
		#ifndef ame_Level_Defined
			#define ame_Level_10
			#define ame_Level_Defined
		#endif
		#ifndef ame_Enviroment_Defined
			#define ame_ArduinoIDE
			#define ame_Enviroment_Defined
			#define ame_Enviroment_Name "ArduinoIDE"
		#endif
		#ifndef ame_Hardware_Name
			#define ame_Hardware_Name "ARDUINO_ARCH_ESP32"
		#endif
	#endif

	#if defined(ARDUINO_TTGO_T7_V14_Mini32)
		#ifndef ame_TTGO_T7
			#define ame_TTGO_T7
		#endif
		#ifndef ame_GENERIC_ESP32
			#define ame_GENERIC_ESP32
		#endif
		#ifndef ame_Hardware_Defined
			#define ame_Hardware_Defined
		#endif
		#ifndef ame_Level_Defined
			#define ame_Level_10
			#define ame_Level_Defined
		#endif
		#ifndef ame_Enviroment_Defined
			#define ame_ArduinoIDE
			#define ame_Enviroment_Defined
			#define ame_Enviroment_Name "ArduinoIDE"
		#endif
		#ifndef ame_Hardware_Name
			#define ame_Hardware_Name "ARDUINO_TTGO_T7_V14_Mini32"
		#endif
	#endif

	#if defined(ARDUINO_SAMD_ZERO)//feather
		#ifndef ame_ADAFRUIT_FEATHER_M0
			#define ame_ADAFRUIT_FEATHER_M0
		#endif
		#ifndef ame_GENERIC_ADAFRUIT_FEATHER
			#define ame_GENERIC_ADAFRUIT_FEATHER
		#endif
		#ifndef ame_Hardware_Defined
			#define ame_Hardware_Defined
		#endif
		#ifndef ame_Level_Defined
			#define ame_Level_8
			#define ame_Level_Defined
		#endif
		#ifndef ame_Enviroment_Defined
			#define ame_ArduinoIDE
			#define ame_Enviroment_Defined
			#define ame_Enviroment_Name "ArduinoIDE"
		#endif
		#ifndef ame_Hardware_Name
			#define ame_Hardware_Name "ARDUINO_SAMD_ZERO"
		#endif
	#endif
	
#endif