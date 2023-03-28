
#ifndef DISABLE_ClassAnnotationList_hpp
#define DISABLE_ClassAnnotationList_hpp

	#if defined(DISABLE_Annotation) || defined(DISABLE_ClassAnnotationList) || defined(DISABLE_cppObjectClass)
		#define ClassAnnotationList_hpp
	#endif
#endif

#ifndef ClassAnnotationList_hpp
#define ClassAnnotationList_hpp
#define ClassAnnotationList_AVAILABLE 

#include "cppObjectClass.hpp"
#include "RawList.hpp"
#include "PrimitiveRawList.hpp"

namespace ame{

template<class cls>
struct ClassAnnotationList{
	static RawList<Annotation>* annotations;
	static void add(Annotation* a){
		if(annotations == nullptr){
			return;
		}
		if(annotations->containByPointer(a)){
			return;
		}
		annotations->addPointer(a);
	}
};

template<class cls> RawList<Annotation>* ClassAnnotationList<cls>::annotations = new PrimitiveRawList<Annotation>();

}

#endif