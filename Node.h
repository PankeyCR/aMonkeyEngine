
#ifndef Node_h
#define Node_h

#include "cppObject.h"
#include "Spatial.h"

class Node : public Spatial{	
    public:
		Node(){
		}
		Node(const Node& n){
			children = n.children;
		}
		virtual ~Node(){
		}
		virtual void operator=(Node n){
			children = n.children;
		}
		virtual void operator=(const Node& n){
			children = n.children;
		}
		virtual bool operator==(Node n){return this->getClassName()==n.getClassName();}
		virtual bool operator!=(Node n){return this->getClassName()!=n.getClassName();}
		
		virtual bool instanceof(String name){return name == "Node" || Spatial::instanceof(name);}
		virtual String getClassName(){return "Node";}
		virtual String toString(){return "Node";}
		virtual bool equal(cppObject *b){
			if(b == this){
				return true;
			}
			return false;
		}
		
		virtual Node* clone(){return new Node(*this);}
		
		template<class T, class... P>
		T* attach(P... p){
			T* t = new T(p...);
			children.addPointer(t);
			return t;
		}
		
		Spatial* attachChild(Spatial* s){
			children.addPointer(s);
			return s;
		}
		
		virtual Spatial* detach(int x){
			return children.removeByPosition(x);
		}
		
		virtual Spatial* detach(String n){
			for(int x = 0; x < children.getPosition(); x++){
				Spatial* spatial = children.getByPosition(x);
				if(n == spatial->getName()){
					children.removeByPosition(x);
					return spatial;
				}
			}
			return nullptr;
		}
		
		virtual Spatial* getChild(int x){
			return children.getByPosition(x);
		}
		
		virtual Spatial* getChild(String n){
			for(int x = 0; x < children.getPosition(); x++){
				Spatial* spatial = children.getByPosition(x);
				if(n == spatial->getName()){
					return spatial;
				}
			}
			return nullptr;
		}
		
		virtual Spatial* detachChildByPosition(int x){
			return children.removeByPosition(x);
		}
		
		virtual int detachChildByPointer(Spatial* s){
			int index = children.getIndexByPointer(s);
			children.removeByPointer(s);
			return index;
		}
		
		virtual Spatial* detachChild(String n){
			for(int x = 0; x < children.getPosition(); x++){
				Spatial* spatial = children.getByPosition(x);
				if(n == spatial->getName()){
					return children.removeByPosition(x);
				}
			}
		}
		
		virtual void detachChildDeleteByPosition(int x){
			children.removeDeleteByPosition(x);
		}
		
		virtual int detachChildDeleteByPointer(Spatial* s){
			int index = children.getIndexByPointer(s);
			children.removeDeleteByPointer(s);
			return index;
		}
		
		virtual void detachChildDelete(String n){
			for(int x = 0; x < children.getPosition(); x++){
				Spatial* spatial = children.getByPosition(x);
				if(n == spatial->getName()){
					children.removeDeleteByPosition(x);
					return;
				}
			}
		}
		
	protected:
		PrimitiveList<Spatial> children;
};
#endif 
