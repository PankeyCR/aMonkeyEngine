
/**
 *
 * @author PankeyCR - Manuel Sanchez Badilla
 *
 */

#ifndef CONFIGURATION_MonkeyFile_hpp
#define CONFIGURATION_MonkeyFile_hpp

	#include "ame_Enviroment.hpp"

	#if defined(DISABLE_MonkeyFile)
		#define MonkeyFile_hpp

		#define IMPLEMENTATION_MonkeyFile
		#define IMPLEMENTING_MonkeyFile
	#else
		#if defined(DISABLE_IMPLEMENTATION_MonkeyFile)
			#define IMPLEMENTATION_MonkeyFile
			#define IMPLEMENTING_MonkeyFile
		#endif
	#endif
#endif

#ifndef MonkeyFile_hpp
#define MonkeyFile_hpp
#define MonkeyFile_AVAILABLE

#ifndef DISABLE_IMPLEMENTATION_MonkeyFile
	#define IMPLEMENTATION_MonkeyFile IMPLEMENTATION(public MonkeyFile)
	#define IMPLEMENTING_MonkeyFile IMPLEMENTING(public MonkeyFile)
#endif

#include "Note.hpp"
#include "NoteHelper.hpp"
#include "ByteArray.hpp"
#include "PrimitiveList.hpp"
#include "PrimitiveMap.hpp"


#ifdef MonkeyFile_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"

	#define MonkeyFileLog(location,method,type,mns) ame_Log(this,location,"MonkeyFile",method,type,mns)
	#define const_MonkeyFileLog(location,method,type,mns)
	#define StaticMonkeyFileLog(pointer,location,method,type,mns) ame_Log(pointer,location,"MonkeyFile",method,type,mns)
#else
	#ifdef MonkeyFile_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"

		#define MonkeyFileLog(location,method,type,mns) ame_LogDebug(this,location,"MonkeyFile",method,type)
		#define const_MonkeyFileLog(location,method,type,mns)
		#define StaticMonkeyFileLog(pointer,location,method,type,mns) ame_LogDebug(pointer,location,"MonkeyFile",method,type)
	#else
		#define MonkeyFileLog(location,method,type,mns)
		#define const_MonkeyFileLog(location,method,type,mns)
		#define StaticMonkeyFileLog(pointer,location,method,type,mns)
	#endif
#endif


namespace ame{

class MonkeyFile IMPLEMENTATION_cppObject {
    public:
		MonkeyFile(){}
		virtual ~MonkeyFile(){}

		virtual void initialize(){}

		virtual bool isOpen(){
			return m_open;
		}

		template<class... Args>
		void setRootPathFile(const Note& a_root_hdd, Args... a_paths){
			MonkeyFileLog(ame_Log_StartMethod, "setRootPathFile",  "println", "");
			MonkeyFileLog(ame_Log_Statement, "setRootPathFile",  "println", "Main Folder: ");
			MonkeyFileLog(ame_Log_Statement, "setRootPathFile",  "println", a_root_hdd);
			this->m_root_hdd = a_root_hdd;
			this->m_rootPath = this->fixFullPaths(this->m_root_hdd, a_paths...);
			MonkeyFileLog(ame_Log_Statement, "setRootPathFile",  "println", "Root Path: ");
			MonkeyFileLog(ame_Log_Statement, "setRootPathFile",  "println", this->m_rootPath);
			this->createPath(this->m_root_hdd, a_paths...);
			m_open = this->exist(this->m_rootPath);
			MonkeyFileLog(ame_Log_EndMethod, "setRootPathFile",  "println", "");
		}
		Note getRootPathFile(){
			return this->m_rootPath;
		}

		virtual bool fastCreateDir(Note a_path){return this->createDir(a_path);}
		virtual bool createDir(Note a_path){return false;}
		virtual bool createRootDir(Note a_path){return false;}

		virtual bool deleteDir(Note a_path){return false;}
		virtual bool deleteRootDir(Note a_path){return false;}

