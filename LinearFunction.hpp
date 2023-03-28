
#ifndef LinearFunction_hpp
#define LinearFunction_hpp
#define LinearFunction_AVAILABLE

#include "Function.hpp"

namespace ame{

class LinearFunction : public Function<float,float>{
	public:
		LinearFunction(){
			this->initializeConstantes(2,0);
			this->setConstante(0,1);
			this->setConstante(1,0);
		}
		LinearFunction(float c_m, float c_b){
			this->initializeConstantes(2,0);
			this->setConstante(0, c_m);
			this->setConstante(1, c_b);
		}
		virtual ~LinearFunction(){}

		virtual float f(float a_x){
			return (m_constantes[0] * a_x) + m_constantes[1];
		}

		virtual Function<float,float>* clone(){
			Function<float,float>* i_function = new LinearFunction();
			i_function->initializeConstantes(2,0);
			i_function->setConstante(0, this->getConstante(0));
			i_function->setConstante(1, this->getConstante(1));
			return i_function;
		}

		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){return Class<LinearFunction>::getClass();}
		virtual bool instanceof(cppObjectClass* cls){return cls == Class<LinearFunction>::getClass();}
		#endif

	protected:
};

}

#endif