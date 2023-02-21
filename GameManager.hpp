/*
*	Component is added first to the GameObject then to the Component-Class-List
*	Component is removed first fromthe GameObject then to the Component-Class-List
*/
#ifndef CONFIGURATION_GameManager_hpp
#define CONFIGURATION_GameManager_hpp

	#include "ame_Enviroment.hpp"

	#if defined(DISABLE_GameManager)
		#define GameManager_hpp

		#define IMPLEMENTATION_GameManager
		#define IMPLEMENTING_GameManager
	#else
		#if defined(DISABLE_IMPLEMENTATION_GameManager)
			#define IMPLEMENTATION_GameManager
			#define IMPLEMENTING_GameManager
		#endif
	#endif
#endif

#ifndef GameManager_hpp
#define GameManager_hpp
#define GameManager_AVAILABLE

#ifndef DISABLE_IMPLEMENTATION_GameManager
	#define IMPLEMENTATION_GameManager IMPLEMENTATION(public GameManager)
	#define IMPLEMENTING_GameManager IMPLEMENTING(public GameManager)
#endif

#include "cppObject.hpp"
#include "BaseAppState.hpp"
#include "PrimitiveMap.hpp"
#include "PrimitiveList.hpp"

#ifdef GameManager_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"

	#define GameManagerLog(location,method,type,mns) ame_Log(this,location,"GameManager",method,type,mns)
	#define const_GameManagerLog(location,method,type,mns)
#else
	#ifdef GameManager_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"

		#define GameManagerLog(location,method,type,mns) ame_LogDebug(this,location,"GameManager",method,type)
		#define const_GameManagerLog(location,method,type,mns)
	#else
		#define GameManagerLog(location,method,type,mns)
		#define const_GameManagerLog(location,method,type,mns)
	#endif
#endif

namespace ame{

template<class ENTITY, class COMPONENT>
class GameManager IMPLEMENTATION_BaseAppState {
    public:		
		GameManager(){
			GameManagerLog(ame_Log_StartMethod, "Constructor",  "println", "");
			GameManagerLog(ame_Log_StartMethod, "Constructor",  "println", "");
		}
		virtual ~GameManager(){
			GameManagerLog(ame_Log_StartMethod, "Destructor",  "println", "");
			GameManagerLog(ame_Log_StartMethod, "Destructor",  "println", "");
		}
		
		virtual int createEntity(ENTITY* a_obj){
			GameManagerLog(ame_Log_StartMethod, "createEntity",  "println", "with parameters");
			if(a_obj == nullptr){
				GameManagerLog(ame_Log_EndMethod, "createEntity",  "println", "a_obj == nullptr");
				return -1;
			}
			GameManagerLog(ame_Log_Statement, "createEntity",  "println", Note("id ") + Note(m_game_objects.getPosition()));
			a_obj->setId(m_game_objects.getPosition());
			m_game_objects.addPointer(a_obj);
			GameManagerLog(ame_Log_EndMethod, "createEntity",  "println", "");
			return a_obj->getId();
		}
		
		virtual ENTITY* createGameObject(ENTITY* a_obj){
			GameManagerLog(ame_Log_StartMethod, "createGameObject",  "println", "with parameters");
			if(a_obj == nullptr){
				GameManagerLog(ame_Log_StartMethod, "createGameObject",  "println", "a_obj == nullptr");
				return nullptr;
			}
			GameManagerLog(ame_Log_Statement, "createGameObject",  "println", Note("id ") + Note(m_game_objects.getPosition()));
			a_obj->setId(m_game_objects.getPosition());
			m_game_objects.addPointer(a_obj);
			GameManagerLog(ame_Log_EndMethod, "createGameObject",  "println", "");
			return a_obj;
		}
		
		virtual int createEntity(){
			GameManagerLog(ame_Log_StartMethod, "createEntity",  "println", "no parameters");
			GameManagerLog(ame_Log_Statement, "createEntity",  "println", Note("id ") + Note(m_game_objects.getPosition()));
			ENTITY* i_obj = new ENTITY();
			i_obj->setId(m_game_objects.getPosition());
			m_game_objects.addPointer(i_obj);
			GameManagerLog(ame_Log_EndMethod, "createEntity",  "println", "");
			return i_obj->getId();
		}
		
		virtual ENTITY* createGameObject(){
			GameManagerLog(ame_Log_StartMethod, "createGameObject",  "println", "no parameters");
			GameManagerLog(ame_Log_StartMethod, "createGameObject",  "println", Note("id ") + Note(m_game_objects.getPosition()));
			ENTITY* i_obj = new ENTITY();
			i_obj->setId(m_game_objects.getPosition());
			m_game_objects.addPointer(i_obj);
			GameManagerLog(ame_Log_EndMethod, "createGameObject",  "println", "");
			return i_obj;
		}
		
		
		virtual void deleteEntity(int a_entity){
			GameManagerLog(ame_Log_StartMethod, "deleteEntity",  "println", Note("id ") + Note(entity));
			ENTITY* i_obj = m_game_objects.getByPosition(a_entity);
			if(i_obj == nullptr){
				GameManagerLog(ame_Log_StartMethod, "deleteEntity",  "println", "i_obj == nullptr");
				return;
			}
			PrimitiveList<COMPONENT>& i_objChilds = i_obj->getChilds();
			GameManagerLog(ame_Log_StartMethod, "deleteEntity",  "println", "start to look for the childs on the component lists");
			for(int x = 0; x < i_objChilds.getPosition(); x++){
				COMPONENT* i_child = i_objChilds.getByPosition(x);
				cppObjectClass* i_classT = i_child->getClass();
				PrimitiveList<COMPONENT>* i_list = m_components.getValueByPointer(i_classT);
				if(i_list == nullptr){
					GameManagerLog(ame_Log_StartMethod, "deleteEntity",  "println", "list == nullptr");
					continue;
				}
				GameManagerLog(ame_Log_StartMethod, "deleteEntity",  "println", "removing from the component list");
				i_list->removeByPointer(i_child);
			}
			GameManagerLog(ame_Log_StartMethod, "deleteEntity",  "println", "removing-deleting from the GameObjects list");
			m_game_objects.removeDeleteByPosition(a_entity);
			GameManagerLog(ame_Log_EndMethod, "deleteEntity",  "println", "");
		}
		
