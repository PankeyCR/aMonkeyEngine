
/**
 *
 * @author PankeyCR - Manuel Sanchez Badilla
 *
 */

#ifndef CONFIGURATION_WindowsFile_hpp
#define CONFIGURATION_WindowsFile_hpp

	#include "ame_Enviroment.hpp"

	#if defined(DISABLE_WindowsFile) || !defined(ame_Windows) 
		#define WindowsFile_hpp

		#define IMPLEMENTATION_WindowsFile
		#define IMPLEMENTING_WindowsFile
	#else
		#if defined(DISABLE_IMPLEMENTATION_WindowsFile)
			#define IMPLEMENTATION_WindowsFile
			#define IMPLEMENTING_WindowsFile
		#endif
	#endif
#endif

#ifndef WindowsFile_hpp
#define WindowsFile_hpp
#define WindowsFile_AVAILABLE

#ifndef DISABLE_IMPLEMENTATION_WindowsFile
	#define IMPLEMENTATION_WindowsFile IMPLEMENTATION(public WindowsFile)
	#define IMPLEMENTING_WindowsFile IMPLEMENTING(public WindowsFile)
#endif

#include <windows.h>
#include <fstream>

#include "MonkeyFile.hpp"
#include "PrimitiveMap.hpp"
#include "Class.hpp"
#include "ByteArrayHelper.hpp"

#ifdef WindowsFile_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"

	#define WindowsFileLog(location,method,type,mns) ame_Log(this,location,"WindowsFile",method,type,mns)
	#define const_WindowsFileLog(location,method,type,mns)
	#define StaticWindowsFileLog(pointer,location,method,type,mns) ame_Log(pointer,location,"WindowsFile",method,type,mns)
#else
	#ifdef WindowsFile_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"

		#define WindowsFileLog(location,method,type,mns) ame_LogDebug(this,location,"WindowsFile",method,type)
		#define const_WindowsFileLog(location,method,type,mns)
		#define StaticWindowsFileLog(pointer,location,method,type,mns) ame_LogDebug(pointer,location,"WindowsFile",method,type)
	#else
		#define WindowsFileLog(location,method,type,mns)
		#define const_WindowsFileLog(location,method,type,mns)
		#define StaticWindowsFileLog(pointer,location,method,type,mns)
	#endif
#endif

namespace ame{

using namespace std;

class WindowsFile : public MonkeyFile{
    public:

		#ifdef ame_Windows
		WindowsFile(){}
		#endif

		virtual ~WindowsFile(){}

		virtual void initialize(){}

		virtual bool fastCreateDir(Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "fastCreateDir",  "println", "");
			WindowsFileLog(ame_Log_Statement, "fastCreateDir",  "println", a_path);
            CreateDirectory (a_path.pointer(), NULL);
			WindowsFileLog(ame_Log_EndMethod, "fastCreateDir",  "println", "");
			return true;
		}

