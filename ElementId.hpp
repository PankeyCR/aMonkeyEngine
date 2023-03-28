
#ifndef CONFIGURATION_ElementId_hpp
#define CONFIGURATION_ElementId_hpp

	#include "ame_Enviroment.hpp"

	#if defined(DISABLE_ElementId)
		#define ElementId_hpp
	#endif
#endif

#ifndef ElementId_hpp
#define ElementId_hpp
#define ElementId_AVAILABLE

#ifdef ame_ArduinoIDE
	#include "Arduino.h"
	#include "Printable.h"
#endif

#include "cppObject.hpp"
#include "Note.hpp"
#include "NoteHelper.hpp"
#include "Class.hpp"

#ifdef ElementId_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"

	#define ElementIdLog(location,method,type,mns) ame_Log(this,location,"ElementId",method,type,mns)
	#define const_ElementIdLog(location,method,type,mns)
#else
	#ifdef ElementId_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"

		#define ElementIdLog(location,method,type,mns) ame_LogDebug(this,location,"ElementId",method,type)
		#define const_ElementIdLog(location,method,type,mns)
	#else
		#define ElementIdLog(location,method,type,mns)
		#define const_ElementIdLog(location,method,type,mns)
	#endif
#endif

namespace ame{

class ElementId : public Printable IMPLEMENTING_cppObject {
	public:
		ElementId(){
			ElementIdLog(ame_Log_StartMethod, "Contructor 1",  "println", Note("id ") + id);
			ElementIdLog(ame_Log_StartMethod, "Contructor 1",  "println", Note("delimiter ") + m_delimiter);
		}
		
		ElementId(const char* i){
			id = i;
			ElementIdLog(ame_Log_StartMethod, "Contructor 2",  "println", Note("id ") + id);
			ElementIdLog(ame_Log_StartMethod, "Contructor 2",  "println", Note("delimiter ") + m_delimiter);
		}
		
		ElementId(const Note& i){
			id = i;
			ElementIdLog(ame_Log_StartMethod, "Contructor 3",  "println", Note("id ") + id);
			ElementIdLog(ame_Log_StartMethod, "Contructor 3",  "println", Note("delimiter ") + m_delimiter);
		}
		
		ElementId(const char* i, const char* i2){
			id = i;
			m_delimiter = i2;
			ElementIdLog(ame_Log_StartMethod, "Contructor 4",  "println", Note("id ") + id);
			ElementIdLog(ame_Log_StartMethod, "Contructor 4",  "println", Note("delimiter ") + m_delimiter);
		}
		
		ElementId(const Note& i, const Note& i2){
			id = i;
			m_delimiter = i2;
			ElementIdLog(ame_Log_StartMethod, "Contructor 5",  "println", Note("id ") + id);
			ElementIdLog(ame_Log_StartMethod, "Contructor 5",  "println", Note("delimiter ") + m_delimiter);
		}
		
		virtual ~ElementId(){
			ElementIdLog(ame_Log_StartMethod, "Destructor",  "println", "");
		}
		
		ElementId child(const char* childId){
			ElementIdLog(ame_Log_StartMethod, "child",  "println", Note(childId));
			if(isNoteEmpty(id)){
				return ElementId(childId);
			}
			return ElementId(id + m_delimiter + Note(childId));
		}
		
		ElementId child(const Note& childId){
			ElementIdLog(ame_Log_StartMethod, "child",  "println", Note(childId));
			if(isNoteEmpty(id)){
				return ElementId(childId);
			}
			return ElementId(id + m_delimiter + childId);
		}

		ElementId child(const ElementId& childId) {
			ElementIdLog(ame_Log_StartMethod, "child",  "println", childId.getId());
			if(isNoteEmpty(id)){
				return ElementId(childId.getId());
			}
			return ElementId(id + m_delimiter + childId.getId());
		}
		
		virtual void setId(Note i){
			ElementIdLog(ame_Log_StartMethod, "setId",  "println", i);
			id = i;
		}
		
		virtual Note getId()const{
			return id;
		}
		