		virtual void deleteGameObject(ENTITY* a_obj){
			GameManagerLog(ame_Log_StartMethod, "deleteGameObject",  "println", "");
			if(!m_game_objects.containByPointer(a_obj)){
				GameManagerLog(ame_Log_StartMethod, "deleteGameObject",  "println", "GameObjects dont contains obj");
				return;
			}
			PrimitiveList<COMPONENT>& i_objChilds = a_obj->getChilds();
			GameManagerLog(ame_Log_StartMethod, "deleteGameObject",  "println", "start to look for the childs on the component lists");
			for(int x = 0; x < i_objChilds.getPosition(); x++){
				COMPONENT* i_child = i_objChilds.getByPosition(x);
				cppObjectClass* i_cls = i_child->getClass();
				PrimitiveList<COMPONENT>* i_list = m_components.getValueByPointer(i_cls);
				if(i_list == nullptr){
					GameManagerLog(ame_Log_StartMethod, "deleteGameObject",  "println", "list == nullptr");
					continue;
				}
				GameManagerLog(ame_Log_StartMethod, "deleteGameObject",  "println", "removing from the component list");
				i_list->removeByPointer(i_child);
			}
			GameManagerLog(ame_Log_StartMethod, "deleteGameObject",  "println", "removing-deleting from the GameObjects list");
			m_game_objects.removeDeleteByPointer(a_obj);
			GameManagerLog(ame_Log_EndMethod, "deleteEntity",  "println", "");
		}
		
		virtual void deleteAllEntities(){
			GameManagerLog(ame_Log_StartMethod, "deleteAllEntities",  "println", "");
			GameManagerLog(ame_Log_StartMethod, "deleteAllEntities",  "println", Note("total entities ") + Note(components.getPosition()));
			for(int x = 0; x < m_components.getPosition(); x++){
				List<COMPONENT>* i_childs = m_components.getValueByPosition(x);
				i_childs->reset();
			}
			m_game_objects.resetDelete();
			GameManagerLog(ame_Log_EndMethod, "deleteEntity",  "println", "");
		}
		
		
		virtual void requestDeleteEntity(int a_entity){
			GameManagerLog(ame_Log_StartMethod, "requestDeleteEntity",  "println", "adding entity to the delete request list");
			GameManagerLog(ame_Log_StartMethod, "requestDeleteEntity",  "println", Note("id ") + Note(a_entity));
			ENTITY* i_obj = m_game_objects.getByPosition(a_entity);
			if(i_obj == nullptr){
				return;
			}
			m_deleteERequest.addPointer(i_obj);
			GameManagerLog(ame_Log_EndMethod, "requestDeleteEntity",  "println", "");
		}
		
		virtual void requestDeleteGameObject(ENTITY* a_obj){
			GameManagerLog(ame_Log_StartMethod, "requestDeleteGameObject",  "println", "");
			if(!m_game_objects.containByPointer(a_obj)){
				return;
			}
			m_deleteERequest.addPointer(a_obj);
			GameManagerLog(ame_Log_EndMethod, "requestDeleteGameObject",  "println", "");
		}
		
		virtual void requestDeleteAllEntities(){
			GameManagerLog(ame_Log_StartMethod, "requestDeleteAllEntities",  "println", "");
			m_deleteAllE = true;
			GameManagerLog(ame_Log_EndMethod, "requestDeleteAllEntities",  "println", "");
		}
		
		
		virtual int getEntityByClass(cppObjectClass* a_cls){
			GameManagerLog(ame_Log_StartMethod, "getEntityByClass",  "println", "");
			for(int x = 0; x < m_game_objects.getPosition(); x++){
				ENTITY* i_obj = m_game_objects.getByPosition(x);
				if(i_obj->getClass() == a_cls){
					GameManagerLog(ame_Log_EndMethod, "getEntityByClass",  "println", "");
					return i_obj->getId();
				}
			}
			GameManagerLog(ame_Log_EndMethod, "getEntityByClass",  "println", "");
			return -1;
		}
		
		virtual ENTITY* getGameObjectByClass(cppObjectClass* a_cls){
			GameManagerLog(ame_Log_StartMethod, "getGameObjectByClass",  "println", "");
			for(int x = 0; x < m_game_objects.getPosition(); x++){
				ENTITY* i_obj = m_game_objects.getByPosition(x);
				if(i_obj->getClass() == a_cls){
					GameManagerLog(ame_Log_EndMethod, "getGameObjectByClass",  "println", "");
					return i_obj;
				}
			}
			GameManagerLog(ame_Log_EndMethod, "getGameObjectByClass",  "println", "");
			return nullptr;
		}
		
		virtual int getEntityByPointer(ENTITY* a_obj){
			GameManagerLog(ame_Log_StartMethod, "getEntityByPointer",  "println", Note(a_obj->getId()));
			if(m_game_objects.containByPointer(a_obj)){
				GameManagerLog(ame_Log_EndMethod, "getEntityByPointer",  "println", "");
				return a_obj->getId();
			}
			GameManagerLog(ame_Log_EndMethod, "getEntityByPointer",  "println", "");
			return -1;
		}
		
		virtual ENTITY* getGameObjectByPosition(int a_entity){
			GameManagerLog(ame_Log_StartMethod, "getGameObject",  "println", Note(a_entity));
			GameManagerLog(ame_Log_EndMethod, "getGameObject",  "println", "");
			return m_game_objects.getByPosition(a_entity);
		}
		
		
		virtual int getFirstEntity(){
			GameManagerLog(ame_Log_StartMethod, "getFirstEntity",  "println", "");
			int i_position = m_game_objects.getPosition();
			if(i_position <= 0){
				GameManagerLog(ame_Log_EndMethod, "getFirstEntity",  "println", "");
				return -1;
			}
			GameManagerLog(ame_Log_EndMethod, "getFirstEntity",  "println", "");
			return 0;
		}
		
		virtual ENTITY* getFirstGameObject(){
			GameManagerLog(ame_Log_StartMethod, "getFirstGameObject",  "println", "");
			int i_position = m_game_objects.getPosition();
			if(i_position <= 0){
				GameManagerLog(ame_Log_EndMethod, "getFirstGameObject",  "println", "");
				return nullptr;
			}
			GameManagerLog(ame_Log_EndMethod, "getFirstGameObject",  "println", "");
			return m_game_objects.getByPosition(0);
		}
		
		virtual int getLastEntity(){
			GameManagerLog(ame_Log_StartMethod, "getLastEntity",  "println", "");
			int i_position = m_game_objects.getPosition();
			if(i_position <= 0){
				GameManagerLog(ame_Log_EndMethod, "getLastEntity",  "println", "");
				return -1;
			}
			GameManagerLog(ame_Log_EndMethod, "getLastEntity",  "println", "");
			return i_position-1;
		}
		