		virtual bool createDir(Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "createDir",  "println", "");
			WindowsFileLog(ame_Log_Statement, "createDir",  "println", a_path);
            CreateDirectory (a_path.pointer(), NULL);
			WindowsFileLog(ame_Log_EndMethod, "createDir",  "println", "");
			return true;
		}

		virtual bool createRootDir(Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "createRootDir",  "println", "");
			Note i_path = this->fixRootPath(a_path);
			WindowsFileLog(ame_Log_Statement, "createRootDir",  "println", i_path);
            CreateDirectory (i_path.pointer(), NULL);
			WindowsFileLog(ame_Log_EndMethod, "createRootDir",  "println", "");
			return true;
		}

		virtual bool deleteDir(Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "deleteDir",  "println", "");
			WindowsFileLog(ame_Log_Statement, "deleteDir",  "println", a_path);
			WindowsFileLog(ame_Log_EndMethod, "deleteDir",  "println", "");
			return RemoveDirectoryA( a_path.pointer() );
		}

		virtual bool deleteRootDir(Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "deleteRootDir",  "println", "");
			Note i_path = this->fixRootPath(a_path);
			WindowsFileLog(ame_Log_Statement, "deleteRootDir",  "println", i_path);

			WindowsFileLog(ame_Log_EndMethod, "deleteRootDir",  "println", "");
			return RemoveDirectoryA( i_path.pointer() );
		}

		virtual bool fastCreateFile(Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "fastCreateFile",  "println", "");
            fstream i_file;
            i_file.open(a_path.pointer(),ios::out);
            i_file.close();
			WindowsFileLog(ame_Log_EndMethod, "fastCreateFile",  "println", "");
			return true;
		}

		virtual bool createFile(Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "createFile",  "println", "");
            fstream file;
            file.open(a_path.pointer(),ios::out);
            file.close();
			WindowsFileLog(ame_Log_EndMethod, "createFile",  "println", "");
			return true;
		}
		virtual bool createRootFile(Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "createRootFile",  "println", "");
			Note i_path = this->fixRootPath(a_path);
            fstream file;
            file.open(i_path.pointer(),ios::out);
            file.close();
			WindowsFileLog(ame_Log_EndMethod, "createRootFile",  "println", "");
			return true;
		}

		virtual bool deleteFile(Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "deleteFile",  "println", "");
			WindowsFileLog(ame_Log_Statement, "deleteFile",  "println", a_path);
			
			WindowsFileLog(ame_Log_EndMethod, "deleteFile",  "println", "");
			return DeleteFileA( a_path.pointer() );
		}

		virtual bool deleteRootFile(Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "deleteRootFile",  "println", "");
			Note i_path = this->fixRootPath(a_path);
			WindowsFileLog(ame_Log_Statement, "deleteRootFile",  "println", i_path);
			
			WindowsFileLog(ame_Log_EndMethod, "deleteRootFile",  "println", "");
			return DeleteFileA( i_path.pointer() );
		}

		virtual bool fastClearFile(Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "fastClearFile",  "println", "");
            fstream file;
            file.open(a_path.pointer(),ios::out);
            file.close();
			WindowsFileLog(ame_Log_EndMethod, "fastClearFile",  "println", "");
			return true;
		}

		virtual bool clearFile(Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "clearFile",  "println", "");
            fstream file;
            file.open(a_path.pointer(),ios::out);
            file.close();
			WindowsFileLog(ame_Log_EndMethod, "clearFile",  "println", "");
			return true;
		}

		virtual bool clearRootFile(Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "clearRootFile",  "println", "");
			Note i_path = this->fixRootPath(a_path);
            fstream file;
            file.open(i_path.pointer(),ios::out);
            file.close();
			WindowsFileLog(ame_Log_EndMethod, "clearRootFile",  "println", "");
			return true;
		}

		virtual bool fastWriteText(Note a_text, Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "fastWriteText",  "println", "");
			WindowsFileLog(ame_Log_Statement, "fastWriteText",  "println", a_path);
			WindowsFileLog(ame_Log_Statement, "fastWriteText",  "println", a_text);
			
            fstream outfile;

            outfile.open(a_path.pointer(), std::ios_base::app);
            if (!outfile.is_open()) {
                outfile.close();
                return false;
            }
            outfile.write(a_text.pointer(), a_text.getPosition());
            outfile.close();
			WindowsFileLog(ame_Log_EndMethod, "fastWriteText",  "println", "");
			return true;
		}

		virtual bool writeText(Note a_text, Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "writeText",  "println", "");
			WindowsFileLog(ame_Log_Statement, "fastWriteText",  "println", a_path);
			WindowsFileLog(ame_Log_Statement, "fastWriteText",  "println", a_text);
			
            fstream outfile;

            outfile.open(a_path.pointer(), std::ios_base::app);
            if (!outfile.is_open()) {
                outfile.close();
                return false;
            }
            outfile.write(a_text.pointer(), a_text.getPosition());
            outfile.close();
			WindowsFileLog(ame_Log_EndMethod, "writeText",  "println", "");
			return true;
		}

		virtual bool writeRootText(Note a_text, Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "writeRootText",  "println", "");
			Note i_path = this->fixRootPath(a_path);
			WindowsFileLog(ame_Log_Statement, "fastWriteText",  "println", i_path);
			WindowsFileLog(ame_Log_Statement, "fastWriteText",  "println", a_text);
            fstream outfile;

            outfile.open(i_path.pointer(), std::ios_base::app);
            if (!outfile.is_open()) {
                outfile.close();
                return false;
            }
            outfile.write(a_text.pointer(), a_text.getPosition());
            outfile.close();
			WindowsFileLog(ame_Log_EndMethod, "writeRootText",  "println", "");
			return true;
		}
