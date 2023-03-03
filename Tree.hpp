
#ifndef Tree_hpp
#define Tree_hpp
#define Tree_AVAILABLE

#include "cppObject.hpp"

namespace ame{

template<class T>
class Tree IMPLEMENTATION_cppObject {
	public:
		Tree(){}

		Tree(const Tree<T>& c_tree){}

		virtual ~Tree(){}

		virtual void operator=(const Tree<T>& c_tree){}
		virtual bool operator==(Tree<T> b){return false;}
		virtual bool operator!=(Tree<T> b){return false;}

			
		#if defined(cppObject_AVAILABLE) && defined(cppObjectClass_AVAILABLE) && defined(Class_AVAILABLE)
		virtual cppObjectClass* getClass(){return Class<Tree<T>>::getClass();}
		virtual bool instanceof(cppObjectClass* cls){return cls == Class<Tree<T>>::getClass() || cls == Class<T>::getClass();}
		#endif
	
	protected:
};

}

#endif