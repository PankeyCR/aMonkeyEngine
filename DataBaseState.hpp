
/*  
 *  DataBase.command
 *  1. put
 *  2. get
 *  3. delete
 *  4. copy
 *  4. cut
 *  
 *  DataBase.type
 *  1. object
 *  2. file
 *  3. 
 *  4. 
 *  5. 
 *
 */

#ifndef DataBaseState_hpp
#define DataBaseState_hpp
#define DataBaseState_AVAILABLE

#include "ame_Enviroment.hpp"

#ifdef ame_Windows
	#include "WindowsFile.hpp"
#endif

#ifdef ame_ArduinoIDE
	#include "ArduinoSDFile.hpp"
#endif

#include "Command.hpp"
#include "DataBase.hpp"
#include "ElementId.hpp"
#include "BaseAppState.hpp"
#include "MonkeyExporter.hpp"
#include "MonkeyImporter.hpp"
#include "TextExporter.hpp"
#include "TextImporter.hpp"
#include "PrimitiveList.hpp"

#ifdef DataBaseState_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"

	#define DataBaseStateLog(location,method,type,mns) ame_Log(this,location,"DataBaseState",method,type,mns)
#else
	#ifdef DataBaseState_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"

		#define DataBaseStateLog(location,method,type,mns) ame_LogDebug((void*)this,location,"DataBaseState",method,type)
	#else
		#define DataBaseStateLog(location,method,type,mns)
	#endif
#endif

namespace ame{

class DataBaseState : public BaseAppState{
    public:
		DataBaseState(){
			DataBaseStateLog(ame_Log_Statement, "Constructor",  "println", "");
			m_owner = true;
			m_exporter = new TextExporter();
			m_importer = new TextImporter();

			#ifdef ame_Windows
				m_file = new WindowsFile();
			#endif

			#ifdef ame_ArduinoIDE
				m_file = new ArduinoSDFile<SDFileSystemClass>(SD);
			#endif
			
		}
		DataBaseState(MonkeyFile* f){
			DataBaseStateLog(ame_Log_Statement, "Constructor",  "println", "");
			owner = true;
			exporter = new TextExporter();
			importer = new TextImporter();
			file = f;
		}
		
		DataBaseState(MonkeyExporter* e, MonkeyImporter* i, bool o){
			DataBaseStateLog(ame_Log_Statement, "Constructor",  "println", "");
			owner = o;
			exporter = e;
			importer = i;
		}
		
		DataBaseState(MonkeyExporter* e, MonkeyImporter* i, MonkeyFile* f, bool o){
			DataBaseStateLog(ame_Log_Statement, "Constructor",  "println", "");
			owner = o;
			exporter = e;
			importer = i;
			file = f;
		}
		
		virtual ~DataBaseState(){
			DataBaseStateLog(ame_Log_Statement, "Destructor",  "println", "");
			if(owner){
				delete exporter;
				delete importer;
				if(file != nullptr){
					delete file;
				}
			}
		}
		
		virtual bool instanceof(cppObjectClass* cls){
			return cls == Class<DataBaseState>::classType || AppState::instanceof(cls);
		}
		
		virtual cppObjectClass* getClass(){return Class<DataBaseState>::classType;}
		
		virtual void initialize(Application *app){
			DataBaseStateLog(ame_Log_Statement, "initialize",  "println", "start");
			AppState* m_state = app->getStateManager()->get(Class<SerialMessageState>::classType);
			if(m_state == nullptr){
				return;
			}
			serialState = (SerialMessageState*)m_state;
			serialState->addListener(this);
			for(int x = 0; x< configuration.getPosition(); x++){
				DataBaseConfig* c = configuration.getByPosition(x);
				c->initialize(exporter, importer, file, serialState);
			}
			DataBaseStateLog(ame_Log_Statement, "initialize",  "println", "end");
			if(file == nullptr){
				return;
			}
			file->initialize();
		}
		
		virtual void execute(Message* message){
			DataBaseStateLog(ame_Log_Statement, "execute",  "println", "start execute");
			if(file == nullptr || serialState == nullptr || exporter == nullptr || importer == nullptr){
				DataBaseStateLog(ame_Log_Statement, "execute",  "println", "file == nullptr || serialState == nullptr || exporter == nullptr || importer == nullptr");
			}
			if(exporter == nullptr || importer == nullptr){
				return;
			}
			DataBaseStateLog(ame_Log_Statement, "execute",  "println", message->text());
			importer->setMessage(message);
			// DataBaseStateLog(ame_Log_Statement, "execute",  "println", importer->toNote());
			
			Note command = importer->getTag(ElementId("DataBase.command"));
			Note type = importer->getTag(ElementId("DataBase.type"));
			
			importer->removeTag(ElementId("DataBase.command"));
			importer->removeTag(ElementId("DataBase.type"));
			
			DataBaseConfig* config = configuration.getByLValue(type);
			
			if(config == nullptr || command == ""){
				DataBaseStateLog(ame_Log_Statement, "execute",  "println", "config == nullptr || command.isEmpty");
				exporter->clear();
				importer->clear();
				return;
			}
			
			if(command == "put"){
				DataBaseStateLog(ame_Log_Statement, "execute",  "println", "command == put");
				exporter->clear();
				config->put(exporter,importer,file,serialState);
			}
			
			if(command == "get"){
				DataBaseStateLog(ame_Log_Statement, "execute",  "println", "command == get");
				exporter->clear();
				config->get(exporter,importer,file,serialState);
			}
			
			if(command == "delete"){
				DataBaseStateLog(ame_Log_Statement, "execute",  "println", "command == delete");
				exporter->clear();
				config->erase(exporter,importer,file,serialState);
			}
			
			if(command == "copy"){
				DataBaseStateLog(ame_Log_Statement, "execute",  "println", "command == copy");
				exporter->clear();
				config->copy(exporter,importer,file,serialState);
			}
			
			if(command == "cut"){
				DataBaseStateLog(ame_Log_Statement, "execute",  "println", "command == cut");
				exporter->clear();
				config->cut(exporter,importer,file,serialState);
			}
			
			exporter->clear();
			importer->clear();
		}
		
		virtual void update(float tpc){
			if(serialState == nullptr){
				return;
			}
			for(int x = 0; x < configuration.getPosition(); x++){
				DataBaseConfig* config = configuration.getByPosition(x);
				config->update(tpc);
			}
		}
		
		virtual DataBaseConfig* addDataBaseConfig(Note name, DataBaseConfig* c){
			configuration.addPointer(name, c);
			if(init){
				c->initialize(exporter, importer, file, serialState);
			}
			return c;
		}
	protected:
		MonkeyExporter* m_exporter = nullptr;
		MonkeyImporter* m_importer = nullptr;
		
		MonkeyFile* m_file = nullptr;
		
		PrimitiveMap<Note,DataBase> m_database_map;
		
		bool m_owner = false;
};

}

#endif