		virtual ENTITY* getLastGameObject(){
			GameManagerLog(ame_Log_StartMethod, "getLastGameObject",  "println", "");
			int i_position = m_game_objects.getPosition();
			if(i_position <= 0){
				GameManagerLog(ame_Log_EndMethod, "getLastGameObject",  "println", "");
				return nullptr;
			}
			GameManagerLog(ame_Log_EndMethod, "getLastGameObject",  "println", "");
			return m_game_objects.getByPosition(i_position-1);
		}
		
		/*
		*	Adds a component to a  entity
		*/
		virtual void addComponentToEntity(int a_entity, COMPONENT* a_component){
			GameManagerLog(ame_Log_StartMethod, "addEntityComponent",  "println", "");
			ENTITY* i_obj = m_game_objects.getByPosition(a_entity);
			if(i_obj == nullptr || a_component == nullptr){
				GameManagerLog(ame_Log_StartMethod, "addEntityComponent",  "println", "no object with these entity id");
				return;
			}
			PrimitiveList<COMPONENT>* i_list = m_components.getValueByPointer(a_component->getClass());
			if(i_list == nullptr){
				GameManagerLog(ame_Log_StartMethod, "addEntityComponent",  "println", "creating list for the component class");
				i_list = new PrimitiveList<COMPONENT>();
				i_list->setOwner(false);
				m_components.addPointers(a_component->getClass(), i_list);
			}
			if(!i_list->containByPointer(a_component)){
				GameManagerLog(ame_Log_StartMethod, "addEntityComponent",  "println", "adding component to the list");
				i_list->addPointer(a_component);
			}
			PrimitiveList<COMPONENT>& i_list_childs = i_obj->getChilds();
			if(!i_list_childs.containByPointer(a_component)){
				GameManagerLog(ame_Log_StartMethod, "addEntityComponent",  "println", "adding component to the gameobject");
				i_obj->attach(a_component);
			}
			GameManagerLog(ame_Log_EndMethod, "addEntityComponent",  "println", "");
		}
		
		virtual void addComponentToGameObject(ENTITY* a_obj, COMPONENT* a_component){
			GameManagerLog(ame_Log_StartMethod, "addComponentToGameObject",  "println", "");
			if(a_obj == nullptr || a_component == nullptr){
				GameManagerLog(ame_Log_EndMethod, "addComponentToGameObject",  "println", "a_obj == nullptr || a_component == nullptr");
				return;
			}
			if(!m_game_objects.containByPointer(a_obj)){
				GameManagerLog(ame_Log_EndMethod, "addComponentToGameObject",  "println", "");
				return;
			}
			if(a_obj->getChilds().containByPointer(a_component)){
				GameManagerLog(ame_Log_EndMethod, "addComponentToGameObject",  "println", "");
				return;
			}
			a_obj->attach(a_component);
			
			PrimitiveList<COMPONENT>* i_list = m_components.getValueByPointer(a_component->getClass());
			if(i_list == nullptr){
				i_list = new PrimitiveList<COMPONENT>();
				i_list->setOwner(false);
				m_components.addPointers(a_component->getClass(), i_list);
			}
			i_list->addPointer(a_component);
			GameManagerLog(ame_Log_EndMethod, "addComponentToGameObject",  "println", "");
		}
		
		
		virtual void requestAddComponentToEntity(int a_entity, COMPONENT* a_component){
			GameManagerLog(ame_Log_StartMethod, "requestAddComponentToEntity",  "println", "");
			ENTITY* i_obj = m_game_objects.getByPosition(a_entity);
			if(i_obj == nullptr){
				GameManagerLog(ame_Log_EndMethod, "requestAddComponentToEntity",  "println", "");
				return;
			}
			m_addRequest.addPointers(i_obj, a_component);
			GameManagerLog(ame_Log_EndMethod, "requestAddComponentToEntity",  "println", "");
		}
		
		virtual void requestAddComponentToGameObject(ENTITY* a_obj, COMPONENT* a_component){
			GameManagerLog(ame_Log_StartMethod, "requestAddComponentToGameObject",  "println", "");
			if(a_obj == nullptr || a_component == nullptr){
				GameManagerLog(ame_Log_EndMethod, "containComponentByClass",  "println", "a_obj == nullptr || a_component == nullptr");
				return;
			}
			if(!m_game_objects.containByPointer(a_obj)){
				GameManagerLog(ame_Log_EndMethod, "requestAddComponentToGameObject",  "println", "!m_game_objects.containByPointer(a_obj)");
				return;
			}
			m_addRequest.addPointers(a_obj, a_component);
			GameManagerLog(ame_Log_EndMethod, "requestAddComponentToGameObject",  "println", "");
		}
		
		virtual bool containComponentByClass(cppObjectClass* a_cls){
			GameManagerLog(ame_Log_StartMethod, "containComponentByClass",  "println", "");
			if(a_cls == nullptr){
				GameManagerLog(ame_Log_EndMethod, "containComponentByClass",  "println", "");
				return false;
			}
			for(int x = 0; x < m_game_objects.getPosition(); x++){
				ENTITY* f_obj = m_game_objects.getByPosition(x);
				if(f_obj == nullptr){
					GameManagerLog(ame_Log_EndMethod, "containComponentByClass",  "println", "");
					continue;
				}
				PrimitiveList<COMPONENT>& f_objChilds = f_obj->getChilds();
				for(int y = 0; y < f_objChilds.getPosition(); y++){
					COMPONENT* ff_child = f_objChilds.getByPosition(y);
					if(ff_child == nullptr){
						GameManagerLog(ame_Log_EndMethod, "containComponentByClass",  "println", "");
						continue;
					}
					if(ff_child->getClass() == a_cls){
						GameManagerLog(ame_Log_EndMethod, "containComponentByClass",  "println", "");
						return true;
					}
				}
			}
			GameManagerLog(ame_Log_EndMethod, "containComponentByClass",  "println", "");
			return false;
		}
		
		virtual bool containEntityComponentByClass(int a_entity, cppObjectClass* a_cls){
			GameManagerLog(ame_Log_StartMethod, "containEntityComponentByClass",  "println", "");
			List<COMPONENT>* i_list = getAllComponentsFromEntity(a_entity);
			
			if(i_list == nullptr){
				GameManagerLog(ame_Log_EndMethod, "containEntityComponentByClass",  "println", "");
				return false;
			}
			
			for(int x = 0; x < i_list->getPosition(); x++){
				COMPONENT* f_child = i_list->getByPosition(x);
				if(f_child == nullptr){
					continue;
				}
				if(f_child->getClass() == a_cls){
					GameManagerLog(ame_Log_EndMethod, "containEntityComponentByClass",  "println", "");
					return true;
				}
			}
			GameManagerLog(ame_Log_EndMethod, "containEntityComponentByClass",  "println", "");
			return false;
		}
		
