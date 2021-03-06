
#ifndef ModifiableFunction_h
#define ModifiableFunction_h

#include "List.h"
#include "PrimitiveList.h"
#include "Iterator.h"
#include "Function.h"

template<class T, class... args>
class ModifiableFunction : public Function<T, args...>, public Iterator{
	public:
		virtual ~ModifiableFunction(){}
    
		virtual T f(args... mf)=0;
		
		virtual void setConstante(int position, T var){
			constants.setLValue(position, var);
		}
		
		virtual void set(int position, T var){
			modifiablevariables.setLValue(position, var);
		}
		
		virtual T* getPointer(int x){
			return modifiablevariables.getByPosition(x);
		}
		
		virtual T getLValue(int x){
			if(modifiablevariables.getByPosition(x) == nullptr){
				return -1;
			}
			return *modifiablevariables.getByPosition(x);
		}
		
		virtual int getIterationSize()=0;
		
		virtual T getLValue(Iterator i){
			return *modifiablevariables.getByPosition(i.getIteration());
		}
		
		virtual T* getPointer(Iterator i){
			return modifiablevariables.getByPosition(i.getIteration());
		}
		
		virtual void set(Iterator i, T var){
			modifiablevariables.setLValue(i.getIteration(), var);
		}
		virtual bool instanceof(cppObjectClass* cls){
			return cls || Class<ModifiableFunction<T,args...>>::classType 
			|| Function<T,args...>::instanceof(cls);
		}
		virtual cppObjectClass* getClass(){return Class<ModifiableFunction<T,args...>>::classType;}
		virtual String toString(){return "ModifiableFunction";}
		
	protected:
		PrimitiveList<T> constants;
		PrimitiveList<T> multivariables;
		PrimitiveList<T> modifiablevariables;
		
		
	
};

#endif 