		template<class... Args>
		bool createPath(const Note& a_root_hdd, Args... a_paths){
			MonkeyFileLog(ame_Log_StartMethod, "createPath",  "println", a_root_hdd);
			Note i_path = a_root_hdd;
			this->createDir(i_path);
			if(!this->exist(i_path)){
				MonkeyFileLog(ame_Log_Statement, "createPath",  "println", "!this->createDir(i_path)");
				MonkeyFileLog(ame_Log_EndMethod, "createPath",  "println", "false");
				return false;
			}
			PrimitiveList<Note> i_list;
			i_list.addPack(a_paths...);
			for(int x = 0; x < i_list.getPosition(); x++){
				Note* f_path = i_list.getByPosition(x);
				if(f_path == nullptr){
					continue;
				}
				i_path = this->mixRootPath(i_path, *f_path);
				MonkeyFileLog(ame_Log_Statement, "createPath",  "println", i_path);
				this->createDir(i_path);
				if(!this->exist(i_path)){
					MonkeyFileLog(ame_Log_Statement, "createPath",  "println", "!this->createDir(i_path)");
					MonkeyFileLog(ame_Log_EndMethod, "createPath",  "println", "false");
					return false;
				}
			}
			MonkeyFileLog(ame_Log_EndMethod, "createPath",  "println", "true");
			return true;
		}

		template<class... Args>
		bool createRootPath(Args... a_paths){
			PrimitiveList<Note> i_list;
			i_list.addPack(a_paths...);
			Note i_path = this->m_rootPath;
			for(int x = 0; x < i_list.getPosition(); x++){
				Note* f_path = i_list.getByPosition(x);
				if(f_path == nullptr){
					continue;
				}
				i_path = this->mixRootPath(i_path, *f_path);
				if(!this->createDir(i_path)){
					return false;
				}
			}
			return true;
		}

		template<class... Args>
		bool deletePath(const Note& a_root_hdd, Args... a_paths){
			Note i_path = this->fixFullPaths(a_root_hdd, a_paths...);
			return this->deleteDir(i_path);
		}
		
		template<class... Args>
		bool deleteRootPath(Args... a_paths){
			Note i_path = this->fixRootPaths(a_paths...);
			return this->deleteDir(i_path);
		}

		virtual bool fastCreateFile(Note a_file){return this->createFile(a_file);}
		virtual bool createFile(Note a_file){return false;}
		virtual bool createRootFile(Note a_file){return false;}

		virtual bool deleteFile(Note a_file){return false;}
		virtual bool deleteRootFile(Note a_file){return false;}

		virtual bool fastClearFile(Note a_file){return this->clearFile(a_file);}
		virtual bool clearFile(Note a_file){return false;}
		virtual bool clearRootFile(Note a_file){return false;}

		virtual bool fastWriteText(Note a_text, Note a_file){return this->writeText(a_text, a_file);}
		virtual bool writeText(Note a_text, Note a_file){return false;}
		virtual bool writeRootText(Note a_text, Note a_file){return false;}

		virtual bool fastWriteLine(Note a_text, Note a_file){return this->writeLine(a_text, a_file);}
		virtual bool writeLine(Note a_text, Note a_file){
			bool ir_text = this->writeText(a_text, a_file);
			bool ir_enter = this->writeText("\n", a_file);
			return ir_text && ir_enter;
		}
		virtual bool writeRootLine(Note a_text, Note a_file){
			bool ir_text = this->writeRootText(a_text, a_file);
			bool ir_enter = this->writeRootText("\n", a_file);
			return ir_text && ir_enter;
		}

