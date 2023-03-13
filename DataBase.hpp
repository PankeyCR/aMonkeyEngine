
#ifndef DataBase_hpp
#define DataBase_hpp
#define DataBase_AVAILABLE

#include "MonkeyFile.hpp"
#include "MonkeyExporter.hpp"
#include "MonkeyImporter.hpp"

#ifdef DataBase_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"

	#define DataBaseLog(location,method,type,mns) ame_Log((void*)this,location,"DataBase",method,type,mns)
#else
	#ifdef DataBase_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"

		#define DataBaseLog(location,method,type,mns) ame_LogDebug((void*)this,location,"DataBase",method,type)
	#else
		#define DataBaseLog(location,method,type,mns)
	#endif
#endif

namespace ame{

class DataBase{
    public:
		virtual ~DataBase(){}
		virtual void initialize(MonkeyExporter* exporter, MonkeyImporter* importer, MonkeyFile* file){}
		virtual void put(MonkeyExporter* exporter, MonkeyImporter* importer, MonkeyFile* file){}
		virtual void get(MonkeyExporter* exporter, MonkeyImporter* importer, MonkeyFile* file){}
		virtual void erase(MonkeyExporter* exporter, MonkeyImporter* importer, MonkeyFile* file){}
		virtual void copy(MonkeyExporter* exporter, MonkeyImporter* importer, MonkeyFile* file){}
		virtual void cut(MonkeyExporter* exporter, MonkeyImporter* importer, MonkeyFile* file){}
		virtual void update(float tpc){}
		
		virtual void operator=(DataBase db){}
		virtual bool operator==(DataBase db){return false;}
		virtual bool operator!=(DataBase db){return false;}
};

}

#endif