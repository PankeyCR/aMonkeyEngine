
#ifndef CONFIGURATION_AppStateManager_hpp
#define CONFIGURATION_AppStateManager_hpp

	#include "ame_Enviroment.hpp"

	#if defined(DISABLE_AppStateManager)
		#define AppStateManager_hpp

		#define IMPLEMENTATION_AppStateManager
		#define IMPLEMENTING_AppStateManager
	#else
		#if defined(DISABLE_IMPLEMENTATION_AppStateManager)
			#define IMPLEMENTATION_AppStateManager
			#define IMPLEMENTING_AppStateManager
		#endif
	#endif

#endif

#ifndef AppStateManager_hpp
#define AppStateManager_hpp
#define AppStateManager_AVAILABLE

#ifndef DISABLE_IMPLEMENTATION_AppStateManager
	#define IMPLEMENTATION_AppStateManager IMPLEMENTATION(public AppStateManager)
	#define IMPLEMENTING_AppStateManager IMPLEMENTING(public AppStateManager)
#endif

#include "cppObject.hpp"
#include "Note.hpp"
#include "AppState.hpp"
#include "AbstractClass.hpp"

namespace ame{

/*
*	Class Configuration:
*	DISABLE_Application
*	DISABLE_cppObject
*	DISABLE_cppObjectClass
*	DISABLE_AbstractClass
*	DISABLE_IMPLEMENTATION_cppObject
*/
class AppStateManager IMPLEMENTATION_cppObject {
    public:
		virtual ~AppStateManager(){}
		
		#if defined(Application_AVAILABLE)
		virtual void setApplication(Application *app){
			this->m_application = app;
		}
		
		virtual Application* getApplication(){return this->m_application;}
		#endif
		
		template<class T>
		T* addState(T* state){
			this->add(state);
			return state;
		}

		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(AbstractClass_AVAILABLE)
		template<class T>
		T* getState(){
			AppState* state = this->get(Class<T>::classType);
			if(state == nullptr){
				return nullptr;
			}
			return (T*)state;
		}
		
		template<class T>
		T* getState(Note appstateId){
			AppState* state = this->get(appstateId, Class<T>::classType);
			if(state == nullptr){
				return nullptr;
			}
			return (T*)state;
		}
		/*
		template<class T>
		T* removeState(){
			return this->remove(ClassType<T>::classType);
		}
		template<class T>
		void removeDeleteState(){
			AppState* s = this->remove(ClassType<T>::classType);
			if(s != nullptr){
				delete s;
			}
		}*/
		#endif

		virtual AppState* add(AppState* state)=0;
		virtual AppState* add(Note a_id, AppState* state){
			if(state == nullptr){
				return nullptr;
			}
			state->setId(a_id);
			return add(state);
		}
		
		virtual AppState* getByPosition(int a_index)=0;
		virtual AppState* getById(Note appstateId)=0;
		
		virtual AppState* getInitializedStateByPosition(int a_index)=0;
		virtual AppState* getInitializedStateById(Note appstateId)=0;
		
		virtual AppState* getUnInitializedStateByPosition(int a_index)=0;
		virtual AppState* getUnInitializedStateById(Note appstateId)=0;
		
		virtual AppState* removeByPosition(int a_index)=0;
		virtual AppState* removeById(Note appstateId)=0;
		
		virtual void removeDeleteById(Note appstateId){
			AppState* appState = this->removeById(appstateId);
			if(appState == nullptr){
				return;
			}
			delete appState;
		}

		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE)
		virtual AppState* get(cppObjectClass* cls)=0;
		virtual AppState* get(Note appstateId, cppObjectClass* cls)=0;
		
		virtual AppState* getInitializedState(cppObjectClass* cls)=0;
		virtual AppState* getInitializedState(Note appstateId, cppObjectClass* cls)=0;
		
		virtual AppState* getUnInitializedState(cppObjectClass* cls)=0;
		virtual AppState* getUnInitializedState(Note appstateId, cppObjectClass* cls)=0;
		
		virtual AppState* remove(cppObjectClass* cls)=0;
		virtual AppState* remove(Note appstateId,cppObjectClass* cls)=0;
		
		virtual void removeDelete(cppObjectClass* cls){
			AppState* appState = this->remove(cls);
			if(appState == nullptr){
				return;
			}
			delete appState;
		}
		virtual void removeDelete(Note appstateId,cppObjectClass* cls){
			AppState* appState = this->remove(appstateId,cls);
			if(appState == nullptr){
				return;
			}
			delete appState;
		}
		virtual bool contain(cppObjectClass* cls)=0;
		virtual bool contain(Note appstateId,cppObjectClass* cls)=0;
		#endif
		
		virtual int getTotalStatesSize()=0;
		virtual int getInitializedStatesSize()=0;
		virtual int getUnInitializedStatesSize()=0;
		
		virtual void removeAll()=0;
		virtual void removeDeleteAll()=0;
		
		virtual void update(float a_tpc)=0;
		
		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(AbstractClass_AVAILABLE)
		virtual cppObjectClass* getClass(){
			return AbstractClass<AppStateManager>::classType;
		}
		
		virtual bool instanceof(cppObjectClass* cls){
			return cls == AbstractClass<AppStateManager>::classType;
		}
		#endif
	protected:
		#if defined(Application_AVAILABLE)
		Application* m_application = nullptr;
		#endif
};

}

#endif