		virtual bool fastInsertLine(int a_line, Note a_text, Note a_file){return this->insertLine(a_line, a_text, a_file);}
		virtual bool insertLine(int a_line, Note a_text, Note a_file){
			MonkeyFileLog(ame_Log_StartMethod, "insertLine",  "println", "");
			Note i_text = this->readText(a_file);
			MonkeyFileLog(ame_Log_Statement, "insertLine",  "println", "i_text: ");
			MonkeyFileLog(ame_Log_Statement, "insertLine",  "println", i_text);
			if(i_text.isEmpty() || a_line < 0){
				MonkeyFileLog(ame_Log_Statement, "insertLine",  "println", "false");
				return false;
			}
			int i_index = 0;
			if(a_line == 0){
				Note i_new_text = i_text.addValue('\n');
				i_text.insertLocalNote(0, i_new_text);
				MonkeyFileLog(ame_Log_Statement, "insertLine",  "println", "i_new_text: ");
				MonkeyFileLog(ame_Log_Statement, "insertLine",  "println", i_new_text);
				MonkeyFileLog(ame_Log_Statement, "insertLine",  "println", "i_text: ");
				MonkeyFileLog(ame_Log_Statement, "insertLine",  "println", i_text);
				this->clearFile(a_file);
				this->writeText(i_text, a_file);
				MonkeyFileLog(ame_Log_EndMethod, "insertLine",  "println", "true");
				return true;
			}
			i_index = i_text.getIndex(a_line - 1, "\n");
			MonkeyFileLog(ame_Log_Statement, "insertLine",  "println", "i_index: ");
			MonkeyFileLog(ame_Log_Statement, "insertLine",  "println", i_index);
			if(i_index == -1){
				MonkeyFileLog(ame_Log_Statement, "insertLine",  "println", "false");
				return false;
			}
			Note i_new_text = i_text.addValue('\n');
			i_text.insertLocalNote(i_index + 1, i_new_text);
			MonkeyFileLog(ame_Log_Statement, "insertLine",  "println", "i_new_text: ");
			MonkeyFileLog(ame_Log_Statement, "insertLine",  "println", i_new_text);
			MonkeyFileLog(ame_Log_Statement, "insertLine",  "println", "i_text: ");
			MonkeyFileLog(ame_Log_Statement, "insertLine",  "println", i_text);
			this->clearFile(a_file);
			this->writeText(i_text, a_file);
			MonkeyFileLog(ame_Log_EndMethod, "insertLine",  "println", "true");
			return true;
		}

		virtual bool insertRootLine(int a_line, Note a_text, Note a_file){
			Note i_file = this->fixRootPath(a_file);
			Note i_text = this->readText(i_file);
			if(i_text.isEmpty()){
				return false;
			}
			int i_index = i_text.getIndex(a_line, "\n");
			if(i_index == -1){
				return false;
			}
			Note i_new_text = i_text.addValue('\n');
			i_text.insertLocalNote(i_index + 1, i_new_text);
			this->clearFile(i_file);
			this->writeText(i_text, i_file);
			return true;
		}

		virtual Note fastReadText(Note a_file){return this->readText(a_file);}
		virtual Note readText(Note a_file){return "";}
		virtual Note readRootText(Note a_file){return "";}

		virtual Note fastReadSizedText(int a_size, Note a_file){return this->readSizedText(a_size, a_file);}
		virtual Note readSizedText(int a_size, Note a_file){return "";}
		virtual Note readRootSizedText(int a_size, Note a_file){return "";}

		virtual PrimitiveList<Note> fastReadLines(Note a_file){return this->readLines(a_file);}
		virtual PrimitiveList<Note> readLines(Note a_file){return PrimitiveList<Note>();}
		virtual PrimitiveList<Note> readRootLines(Note a_file){return PrimitiveList<Note>();}

		virtual PrimitiveList<Note> fastReadSizedLines(int a_size, Note a_file){return this->readLines(a_file);}
		virtual PrimitiveList<Note> readSizedLines(int a_size, Note a_file){return PrimitiveList<Note>();}
		virtual PrimitiveList<Note> readRootSizedLines(int a_size, Note a_file){return PrimitiveList<Note>();}

		virtual Note fastReadLine(int a_line, Note a_file){return this->readLine(a_line, a_file);}
		virtual Note readLine(int a_line, Note a_file){return "";}
		virtual Note readRootLine(int a_line, Note a_file){return "";}

		virtual bool writeByteArray(ByteArray array, Note a_file){return false;}
		virtual bool writeRootByteArray(ByteArray text, Note a_file){return false;}

		virtual ByteArray readByteArray(Note a_file){return ByteArray();}
		virtual ByteArray readRootByteArray(Note a_file){return ByteArray();}

		virtual bool exist(Note a_file){return false;}
		virtual bool existRoot(Note a_file){return false;}

		template<class... Args>
		bool existPath(const Note& a_root_hdd, Args... a_paths){
			Note i_path = this->fixFullPaths(a_root_hdd, a_paths...);
			return this->exist(i_path);
		}
		
		template<class... Args>
		bool existRootPath(Args... a_paths){
			Note i_path = this->fixRootPaths(a_paths...);
			return this->exist(i_path);
		}
		
