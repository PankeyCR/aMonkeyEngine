
#ifndef LinkedStorage_hpp
#define LinkedStorage_hpp
#define LinkedStorage_AVAILABLE

#include "MemoryStorage.hpp"

#ifdef LinkedStorage_LogApp
	#include "ame_Logger_config.hpp"
	#include "ame_Logger.hpp"

	#define LinkedStorageLog(location,method,type,mns) ame_Log((void*)this,location,"LinkedStorage",method,type,mns)
#else
	#ifdef LinkedStorage_LogDebugApp
		#include "ame_Logger_config.hpp"
		#include "ame_Logger.hpp"

		#define LinkedStorageLog(location,method,type,mns) ame_LogDebug((void*)this,location,"LinkedStorage",method,type)
	#else
		#define LinkedStorageLog(location,method,type,mns)
	#endif
#endif

namespace ame{

template<class T>
class LinkedStorage : public MemoryStorage<T>{
	public:
		LinkedStorage(){
			LinkedStorageLog(ame_Log_StartMethod, "Constructor", "println", "");
			LinkedStorageLog(ame_Log_EndMethod, "Constructor", "println", "");
		}

		virtual ~LinkedStorage(){
			LinkedStorageLog(ame_Log_StartMethod, "Destructor", "println", "");
			LinkedListNode<T>* node = this->getStartNode();
			this->deleteListNode(node);
			m_start = nullptr;
			m_end = nullptr;
			m_node = nullptr;
			this->setPosition(0);
			this->setSize(0);
			LinkedStorageLog(ame_Log_EndMethod, "Destructor", "println", "");
		}
		
		virtual bool deleteListNode(LinkedListNode<T>* a_node){
			LinkedStorageLog(ame_Log_StartMethod, "deleteListNode", "println", "");
			if(a_node == nullptr){
				return false;
			}
			LinkedListNode<T>* node = a_node;
			LinkedListNode<T>* nextNode = nullptr;
			for(int x = 0; node != nullptr; x++){
				nextNode = node->next;
				this->removingMemory(node->value);
				delete node;
				node = nullptr;
				if(nextNode == nullptr){
					break;
				}
				nextNode->last = nullptr;
				node = nextNode;
			}
			LinkedStorageLog(ame_Log_EndMethod, "deleteListNode", "println", "");
			return true;
		}
		
		virtual LinkedListNode<T>* getNextNode(LinkedListNode<T>* a_node) const{
			LinkedStorageLog(ame_Log_StartMethod, "getNextNode", "println", "");
			if(a_node == nullptr){
				return nullptr;
			}
			LinkedStorageLog(ame_Log_EndMethod, "getNextNode", "println", "");
			return a_node->next;
		}
		
		virtual LinkedListNode<T>* getLastNode(LinkedListNode<T>* a_node) const{
			LinkedStorageLog(ame_Log_StartMethod, "getLastNode", "println", "");
			if(a_node == nullptr){
				return nullptr;
			}
			LinkedStorageLog(ame_Log_EndMethod, "getLastNode", "println", "");
			return a_node->last;
		}
		
		virtual LinkedListNode<T>* setNode(LinkedListNode<T>* a_node){
			LinkedStorageLog(ame_Log_StartMethod, "setNode", "println", "");
			m_node = a_node;
			LinkedStorageLog(ame_Log_EndMethod, "setNode", "println", "");
			return m_node;
		}
		
		virtual LinkedListNode<T>* initNodes(T* a_value){
			LinkedStorageLog(ame_Log_StartMethod, "initNodes", "println", "");
			LinkedListNode<T>* s_node = this->getStartNode();
			LinkedListNode<T>* e_node = this->getEndNode();
			LinkedListNode<T>* i_node = this->getNode();
			if(s_node == nullptr && e_node == nullptr && i_node == nullptr){
				i_node = new LinkedListNode<T>();
				m_node = i_node;
				m_start = i_node;
				m_end = i_node;
				i_node->set(a_value);
				this->setPosition(1);
				this->setSize(1);
				return i_node;
			}
			LinkedStorageLog(ame_Log_EndMethod, "initNodes", "println", "");
			return nullptr;
		}

