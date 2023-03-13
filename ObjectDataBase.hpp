/*	
**	DataBase.project.name
**	DataBase.project.dir
**	DataBase.project.id
**	
**	
**	Layers: 3
**	
**	Layer 1:
**	ask for project name, if there is not, search on the greenFile
**	
**	
*/	

#ifndef ObjectDataBase_hpp
#define ObjectDataBase_hpp
#define ObjectDataBase_AVAILABLE

#include "DataBase.hpp"
#include "MonkeyFile.hpp"
#include "MonkeyExporter.hpp"
#include "MonkeyImporter.hpp"
#include "TextExporter.hpp"
#include "TextImporter.hpp"
#include "MemoryRam.hpp"

#ifdef ObjectDataBase_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"

	#define ObjectDataBaseLog(location,method,type,mns) ame_Log(this,location,"ObjectDataBase",method,type,mns)
#else
	#ifdef ObjectDataBase_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"

		#define ObjectDataBaseLog(location,method,type,mns) ame_LogDebug((void*)this,location,"ObjectDataBase",method,type)
	#else
		#define ObjectDataBaseLog(location,method,type,mns)
	#endif
#endif

namespace ame{

class ObjectDataBase : public DataBase{
    public:
		ObjectDataBase(){}
		virtual ~ObjectDataBase(){}
		
		virtual void initialize(MonkeyExporter* exporter, MonkeyImporter* importer, MonkeyFile* file){
			if(file == nullptr || exporter == nullptr || importer == nullptr){
				return;
			}
			ObjectDataBaseLog(ame_Log_Statement, "initialize", "println", "");
			Note i_root_dir = file->fixPath(m_rootDir);
			Note i_tag_path = file->fixPath(m_rootPath, m_tagPath);
			if(!file->exist(m_rootDir)){
				file->createDir(m_rootDir);
			}
			if(!file->existPath(m_rootDir, m_tagPath)){
				file->createFilePath(m_rootDir, m_tagPath);
			}
			ObjectDataBaseLog(ame_Log_Statement, "initialize", "println", "");
		}
		
		virtual void put(MonkeyExporter* exporter, MonkeyImporter* importer, MonkeyFile* file){
			if(file == nullptr || exporter == nullptr || importer == nullptr){
				return;
			}
			ObjectDataBaseLog(ame_Log_Statement, "put", "println", "");
			
			Note project_dir = importer->getTag("DataBase.project");
			
			
			ObjectDataBaseLog(ame_Log_Statement, "put",  "println", "");
		}
			
		virtual void get(MonkeyExporter* exporter, MonkeyImporter* importer, MonkeyFile* file){
			if(file == nullptr || exporter == nullptr || importer == nullptr){
				return;
			}
			ObjectDataBaseLog(ame_Log_Statement, "get",  "println", "");
			
			Note project_dir = importer->getTag("DataBase.project");
			if(project_dir == ""){
				return;
			}
			importer->removeTag("DataBase.project");
			
			Note project_folder_path = file->fixPath(m_rootDir, project_dir);
			Note project_folder_tag_path = file->fixPath(project_folder_path, m_tagPath);
			Note project_folder_helper_path = file->fixPath(project_folder_path, helperPath);
			
			if(!file->exist(project_folder_path)){
				ObjectDataBaseLog(ame_Log_Statement, "put", "println", "!file->exist(project_folder_path)");
				// ObjectDataBaseLog(ame_Log_Statement, "put", "println", Note("project_folder_path ") + project_folder_path);
				return;
			}
			
			Note folder_dir = importer->getTag("DataBase.dir");
			
			if(folder_dir == ""){
				ObjectDataBaseLog(ame_Log_Statement, "put",  "println", "folder_dir.isEmpty");
				return;
			}
			
			ElementId id = importer->getTag("DataBase.id");
			
			if(id == ""){
				ObjectDataBaseLog(ame_Log_Statement, "get",  "println", "id.isEmpty");
				return;
			}
			
			importer->removeTag("DataBase.id");
			
			Note objMap_path = file->fixPath(folder_dir, idRegisterPath);
			
			TextImporter textImporter = file->fastReadText(objMap_path);
			Note idPath = textImporter.read(id, "");
			
			if(idPath == ""){
				ObjectDataBaseLog(ame_Log_Statement, "get",  "println", "path.isEmpty");
				return;
			}
			// ObjectDataBaseLog(ame_Log_Statement, "get",  "println", Note("idPath ") + Note(idPath));
			
			Note port = importer->getTag("DataBase.port");
			Note idText = file->fastReadText(idPath);
			
			if(port == ""){
				ObjectDataBaseLog(ame_Log_Statement, "get",  "println", "broadcast");
				serialState->send(idText);
			}else{
				ObjectDataBaseLog(ame_Log_Statement, "get",  "println", "not broadcast");
				importer->removeTag("DataBase.port");
				serialState->send(port.toInt(), idText);
			}
			// ObjectDataBaseLog(ame_Log_Statement, "get",  "println", Note("sending ") + objTextImporter.getText());
			// exporter->clear();
			// exporter->read(file, idPath);
		}
			 