		virtual Note getPart(int x)const{
			const_ElementIdLog(ame_Log_StartMethod, "getPart",  "println", "");
			Note part = "";
			int delimiter = 0;
			int delimiterSize = m_delimiter.length();
			int delimiterEqual = 0;
			bool startConcat = false;
			const_ElementIdLog(ame_Log_StartMethod, "getPart",  "println", Note("id.length() ") + Note(id.length()));
			for(int i=0; i < id.length(); i++){
				char c = getChar(id, i);
				char c2 = getChar(m_delimiter, delimiterEqual);
				const_ElementIdLog(ame_Log_StartMethod, "getPart",  "println", Note("iteration ") + Note(i));
				const_ElementIdLog(ame_Log_StartMethod, "getPart",  "println", Note("char ") + Note(c));
				const_ElementIdLog(ame_Log_StartMethod, "getPart",  "println", Note("char delimiter ") + Note(c2));
				if(c == c2){
					const_ElementIdLog(ame_Log_StartMethod, "getPart",  "println", "c == c2");
					delimiterEqual++;
					if(delimiterEqual == delimiterSize){
						const_ElementIdLog(ame_Log_StartMethod, "getPart",  "println", "delimiterEqual == delimiterSize");
						delimiter++;
						delimiterEqual = 0;
					}
					continue;
				}else{
					const_ElementIdLog(ame_Log_StartMethod, "getPart",  "println", "else delimiterEqual = 0");
					delimiterEqual = 0;
				}
				if((x == delimiter)){
					const_ElementIdLog(ame_Log_StartMethod, "getPart",  "println", "x == delimiter");
					part += c;
					startConcat = true;
				}
				if((x != delimiter) && startConcat){
					return part;
				}
			}
			const_ElementIdLog(ame_Log_StartMethod, "getPart",  "println", "");
			return part;
		}
		
		virtual int getSize()const{
			int delimiter = 1;
			int delimiterSize = m_delimiter.length();
			int delimiterEqual = 0;
			for(int i=0; i < id.length(); i++){
				char c = getChar(id, i);
				if(c == getChar(m_delimiter, delimiterEqual)){                   
					delimiterEqual++;
					if(delimiterEqual == delimiterSize){
						delimiter++;
						delimiterEqual = 0;
					}
					continue;
				}else{
					delimiterEqual = 0;
				}
			}
			return delimiter;
		}
		
		virtual bool containParent(ElementId m_parent){
			ElementIdLog(ame_Log_StartMethod, "containParent",  "println", "");
			int sizeParent = m_parent.getSize();
			int sizeChild = getSize();
			if(sizeParent >= sizeChild){
				return false;
			}
			for(int x = 0; x < sizeParent; x++){
				if(m_parent.getPart(x) != getPart(x)){
					return false;
				}
			}
			return true;
		}
		
		virtual bool containChild(ElementId m_child){
			ElementIdLog(ame_Log_StartMethod, "containChild",  "println", "");
			int sizeParent = getSize();
			int sizeChild = m_child.getSize();
			if(sizeParent >= sizeChild){
				return false;
			}
			for(int x = 0; x < sizeParent; x++){
				if(m_child.getPart(x) != getPart(x)){
					return false;
				}
			}
			return true;
		}
		
		virtual bool hasPart(Note s){
			ElementIdLog(ame_Log_StartMethod, "hasPart",  "println", "");
			int sizeOriginal = getSize();
			for(int x = 0; x < sizeOriginal; x++){
				if(s == getPart(x)){
					return true;
				}
			}
			return false;
		}
		
		virtual ElementId removePart(Note s){
			ElementIdLog(ame_Log_StartMethod, "removePart",  "println", "");
			Note newId = "";
			int sizeOriginal = getSize();
			for(int x = 0; x < sizeOriginal; x++){
				Note partE = getPart(x);
				if(s != partE){
					if(isNoteEmpty(newId)){
						newId = partE;
						continue;
					}
					newId += Note(".") + partE;
				}
			}
			return ElementId(newId);
		}
		
		virtual ElementId remove(ElementId nid){
			ElementIdLog(ame_Log_StartMethod, "remove",  "println", "");
			int sizeNID = nid.getSize();
			int sizeOriginal = getSize();
			if(sizeNID > sizeOriginal){
				return *this;
			}
			ElementId newId;
			int positionNID = 0;
			bool startN = false;
			for(int x = 0; x < sizeOriginal; x++){
				Note partE = getPart(x);
				Note partN = nid.getPart(positionNID);
				if(partE == partN){
					positionNID++;
					startN = true;
				}else{
					if(startN && positionNID < sizeNID){
						return *this;
					}
					newId += partE;
				}
			}
			if(newId.getSize() == sizeOriginal - sizeNID){
				return newId;
			}
			return *this;
		}
		