		/*
			a_node = origin node
			a_value = pointer added to the new node added next to a_node
			if a_node dont have a next node, the new node is the next node
			if a_node has a next node, the new node is added in between a_node and the next node, making it he next node
		*/
		virtual LinkedListNode<T>* addPointerToNextNode(LinkedListNode<T>* a_node, T* a_value){
			LinkedStorageLog(ame_Log_StartMethod, "addPointerToNextNode", "println", "");
			if(a_node == nullptr){
				return nullptr;
			}
			this->addingMemory(a_value);

			LinkedListNode<T>* nextNode = a_node->next;
			if(nextNode == nullptr){
				nextNode = new LinkedListNode<T>();
				nextNode->set(a_value);
				a_node->next = nextNode;
				nextNode->last = a_node;
				return nextNode;
			}
			LinkedListNode<T>* n_Node = new LinkedListNode<T>();
			a_node->next = n_Node;
			nextNode->last = n_Node;
			n_Node->next = nextNode;
			n_Node->last = a_node;
			n_Node->set(a_value);
			LinkedStorageLog(ame_Log_EndMethod, "addPointerToNextNode", "println", "");
			return n_Node;
		}
		
		virtual LinkedListNode<T>* addPointerToLastNode(LinkedListNode<T>* a_node, T* a_value){
			LinkedStorageLog(ame_Log_StartMethod, "addPointerToLastNode", "println", "");
			if(a_node == nullptr){
				return nullptr;
			}
			this->addingMemory(a_value);

			LinkedListNode<T>* lastNode = a_node->last;
			if(lastNode == nullptr){
				lastNode = new LinkedListNode<T>();
				lastNode->set(a_value);
				a_node->last = lastNode;
				lastNode->next = a_node;
				return lastNode;
			}
			LinkedListNode<T>* n_Node = new LinkedListNode<T>();
			a_node->last = n_Node;
			lastNode->next = n_Node;
			n_Node->last = lastNode;
			n_Node->next = a_node;
			n_Node->set(a_value);
			LinkedStorageLog(ame_Log_EndMethod, "addPointerToLastNode", "println", "");
			return n_Node;
		}
		
		virtual LinkedListNode<T>* getNode() const{
			LinkedStorageLog(ame_Log_StartMethod, "getNode", "println", "");
			LinkedStorageLog(ame_Log_EndMethod, "getNode", "println", "");
			return m_node;
		}
		
		virtual LinkedListNode<T>* getStartNode() const{
			LinkedStorageLog(ame_Log_StartMethod, "getStartNode", "println", "");
			LinkedStorageLog(ame_Log_EndMethod, "getStartNode", "println", "");
			return m_start;
		}
		
		virtual LinkedListNode<T>* getEndNode() const{
			LinkedStorageLog(ame_Log_StartMethod, "getEndNode", "println", "");
			LinkedStorageLog(ame_Log_EndMethod, "getEndNode", "println", "");
			return m_end;
		}
		
		virtual LinkedListNode<T>* getNode(int x) const{
			LinkedStorageLog(ame_Log_StartMethod, "getNode", "println", "");
			if(this->isEmpty()){
				return nullptr;
			}
			if(x == 0){
				return this->getStartNode();
			}
			if(x == this->getPosition() - 1){
				return this->getEndNode();
			}
			LinkedListNode<T>* node = getStartNode();
			for(int count = 0; node != nullptr; count++){
				if(x == count){
					return node;
				}
				node = getNextNode(node);
			}
			LinkedStorageLog(ame_Log_EndMethod, "getNode", "println", "");
			return nullptr;
		}
		
		virtual LinkedListNode<T>* getNodeI(int x) const{
			LinkedStorageLog(ame_Log_StartMethod, "getNodeI", "println", "");
			if(this->isEmpty()){
				return nullptr;
			}
			if(x == 0){
				return this->getEndNode();
			}
			if(x == this->getPosition() - 1){
				return this->getStartNode();
			}
			LinkedListNode<T>* node = getEndNode();
			for(int count = 0; node != nullptr; count++){
				if(x == count){
					return node;
				}
				node = getLastNode(node);
			}
			LinkedStorageLog(ame_Log_EndMethod, "getNodeI", "println", "");
			return nullptr;
		}
		