		template<class... s>
		bool containEntityComponentsByClass(int a_entity, s... componentClass){
			PrimitiveList<Note> i_classNs;
			i_classNs.addPack(componentClass...);
			if(i_classNs.isEmpty()){
				GameManagerLog(ame_Log_EndMethod, "containEntityComponentsByClass",  "println", "");
				return false;
			}
			for(int x = 0; x < i_classNs.getPosition(); x++){
				cppObjectClass* f_cls = i_classNs.getByPosition(x);
				if(!this->containEntityComponentByClass(a_entity, f_cls)){
					GameManagerLog(ame_Log_EndMethod, "containEntityComponentsByClass",  "println", "");
					return false;
				}
			}
			GameManagerLog(ame_Log_EndMethod, "containEntityComponentsByClass",  "println", "");
			return true;
		}
		
		virtual bool containGameObjectComponentByClass(ENTITY* a_obj, cppObjectClass* a_cls){
			GameManagerLog(ame_Log_StartMethod, "containGameObjectComponentByClass",  "println", "");
			if(a_obj == nullptr){
				GameManagerLog(ame_Log_EndMethod, "containGameObjectComponentByClass",  "println", "");
				return false;
			}
			PrimitiveList<COMPONENT>& i_list = a_obj->getChilds();
			
			for(int x = 0; x < i_list.getPosition(); x++){
				COMPONENT* f_component = i_list.getByPosition(x);
				if(f_component->getClass() == a_cls){
					GameManagerLog(ame_Log_EndMethod, "containGameObjectComponentByClass",  "println", "");
					return true;
				}
			}
			GameManagerLog(ame_Log_EndMethod, "containGameObjectComponentByClass",  "println", "");
			return false;
		}
		
		virtual bool isEmpty(){
			GameManagerLog(ame_Log_StartMethod, "isEmpty",  "println", "");
			GameManagerLog(ame_Log_EndMethod, "isEmpty",  "println", "");
			return m_game_objects.isEmpty();
		}
		
		
		virtual COMPONENT* getEntityComponentByPosition(int a_entity, int a_index){
			GameManagerLog(ame_Log_StartMethod, "getEntityComponentByPosition",  "println", "");
			ENTITY* i_obj = m_game_objects.getByPosition(a_entity);
			if(i_obj == nullptr){
				GameManagerLog(ame_Log_EndMethod, "getEntityComponentByPosition",  "println", "");
				return nullptr;
			}
			PrimitiveList<COMPONENT>& i_list = i_obj->getChilds();
			GameManagerLog(ame_Log_EndMethod, "getEntityComponentByPosition",  "println", "");
			return i_list.getByPosition(a_index);
		}
		
		virtual COMPONENT* getEntityComponentByClass(int a_entity, cppObjectClass* a_cls){
			GameManagerLog(ame_Log_StartMethod, "getEntityComponentByClass",  "println", "");
			List<COMPONENT>* i_list = this->getAllComponentsFromEntity(a_entity);
			
			if(i_list == nullptr){
				GameManagerLog(ame_Log_EndMethod, "getEntityComponentByClass",  "println", "");
				return nullptr;
			}
			
			for(int x = 0; x < i_list->getPosition(); x++){
				COMPONENT* f_child = i_list->getByPosition(x);
				if(f_child == nullptr){
					continue;
				}
				if(f_child->getClass() == a_cls){
				GameManagerLog(ame_Log_EndMethod, "getEntityComponentByClass",  "println", "");
					return f_child;
				}
			}
			GameManagerLog(ame_Log_EndMethod, "getEntityComponentByClass",  "println", "");
			return nullptr;
		}
		
		virtual COMPONENT* getGameObjectComponentByClass(ENTITY* a_obj, cppObjectClass* a_cls){
			GameManagerLog(ame_Log_StartMethod, "getGameObjectComponentByClass",  "println", "");
			if(a_obj == nullptr){
				GameManagerLog(ame_Log_EndMethod, "getGameObjectComponentByClass",  "println", "");
				return nullptr;
			}
			PrimitiveList<COMPONENT>& i_list = a_obj->getChilds();
			
			for(int x = 0; x < i_list.getPosition(); x++){
				COMPONENT* f_child = i_list.getByPosition(x);
				if(f_child == nullptr){
					continue;
				}
				if(f_child->getClass() == a_cls){
					GameManagerLog(ame_Log_EndMethod, "getGameObjectComponentByClass",  "println", "");
					return f_child;
				}
			}
			GameManagerLog(ame_Log_EndMethod, "getGameObjectComponentByClass",  "println", "");
			return nullptr;
		}

		virtual COMPONENT* getParentComponentByClass(COMPONENT* a_component, cppObjectClass* a_cls){
			GameManagerLog(ame_Log_StartMethod, "getParentComponentByClass",  "println", "");
			if(a_component == nullptr){
				GameManagerLog(ame_Log_EndMethod, "getParentComponentByClass",  "println", "");
				return nullptr;
			}
			ENTITY* i_obj = (ENTITY*)a_component->getParent();
			if(i_obj == nullptr){
				GameManagerLog(ame_Log_EndMethod, "getParentComponentByClass",  "println", "");
				return nullptr;
			}

			GameManagerLog(ame_Log_EndMethod, "getParentComponentByClass",  "println", "");
			return this->getGameObjectComponentByClass(i_obj, a_cls);
		}
		
		//returns the first component founded on the gameobjects list searched by the componentClassName
		virtual COMPONENT* getComponentByClass(cppObjectClass* a_cls){
			GameManagerLog(ame_Log_StartMethod, "getComponentByClass",  "println", "");
			for(int x = 0; x < m_game_objects.getPosition(); x++){
				ENTITY* f_obj = m_game_objects.getByPosition(x);
				if(f_obj == nullptr){
					continue;
				}
				PrimitiveList<COMPONENT>& i_list = f_obj->getChilds();
				for(int xc = 0; xc < i_list.getPosition(); xc++){
					COMPONENT* ff_objGON = i_list.getByPosition(x);
					if(ff_objGON == nullptr){
						continue;
					}
					cppObjectClass* ff_objClass = ff_objGON->getClass();
					if(ff_objClass == a_cls){
						GameManagerLog(ame_Log_EndMethod, "getComponentByClass",  "println", "");
						return ff_objGON;
					}
				}
			}
			GameManagerLog(ame_Log_EndMethod, "getComponentByClass",  "println", "");
			return nullptr;
		}
		
