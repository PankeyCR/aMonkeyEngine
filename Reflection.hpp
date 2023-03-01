
#ifndef Reflection_hpp
#define Reflection_hpp
#define Reflection_AVAILABLE

#include "cppObject.hpp"

#include "Note.hpp"
#include "Class.hpp"
// #include "Object.hpp"
#include "GenericClass.hpp"
#include "PrimitiveRawMap.hpp"

#ifdef Reflection_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"
	
	#define ReflectionLog(location,method,type,mns) ame_Log(nullptr,location,"Reflection",method,type,mns)
	#define ReflectionMethodLog(location,method,type,mns) ame_Log(nullptr,location,"RawMethod",method,type,mns)
	#define const_ReflectionLog(location,method,type,mns) 
	#define StaticReflectionLog(pointer,location,method,type,mns) ame_Log(pointer,location,"Reflection",method,type,mns)
#else
	#ifdef Reflection_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"
		
		#define ReflectionLog(location,method,type,mns) ame_LogDebug(nullptr,location,"Reflection",method,type)
		#define ReflectionMethodLog(location,method,type,mns) ame_LogDebug(nullptr,location,"RawMethod",method,type)
		#define const_ReflectionLog(location,method,type,mns) 
		#define StaticReflectionLog(pointer,location,method,type,mns) ame_LogDebug(pointer,location,"Reflection",method,type)
	#else
		#define ReflectionLog(location,method,type,mns) 
		#define ReflectionMethodLog(location,method,type,mns) 
		#define const_ReflectionLog(location,method,type,mns) 
		#define StaticReflectionLog(pointer,location,method,type,mns) 
	#endif
#endif

namespace ame{

class Reflection : public cppObject{
	public:
	
	template<class R = bool, class... Args> 
	using Raw_Method = R(*)(Args...);
		
	template<class... Args> 
	using R_Raw_NTMethod = void(*)(Args...);
		
	template<class T, class R = bool, class... Args> 
	using Raw_Class_Method = R(*)(T*,Args...);
		
	template<class T, class... Args> 
	using Raw_Class_NTMethod = void(*)(T*,Args...);
		
	template<class T, class R = bool, class... Args> 
	using Class_Method = R(T::*)(Args...);
		
	template<class T, class R = bool, class... Args> 
	using Class_NTMethod = void(T::*)(Args...);
		
		Reflection(){}
		virtual ~Reflection(){}
		
	
		virtual void addClass(Note a_note){
			this->addClass(a_note, nullptr);
		}
		
		virtual void addClass(Note a_note, cppObjectClass* cls){
			ReflectionLog(ame_Log_Statement, "addClass",  "println", Note("Name: ") + a_note);
			if(cls == nullptr){
				cls = new GenericClass(a_note.clonePointer());
			}
			cls->setName(a_note.pointer());
			m_classes.addPointer(a_note, cls);
		}
	
		template<class... Args> 
		void addMethod(Note a_class_name, Note a_method_name, R_Raw_NTMethod<Args...> a_method){
			ReflectionLog(ame_Log_Statement, "addMethod",  "println", Note("Name: ") + a_method_name);
			
			cppObjectClass* cls = this->m_classes.getValueByLValue(a_class_name);
			
			if(cls == nullptr){
				return;
			}
			
			Method* i_method = new Method(new cppObjectClass(), MethodType::Method);
			i_method->setName(a_method_name.clonePointer());
			
			cls->addMethod(i_method);
			
			MethodMap<Args...>::add(i_method->getClass(), a_method);
		}
	
		cppObject* newInstance(Note a_class_name){
			cppObjectClass* cls = this->m_classes.getValueByLValue(a_class_name);
			if(cls == nullptr){
				return new Object();
			}
			
			return cls->newInstance();
		}
	