		virtual LinkedListNode<T>* getNodeByPointer(T* key) const{
			LinkedStorageLog(ame_Log_StartMethod, "getNodeByPointer", "println", "");
			LinkedListNode<T>* node = getStartNode();
			for(int count = 0; node != nullptr; count++){
				T* i_value = node->get();
				if(key == i_value){
					return node;
				}
				node = getNextNode(node);
			}
			LinkedStorageLog(ame_Log_EndMethod, "getNodeByPointer", "println", "");
			return nullptr;
		}
		
		virtual LinkedListNode<T>* getNodeByPointerI(T* key) const{
			LinkedStorageLog(ame_Log_StartMethod, "getNodeByPointerI", "println", "");
			LinkedListNode<T>* node = getEndNode();
			for(int count = 0; node != nullptr; count++){
				T* i_value = node->get();
				if(key == i_value){
					return node;
				}
				node = getLastNode(node);
			}
			LinkedStorageLog(ame_Log_EndMethod, "getNodeByPointerI", "println", "");
			return nullptr;
		}
		
		virtual bool nextNode(){
			LinkedStorageLog(ame_Log_StartMethod, "nextNode", "println", "");
			if(m_node == nullptr){
				LinkedStorageLog(ame_Log_EndMethod, "nextNode", "println", "");
				return false;
			}
			LinkedListNode<T>* node = m_node->next;
			if(node == nullptr){
				LinkedStorageLog(ame_Log_EndMethod, "nextNode", "println", "");
				return false;
			}
			m_node = node;
			LinkedStorageLog(ame_Log_EndMethod, "nextNode", "println", "");
			return true;
		}
		
		virtual bool lastNode(){
			LinkedStorageLog(ame_Log_StartMethod, "lastNode", "println", "");
			if(m_node == nullptr){
				LinkedStorageLog(ame_Log_EndMethod, "lastNode", "println", "");
				return false;
			}
			LinkedListNode<T>* node = m_node->last;
			if(node == nullptr){
				LinkedStorageLog(ame_Log_EndMethod, "lastNode", "println", "");
				return false;
			}
			m_node = node;
			LinkedStorageLog(ame_Log_EndMethod, "lastNode", "println", "");
			return true;
		}
		
		virtual void setNodePosition(int a_position){
			LinkedStorageLog(ame_Log_StartMethod, "setPosition", "println", "");
			if(a_position >= this->getSize()){
				LinkedStorageLog(ame_Log_EndMethod, "setPosition", "println", "");
				return;
			}
			this->setPosition(a_position);
			LinkedListNode<T>* i_node = getNode(a_position);
			this->setNode(i_node);
			LinkedStorageLog(ame_Log_EndMethod, "setPosition", "println", "");
		}
		
		virtual T* addPointerToNode(T* a_value){
			LinkedRawPointerListLog(ame_Log_StartMethod, "addPointerToNode", "println", "");
			LinkedListNode<T>* i_node = this->getNode();
			
			if(i_node == nullptr){
				LinkedListNode<T>* ii_node = this->initNodes(a_value);
				if(ii_node == nullptr){
					LinkedRawPointerListLog(ame_Log_EndMethod, "addPointerToNode", "println", "");
					return nullptr;
				}
				LinkedRawPointerListLog(ame_Log_EndMethod, "addPointerToNode", "println", "");
				return ii_node->get();
			}
			
			m_node = this->addPointerToNextNode(i_node, a_value);
			this->incrementPosition();
			this->incrementSize();
			
			if(i_node == this->getEndNode()){
				m_end = m_node;
			}
			LinkedRawPointerListLog(ame_Log_EndMethod, "addPointerToNode", "println", "");
			return a_value;
		}
		
		virtual T* addPointerToStartNode(T* a_value){
			LinkedRawPointerListLog(ame_Log_StartMethod, "addPointerToStartNode", "println", "");
			LinkedListNode<T>* i_node = this->getStartNode();
			
			if(i_node == nullptr){
				LinkedListNode<T>* ii_node = this->initNodes(a_value);
				if(ii_node == nullptr){
					LinkedRawPointerListLog(ame_Log_EndMethod, "addPointerToStartNode", "println", "");
					return nullptr;
				}
				LinkedRawPointerListLog(ame_Log_EndMethod, "addPointerToStartNode", "println", "");
				return ii_node->get();
			}
			
			m_start = this->addPointerToLastNode(i_node, a_value);
			this->incrementPosition();
			this->incrementSize();
			LinkedRawPointerListLog(ame_Log_EndMethod, "addPointerToStartNode", "println", "");
			return a_value;
		}
		