		//returns the first entity founded with the componentClassName 
		virtual int getEntityByComponentClass(cppObjectClass* a_cls){
			GameManagerLog(ame_Log_StartMethod, "getEntityByComponentClass",  "println", "");
			for(int x = 0; x < m_game_objects.getPosition(); x++){
				ENTITY* f_obj = m_game_objects.getByPosition(x);
				if(f_obj == nullptr){
					GameManagerLog(ame_Log_EndMethod, "getEntityByComponentClass",  "println", "");
					return -1;
				}
				PrimitiveList<COMPONENT>& i_list = f_obj->getChilds();
				for(int y = 0; y < i_list.getPosition(); y++){
					COMPONENT* ff_component = i_list.getByPosition(y);
					if(ff_component == nullptr){
						GameManagerLog(ame_Log_EndMethod, "getEntityByComponentClass",  "println", "");
						return -1;
					}
					if(ff_component->getClass() == a_cls){
						GameManagerLog(ame_Log_EndMethod, "getEntityByComponentClass",  "println", "");
						return x;
					}
				}
			}
			GameManagerLog(ame_Log_EndMethod, "getEntityByComponentClass",  "println", "");
			return -1;
		}
		
		virtual int getEntityByComponentPointer(COMPONENT* a_component){
			GameManagerLog(ame_Log_StartMethod, "getEntityByComponentPointer",  "println", "");
			for(int x = 0; x < m_game_objects.getPosition(); x++){
				ENTITY* f_obj = m_game_objects.getByPosition(x);
				if(f_obj == nullptr){
					GameManagerLog(ame_Log_EndMethod, "getEntityByComponentPointer",  "println", "");
					return -1;
				}
				PrimitiveList<COMPONENT>& i_list = f_obj->getChilds();
				for(int y = 0; y < i_list.getPosition(); y++){
					COMPONENT* ff_component = i_list.getByPosition(y);
					if(ff_component == nullptr){
						GameManagerLog(ame_Log_EndMethod, "getEntityByComponentPointer",  "println", "");
						return -1;
					}
					if(ff_component == a_component){
						GameManagerLog(ame_Log_EndMethod, "getEntityByComponentPointer",  "println", "");
						return x;
					}
				}
			}
			GameManagerLog(ame_Log_EndMethod, "getEntityByComponentPointer",  "println", "");
			return -1;
		}

		template<class... s>
		int getEntityByComponentsClass(s... a_componentClass){
			GameManagerLog(ame_Log_StartMethod, "getEntityByComponentsClass",  "println", "");
			PrimitiveList<cppObjectClass> i_classNs;
			i_classNs.addPack(a_componentClass...);
			if(i_classNs.isEmpty()){
				GameManagerLog(ame_Log_EndMethod, "getEntityByComponentsClass",  "println", "");
				return -1;
			}
			int i_ec = -1;
			for(int x = 0; x < i_classNs.getPosition(); x++){
				cppObjectClass* f_cls = i_classNs.getByPosition(x);
				i_ec = this->getEntityByComponentClass(f_cls);
				if(i_ec == -1){
					GameManagerLog(ame_Log_EndMethod, "getEntityByComponentsClass",  "println", "");
					return -1;
				}
			}
			GameManagerLog(ame_Log_EndMethod, "getEntityByComponentsClass",  "println", "");
			return i_ec;
		}
		
		virtual int getEntityComponentIndexByClass(int a_entity, cppObjectClass* a_cls){
			GameManagerLog(ame_Log_StartMethod, "getEntityComponentIndexByClass",  "println", "");
			List<COMPONENT>* i_list = getAllComponentsFromEntity(a_entity);
			
			if(i_list == nullptr){
				GameManagerLog(ame_Log_EndMethod, "getEntityComponentIndexByClass",  "println", "");
				return -1;
			}
			
			for(int x = 0; x < i_list->getPosition(); x++){
				COMPONENT* f_child = i_list->getByPosition(x);
				if(f_child == nullptr){
					continue;
				}
				if(f_child->getClass() == a_cls){
					GameManagerLog(ame_Log_EndMethod, "getEntityComponentIndexByClass",  "println", "");
					return x;
				}
			}
			GameManagerLog(ame_Log_EndMethod, "getEntityComponentIndexByClass",  "println", "");
			return -1;
		}
		
		virtual int getGameObjectComponentIndexByClass(ENTITY* a_obj, cppObjectClass* a_cls){
			GameManagerLog(ame_Log_StartMethod, "getGameObjectComponentIndexByClass",  "println", "");
			if(a_obj == nullptr){
				GameManagerLog(ame_Log_EndMethod, "getGameObjectComponentIndexByClass",  "println", "");
				return -1;
			}
			PrimitiveList<COMPONENT>& i_list = a_obj->getChilds();
			
			for(int x = 0; x < i_list.getPosition(); x++){
				COMPONENT* f_component = i_list.getByPosition(x);
				if(f_component == nullptr){
					continue;
				}
				if(f_component->getClass() == a_cls){
					GameManagerLog(ame_Log_EndMethod, "getGameObjectComponentIndexByClass",  "println", "");
					return x;
				}
			}
			GameManagerLog(ame_Log_EndMethod, "getGameObjectComponentIndexByClass",  "println", "");
			return -1;
		}

		//returns the position of the first component founded on the gameobjects list searched by the componentClassName
		virtual int getComponentEntityByClass(cppObjectClass* a_cls){
			GameManagerLog(ame_Log_StartMethod, "getComponentEntityByClass",  "println", "");
			for(int x = 0; x < m_game_objects.getPosition(); x++){
				ENTITY* f_obj = m_game_objects.getByPosition(x);
				if(f_obj == nullptr){
					continue;
				}
				PrimitiveList<COMPONENT>& i_list = f_obj->getChilds();
				for(int y = 0; y < i_list.getPosition(); y++){
					COMPONENT* ff_child = i_list.getByPosition(y);
					if(ff_child == nullptr){
						continue;
					}
					if(ff_child->getClass() == a_cls){
						GameManagerLog(ame_Log_EndMethod, "getComponentEntityByClass",  "println", "");
						return y;
					}
				}
			}
			GameManagerLog(ame_Log_EndMethod, "getComponentEntityByClass",  "println", "");
			return -1;
		}
		