		virtual void erase(MonkeyExporter* exporter, MonkeyImporter* importer, MonkeyFile* file){
			if(file == nullptr || exporter == nullptr || importer == nullptr){
				return;
			}
			Note all = importer->read("DataBase.All", "");
			
			Note m_rootPath = file->fixPath(m_rootDir);
			Note path = file->fixPath(m_rootPath, m_tagPath);
			
			if(all != ""){
				ObjectDataBaseLog(ame_Log_Statement, "get",  "println", "delete all");
				file->deleteFile(path);
				return;
			}
			
			ElementId id = importer->read("DataBase.id", ElementId());
			
			if(id == ""){
				ObjectDataBaseLog(ame_Log_Statement, "get",  "println", "id.isEmpty");
				return;
			}
			
			importer->remove("DataBase.id");
			
			TextImporter textImporter = file->fastReadText(path);
			Note idPath = textImporter.read(id, "");
			
			if(idPath == ""){
				return;
			}
			
			textImporter.remove(id);
			
			file->fastClearFile(path);
			file->writeText(textImporter.getText(), path);
			
			file->deleteFile(idPath);
		}
			
		virtual void copy(MonkeyExporter* exporter, MonkeyImporter* importer, MonkeyFile* file){
			if(file == nullptr || exporter == nullptr || importer == nullptr){
				return;
			}
			ElementId id = importer->read("DataBase.id", ElementId());
			
			if(id == ""){
				return;
			}
			
			importer->remove("DataBase.id");
			
			Note m_rootPath = file->fixPath(m_rootDir);
			Note path = file->fixPath(m_rootPath, m_tagPath);
			
			TextImporter textImporter = file->fastReadText(path);
			Note idPath = textImporter.read(id, "");
			Note copyPath = importer->read("DataBase.copy.path", "");
			
			if(idPath == "" || copyPath == ""){
				return;
			}
			
			Note f_1 = file->fastReadText(idPath);
			file->writeText(f_1, copyPath);
		}
			
		virtual void cut(MonkeyExporter* exporter, MonkeyImporter* importer, MonkeyFile* file){
			if(file == nullptr || exporter == nullptr || importer == nullptr){
				return;
			}
			ElementId id = importer->read("DataBase.id", ElementId());
			
			if(id == ""){
				return;
			}
			
			importer->remove("DataBase.id");
			
			Note m_rootPath = file->fixPath(m_rootDir);
			Note path = file->fixPath(m_rootPath, m_tagPath);
			
			TextImporter textImporter = file->fastReadText(path);
			Note idPath = textImporter.read(id, "");
			Note copyPath = importer->read("DataBase.cut.path", "");
			
			if(idPath == "" || copyPath == ""){
				return;
			}
			
			Note f_1 = file->fastReadText(idPath);
			file->writeText(f_1, copyPath);
			file->deleteFile(idPath);
		}
		
		virtual void setFileSize(int s){
			fileSize = s;
		}
		
	protected:
		Note m_rootDir = "DataBase";
		Note m_tagPath = "Tags.txt";
		Note helperPath = "Helper.txt";
		
		Note idRegisterPath = "idRegister.txt";
		
		int fileSize = 50;
		
		Note m_idName = "object";
		Note m_fileName = "object";
		Note m_folderName = "object";
};

}

#endif