		virtual T* addPointerToEndNode(T* a_value){
			LinkedRawPointerListLog(ame_Log_StartMethod, "addPointerToEndNode", "println", "");
			LinkedListNode<T>* i_node = this->getEndNode();
			
			if(i_node == nullptr){
				LinkedListNode<T>* ii_node = this->initNodes(a_value);
				if(ii_node == nullptr){
					LinkedRawPointerListLog(ame_Log_EndMethod, "addPointerToEndNode", "println", "");
					return nullptr;
				}
				LinkedRawPointerListLog(ame_Log_EndMethod, "addPointerToEndNode", "println", "");
				return ii_node->get();
			}
			
			m_end = this->addPointerToNextNode(i_node, a_value);
			this->incrementPosition();
			this->incrementSize();
			LinkedRawPointerListLog(ame_Log_EndMethod, "addPointerToEndNode", "println", "");
			return a_value;
		}
		
		//special removes
		
		//cuts the list in 2 parts, it removes all nodes before the position a_position
		virtual LinkedListNode<T>* cutBefore(int a_position){
			LinkedRawPointerListLog(ame_Log_StartMethod, "cutBefore", "println", "");
			if(this->isEmpty() || a_position <= 0){
				LinkedRawPointerListLog(ame_Log_EndMethod, "cutBefore", "println", "this->isEmpty() || a_position == 0");
				return nullptr;
			}
			if(!this->isInOrder()){
				LinkedRawPointerListLog(ame_Log_Statement, "cutBefore", "println", "!this->isInOrder()");
				LinkedListNode<T>* node = this->getNode(a_position);
				LinkedListNode<T>* lastNode = nullptr;
				for(int x = 0; node != nullptr; x++){
					lastNode = node->last;
					node->value = nullptr;
					node = nullptr;
					if(lastNode == nullptr){
						break;
					}
					node = lastNode;
				}
				LinkedRawPointerListLog(ame_Log_EndMethod, "cutBefore", "println", "");
				return nullptr;
			}
			if(a_position == this->getPosition() - 1){
				LinkedRawPointerListLog(ame_Log_StartMethod, "cutBefore", "println", "a_position == this->getPosition() - 1");
				LinkedListNode<T>* b_node = this->m_end;
				this->m_end = b_node->last;
				this->m_end->next = nullptr;
				this->m_node = this->m_end;
				this->decrementPosition(a_position);
				this->decrementSize(a_position);
				return b_node;
			}
			LinkedListNode<T>* b_node = this->getNode(a_position);
			if(b_node == nullptr){
				LinkedRawPointerListLog(ame_Log_StartMethod, "cutBefore", "println", "b_node == nullptr");
				return nullptr;
			}
			LinkedRawPointerListLog(ame_Log_StartMethod, "cutBefore", "println", "cutting regular node");
			b_node->cutLastNode();
			this->decrementPosition(a_position);
			this->decrementSize(a_position);
			LinkedListNode<T>* stating_node = this->getStartNode();
			m_start = b_node;
			LinkedRawPointerListLog(ame_Log_EndMethod, "cutBefore", "println", "");
			return stating_node;
		}
		
		virtual bool cutDeleteBefore(int a_position){
			LinkedRawPointerListLog(ame_Log_StartMethod, "cutDeleteBefore", "println", "");
			LinkedListNode<T>* node = cutBefore(a_position);
			if(node == nullptr){
				return false;
			}
			this->deleteListNode(node);
			LinkedRawPointerListLog(ame_Log_EndMethod, "cutDeleteBefore", "println", "");
			return true;
		}
		