		template<class... Args>
		Note fixPaths(Args... a_paths){
			MonkeyFileLog(ame_Log_StartMethod, "fixPaths",  "println", "");
			PrimitiveList<Note> i_list;
			i_list.addPack(a_paths...);
			Note i_path;
			for(int x = 0; x < i_list.getPosition(); x++){
				Note* f_path = i_list.getByPosition(x);
				if(f_path == nullptr){
					continue;
				}
				i_path = this->mixPath(i_path, *f_path);
				MonkeyFileLog(ame_Log_Statement, "fixPaths",  "println", "i_path: ");
				MonkeyFileLog(ame_Log_Statement, "fixPaths",  "println", i_path);
			}
			MonkeyFileLog(ame_Log_EndMethod, "fixPaths",  "println", "");
			return i_path;
		}
		
		template<class... Args>
		Note fixFullPaths(const Note& a_root_hdd, Args... a_paths){
			MonkeyFileLog(ame_Log_StartMethod, "fixFullPaths",  "println", "");
			PrimitiveList<Note> i_list;
			i_list.addPack(a_paths...);
			Note i_path = a_root_hdd;
			for(int x = 0; x < i_list.getPosition(); x++){
				Note* f_path = i_list.getByPosition(x);
				if(f_path == nullptr){
					continue;
				}
				i_path = this->mixRootPath(i_path, *f_path);
				MonkeyFileLog(ame_Log_Statement, "fixFullPaths",  "println", "i_path: ");
				MonkeyFileLog(ame_Log_Statement, "fixFullPaths",  "println", i_path);
			}
			MonkeyFileLog(ame_Log_EndMethod, "fixFullPaths",  "println", "");
			return i_path;
		}

		template<class... Args>
		Note fixRootPaths(Args... a_paths){
			PrimitiveList<Note> i_list;
			i_list.addPack(a_paths...);
			Note i_path = this->m_rootPath;
			for(int x = 0; x < i_list.getPosition(); x++){
				Note* f_path = i_list.getByPosition(x);
				if(f_path == nullptr){
					continue;
				}
				i_path = this->mixRootPath(i_path, *f_path);
			}
			return i_path;
		}
		
		virtual Note fixPath(Note a_path);
		virtual Note mixPath(Note a_path_1, Note a_path_2);

		virtual Note fixRootPath(Note a_path);
		virtual Note mixRootPath(Note a_path_1, Note a_path_2);

		virtual int getFileSize(Note path){return 0;}
		virtual int getDirectoriesSize(Note path){return 0;}

		virtual PrimitiveMap<Note,Note> getDirectories(Note dirname, int levels){
			return PrimitiveMap<Note,Note>();
		}
			
		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){
			return Class<MonkeyFile>::getClass();
		}
		
		virtual bool instanceof(cppObjectClass* cls){
			return cls == Class<MonkeyFile>::getClass();
		}
		#endif

	protected:
		Note m_root_hdd;
		Note m_rootPath;
		bool m_open = false;
};

//add a / before the text
Note MonkeyFile::fixPath(Note a_path){
	MonkeyFileLog(ame_Log_StartMethod, "fixPath",  "println", "");
	if(a_path.length() == 0){
		MonkeyFileLog(ame_Log_EndMethod, "fixPath",  "println", "");
		return "";
	}
	if(a_path[0] == '/'){
		MonkeyFileLog(ame_Log_EndMethod, "fixPath",  "println", "");
		return a_path;
	}
	MonkeyFileLog(ame_Log_EndMethod, "fixPath",  "println", "");
	return Note("/") + a_path;
}

