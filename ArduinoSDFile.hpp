
/**
 *
 * @author PankeyCR - Manuel Sanchez Badilla
 *
 */

#ifndef CONFIGURATION_ArduinoSDFile_hpp
#define CONFIGURATION_ArduinoSDFile_hpp

	#include "ame_Enviroment.hpp"

	#if defined(DISABLE_ArduinoSDFile)
		#define ArduinoSDFile_hpp
	#endif
#endif

#ifndef ArduinoSDFile_hpp
#define ArduinoSDFile_hpp
#define ArduinoSDFile_AVAILABLE

#ifdef ame_Windows

#endif

#ifdef ame_ArduinoIDE
	#include "Arduino.h"
	#include <SPI.h>
	#include <SD.h>
	#if defined(ame_GENERIC_ESP32)
		#include "FS.h"
	#endif
#endif

#include "MonkeyFile.hpp"
#include "PrimitiveMap.hpp"
#include "ArgsClass.hpp"
#include "ByteArrayHelper.hpp"

#ifdef ArduinoSDFile_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"
	
	#define ArduinoSDFileLog(location,method,type,mns) ame_Log(this,location,"ArduinoSDFile",method,type,mns)
	#define const_ArduinoSDFileLog(location,method,type,mns) 
	#define StaticArduinoSDFileLog(pointer,location,method,type,mns) ame_Log(pointer,location,"ArduinoSDFile",method,type,mns)
#else
	#ifdef ArduinoSDFile_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"
		
		#define ArduinoSDFileLog(location,method,type,mns) ame_LogDebug(this,location,"ArduinoSDFile",method,type)
		#define const_ArduinoSDFileLog(location,method,type,mns) 
		#define StaticArduinoSDFileLog(pointer,location,method,type,mns) ame_LogDebug(pointer,location,"ArduinoSDFile",method,type)
	#else
		#define ArduinoSDFileLog(location,method,type,mns) 
		#define const_ArduinoSDFileLog(location,method,type,mns) 
		#define StaticArduinoSDFileLog(pointer,location,method,type,mns) 
	#endif
#endif

namespace ame{

template<class T>
class ArduinoSDFile : public MonkeyFile{
    public:
		static bool init;
		
		ArduinoSDFile(const ArduinoSDFile& file) : m_sd(file.m_sd){}
		ArduinoSDFile(T &t) : m_sd(t){}
		ArduinoSDFile(){}
		
		virtual ~ArduinoSDFile(){}
		
		virtual void initialize(){
			ArduinoSDFileLog(ame_Log_StartMethod, "initialize",  "println", "");
			if(!init){
				init = true;
				#if defined(ame_ESP32_POE_ETHERNET)
				ArduinoSDFileLog(ame_Log_Statement, "initialize",  "println", "ARDUINO_ESP32_POE_ETHERNET");
				SPI.begin(14, 2, 15, 13);//sclk , miso , mosi , cs
				m_sd.begin(13);
				uint8_t cardType = m_sd.cardType();

				if(cardType == CARD_NONE){
					ArduinoSDFileLog(ame_Log_Statement, "initialize",  "println", "No SD card attached");
					ArduinoSDFileLog(ame_Log_EndMethod, "initialize",  "println", "");
					return;
				}
				#elif defined(ame_ESP32_DEV)
				ArduinoSDFileLog(ame_Log_Statement, "initialize",  "println", "ARDUINO_ESP32_DEV");
				SPI.begin(14, 2, 15, 13);
				m_sd.begin(13);
				uint8_t cardType = m_sd.cardType();

				if(cardType == CARD_NONE){
					ArduinoSDFileLog(ame_Log_Statement, "initialize",  "println", "No SD card attached");
					ArduinoSDFileLog(ame_Log_EndMethod, "initialize",  "println", "");
					return;
				}
				#elif defined(ame_TTGO_T7)
				ArduinoSDFileLog(ame_Log_Statement, "initialize",  "println", "ARDUINO_TTGO_T7_V14_Mini32");
				SPI.begin(21, 22, 19, 0);//sclk , miso , mosi , cs
				m_sd.begin(0);
				uint8_t cardType = m_sd.cardType();

				if(cardType == CARD_NONE){
					ArduinoSDFileLog(ame_Log_Statement, "initialize",  "println", "No SD card attached");
					ArduinoSDFileLog(ame_Log_EndMethod, "initialize",  "println", "");
					return;
				}
				#elif defined(ame_GENERIC_ARDUINO)
				ArduinoSDFileLog(ame_Log_Statement, "initialize",  "println", "ARDUINO_ARCH_AVR");
				m_sd.begin(4);
				#elif defined(ame_ADAFRUIT_FEATHER_M0)
				ArduinoSDFileLog(ame_Log_Statement, "initialize",  "println", "ARDUINO_SAMD_ZERO");
				m_sd.begin(4);
				#endif

				this->m_open = true;
			}
			ArduinoSDFileLog(ame_Log_EndMethod, "initialize",  "println", "");
		}
		