		virtual List<COMPONENT>* getAllComponentsFromEntity(int a_entity){
			GameManagerLog(ame_Log_StartMethod, "getAllComponentsFromEntity",  "println", "");
			ENTITY* i_obj = m_game_objects.getByPosition(a_entity);
			if(i_obj != nullptr){
				GameManagerLog(ame_Log_EndMethod, "getAllComponentsFromEntity",  "println", "");
				return i_obj->getChildsPointer();
			}
			GameManagerLog(ame_Log_EndMethod, "getAllComponentsFromEntity",  "println", "");
			return nullptr;
		}
		
		virtual List<COMPONENT>* getAllComponentsFromGameObject(ENTITY* a_obj){
			GameManagerLog(ame_Log_StartMethod, "getAllComponentsFromGameObject",  "println", "");
			if(a_obj != nullptr){
			GameManagerLog(ame_Log_EndMethod, "getAllComponentsFromGameObject",  "println", "");
				return a_obj->getChildsPointer();
			}
			GameManagerLog(ame_Log_EndMethod, "getAllComponentsFromGameObject",  "println", "");
			return nullptr;
		}
		
		virtual PrimitiveList<COMPONENT>* getComponentsByClass(cppObjectClass* a_cls){
			GameManagerLog(ame_Log_StartMethod, "getComponentsByClass",  "println", "");
			PrimitiveList<COMPONENT>* i_list = m_components.getValueByPointer(a_cls);
			if(i_list == nullptr){
				i_list = new PrimitiveList<COMPONENT>(5, false, true);
				m_components.addPointers(a_cls, i_list);
			}
			GameManagerLog(ame_Log_EndMethod, "getComponentsByClass",  "println", "");
			return i_list;
		}
		
		virtual void deleteComponentByClass(cppObjectClass* a_cls){
			GameManagerLog(ame_Log_StartMethod, "deleteComponentByClass",  "println", "");
			for(int x= 0; x < m_game_objects.getPosition(); x++){
				COMPONENT* f_component = nullptr;
				ENTITY* f_obj = m_game_objects.getByPosition(x);
				if(f_obj == nullptr){
					continue;
				}
				f_component = f_obj->detachByClass(a_cls);
				if(f_component == nullptr){
					continue;
				}
				PrimitiveList<COMPONENT>* f_list = m_components.getValueByPointer(a_cls);
				if(f_list == nullptr){
					continue;
				}
				f_list->removeByPointer(f_component);
				if(f_component == nullptr){
					continue;
				}
				delete f_component;
			}
			GameManagerLog(ame_Log_EndMethod, "deleteComponentByClass",  "println", "");
		}
		
		/*
		*	removes the component from the gameobject and the component class list
		*/
		virtual COMPONENT* removeComponentFromEntityByClass(int a_entity, cppObjectClass* a_cls){
			GameManagerLog(ame_Log_StartMethod, "removeComponentFromEntityByClass",  "println", "");
			COMPONENT* i_component = nullptr;
			ENTITY* i_obj = m_game_objects.getByPosition(a_entity);
			if(i_obj == nullptr){
				GameManagerLog(ame_Log_EndMethod, "removeComponentFromEntityByClass",  "println", "a_obj == nullptr");
				return nullptr;
			}

			i_component = i_obj->detachByClass(a_cls);
			PrimitiveList<COMPONENT>* i_list = m_components.getValueByPointer(a_cls);
			if(i_list != nullptr){
				i_list->removeByPointer(i_component);
			}
			GameManagerLog(ame_Log_EndMethod, "removeComponentFromEntityByClass",  "println", "");
			return i_component;
		}
		
		virtual COMPONENT* removeComponentFromGameObjectByClass(ENTITY* a_obj, cppObjectClass* a_cls){
			GameManagerLog(ame_Log_StartMethod, "removeComponentFromGameObjectByClass",  "println", "");
			COMPONENT* i_component = nullptr;
			if(a_obj == nullptr){
				GameManagerLog(ame_Log_EndMethod, "removeComponentFromGameObjectByClass",  "println", "a_obj == nullptr");
				return nullptr;
			}

			i_component = a_obj->detachByClass(a_cls);
			PrimitiveList<COMPONENT>* i_list = m_components.getValueByPointer(a_cls);
			if(i_list != nullptr){
				i_list->removeByPointer(i_component);
			}
			GameManagerLog(ame_Log_EndMethod, "removeComponentFromGameObjectByClass",  "println", "");
			return i_component;
		}
		
		virtual void deleteComponentFromEntityByClass(int a_entity, cppObjectClass* a_cls){
			GameManagerLog(ame_Log_StartMethod, "deleteComponentFromEntityByClass",  "println", "");
			ENTITY* i_obj = m_game_objects.getByPosition(a_entity);
			if(i_obj == nullptr){
				GameManagerLog(ame_Log_EndMethod, "deleteComponentFromEntityByClass",  "println", "");
				return;
			}
			
			COMPONENT* i_component = i_obj->detachByClass(a_cls);
			PrimitiveList<COMPONENT>* i_list = m_components.getValueByPointer(a_cls);
			if(i_list != nullptr){
				i_list->removeByPointer(i_component);
			}
			if(i_component != nullptr){
				delete i_component;
			}
			GameManagerLog(ame_Log_EndMethod, "deleteComponentFromEntityByClass",  "println", "");
		}
		
		virtual void deleteComponentFromGameObjectByClass(ENTITY* a_obj, cppObjectClass* a_cls){
			GameManagerLog(ame_Log_StartMethod, "deleteComponentFromGameObjectByClass",  "println", "");
			if(a_obj == nullptr || a_cls == nullptr){
				GameManagerLog(ame_Log_EndMethod, "deleteComponentFromGameObjectByClass",  "println", "a_obj == nullptr || a_cls == nullptr");
				return;
			}
			
			COMPONENT* i_component = a_obj->detachByClass(a_cls);
			if(i_component == nullptr){
				GameManagerLog(ame_Log_EndMethod, "deleteComponentFromGameObjectByClass",  "println", "i_component == nullptr");
				return;
			}
			PrimitiveList<COMPONENT>* i_list = m_components.getValueByPointer(a_cls);
			if(i_list != nullptr){
				i_list->removeByPointer(i_component);
			}
			delete i_component;
			GameManagerLog(ame_Log_EndMethod, "deleteComponentFromGameObjectByClass",  "println", "");
		}
		