		virtual ElementId removeParent(){
			ElementIdLog(ame_Log_StartMethod, "removeParent",  "println", "");
			Note newId = "";
			int sizeOriginal = getSize();
			for(int x = 1; x < sizeOriginal; x++){
				Note partE = getPart(x);
				if(isNoteEmpty(newId)){
					newId = partE;
					continue;
				}
				newId += Note(".") + partE;
			}
			return ElementId(newId);
		}
		
		virtual ElementId changeDelimiter(Note n_delimiter){
			ElementIdLog(ame_Log_StartMethod, "changeDelimiter",  "println", "");
			Note newId = "";
			int sizeOriginal = getSize();
			for(int x = 0; x < sizeOriginal; x++){
				Note partE = getPart(x);
				newId += m_delimiter + partE;
			}
			return ElementId(newId, n_delimiter);
		}
		
		virtual ElementId changeDelimiterLocal(Note n_delimiter){
			ElementIdLog(ame_Log_StartMethod, "changeDelimiterLocal",  "println", "");
			Note newId = "";
			int sizeOriginal = getSize();
			for(int x = 0; x < sizeOriginal; x++){
				Note partE = getPart(x);
				if(isNoteEmpty(newId)){
					newId = partE;
				}else{
					newId += n_delimiter + partE;
				}
			}
			id = newId;
			m_delimiter = n_delimiter;
			return ElementId(newId, n_delimiter);
		}
		
		virtual void operator=(const ElementId& b){
			ElementIdLog(ame_Log_StartMethod, "operator=",  "println", "");
			id=b.id;
		}
		
		virtual void operator+=(const ElementId& b){
			ElementIdLog(ame_Log_StartMethod, "operator+=",  "println", "");
			int sizeNew = b.getSize();
			for(int x = 1; x < sizeNew; x++){
				Note partE = b.getPart(x);
				if(isNoteEmpty(id)){
					id = partE;
					continue;
				}
				id += m_delimiter + partE;
			}
		}
		
		virtual void operator+=(Note b){
			ElementIdLog(ame_Log_StartMethod, "operator+=",  "println", "");
			if(isNoteEmpty(id)){
				id = b;
				return;
			}
			id += m_delimiter + b;
		}
		
		virtual bool operator==(const ElementId& b){
			ElementIdLog(ame_Log_StartMethod, "operator==",  "println", "");
			return id == b.id;
		}
		
		virtual bool operator!=(const ElementId& b){
			ElementIdLog(ame_Log_StartMethod, "operator!=",  "println", "");
			return id != b.id;
		}
		
		virtual bool operator==(const Note& b){
			ElementIdLog(ame_Log_StartMethod, "operator==",  "println", "");
			return id == b;
		}
		
		virtual bool operator!=(const Note& b){
			ElementIdLog(ame_Log_StartMethod, "operator!=",  "println", "");
			return id != b;
		}
		
		virtual bool operator==(const char* b){
			ElementIdLog(ame_Log_StartMethod, "operator==",  "println", "");
			return id == b;
		}
		
		virtual bool operator!=(const char* b){
			ElementIdLog(ame_Log_StartMethod, "operator!=",  "println", "");
			return id != b;
		}
		
		virtual ElementId operator+(const ElementId& b){
			ElementIdLog(ame_Log_StartMethod, "operator+",  "println", "");
			return ElementId(id + b.id);
		}
		
		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){
			ElementIdLog(ame_Log_StartMethod, "getClass",  "println", "");
			return Class<ElementId>::classType;
		}
		
		virtual bool equal(cppObject *b){
			ElementIdLog(ame_Log_StartMethod, "equal",  "println", "");
			if(b == this){
				return true;
			}
			if(!b->instanceof(Class<ElementId>::classType)){
				return false;
			}
			return id == ((ElementId*)b)->id;
		}
		
		virtual bool instanceof(cppObjectClass* cls){
			ElementIdLog(ame_Log_StartMethod, "instanceof",  "println", "");
			return cls == Class<ElementId>::classType || cppObject::instanceof(cls);
		}
		#endif
	
		size_t printTo(Print& p) const{
			return p.print(id);
		}
	protected:
		Note id = "";
		Note m_delimiter = ".";
};

}

#endif