/*
		virtual Note fastReadText(Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "fastReadText",  "println", "");
			Note i_path = this->m_root_hdd.addNote(this->fixPath(a_path));
			WindowsFileLog(ame_Log_Statement, "fastReadText",  "println", i_path);
            std::string readLineFromInput;

            std::ifstream readFile(i_path.pointer());
            if (readFile)
                std::getline(readFile, readLineFromInput);
			WindowsFileLog(ame_Log_EndMethod, "fastReadText",  "println", "");
            return Note(readLineFromInput.c_str());
		}
*/
		virtual Note readText(Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "readText",  "println", "");
			WindowsFileLog(ame_Log_Statement, "readText",  "println", a_path);
            Note i_text;
            ifstream i_file;

            i_file.open(a_path.pointer());
			if ( i_file.is_open() ) {
				char i_char;
				while ( i_file ) {
					i_char = i_file.get();
					if(i_char == '\0' || i_char == '\r'){
						break;
					}
					i_text.addLocalValue(i_char);
				}
			}
			WindowsFileLog(ame_Log_EndMethod, "readText",  "println", "");
			return i_text;
		}

		virtual Note readRootText(Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "readRootText",  "println", "");
			Note i_path = this->fixRootPath(a_path);
			WindowsFileLog(ame_Log_Statement, "readRootText",  "println", i_path);
            Note i_text;
            ifstream i_file;

            i_file.open(i_path.pointer());
			if ( i_file.is_open() ) {
				char i_char;
				while ( i_file ) {
					i_char = i_file.get();
					if(i_char == '\0' || i_char == '\r'){
						continue;
					}
					i_text.addLocalValue(i_char);
				}
			}
			WindowsFileLog(ame_Log_EndMethod, "readRootText",  "println", "");
			return i_text;
		}

		virtual Note readSizedText(int a_size, Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "readSizedText",  "println", "");
			WindowsFileLog(ame_Log_Statement, "readSizedText",  "println", a_path);
            Note i_text;
            ifstream i_file;

            i_file.open(a_path.pointer());
			if ( i_file.is_open() ) {
				char i_char;
				for(int x = 0; x < a_size; x++) {
					i_char = i_file.get();
					if(i_char == '\0' || i_char == '\r'){
						break;
					}
					i_text.addLocalValue(i_char);
				}
			}
			WindowsFileLog(ame_Log_EndMethod, "readSizedText",  "println", "");
			return i_text;
		}
		virtual Note readRootSizedText(int a_size, Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "readRootSizedText",  "println", "");
			Note i_path = this->fixRootPath(a_path);
			WindowsFileLog(ame_Log_Statement, "readRootSizedText",  "println", i_path);
            Note i_text;
            ifstream i_file;

            i_file.open(i_path.pointer());
			if ( i_file.is_open() ) {
				char i_char;
				for(int x = 0; x < a_size; x++) {
					i_char = i_file.get();
					if(i_char == '\0' || i_char == '\r'){
						break;
					}
					i_text.addLocalValue(i_char);
				}
			}
			WindowsFileLog(ame_Log_EndMethod, "readRootSizedText",  "println", "");
			return i_text;
		}

		virtual PrimitiveList<Note> readLines(Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "readLines",  "println", "");
			WindowsFileLog(ame_Log_Statement, "readLines",  "println", a_path);
			PrimitiveList<Note> i_list;
            Note i_text;
            ifstream i_file;

            i_file.open(a_path.pointer());
			if ( i_file.is_open() ) {
				char i_char;
				while ( i_file ) {
					i_char = i_file.get();
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
			}
			if(!i_text.isEmpty()){
				i_list.add(i_text);
				i_text.clear();
			}
			WindowsFileLog(ame_Log_EndMethod, "readLines",  "println", "");
			return i_list;
		}

		virtual PrimitiveList<Note> readRootLines(Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "readRootLines",  "println", "");
			Note i_path = this->fixRootPath(a_path);
			WindowsFileLog(ame_Log_Statement, "readRootLines",  "println", i_path);
			PrimitiveList<Note> i_list;
            Note i_text;
            ifstream i_file;

            i_file.open(i_path.pointer());
			if ( i_file.is_open() ) {
				char i_char;
				while ( i_file ) {
					i_char = i_file.get();
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
			}
			if(!i_text.isEmpty()){
				i_list.add(i_text);
				i_text.clear();
			}
			WindowsFileLog(ame_Log_EndMethod, "readRootLines",  "println", "");
			return i_list;
		}
		
		virtual PrimitiveList<Note> readSizedLines(int a_size, Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "readSizedLines",  "println", "");
			WindowsFileLog(ame_Log_Statement, "readSizedLines",  "println", a_path);
			PrimitiveList<Note> i_list;
            Note i_text;
            ifstream i_file;

            i_file.open(a_path.pointer());
			if ( i_file.is_open() ) {
				char i_char;
				for(int x = 0; x < a_size; x++) {
					i_char = i_file.get();
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
			}
			if(!i_text.isEmpty()){
				i_list.add(i_text);
				i_text.clear();
			}
			WindowsFileLog(ame_Log_EndMethod, "readSizedLines",  "println", "");
			return i_list;
		}

		virtual PrimitiveList<Note> readRootSizedLines(int a_size, Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "readRootSizedLines",  "println", "");
			Note i_path = this->fixRootPath(a_path);
			WindowsFileLog(ame_Log_Statement, "readRootSizedLines",  "println", i_path);
			PrimitiveList<Note> i_list;
            Note i_text;
            ifstream i_file;

            i_file.open(i_path.pointer());
			if ( i_file.is_open() ) {
				char i_char;
				for(int x = 0; x < a_size; x++) {
					i_char = i_file.get();
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
			}
			if(!i_text.isEmpty()){
				i_list.add(i_text);
				i_text.clear();
			}
			WindowsFileLog(ame_Log_EndMethod, "readRootSizedLines",  "println", "");
			return i_list;
		}
		
		virtual Note readLine(int a_line, Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "readLine",  "println", "");
			WindowsFileLog(ame_Log_Statement, "readLine",  "println", a_path);
            Note i_text;
            ifstream i_file;
			int i_line = 0;

            i_file.open(a_path.pointer());
			if ( i_file.is_open() ) {
				char i_char;
				while ( i_file ) {
					i_char = i_file.get();
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
			}
			WindowsFileLog(ame_Log_EndMethod, "readLine",  "println", "");
			return i_text;
		}

		virtual Note readRootLine(int a_line, Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "readRootLine",  "println", "");
			Note i_path = this->fixRootPath(a_path);
			WindowsFileLog(ame_Log_Statement, "readRootLine",  "println", i_path);
            Note i_text;
            ifstream i_file;
			int i_line = 0;

            i_file.open(i_path.pointer());
			if ( i_file.is_open() ) {
				char i_char;
				while ( i_file ) {
					i_char = i_file.get();
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
			}
			WindowsFileLog(ame_Log_EndMethod, "readRootLine",  "println", "");
			return i_text;
		}


		virtual bool writeByteArray(ByteArray array, Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "writeByteArray",  "println", "");
			WindowsFileLog(ame_Log_Statement, "writeByteArray",  "println", a_path);

			WindowsFileLog(ame_Log_EndMethod, "writeByteArray",  "println", "");
			return true;
		}

		virtual bool writeRootByteArray(ByteArray array, Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "writeRootByteArray",  "println", "");
			Note i_path = this->fixRootPath(a_path);
			WindowsFileLog(ame_Log_Statement, "writeRootByteArray",  "println", i_path);

			WindowsFileLog(ame_Log_EndMethod, "writeRootByteArray",  "println", "");
			return true;
		}

		virtual ByteArray readByteArray(Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "readByteArray",  "println", "");
			WindowsFileLog(ame_Log_Statement, "readByteArray",  "println", a_path);

			ByteArray array;
			WindowsFileLog(ame_Log_EndMethod, "readByteArray",  "println", "");
			return array;
		}

		virtual ByteArray readRootByteArray(Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "readRootByteArray",  "println", "");
			Note i_path = this->fixRootPath(a_path);
			WindowsFileLog(ame_Log_Statement, "readRootByteArray",  "println", i_path);

			ByteArray array;
			WindowsFileLog(ame_Log_EndMethod, "readRootByteArray",  "println", "");
			return array;
		}

		virtual bool exist(Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "exist",  "println", "");
			WindowsFileLog(ame_Log_Statement, "exist ",  "println", a_path);
			
  			WIN32_FIND_DATAA FindFileData = {0};
   			HANDLE handle = FindFirstFileA(a_path.pointer(), &FindFileData) ;
			FindClose(handle);

			WindowsFileLog(ame_Log_EndMethod, "exist",  "println", handle != INVALID_HANDLE_VALUE);
    		return handle != INVALID_HANDLE_VALUE;
		}
		virtual bool existRoot(Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "existRoot",  "println", "");
			Note i_path = this->fixRootPath(a_path);
			WindowsFileLog(ame_Log_Statement, "existRoot",  "println", "");
			WindowsFileLog(ame_Log_Statement, "existRoot ",  "println", i_path);
			
  			WIN32_FIND_DATAA FindFileData = {0};
   			HANDLE handle = FindFirstFileA(i_path.pointer(), &FindFileData) ;
			FindClose(handle);

			WindowsFileLog(ame_Log_EndMethod, "existRoot",  "println", "");
    		return handle != INVALID_HANDLE_VALUE;
		}

		virtual int getFileSize(Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "getFileSize",  "println", "");
			WindowsFileLog(ame_Log_Statement, "getFileSize",  "println", Note("path: ") + a_path);

			WindowsFileLog(ame_Log_EndMethod, "getFileSize",  "println", "");
			return 0;
		}

		virtual int getDirectoriesSize(Note a_path){
			WindowsFileLog(ame_Log_StartMethod, "getDirectoriesSize",  "println", "");
			WindowsFileLog(ame_Log_Statement, "getDirectoriesSize",  "println", Note("path: ") + a_path);

			WindowsFileLog(ame_Log_EndMethod, "getDirectoriesSize",  "println", "");
			return 0;
		}

		virtual PrimitiveMap<Note,Note> getDirectories(Note dirname, int levels){
			WindowsFileLog(ame_Log_StartMethod, "getDirectories",  "println", "");
			WindowsFileLog(ame_Log_Statement, "getDirectories",  "println", Note("Listing directory: ") + dirname);

			PrimitiveMap<Note,Note> m_map;

			WindowsFileLog(ame_Log_EndMethod, "getDirectories",  "println", "");
			return m_map;
		}

		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(ArgsClass_AVAILABLE)
		virtual cppObjectClass* getClass(){
			return ArgsClass<WindowsFile>::getClass();
		}

		virtual bool instanceof(cppObjectClass* cls){
			return cls == ArgsClass<WindowsFile>::getClass();
		}
		#endif

	protected:
};

}

#endif