		//splits the Nodes in 2, it removes and returns the nodes after the position a_position
		virtual LinkedListNode<T>* cutAfter(int a_position){
			LinkedRawPointerListLog(ame_Log_StartMethod, "cutAfter", "println", "");
			if(this->isEmpty() || a_position == this->getPosition() - 1){
				LinkedRawPointerListLog(ame_Log_StartMethod, "cutAfter", "println", "this->isEmpty()");
				return nullptr;
			}
			if(!this->isInOrder()){
				LinkedRawPointerListLog(ame_Log_Statement, "cutBefore", "println", "!this->isInOrder()");
				LinkedListNode<T>* node = this->getNode(a_position);
				LinkedListNode<T>* nextNode = nullptr;
				for(int x = 0; node != nullptr; x++){
					nextNode = node->next;
					node->value = nullptr;
					node = nullptr;
					if(nextNode == nullptr){
						break;
					}
					node = nextNode;
				}
				LinkedRawPointerListLog(ame_Log_EndMethod, "cutBefore", "println", "");
				return nullptr;
			}
			if(a_position == 0){
				LinkedRawPointerListLog(ame_Log_StartMethod, "cutAfter", "println", "a_position == 0");
				LinkedListNode<T>* b_node = this->m_start;
				this->m_start = nullptr;
				this->m_end = nullptr;
				this->m_node = nullptr;
				this->setPosition(0);
				this->setSize(0);
				return b_node;
			}
			LinkedListNode<T>* b_node = this->getNode(a_position);
			if(b_node == nullptr){
				LinkedRawPointerListLog(ame_Log_StartMethod, "cutAfter", "println", "b_node == nullptr");
				return nullptr;
			}
			LinkedRawPointerListLog(ame_Log_StartMethod, "cutAfter", "println", "cutting regular node");
			m_end = b_node->last;
			b_node->cutLastNode();
			this->decrementPosition(a_position + 1);
			this->decrementSize(a_position + 1);
			LinkedRawPointerListLog(ame_Log_EndMethod, "cutAfter", "println", "");
			return b_node;
		}
		virtual bool cutDeleteAfter(int a_position){
			LinkedRawPointerListLog(ame_Log_StartMethod, "cutDeleteAfter", "println", "");
			LinkedListNode<T>* node = cutAfter(a_position);
			if(node == nullptr){
				return false;
			}
			this->deleteListNode(node);
			LinkedRawPointerListLog(ame_Log_EndMethod, "cutDeleteAfter", "println", "");
			return false;
		}
		
		virtual bool isNull()const{
			LinkedStorageLog(ame_Log_StartMethod, "isNull", "println", "");
			LinkedStorageLog(ame_Log_EndMethod, "isNull", "println", this->m_values == nullptr);
			return m_node == nullptr || m_start == nullptr || m_end == nullptr;
		}
		
		virtual bool isEmpty()const{
			LinkedStorageLog(ame_Log_StartMethod, "isEmpty", "println", "");
			LinkedStorageLog(ame_Log_Statement, "isEmpty", "println", "Node Size:");
			LinkedStorageLog(ame_Log_Statement, "isEmpty", "println", this->getSize());
			return m_node == nullptr || m_start == nullptr || m_end == nullptr || this->getSize() == 0;
		}
		
		virtual bool replace(int i, int j){
			LinkedStorageLog(ame_Log_StartMethod, "replace", "println", "");
			if(i >= this->getPosition() || j >= this->getPosition() || i == j){
				return false;
			}
			LinkedListNode<T>* node = getStartNode();
			LinkedListNode<T>* node_i = nullptr;
			LinkedListNode<T>* node_j = nullptr;
			for(int count = 0; node != nullptr; count++){
				T* i_value = node->get();
				if(i == count){
					node_i = node;
				}
				if(j == count){
					node_j = node;
				}
				if(node_i != nullptr && node_j != nullptr){
					T* i_value = node_i->get();
					T* j_value = node_j->get();
					node_i->set(j_value);
					node_j->set(i_value);
					return true;
				}
				node = getNextNode(node);
			}
			LinkedStorageLog(ame_Log_EndMethod, "replace", "println", "");
			return true;
		}

		virtual void set(int a_position, T* a_pointer){
			LinkedStorageLog(ame_Log_StartMethod, "set", "println", "T* a_pointer");
			LinkedStorageLog(ame_Log_StartMethod, "set", "println", "Position: ");
			LinkedStorageLog(ame_Log_StartMethod, "set", "println", a_position);
			if(this->isEmpty() && a_position >= this->getSize()){
				LinkedStorageLog(ame_Log_EndMethod, "set", "println", "this->isEmpty()");
				return;
			}
			if(this->m_values[a_position] == a_pointer){
				LinkedStorageLog(ame_Log_EndMethod, "set", "println", "this->m_values[a_position] == a_value");
				return;
			}
			this->removingMemory(this->m_values[a_position]);
			this->m_values[a_position] = a_pointer;
			this->addingMemory(a_pointer);
			LinkedStorageLog(ame_Log_EndMethod, "set", "println", "");
		}