//add a / before the text and in between the 2 paths
Note MonkeyFile::mixPath(Note a_path_1, Note a_path_2){
	MonkeyFileLog(ame_Log_StartMethod, "mixPath",  "println", "");
	if(a_path_1.length() == 0){
		MonkeyFileLog(ame_Log_EndMethod, "mixPath",  "println", "");
		return this->fixPath(a_path_2);
	}
	if(a_path_2.length() == 0){
		MonkeyFileLog(ame_Log_EndMethod, "mixPath",  "println", "");
		return this->fixPath(a_path_1);
	}
	if(a_path_1[0] != '/'){
		MonkeyFileLog(ame_Log_Statement, "mixPath",  "println", Note("a_path_1[0] != '/'"));
		a_path_1 = Note("/") + a_path_1;
	}
	int sizeRP = a_path_1.length();
	if(a_path_1[sizeRP - 1] == '/' && a_path_2[0] == '/'){
		MonkeyFileLog(ame_Log_Statement, "mixPath",  "println", "a_path_1[sizeRP - 1] == '/' && a_path_2[0] == '/'");
		MonkeyFileLog(ame_Log_EndMethod, "mixPath",  "println", "");
		return a_path_1 + getNotePart(a_path_2, 1);
	}
	if(a_path_1[sizeRP - 1] != '/' && a_path_2[0] == '/'){
		MonkeyFileLog(ame_Log_Statement, "mixPath",  "println", "a_path_1[sizeRP - 1] != '/' && a_path_2[0] == '/'");
		MonkeyFileLog(ame_Log_EndMethod, "mixPath",  "println", "");
		return a_path_1 + a_path_2;
	}
	if(a_path_1[sizeRP - 1] == '/' && a_path_2[0] != '/'){
		MonkeyFileLog(ame_Log_Statement, "mixPath",  "println", "a_path_1[sizeRP - 1] == '/' && a_path_2[0] != '/'");
		MonkeyFileLog(ame_Log_EndMethod, "mixPath",  "println", "");
		return a_path_1 + a_path_2;
	}
	if(a_path_1[sizeRP - 1] != '/' && a_path_2[0] != '/'){
		MonkeyFileLog(ame_Log_Statement, "mixPath",  "println", "a_path_1[sizeRP - 1] != '/' && a_path_2[0] != '/'");
		MonkeyFileLog(ame_Log_EndMethod, "mixPath",  "println", "");
		return a_path_1 + Note('/') + a_path_2;
	}
	MonkeyFileLog(ame_Log_EndMethod, "mixPath",  "println", "");
	return a_path_1 + a_path_2;
}

Note MonkeyFile::fixRootPath(Note a_path){
	MonkeyFileLog(ame_Log_StartMethod, "fixRootPath",  "println", "");
	MonkeyFileLog(ame_Log_EndMethod, "fixRootPath",  "println", "");
	return this->mixRootPath( this->m_rootPath, a_path );
}

Note MonkeyFile::mixRootPath(Note a_path_1, Note a_path_2){
	MonkeyFileLog(ame_Log_StartMethod, "mixRootPath",  "println", "");
	if(a_path_1.length() == 0 || a_path_2.length() == 0){
		MonkeyFileLog(ame_Log_EndMethod, "mixRootPath",  "println", "");
		return "";
	}
	int sizeRP = a_path_1.length();
	if(a_path_1[sizeRP - 1] == '/' && a_path_2[0] == '/'){
		MonkeyFileLog(ame_Log_Statement, "mixRootPath",  "println", "a_path_1[sizeRP - 1] == '/' && a_path_2[0] == '/'");
		MonkeyFileLog(ame_Log_EndMethod, "mixRootPath",  "println", "");
		return a_path_1 + getNotePart(a_path_2, 1);
	}
	if(a_path_1[sizeRP - 1] != '/' && a_path_2[0] == '/'){
		MonkeyFileLog(ame_Log_Statement, "mixRootPath",  "println", "a_path_1[sizeRP - 1] != '/' && a_path_2[0] == '/'");
		MonkeyFileLog(ame_Log_EndMethod, "mixRootPath",  "println", "");
		return a_path_1 + a_path_2;
	}
	if(a_path_1[sizeRP - 1] == '/' && a_path_2[0] != '/'){
		MonkeyFileLog(ame_Log_Statement, "mixRootPath",  "println", "a_path_1[sizeRP - 1] == '/' && a_path_2[0] != '/'");
		MonkeyFileLog(ame_Log_EndMethod, "mixRootPath",  "println", "");
		return a_path_1 + a_path_2;
	}
	if(a_path_1[sizeRP - 1] != '/' && a_path_2[0] != '/'){
		MonkeyFileLog(ame_Log_Statement, "mixRootPath",  "println", "a_path_1[sizeRP - 1] != '/' && a_path_2[0] != '/'");
		MonkeyFileLog(ame_Log_EndMethod, "mixRootPath",  "println", "");
		return a_path_1 + Note('/') + a_path_2;
	}
	MonkeyFileLog(ame_Log_EndMethod, "mixRootPath",  "println", "");
	return a_path_1 + a_path_2;
}

}

#endif