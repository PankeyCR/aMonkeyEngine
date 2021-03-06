
#ifndef ArrayFunction_h
#define ArrayFunction_h

#include "ArrayList.h"
#include "ModifiableFunction.h"

template<int C, int V, int S1, int S2, int S3, class T, class... args>
class ArrayFunction : public ModifiableFunction<T,args...>{
	public:
		
		ArrayFunction(){
			this->constants = new PrimitiveList<T>;
			this->multivariables = new PrimitiveList<T>;
			this->modifiablevariables = new PrimitiveList<T>;
			for(int x=0; x <= C; x++){
				this->constants->addPointer(new T());
			}
			for(int x=0; x <= V; x++){
				this->modifiablevariables->addPointer(new T());
			}
		}
		
		virtual ~ArrayFunction(){
			delete this->constants;
			delete this->multivariables;
			delete this->modifiablevariables;
		}
    
		//cppObject part
		String getClassName(){
			return "ArrayFunction";
		}
		String toString(){
			return "ArrayFunction";
		}
		virtual T f(args... x){
			this->multivariables->addPack(x...);
			T t;
			if(this->constants->isEmpty()){
				T multivar;
				T modivar;
				for(int j = 0; j < this->multivariables->getPosition(); j++){
					multivar = (*this->multivariables->getByPosition(j));
					for(int k = 0; k < this->modifiablevariables->getPosition(); k++){
						modivar = (*this->modifiablevariables->getByPosition(k));
						if(k < S1){
							t += multivar * modivar;
						}
						if(k >= S2){
							t += modivar;
						}
					}
				}
			}
			for(int i = 0; i < this->constants->getPosition(); i++){
				T c = (*this->constants->getByPosition(i));
				T multivar;
				T modivar;
				for(int j = 0; j < this->multivariables->getPosition(); j++){
					multivar = (*this->multivariables->getByPosition(j));
					for(int k = 0; k < this->modifiablevariables->getPosition(); k++){
						modivar = (*this->modifiablevariables->getByPosition(k));
						if(k < S1){
							t += c * multivar * modivar;
						}
						if(k >= S2 && k < S3){
							t += c * modivar;
						}
						if(k >= S3){
							t += modivar;
						}
					}
				}
			}
			return t;
		}
		
		virtual int getIterationSize(){
			return V;
		}
		virtual bool instanceof(String name){return name == "ArrayFunction" || name == "ModifiableFunction" || name == "Function";}
		
	protected:
		
		
	
};

#endif 