		virtual void set(int a_position, const Pointer<T>& a_pointer){
			LinkedStorageLog(ame_Log_StartMethod, "set", "println", "const Pointer<T>& a_pointer");
			this->set(a_position, a_pointer.get());
			LinkedStorageLog(ame_Log_EndMethod, "set", "println", "");
		}
		
		virtual Pointer<T> get(int a_position)const{
			LinkedStorageLog(ame_Log_StartMethod, "get", "println", "");
			if(this->isEmpty() || a_position >= this->getSize()){
				return Pointer<T>(nullptr, this->m_manager);
			}
			LinkedStorageLog(ame_Log_EndMethod, "get", "println", "");
			return Pointer<T>(this->m_values[a_position], this->m_manager);
		}

		virtual bool contain(T* a_value){
			LinkedStorageLog(ame_Log_StartMethod, "contain", "println", "");
			if(this->isEmpty()){
				LinkedStorageLog(ame_Log_Statement, "contain", "println", "this->isEmpty()");
				LinkedStorageLog(ame_Log_EndMethod, "contain", "println", "return false");
				return false;
			}
			for(int x = 0; x < this->getSize(); x++){
				if(a_value == this->m_values[x]){
					LinkedStorageLog(ame_Log_Statement, "contain", "println", "a_value == this->m_values[x]");
					LinkedStorageLog(ame_Log_EndMethod, "contain", "println", "return true");
					return true;
				}
			}
			LinkedStorageLog(ame_Log_EndMethod, "contain", "println", "");
			return false;
		}

		virtual bool contain(const Pointer<T>& a_value){
			LinkedStorageLog(ame_Log_StartMethod, "contain", "println", "");
			LinkedStorageLog(ame_Log_EndMethod, "contain", "println", "");
			return this->contain(a_value.get());
		}
		
		virtual int getIndex(T* a_value){
			LinkedStorageLog(ame_Log_StartMethod, "getIndex", "println", "");
			if(this->isEmpty()){
				LinkedStorageLog(ame_Log_EndMethod, "getIndex", "println", "this->isEmpty()");
				return -1;
			}
			for(int x = 0; x < this->getSize(); x++){
				if(a_value == this->m_values[x]){
					LinkedStorageLog(ame_Log_EndMethod, "getIndex", "println", "a_value == this->m_values[x]");
					return x;
				}
			}
			LinkedStorageLog(ame_Log_EndMethod, "getIndex", "println", "");
			return -1;
		}

		virtual int getIndex(const Pointer<T>& a_value){
			LinkedStorageLog(ame_Log_StartMethod, "getIndex", "println", "");
			LinkedStorageLog(ame_Log_EndMethod, "getIndex", "println", "");
			return this->getIndex(a_value.get());
		}

		virtual void clear(){
			LinkedStorageLog(ame_Log_StartMethod, "clear", "println", "");
			if(this->isEmpty()){
				LinkedStorageLog(ame_Log_EndMethod, "clear", "println", "this->isEmpty()");
				return;
			}
			for(int x = 0; x < this->getSize(); x++){
				this->removingMemory(this->m_values[x]);
				this->m_values[x] = nullptr;
			}
			LinkedStorageLog(ame_Log_EndMethod, "clear", "println", "");
		}

		virtual bool removeByPointer(T* a_value){
			LinkedStorageLog(ame_Log_StartMethod, "removeByPointer", "println", "");
			int i_position = this->getIndex(a_value);
			LinkedStorageLog(ame_Log_EndMethod, "removeByPointer", "println", "removed position: ");
			LinkedStorageLog(ame_Log_EndMethod, "removeByPointer", "println", i_position);
			if(this->isEmpty() || i_position >= this->getSize() || i_position < 0){
				return false;
			}
			LinkedStorageLog(ame_Log_EndMethod, "removeByPointer", "println", "");
			this->removeByPosition(i_position);
			return true;
		}

		virtual bool removeByPointer(const Pointer<T>& a_value){
			LinkedStorageLog(ame_Log_StartMethod, "removeByPointer", "println", "");
			LinkedStorageLog(ame_Log_EndMethod, "removeByPointer", "println", "");
			return this->removeByPointer(a_value.get());
		}