		virtual void deleteAllComponentsFromEntity(int a_entity){
			GameManagerLog(ame_Log_StartMethod, "deleteAllComponentsFromEntity",  "println", "");
			ENTITY* i_obj = m_game_objects.getByPosition(a_entity);
			if(i_obj == nullptr){
				GameManagerLog(ame_Log_EndMethod, "deleteAllComponentsFromEntity",  "println", "");
				return;
			}
			
			PrimitiveList<COMPONENT>& i_list = i_obj->getChilds();
			PrimitiveList<cppObjectClass> i_classT;
			for(int x = 0; x < i_list.getPosition(); x++){
				COMPONENT* f_component = i_list.getByPosition(x);
				i_classT.addPointer(f_component->getClass());
			}
			for(int x = 0; x < i_classT.getPosition(); x++){
				cppObjectClass* f_cls = i_classT.getByPosition(x);
				PrimitiveList<COMPONENT>* f_list2 = m_components.getValueByPointer(f_cls);
				if(f_list2 == nullptr){
					continue;
				}
				COMPONENT* f_component = i_obj->detachByClass(f_cls);
				if(f_component == nullptr){
					continue;
				}
				f_list2->removeByPointer(f_component);
				delete f_component;
			}
			GameManagerLog(ame_Log_EndMethod, "deleteAllComponentsFromEntity",  "println", "");
		}
		
		virtual void deleteAllComponentsFromGameObject(ENTITY* a_obj){
			GameManagerLog(ame_Log_StartMethod, "deleteAllComponentsFromGameObject",  "println", "");
			if(a_obj == nullptr){
				GameManagerLog(ame_Log_EndMethod, "deleteAllComponentsFromGameObject",  "println", "");
				return;
			}
			
			PrimitiveList<COMPONENT>& i_list = a_obj->getChilds();
			PrimitiveList<cppObjectClass> i_classT;
			for(int x = 0; x < i_list.getPosition(); x++){
				COMPONENT* f_component = i_list.getByPosition(x);
				i_classT.addPointer(f_component->getClass());
			}
			for(int x = 0; x < i_classT.getPosition(); x++){
				cppObjectClass* f_cls = i_classT.getByPosition(x);
				PrimitiveList<COMPONENT>* f_list2 = m_components.getValueByPointer(f_cls);
				if(f_list2 == nullptr){
					continue;
				}
				COMPONENT* f_component = a_obj->detachByClass(f_cls);
				if(f_component == nullptr){
					continue;
				}
				f_list2->removeByPointer(f_component);
				delete f_component;
			}
			GameManagerLog(ame_Log_EndMethod, "deleteAllComponentsFromGameObject",  "println", "");
		}
		
		virtual void requestDeleteComponentFromEntityByClass(int a_entity, cppObjectClass* a_cls){
			GameManagerLog(ame_Log_StartMethod, "requestDeleteComponentFromEntityByClass",  "println", "");
			ENTITY* i_obj = m_game_objects.getByPosition(a_entity);
			if(i_obj == nullptr){
				GameManagerLog(ame_Log_EndMethod, "requestDeleteComponentFromEntityByClass",  "println", "");
				return;
			}
			m_deleteRequest.addPointers(i_obj, a_cls);
			GameManagerLog(ame_Log_EndMethod, "requestDeleteComponentFromEntityByClass",  "println", "");
		}
		
		void requestDeleteComponentFromGameObjectByClass(ENTITY* a_obj, cppObjectClass* a_cls){
			GameManagerLog(ame_Log_StartMethod, "requestDeleteComponentFromGameObjectByClass",  "println", "");
			if(a_obj == nullptr || a_cls == nullptr){
				GameManagerLog(ame_Log_EndMethod, "requestDeleteComponentFromGameObjectByClass",  "println", "a_obj == nullptr || a_cls == nullptr");
				return;
			}
			if(!m_game_objects.containByPointer(a_obj)){
				GameManagerLog(ame_Log_EndMethod, "requestDeleteComponentFromGameObjectByClass",  "println", "");
				return;
			}
			m_deleteRequest.addPointers(a_obj, a_cls);
			GameManagerLog(ame_Log_EndMethod, "requestDeleteComponentFromGameObjectByClass",  "println", "");
		}
		
		virtual void removeComponentFromEntityByPointer(int a_entity, COMPONENT* a_component){
			GameManagerLog(ame_Log_StartMethod, "removeComponentFromEntityByPointer",  "println", "");
			ENTITY* i_obj = m_game_objects.getByPosition(a_entity);
			if(i_obj == nullptr){
				GameManagerLog(ame_Log_EndMethod, "removeComponentFromEntityByPointer",  "println", "");
				return;
			}
			
			i_obj->detachByPointer(a_component);
			PrimitiveList<COMPONENT>* i_list = m_components.getValueByPointer(a_component->getClass());
			if(i_list == nullptr){
				GameManagerLog(ame_Log_EndMethod, "removeComponentFromEntityByPointer",  "println", "");
				return;
			}

			i_list->removeByPointer(a_component);
			GameManagerLog(ame_Log_EndMethod, "removeComponentFromEntityByPointer",  "println", "");
		}
		
		virtual void removeComponentFromGameObjectByPointer(ENTITY* a_obj, COMPONENT* a_component){
			GameManagerLog(ame_Log_StartMethod, "removeComponentFromGameObjectByPointer",  "println", "");
			if(a_obj == nullptr){
				GameManagerLog(ame_Log_EndMethod, "removeComponentFromGameObjectByPointer",  "println", "");
				return;
			}
			
			a_obj->detachByPointer(a_component);
			PrimitiveList<COMPONENT>* i_list = m_components.getValueByPointer(a_component->getClass());
			if(i_list == nullptr){
				GameManagerLog(ame_Log_EndMethod, "removeComponentFromGameObjectByPointer",  "println", "");
				return;
			}

			i_list->removeByPointer(a_component);
			GameManagerLog(ame_Log_EndMethod, "removeComponentFromGameObjectByPointer",  "println", "");
		}
		
		virtual void deleteComponentFromEntityByPointer(int a_entity, COMPONENT* a_component){
			GameManagerLog(ame_Log_StartMethod, "deleteComponentFromEntityByPointer",  "println", "");
			if(a_component == nullptr){
				return;
			}
			
			ENTITY* i_obj = m_game_objects.getByPosition(a_entity);
			if(i_obj == nullptr){
				GameManagerLog(ame_Log_EndMethod, "deleteComponentFromEntityByPointer",  "println", "");
				return;
			}
			i_obj->detachByPointer(a_component);
			PrimitiveList<COMPONENT>* i_list = m_components.getValueByPointer(a_component->getClass());
			if(i_list != nullptr){
				i_list->removeByPointer(a_component);
			}
			delete a_component;
			GameManagerLog(ame_Log_EndMethod, "deleteComponentFromEntityByPointer",  "println", "");
		}
		