		template<class... Args>
		void invoke(cppObject* a_obj, Note a_method_name, Args... a_invoke){
			ReflectionLog(ame_Log_StartMethod, "invokeMethod",  "println", "");
			ReflectionLog(ame_Log_Statement, "invokeMethod",  "println", Note("Name: ") + a_method_name);
			cppObjectClass* cls = a_obj->getClass();
			if(cls == nullptr){
				ReflectionLog(ame_Log_EndMethod, "invokeMethod",  "println", "");
				return;
			}

			Method* i_method = cls->getMethodByName(a_method_name.pointer());
			if(i_method == nullptr){
				ReflectionLog(ame_Log_EndMethod, "invokeMethod",  "println", "");
				return;
			}

			MethodMap<Args...>::invoke(i_method->getClass(), a_invoke...);
			ReflectionLog(ame_Log_EndMethod, "invokeMethod",  "println", "");
		}
	/*
	static RawMap<Note,cppObjectClass>* m_classes;
	
	///////////////////////////////////////////////////////////////////////////////////////////////////
	//normal method reflection
	
	template<class... Args> 
	static void addMethod(Note a_name, Raw_NTMethod<Args...> a_method){
		ReflectionLog(ame_Log_Statement, "addMethod",  "println", Note("Name: ") + a_name);
		MethodMap<Args...>::add(a_name, a_method);
		
		Method* i_method = new DefaultMethod<cppObject>();
		i_method->setName(a_name);
		i_method->setType(MethodType::MethodInvokerType);
		
		m_methods->addPointer(i_method);
	}
	
	template<class R,class... Args> 
	static void addMethod(Note a_name, Raw_Method<R,Args...> a_method){
		ReflectionLog(ame_Log_Statement, "addMethod",  "println", Note("Name: ") + a_name);
		ReturnMethodMap<R,Args...>::add(a_name, a_method);
		
		Method* i_method = new DefaultMethod<cppObject>();
		i_method->setName(a_name);
		i_method->setType(MethodType::MethodInvokerType);
		
		m_methods->addPointer(i_method);
	}
	
	static Method* getMethod(Note a_name){
		if(m_methods == nullptr){
			return nullptr;
		}
		return m_methods->getByLValue(a_name);
	}
	
	template<class R = bool, class... Args> 
	static void removeMethod(Note a_name){
		ReflectionLog(ame_Log_Statement, "removeMethod",  "println", Note("Name: ") + a_name);
		MethodMap<Args...>::remove(a_name);
		ReturnMethodMap<R,Args...>::remove(a_name);
	}
	
	template<class R = bool, class... Args> 
	static R invokeMethod(Note a_name, Args... a_invoke){
		ReflectionLog(ame_Log_Statement, "invokeMethod",  "println", Note("Name: ") + a_name);
		if(MethodMap<Args...>::invoke(a_name,a_invoke...)){
			return R();
		}
		return ReturnMethodMap<R,Args...>::invoke(a_name,a_invoke...);
	}
	
	template<class R = bool, class... Args> 
	static R invokeReturnMethod(Note a_name, Args... a_invoke){
		ReflectionLog(ame_Log_Statement, "invokeMethod",  "println", Note("Name: ") + a_name);
		return ReturnMethodMap<R,Args...>::invoke(a_name,a_invoke...);
	}
	
	///////////////////////////////////////////////////////////////////////////////////////////////////
	//class reflection
	
	static void addClass(Note a_note){
		addClass(a_note, nullptr);
	}
	
	static void addClass(Note a_note, cppObjectClass* cls){
		ReflectionLog(ame_Log_Statement, "addClass",  "println", Note("Name: ") + a_note);
		if(cls == nullptr){
			cls = new GenericClass(a_note);
		}
		cls->setName(a_note);
		m_classes->addPointer(a_note, cls);
	}
	
	template<class T, class... Args>
	static void addClassMethod(Note a_cls_name, Note a_method_name, Class_Method<T,R,Args...> a_method){
		ReflectionLog(ame_Log_Statement, "addClassMethod",  "println", Note("Name ") + a_name);
		// ClassMethodParameters<T>::add(a_name, ClassMethodParametersSize<Args...>::get());
		// cppObjectClass* i_class = m_classes->getByLValue(a_cls_name);
		// if(i_class == nullptr){
			// return;
		// }
		// Method* i_method = new DefaultMethod<T>();
		// i_method->setParentClass(i_class);
		// i_method->setName(a_method_name);
		// i_method->setType(MethodType::MethodInvokerType);
		// ClassMethodList<T>::add(i_method);
		// ClassMethodMap<T,Args...>::add(a_method_name, a_method);
		// ClassMethodReturnInvoker<T,R,Args...>::add(Class<T>::classType, a_method_name, a_method);
	}
	
	static cppObject* invoke(Note a_note){
		
		return new Object();
	}
	
	template<class T, class R = bool, class... Args>
	static void addGenericClassMethod(Note a_cls_name, Note a_method_name, Class_Method<T,R,Args...> a_method){
		ReflectionLog(ame_Log_Statement, "addClassMethod",  "println", Note("Name ") + a_name);
		// cppObjectClass* cls = m_classes->getBylValue(a_cls_name);
		// if(cls == nullptr){
			// return;
		// }
		// RawList<Method>* list = cls->getMethods();
		// list->addPointer(new GenericMethod(Class<T>::classType, a_name, MethodType::MethodInvokerType));
		// ClassMethodReturnInvoker<T,R,Args...>::add(Class<T>::classType, a_name, a_method);
	}
	/*
	template<class T, class... Args>
	static void addClassRawMethod(Note a_cls_name, Note a_method_name, Class_Method<T,Args...> a_method){
		ReflectionLog(ame_Log_Statement, "addClassMethod",  "println", Note("Name ") + a_name);
		// ClassMethodParameters<T>::add(a_name, ClassMethodParametersSize<Args...>::get());
		ClassMethodList<T>::add(new DefaultMethod<T>(Class<T>::classType, a_method_name, MethodType::MethodInvokerType));
		ClassMethodReturnInvoker<T,R,Args...>::add(Class<T>::classType, a_method_name, a_method);
	}
	*/
	/*
	static void addMethod(Note a_name, Raw_Method a_method){
		ReflectionLog(ame_Log_Statement, "addMethod",  "println", Note("Name ") + a_name);
		// MethodParameter<T>::add<Args...>(a_name);
		ClassMethod<T>::add(new DefaultMethod<T>(Class<T>::classType, a_name, MethodType::MethodInvokerType));
		MethodReturnInvoker<R,Args...>::add(Class<T>::classType, a_name, a_method);
	}
	
	static void addMethod(Note a_name, Raw_Class_Method a_method){
		ReflectionLog(ame_Log_Statement, "addMethod",  "println", Note("Name ") + a_name);
		ClassMethod<T>::add(new DefaultMethod<T>(Class<T>::classType, a_name, MethodType::MethodPointerInvokerType));
		MethodReturnInvoker<R,T*,Args...>::add(Class<T>::classType, a_name, a_method);
	}
	
	static void addMethod(Note a_name, Class_Method a_method){
		ReflectionLog(ame_Log_Statement, "addMethod",  "println", Note("Name ") + a_name);
		ClassMethod<T>::add(new DefaultMethod<T>(Class<T>::classType, a_name, MethodType::ClassMethodInvokerType));
		ClassMethodReturnInvoker<T,R,Args...>::add(Class<T>::classType, a_name, a_method);
	}
	
	static void setDefaultReturn(R a_r){
		ReflectionLog(ame_Log_Statement, "setDefaultReturn",  "println", "");
		DefaultMethodReturn<T,R>::set(a_r);
	}
	
	static R getReturn(){
		ReflectionLog(ame_Log_Statement, "getReturn",  "println", "");
		return DefaultMethodReturn<T,R>::getReturn();
	}*/
	
	
		
		virtual cppObjectClass* getClass(){return Class<Reflection>::getClass();}
		
		virtual bool instanceof(cppObjectClass* cls){
			return cls == Class<Reflection>::getClass();
		}
	protected:
		PrimitiveRawMap<Note,cppObjectClass> m_classes;
		PrimitiveRawMap<Note,PrimitiveRawList<Method>> m_classe_methods;
};

//	RawMap<Note,cppObjectClass>* Reflection::m_classes = new PrimitiveRawMap<Note,cppObjectClass>();

}

#define ReflectClass(T) 															\
  public:																			\
  virtual cppObjectClass* getClass(){return Class<T>::classType;}					\
  virtual bool instanceof(cppObjectClass* cls){return cls == Class<T>::classType || cls == Class<cppObject>::classType;}			\


#endif