		virtual Pointer<T> removeByPosition(int a_position){
			LinkedStorageLog(ame_Log_StartMethod, "removeByPosition", "println", "");
			if(this->isEmpty() || a_position >= this->getSize() || a_position < 0){
				return nullptr;
			}
			T* i_value = this->m_values[a_position];
			Pointer<T> i_pointer = Pointer<T>(i_value, this->m_manager);
			this->m_values[a_position] = nullptr;
			this->removingMemory(i_value);
			LinkedStorageLog(ame_Log_EndMethod, "removeByPosition", "println", "");
			return i_pointer;
		}

		virtual int reorder(){
			LinkedStorageLog(ame_Log_StartMethod, "reorder", "println", "");
			if(this->isNull()){
				LinkedStorageLog(ame_Log_EndMethod, "clear", "println", "this->isNull()");
				return -1;
			}
			if(this->isEmpty()){
				LinkedStorageLog(ame_Log_EndMethod, "clear", "println", "this->isEmpty()");
				return 0;
			}
			int i_offset = 0;
			for(int x = 0; x < this->getSize(); x++){
				T* f_value = this->m_values[x];
				if(f_value == nullptr){
					continue;
				}
				this->m_values[i_offset] = f_value;
				i_offset++;
			}
			LinkedStorageLog(ame_Log_EndMethod, "reorder", "println", "");
			return i_offset;
		}

		virtual MemoryStorage<T>* clone()const{
			LinkedStorageLog(ame_Log_StartMethod, "clone", "println", "");
			LinkedStorage<T>* i_clone = new LinkedStorage<T>();
			i_clone->expandLocal(this->getSize());
			for(int x = 0; x < this->getSize(); x++){
				i_clone->set(x, this->get(x));
			}
			LinkedStorageLog(ame_Log_EndMethod, "clone", "println", "");
			return i_clone;
		}

		virtual bool expandLocal(int a_size){
			LinkedStorageLog(ame_Log_StartMethod, "expandLocal", "println", "");
			
			int i_size = this->getSize() + a_size;
			LinkedStorageLog(ame_Log_Statement, "expandLocal", "println", "List Size:");
			LinkedStorageLog(ame_Log_Statement, "expandLocal", "println", this->getSize());	
			LinkedStorageLog(ame_Log_Statement, "expandLocal", "println", "List extra size added:");
			LinkedStorageLog(ame_Log_Statement, "expandLocal", "println", a_size);
			LinkedStorageLog(ame_Log_Statement, "expandLocal", "println", "List new size:");
			LinkedStorageLog(ame_Log_Statement, "expandLocal", "println", i_size);
			if(i_size <= 1){
				LinkedStorageLog(ame_Log_EndMethod, "expandLocal", "println", "new size is too small");
				return false;
			}
			T **nT;
			nT = new T*[i_size];
			for(int x = 0; x < this->getSize(); x++){
				LinkedStorageLog(ame_Log_Statement, "expandLocal", "println", "iteration:");
				LinkedStorageLog(ame_Log_Statement, "expandLocal", "println", x);
				if(this->m_values != nullptr){
					nT[x] = this->m_values[x];
				}
			}
			for(int x = this->getSize(); x < i_size; x++){
				LinkedStorageLog(ame_Log_Statement, "expandLocal", "println", "iteration:");
				LinkedStorageLog(ame_Log_Statement, "expandLocal", "println", x);
				nT[x] = nullptr;
			}
			if(this->m_values != nullptr){
				LinkedStorageLog(ame_Log_Statement, "expandLocal", "println", "this->m_values != nullptr");
				delete[] this->m_values;
			}
			this->m_values = nT;
			this->setSize(i_size);
			
			LinkedStorageLog(ame_Log_Statement, "expandLocal", "println", "List Size:");
			LinkedStorageLog(ame_Log_Statement, "expandLocal", "println", this->getSize());	
			LinkedStorageLog(ame_Log_EndMethod, "expandLocal", "println", "");
			return true;
		}
	
	protected:
		LinkedNode<T>* m_start = nullptr;
		LinkedNode<T>* m_end = nullptr;
		LinkedNode<T>* m_node = nullptr;
};

}

#endif