		virtual bool fastCreateDir(Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "fastCreateDir",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "fastCreateDir",  "println", "Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "fastCreateDir",  "println", a_path);
			ArduinoSDFileLog(ame_Log_EndMethod, "fastCreateDir",  "println", "");
			return m_sd.mkdir(a_path.toString());
		}
		
		virtual bool createDir(Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "createDir",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "createDir",  "println", "Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "createDir",  "println", a_path);
			if(m_sd.mkdir(a_path.toString())){
				ArduinoSDFileLog(ame_Log_Statement, "createDir",  "println", "Dir created");
				ArduinoSDFileLog(ame_Log_EndMethod, "createDir",  "println", "");
				return true;
			}else{
				ArduinoSDFileLog(ame_Log_Statement, "createDir",  "println", "mkdir failed");
			}
			ArduinoSDFileLog(ame_Log_EndMethod, "createDir",  "println", "");
			return false;
		}
		
		virtual bool createRootDir(Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "createRootDir",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "createRootDir",  "println", "Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "createRootDir",  "println", a_path);
			Note i_path = this->fixRootPath(a_path);
			ArduinoSDFileLog(ame_Log_Statement, "createRootDir",  "println", "Fixed Root Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "createRootDir",  "println", i_path);
			if(m_sd.mkdir(i_path.toString())){
				ArduinoSDFileLog(ame_Log_Statement, "createRootDir",  "println", "Dir created");
			}else{
				ArduinoSDFileLog(ame_Log_Statement, "createRootDir",  "println", "mkdir failed");
			}
			ArduinoSDFileLog(ame_Log_EndMethod, "createRootDir",  "println", "");
			return true;
		}
		
		virtual bool deleteDir(Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "deleteDir",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "deleteDir",  "println", "Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "deleteDir",  "println", a_path);
			if(m_sd.rmdir(a_path.toString())){
				ArduinoSDFileLog(ame_Log_Statement, "deleteDir",  "println", "Dir deleted");
				return true;
			}else{
				ArduinoSDFileLog(ame_Log_Statement, "deleteDir",  "println", "rmdir failed");
			}
			ArduinoSDFileLog(ame_Log_EndMethod, "deleteDir",  "println", "");
			return false;
		}
		
		virtual bool deleteRootDir(Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "deleteRootDir",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "deleteRootDir",  "println", "Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "deleteRootDir",  "println", a_path);
			Note i_path = this->fixRootPath(a_path);
			ArduinoSDFileLog(ame_Log_Statement, "deleteRootDir",  "println", "Fixed Root Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "deleteRootDir",  "println", i_path);
			if(m_sd.rmdir(i_path.toString())){
				ArduinoSDFileLog(ame_Log_Statement, "deleteRootDir",  "println", "Dir deleted");
				return true;
			}else{
				ArduinoSDFileLog(ame_Log_Statement, "deleteRootDir",  "println", "rmdir failed");
			}
			ArduinoSDFileLog(ame_Log_EndMethod, "deleteDir",  "println", "");
			return false;
		}
		
		virtual bool fastCreateFile(Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "fastCreateFile",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "fastCreateFile",  "println", "Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "fastCreateFile",  "println", a_path);
			File myFile = m_sd.open(a_path.toString(), FILE_WRITE);
			myFile.close();
			ArduinoSDFileLog(ame_Log_EndMethod, "fastCreateFile",  "println", "");
			return true;
		}
		
		virtual bool createFile(Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "createFile",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "createFile",  "println", "Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "createFile",  "println", a_path);
			File myFile = m_sd.open(a_path.toString(), FILE_WRITE);
			myFile.close();
			ArduinoSDFileLog(ame_Log_EndMethod, "createFile",  "println", "");
			return true;
		}

		virtual bool createRootFile(Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "createRootFile",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "createRootFile",  "println", "Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "createRootFile",  "println", a_path);
			Note i_path = this->fixRootPath(a_path);
			ArduinoSDFileLog(ame_Log_Statement, "createRootFile",  "println", "Fixed Root Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "createRootFile",  "println", i_path);
			File myFile = m_sd.open(i_path.toString(), FILE_WRITE);
			myFile.close();
			ArduinoSDFileLog(ame_Log_EndMethod, "createFile",  "println", "");
			return true;
		}
		
		virtual bool deleteFile(Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "deleteFile",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "deleteFile",  "println", "Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "deleteFile",  "println", a_path);
			ArduinoSDFileLog(ame_Log_EndMethod, "deleteFile",  "println", "");
			return m_sd.remove(a_path.toString());
		}

		virtual bool deleteRootFile(Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "deleteRootFile",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "deleteRootFile",  "println", "Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "deleteRootFile",  "println", a_path);
			Note i_path = this->fixRootPath(a_path);
			ArduinoSDFileLog(ame_Log_Statement, "deleteRootFile",  "println", "Fixed Root Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "deleteRootFile",  "println", i_path);
			ArduinoSDFileLog(ame_Log_EndMethod, "deleteRootFile",  "println", "");
			return m_sd.remove(i_path.toString());
		}
		
		virtual bool fastClearFile(Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "fastClearFile",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "fastClearFile",  "println", "Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "fastClearFile",  "println", a_path);
			m_sd.remove(a_path.toString());
			File myFile = m_sd.open(a_path.toString(), FILE_WRITE);
			myFile.close();
			ArduinoSDFileLog(ame_Log_EndMethod, "fastClearFile",  "println", "");
			return true;
		}
		
		virtual bool clearFile(Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "clearFile",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "clearFile",  "println", "Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "clearFile",  "println", a_path);
			m_sd.remove(a_path.toString());
			File myFile = m_sd.open(a_path.toString(), FILE_WRITE);
			myFile.close();
			ArduinoSDFileLog(ame_Log_EndMethod, "clearFile",  "println", "");
			return true;
		}
		
		virtual bool clearRootFile(Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "clearRootFile",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "clearRootFile",  "println", "Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "clearRootFile",  "println", a_path);
			Note i_path = this->fixRootPath(a_path);
			ArduinoSDFileLog(ame_Log_Statement, "clearRootFile",  "println", "Fixed Root Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "clearRootFile",  "println", i_path);
			m_sd.remove(i_path.toString());
			File myFile = m_sd.open(i_path.toString(), FILE_WRITE);
			myFile.close();
			ArduinoSDFileLog(ame_Log_EndMethod, "clearRootFile",  "println", "");
			return true;
		}
		
		virtual bool fastWriteText(Note a_text, Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "fastWriteText",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "fastWriteText",  "println", "Text: ");
			ArduinoSDFileLog(ame_Log_Statement, "fastWriteText",  "println", a_text);
			ArduinoSDFileLog(ame_Log_Statement, "fastWriteText",  "println", "Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "fastWriteText",  "println", a_path);

			#if defined(ARDUINO_ARCH_AVR)
			File myFile = m_sd.open(a_path.toString(), FILE_WRITE);
			#elif defined(ame_ESP32_POE_ETHERNET)
			File myFile = m_sd.open(a_path.toString(), FILE_WRITE);
			#elif defined(ame_ESP32_DEV)
			File myFile = m_sd.open(a_path.toString(), FILE_APPEND);
			#elif defined(ame_TTGO_T7)
			File myFile = m_sd.open(a_path.toString(), FILE_APPEND);
			#elif defined(ame_ADAFRUIT_FEATHER_M0)
			File myFile = m_sd.open(a_path.toString(), FILE_WRITE);
			#endif
			myFile.print(a_text.toString());
			myFile.close();
			ArduinoSDFileLog(ame_Log_EndMethod, "fastWriteText",  "println", "");
			return true;
		}
		
		virtual bool writeText(Note a_text, Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "writeText",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "writeText",  "println", "Text: ");
			ArduinoSDFileLog(ame_Log_Statement, "writeText",  "println", a_text);
			ArduinoSDFileLog(ame_Log_Statement, "writeText",  "println", "Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "writeText",  "println", a_path);

			#if defined(ARDUINO_ARCH_AVR)
			File myFile = m_sd.open(a_path.toString(), FILE_WRITE);
			#elif defined(ame_ESP32_POE_ETHERNET)
			File myFile = m_sd.open(a_path.toString(), FILE_WRITE);
			#elif defined(ame_ESP32_DEV)
			File myFile = m_sd.open(a_path.toString(), FILE_APPEND);
			#elif defined(ame_TTGO_T7)
			File myFile = m_sd.open(a_path.toString(), FILE_APPEND);
			#elif defined(ame_ADAFRUIT_FEATHER_M0)
			File myFile = m_sd.open(a_path.toString(), FILE_WRITE);
			#endif
			String i_string = a_text.toString();
			ArduinoSDFileLog(ame_Log_Statement, "writeText",  "println", i_string);
			myFile.print(i_string);
			myFile.close();
			ArduinoSDFileLog(ame_Log_EndMethod, "writeText",  "println", "");
			return true;
		}
		virtual bool writeRootText(Note a_text, Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "writeRootText",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "writeRootText",  "println", "Text: ");
			ArduinoSDFileLog(ame_Log_Statement, "writeRootText",  "println", a_text);
			ArduinoSDFileLog(ame_Log_Statement, "writeRootText",  "println", "Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "writeRootText",  "println", a_path);
			Note i_path = this->fixRootPath(a_path);
			ArduinoSDFileLog(ame_Log_Statement, "writeRootText",  "println", "Fixed Root Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "writeRootText",  "println", i_path);

			#if defined(ARDUINO_ARCH_AVR)
			File myFile = m_sd.open(i_path.toString(), FILE_WRITE);
			#elif defined(ARDUINO_ESP32_DEV)
			File myFile = m_sd.open(i_path.toString(), FILE_APPEND);
			#elif defined(ARDUINO_TTGO_T7_V14_Mini32)
			File myFile = m_sd.open(i_path.toString(), FILE_APPEND);
			#elif defined(ARDUINO_SAMD_ZERO)
			File myFile = m_sd.open(i_path.toString(), FILE_WRITE);
			#endif
			myFile.print(a_text.toString());
			myFile.close();
			ArduinoSDFileLog(ame_Log_EndMethod, "writeRootText",  "println", "");
			return true;
		}
		
		virtual Note fastReadText(Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "fastReadText",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "fastReadText",  "println", "Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "fastReadText",  "println", a_path);

			File myFile = m_sd.open(a_path.toString());
            Note i_text;
			char i_char;

			while(myFile.available()){
				i_char = (char)myFile.read();
				if(i_char == '\0' || i_char == '\r'){
					ArduinoSDFileLog(ame_Log_Statement, "fastReadText",  "println", "i_char == 0 or r");
					break;
				}
				ArduinoSDFileLog(ame_Log_Statement, "fastReadText",  "println", Note(i_char));
				i_text.addLocalValue(i_char);
			}
			
			myFile.close();

			ArduinoSDFileLog(ame_Log_EndMethod, "fastReadText",  "println", "");
			return i_text;
		}
		
		virtual Note readText(Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "readText",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "readText",  "println", "Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "readText",  "println", a_path);

			File myFile = m_sd.open(a_path.toString());
            Note i_text;
			char i_char;

			while(myFile.available()){
				i_char = (char)myFile.read();
				if(i_char == '\0' || i_char == '\r'){
					ArduinoSDFileLog(ame_Log_Statement, "readText",  "println", "i_char == 0 or r");
					break;
				}
				ArduinoSDFileLog(ame_Log_Statement, "readText",  "println", Note(i_char));
				i_text.addLocalValue(i_char);
			}
			
			myFile.close();

			ArduinoSDFileLog(ame_Log_EndMethod, "readText",  "println", "");
			return i_text;
		}

		virtual Note readRootText(Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "readRootText",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "readRootText",  "println", "Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "readRootText",  "println", a_path);
			Note i_path = this->fixRootPath(a_path);
			ArduinoSDFileLog(ame_Log_Statement, "readRootText",  "println", "Fixed Root Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "readRootText",  "println", i_path);

			File myFile = m_sd.open(i_path.toString());
            Note i_text;
			char i_char;

			while(myFile.available()){
				i_char = (char)myFile.read();
				if(i_char == '\0' || i_char == '\r'){
					ArduinoSDFileLog(ame_Log_Statement, "readText",  "println", "i_char == 0 or r");
					break;
				}
				ArduinoSDFileLog(ame_Log_Statement, "readText",  "println", Note(i_char));
				i_text.addLocalValue(i_char);
			}
			
			myFile.close();

			ArduinoSDFileLog(ame_Log_EndMethod, "readRootText",  "println", "");
			return i_text;
		}

		virtual Note readSizedText(int a_size, Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "readSizedText",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "readSizedText",  "println", "Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "readSizedText",  "println", a_path);

			File myFile = m_sd.open(a_path.toString());
            Note i_text;
			char i_char;

			for(int x = 0; x < a_size && myFile.available(); x++) {
				i_char = (char)myFile.read();
				if(i_char == '\0' || i_char == '\r'){
					ArduinoSDFileLog(ame_Log_Statement, "readSizedText",  "println", "i_char == 0 or r");
					break;
				}
				ArduinoSDFileLog(ame_Log_Statement, "readSizedText",  "println", Note(i_char));
				i_text.addLocalValue(i_char);
			}

			myFile.close();

			ArduinoSDFileLog(ame_Log_EndMethod, "readSizedText",  "println", "");
			return i_text;
		}
		
		virtual Note readRootSizedText(int a_size, Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "readRootSizedText",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "readRootSizedText",  "println", "Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "readRootSizedText",  "println", a_path);
			Note i_path = this->fixRootPath(a_path);
			ArduinoSDFileLog(ame_Log_Statement, "readRootSizedText",  "println", "Fixed Root Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "readRootSizedText",  "println", i_path);

			File myFile = m_sd.open(i_path.toString());
            Note i_text;
			char i_char;

			for(int x = 0; x < a_size && myFile.available(); x++) {
				i_char = (char)myFile.read();
				if(i_char == '\0' || i_char == '\r'){
					ArduinoSDFileLog(ame_Log_Statement, "readRootSizedText",  "println", "i_char == 0 or r");
					break;
				}
				ArduinoSDFileLog(ame_Log_Statement, "readRootSizedText",  "println", Note(i_char));
				i_text.addLocalValue(i_char);
			}

			myFile.close();

			ArduinoSDFileLog(ame_Log_EndMethod, "readRootSizedText",  "println", "");
			return i_text;
		}

		virtual PrimitiveList<Note> readLines(Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "readLines",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "readLines",  "println", "Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "readLines",  "println", a_path);

			PrimitiveList<Note> i_list;
            Note i_text;
			File i_file = m_sd.open(a_path.toString());

			char i_char;
			while ( i_file.available() ) {
				i_char = (char)i_file.read();
				if(i_char == '\n'){
					i_list.add(i_text);
					i_text.clear();
					continue;
				}
				if(i_char == '\0' || i_char == '\r'){
					break;
				}
				i_text.addLocalValue(i_char);
			}
			if(!i_text.isEmpty()){
				i_list.add(i_text);
				i_text.clear();
			}
			ArduinoSDFileLog(ame_Log_EndMethod, "readLines",  "println", "");
			return i_list;
		}

		virtual PrimitiveList<Note> readRootLines(Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "readRootLines",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "readRootLines",  "println", "Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "readRootLines",  "println", a_path);
			Note i_path = this->fixRootPath(a_path);
			ArduinoSDFileLog(ame_Log_Statement, "readRootLines",  "println", "Fixed Root Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "readRootLines",  "println", i_path);
			PrimitiveList<Note> i_list;
            Note i_text;
			File i_file = m_sd.open(i_path.toString());

			char i_char;
			while ( i_file.available() ) {
				i_char = (char)i_file.read();
				if(i_char == '\n'){
					i_list.add(i_text);
					i_text.clear();
					continue;
				}
				if(i_char == '\0' || i_char == '\r'){
					break;
				}
				i_text.addLocalValue(i_char);
			}
			if(!i_text.isEmpty()){
				i_list.add(i_text);
				i_text.clear();
			}
			ArduinoSDFileLog(ame_Log_EndMethod, "readRootLines",  "println", "");
			return i_list;
		}
		
		virtual PrimitiveList<Note> readSizedLines(int a_size, Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "readSizedLines",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "readSizedLines",  "println", "Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "readSizedLines",  "println", a_path);

			PrimitiveList<Note> i_list;
            Note i_text;
			File i_file = m_sd.open(a_path.toString());

			char i_char;
			int i_size = 0;
			for(int x = 0; i_size < a_size && i_file.available(); x++) {
				i_char = (char)i_file.read();
				if(i_char == '\n'){
					i_list.add(i_text);
					i_text.clear();
					continue;
				}
				if(i_char == '\0' || i_char == '\r'){
					break;
				}
				i_text.addLocalValue(i_char);
				i_size++;
			}
			if(!i_text.isEmpty()){
				i_list.add(i_text);
				i_text.clear();
			}
			ArduinoSDFileLog(ame_Log_EndMethod, "readSizedLines",  "println", "");
			return i_list;
		}

		virtual PrimitiveList<Note> readRootSizedLines(int a_size, Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "readRootSizedLines",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "readRootSizedLines",  "println", "Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "readRootSizedLines",  "println", a_path);
			Note i_path = this->fixRootPath(a_path);
			ArduinoSDFileLog(ame_Log_Statement, "readRootSizedLines",  "println", "Fixed Root Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "readRootSizedLines",  "println", i_path);

			PrimitiveList<Note> i_list;
            Note i_text;
			File i_file = m_sd.open(i_path.toString());

			char i_char;
			int i_size = 0;
			for(int x = 0; i_size < a_size && i_file.available(); x++) {
				i_char = (char)i_file.read();
				if(i_char == '\n'){
					i_list.add(i_text);
					i_text.clear();
					continue;
				}
				if(i_char == '\0' || i_char == '\r'){
					break;
				}
				i_text.addLocalValue(i_char);
				i_size++;
			}
			if(!i_text.isEmpty()){
				i_list.add(i_text);
				i_text.clear();
			}
			ArduinoSDFileLog(ame_Log_EndMethod, "readRootSizedLines",  "println", "");
			return i_list;
		}
		/*
		virtual PrimitiveList<Note> readSizedLines(int a_line_size, int a_total_size, Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "readSizedLines",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "readSizedLines",  "println", "Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "readSizedLines",  "println", a_path);

			PrimitiveList<Note> i_list;
            Note i_text;
			File i_file = m_sd.open(a_path.toString());

			char i_char;
			int i_total_size = 0;
			int i_line_size = 0;
			for(int x = 0; i_total_size < a_total_size && i_file.available(); x++) {
				i_char = (char)i_file.read();
				if(i_char == '\n' || i_line_size < a_line_size){
					i_list.add(i_text);
					i_text.clear();
					continue;
				}
				if(i_char == '\0' || i_char == '\r'){
					break;
				}
				i_text.addLocalValue(i_char);
				i_total_size++;
			}
			if(!i_text.isEmpty()){
				i_list.add(i_text);
				i_text.clear();
			}
			ArduinoSDFileLog(ame_Log_EndMethod, "readSizedLines",  "println", "");
			return i_list;
		}

		virtual PrimitiveList<Note> readRootSizedLines(int a_line_size, int a_total_size, Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "readRootSizedLines",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "readRootSizedLines",  "println", "Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "readRootSizedLines",  "println", a_path);
			Note i_path = this->fixRootPath(a_path);
			ArduinoSDFileLog(ame_Log_Statement, "readRootSizedLines",  "println", "Fixed Root Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "readRootSizedLines",  "println", i_path);

			PrimitiveList<Note> i_list;
            Note i_text;
			File i_file = m_sd.open(i_path.toString());

			char i_char;
			int i_size = 0;
			for(int x = 0; i_size < a_size && i_file.available(); x++) {
				i_char = (char)i_file.read();
				if(i_char == '\n'){
					i_list.add(i_text);
					i_text.clear();
					continue;
				}
				if(i_char == '\0' || i_char == '\r'){
					break;
				}
				i_text.addLocalValue(i_char);
				i_size++;
			}
			if(!i_text.isEmpty()){
				i_list.add(i_text);
				i_text.clear();
			}
			ArduinoSDFileLog(ame_Log_EndMethod, "readRootSizedLines",  "println", "");
			return i_list;
		}
		*/
		virtual Note readLine(int a_line, Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "readLine",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "readLine",  "println", "Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "readLine",  "println", a_path);

            Note i_text;
			File i_file = m_sd.open(a_path.toString());
			int i_line = 0;

			char i_char;
			while ( i_file.available() ) {
				i_char = (char)i_file.read();
				if(i_char == '\n'){
					i_line++;
					continue;
				}
				if(i_char == '\0' || i_char == '\r'){
					break;
				}
				if(i_line == a_line){
					i_text.addLocalValue(i_char);
				}
			}
			ArduinoSDFileLog(ame_Log_EndMethod, "readLine",  "println", "");
			return i_text;
		}

		virtual Note readRootLine(int a_line, Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "readRootLine",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "readRootLine",  "println", "Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "readRootLine",  "println", a_path);
			Note i_path = this->fixRootPath(a_path);
			ArduinoSDFileLog(ame_Log_Statement, "readRootLine",  "println", "Fixed Root Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "readRootLine",  "println", i_path);

            Note i_text;
			File i_file = m_sd.open(i_path.toString());
			int i_line = 0;

			char i_char;
			while ( i_file.available() ) {
				i_char = (char)i_file.read();
				if(i_char == '\n'){
					i_line++;
					continue;
				}
				if(i_char == '\0' || i_char == '\r'){
					break;
				}
				if(i_line == a_line){
					i_text.addLocalValue(i_char);
				}
			}
			ArduinoSDFileLog(ame_Log_EndMethod, "readRootLine",  "println", "");
			return i_text;
		}
		
		virtual bool writeByteArray(ByteArray array, Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "writeByteArray",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "writeByteArray",  "println", a_path);
			Note i_path = this->fixPath(a_path);
			ArduinoSDFileLog(ame_Log_Statement, "createRootDir",  "println", i_path);

			#if defined(ARDUINO_ARCH_AVR)
			File myFile = m_sd.open(i_path.toString(), FILE_WRITE);
			#elif defined(ARDUINO_ESP32_DEV)
			File myFile = m_sd.open(i_path.toString(), FILE_APPEND);
			#elif defined(ARDUINO_TTGO_T7_V14_Mini32)
			File myFile = m_sd.open(i_path.toString(), FILE_APPEND);
			#elif defined(ARDUINO_SAMD_ZERO)
			File myFile = m_sd.open(i_path.toString(), FILE_WRITE);
			#endif
			myFile.print(toNote(array).toString());
			myFile.close();
			ArduinoSDFileLog(ame_Log_EndMethod, "writeByteArray",  "println", "");
			return true;
		}

		virtual bool writeRootByteArray(ByteArray array, Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "readRootText",  "println", "");
			Note i_path = this->fixRootPath(a_path);
			ArduinoSDFileLog(ame_Log_Statement, "readRootText",  "println", i_path);
			#if defined(ARDUINO_ARCH_AVR)
			File myFile = m_sd.open(i_path.toString(), FILE_WRITE);
			#elif defined(ARDUINO_ESP32_DEV)
			File myFile = m_sd.open(i_path.toString(), FILE_APPEND);
			#elif defined(ARDUINO_TTGO_T7_V14_Mini32)
			File myFile = m_sd.open(i_path.toString(), FILE_APPEND);
			#elif defined(ARDUINO_SAMD_ZERO)
			File myFile = m_sd.open(i_path.toString(), FILE_WRITE);
			#endif
			myFile.print(toNote(array).toString());
			myFile.close();
			ArduinoSDFileLog(ame_Log_EndMethod, "fastWriteText",  "println", "");
			return true;
		}
		
		virtual ByteArray readByteArray(Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "readByteArray",  "println", "");
			Note i_path = this->fixPath(a_path);
			ArduinoSDFileLog(ame_Log_Statement, "createRootDir",  "println", i_path);
			File myFile = m_sd.open(i_path.toString());
			Note sr = "";
			while(myFile.available()){
				char c = (char)myFile.read();
				ArduinoSDFileLog(ame_Log_Statement, "readByteArray",  "println", Note(c));
				sr.addLocalValue(c);
			}
			myFile.close();
			ByteArray array = toByteArray(sr);
			ArduinoSDFileLog(ame_Log_EndMethod, "readByteArray",  "println", "");
			return array;
		}
		
		virtual ByteArray readRootByteArray(Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "readRootByteArray",  "println", "");
			Note i_path = this->fixRootPath(a_path);
			ArduinoSDFileLog(ame_Log_Statement, "readRootByteArray",  "println", i_path);
			File myFile = m_sd.open(i_path.toString());
			Note s;
			while (myFile.available()) {
				char c = (char)myFile.read();
				ArduinoSDFileLog(ame_Log_Statement, "readRootByteArray",  "println", Note(c));
				s.addLocalValue(c);
			}
			myFile.close();
			ByteArray array = toByteArray(s);
			ArduinoSDFileLog(ame_Log_EndMethod, "readRootByteArray",  "println", "");
			return array;
		}
		
		virtual bool exist(Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "exist",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "exist",  "println", "Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "exist",  "println", a_path);
			ArduinoSDFileLog(ame_Log_EndMethod, "exist",  "println", "");
			return m_sd.exists(a_path.toString());
		}

		virtual bool existRoot(Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "existRoot",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "existRoot",  "println", "Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "existRoot",  "println", a_path);
			Note i_path = this->fixRootPath(a_path);
			ArduinoSDFileLog(ame_Log_Statement, "existRoot",  "println", "Fixed Root Path: ");
			ArduinoSDFileLog(ame_Log_Statement, "existRoot",  "println", i_path);
			ArduinoSDFileLog(ame_Log_EndMethod, "existRoot",  "println", "");
			return m_sd.exists(i_path.toString());
		}
		
		virtual bool isOpen(){
			return init;
		}
		
		virtual int getFileSize(Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "getFileSize",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "getFileSize",  "println", a_path);


			File root = m_sd.open(a_path.toString());
			if(!root){
				ArduinoSDFileLog(ame_Log_Statement, "getFileSize",  "println", "Failed to open directory");
				ArduinoSDFileLog(ame_Log_EndMethod, "getFileSize",  "println", "");
				return 0;
			}
			if(!root.isDirectory()){
				ArduinoSDFileLog(ame_Log_Statement, "getFileSize",  "println", "Not a directory");
				ArduinoSDFileLog(ame_Log_EndMethod, "getFileSize",  "println", "");
				return 0;
			}
			int x = 0;
			File file = root.openNextFile();
			while(file){
				if(!file.isDirectory()){
					x++;
				}
				file = root.openNextFile();
			}
			ArduinoSDFileLog(ame_Log_EndMethod, "getFileSize",  "println", "");
			return x;
		}
		
		virtual int getDirectoriesSize(Note a_path){
			ArduinoSDFileLog(ame_Log_StartMethod, "getDirectoriesSize",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "getDirectoriesSize",  "println", a_path);

			File root = m_sd.open(a_path.toString());
			if(!root){
				ArduinoSDFileLog(ame_Log_Statement, "getDirectoriesSize",  "println", "Failed to open directory");
				ArduinoSDFileLog(ame_Log_EndMethod, "getDirectoriesSize",  "println", "");
				return 0;
			}
			if(!root.isDirectory()){
				ArduinoSDFileLog(ame_Log_Statement, "getDirectoriesSize",  "println", "Not a directory");
				ArduinoSDFileLog(ame_Log_EndMethod, "getDirectoriesSize",  "println", "");
				return 0;
			}
			int x = 0;
			File file = root.openNextFile();
			while(file){
				if(file.isDirectory()){
					x++;
				}
				file = root.openNextFile();
			}
			ArduinoSDFileLog(ame_Log_EndMethod, "getDirectoriesSize",  "println", "");
			return x;
		}
		
		virtual PrimitiveMap<Note,Note> getDirectories(Note dirname, int levels){
			ArduinoSDFileLog(ame_Log_StartMethod, "getDirectories",  "println", "");
			ArduinoSDFileLog(ame_Log_Statement, "getDirectories",  "println", Note("Listing directory: ") + dirname);

			PrimitiveMap<Note,Note> m_map;
			File root = m_sd.open(dirname.toString());
			if(!root){
				ArduinoSDFileLog(ame_Log_Statement, "getDirectories",  "println", "Failed to open directory");
				ArduinoSDFileLog(ame_Log_EndMethod, "getDirectories",  "println", "");
				return m_map;
			}
			if(!root.isDirectory()){
				ArduinoSDFileLog(ame_Log_Statement, "getDirectories",  "println", "Not a directory");
				ArduinoSDFileLog(ame_Log_EndMethod, "getDirectories",  "println", "");
				return m_map;
			}
			File file = root.openNextFile();
			while(file){
				if(file.isDirectory()){
					m_map.add("Dir", file.name());
					if(levels){
						PrimitiveMap<Note,Note> i_directories = getDirectories(file.name(), levels -1);
						m_map.addMap(i_directories);
					}
				} else {
					m_map.add("File", file.name());
				}
				file = root.openNextFile();
			}
			ArduinoSDFileLog(ame_Log_EndMethod, "getDirectories",  "println", "");
			return m_map;
		}	

		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(ArgsClass_AVAILABLE)
		virtual cppObjectClass* getClass(){
			return ArgsClass<ArduinoSDFile>::getClass();
		}
		
		virtual bool instanceof(cppObjectClass* cls){
			return cls == ArgsClass<ArduinoSDFile>::getClass();
		}
		#endif
		
	protected:
		T& m_sd;
};

}

template<class T>
bool ame::ArduinoSDFile<T>::init = false;

#endif