		virtual void deleteComponentFromGameObjectByPointer(ENTITY* a_obj, COMPONENT* a_component){
			GameManagerLog(ame_Log_StartMethod, "deleteComponentFromGameObjectByPointer",  "println", "");
			if(a_component == nullptr){
				GameManagerLog(ame_Log_EndMethod, "deleteComponentFromGameObjectByPointer",  "println", "");
				return;
			}
			if(a_obj == nullptr){
				GameManagerLog(ame_Log_EndMethod, "deleteComponentFromGameObjectByPointer",  "println", "");
				return;
			}
			if(!m_game_objects.containByPointer(a_obj)){
				GameManagerLog(ame_Log_EndMethod, "deleteComponentFromGameObjectByPointer",  "println", "");
				return;
			}
			a_obj->detachByPointer(a_component);
			PrimitiveList<COMPONENT>* i_list = m_components.getValueByPointer(a_component->getClass());
			if(i_list != nullptr){
				i_list->removeByPointer(a_component);
			}
			delete a_component;
			GameManagerLog(ame_Log_EndMethod, "deleteComponentFromGameObjectByPointer",  "println", "");
		}
		
		//resets the list and it deletes the components from there entities
		virtual void deleteComponentsFromList(PrimitiveList<COMPONENT>* a_list_components){
			GameManagerLog(ame_Log_StartMethod, "deleteComponentsFromList",  "println", "");
			if(a_list_components == nullptr){
				GameManagerLog(ame_Log_EndMethod, "deleteComponentsFromList",  "println", "");
				return;
			}
			if(a_list_components->isEmpty()){
				GameManagerLog(ame_Log_EndMethod, "deleteComponentsFromList",  "println", "");
				return;
			}
			cppObjectClass* i_class = m_components.getKeyByPointer(a_list_components);
			if(i_class == nullptr){
				GameManagerLog(ame_Log_EndMethod, "deleteComponentsFromList",  "println", "");
				return;
			}
			for(int x = 0; x > m_game_objects.getPosition(); x++){
				ENTITY* f_obj = m_game_objects.getByPosition(x);
				PrimitiveList<COMPONENT>& f_list = f_obj->getChilds();
				for(int x = 0; x < f_list.getPosition(); x++){
					COMPONENT* ff_component = f_list.getByPosition(x);
					if(ff_component->getClass() == i_class){
						f_list.removeDeleteByPosition(x);
						x--;
					}
				}
			}
			a_list_components->reset();
			GameManagerLog(ame_Log_EndMethod, "deleteComponentsFromList",  "println", "");
		}
		
		virtual int getEntitySize(){
			GameManagerLog(ame_Log_StartMethod, "getEntitySize",  "println", "");
			GameManagerLog(ame_Log_EndMethod, "deleteEntity",  "println", "");
			return m_game_objects.getPosition();
		}
		
		virtual int getComponentSizeByPosition(int a_entity){
			GameManagerLog(ame_Log_StartMethod, "getComponentSizeByPosition",  "println", "");
			ENTITY* i_obj = m_game_objects.getByPosition(a_entity);
			if(i_obj == nullptr){
				GameManagerLog(ame_Log_EndMethod, "getComponentSizeByPosition",  "println", "");
				return -1;
			}
			PrimitiveList<COMPONENT>& i_list = i_obj->getChilds();
			GameManagerLog(ame_Log_EndMethod, "getComponentSizeByPosition",  "println", "");
			return i_list.getPosition();
		}
		
		virtual void rearrange(){
			GameManagerLog(ame_Log_StartMethod, "rearrange",  "println", "");
			for(int x = 0; x < m_game_objects.getPosition(); x++){
				COMPONENT* f_game_object = m_game_objects.getByPosition(x);
				f_game_object->setId(x);
			}
			GameManagerLog(ame_Log_EndMethod, "deleteEntity",  "println", "");
		}
		
		virtual cppObjectClass* getClass(){
			return Class<GameManager>::getClass();
		}
		
		virtual void updateState(float tpc){
			// Serial.println("start GameManager update");
			for(int txp = 0; txp < this->m_addRequest.getPosition(); txp++){
				GameManagerLog(ame_Log_Statement, "update",  "println", "addRequest");
				this->addComponentToGameObject(this->m_addRequest.getKeyByPosition(txp), this->m_addRequest.getValueByPosition(txp));
			}
			this->m_addRequest.reset();
			
			for(int txp = 0; txp < this->m_deleteRequest.getPosition(); txp++){
				GameManagerLog(ame_Log_Statement, "update",  "println", "deleteRequest");
				this->deleteComponentFromGameObjectByClass(this->m_deleteRequest.getKeyByPosition(txp), this->m_deleteRequest.getValueByPosition(txp));
			}
			this->m_deleteRequest.resetDeleteValue();
			
			for(int txp = 0; txp < this->m_deleteERequest.getPosition(); txp++){
				GameManagerLog(ame_Log_Statement, "update",  "println", "deleteERequest");
				this->deleteGameObject(this->m_deleteERequest.getByPosition(txp));
			}
			this->m_deleteERequest.reset();
			
			if(this->m_deleteAllE){
				GameManagerLog(ame_Log_Statement, "update",  "println", "deleteAllE");
				m_deleteAllE = false;
				this->deleteAllEntities();
			}
		}
		
	protected:

		bool m_deleteAllE = false;

		PrimitiveList<ENTITY> m_deleteERequest = PrimitiveList<ENTITY>(5, false, true);
		PrimitiveMap<ENTITY,COMPONENT> m_addRequest = (PrimitiveMap<ENTITY,COMPONENT>(5, false, false, true));
		PrimitiveMap<ENTITY,cppObjectClass> m_deleteRequest = (PrimitiveMap<ENTITY,cppObjectClass>(5, false, false, true));

		PrimitiveMap<cppObjectClass,PrimitiveList<COMPONENT>> m_components = (PrimitiveMap<cppObjectClass,PrimitiveList<COMPONENT>>(5, false, true, true));
		PrimitiveList<ENTITY> m_game_objects = PrimitiveList<ENTITY>(5, true, true);
};

}

#endif