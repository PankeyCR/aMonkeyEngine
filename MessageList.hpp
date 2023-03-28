
#ifndef MessageList_hpp
#define MessageList_hpp
#define MessageList_AVAILABLE

#include "PrimitiveList.hpp"
#include "Note.hpp"
#include "ByteArray.hpp"

#ifdef ame_Windows
	#include "ame_Printable.hpp"
	#include "ame_Print.hpp"
#endif

#ifdef ame_ArduinoIDE
	#include "Arduino.h"
	#include "Printable.h"
#endif

namespace ame{

class MessageList : public Printable{
public:
MessageList(){}
MessageList(const MessageList& b){
	m_id = b.m_id;
	m_name = b.m_name;
	m_list = b.m_list;
	m_type = b.m_type;
	m_array = b.m_array;
}
virtual ~MessageList(){}

virtual int id()const{
	return m_id;
}
virtual Note name()const{
	return m_name;
}
virtual PrimitiveList<Note> list()const{
	return m_list;
}
virtual Note type()const{
	return m_type;
}
virtual ByteArray array()const{
	return m_array;
}

virtual void id(int i){
	m_id = i;
}
virtual void name(Note n){
	m_name = n;
}
virtual void list(PrimitiveList<Note> t){
	m_list = t;
}
virtual void type(Note t){
	m_type = t;
}
virtual void operator=(const MessageList& b){
	m_id = b.m_id;
	m_name = b.m_name;
	m_list = b.m_list;
	m_type = b.m_type;
}
virtual bool operator==(const MessageList& b){
	return m_id == b.m_id && m_name == b.m_name && m_list == b.m_list && m_type == b.m_type;
}
virtual bool operator!=(const MessageList& b){
	return m_id != b.m_id && m_name != b.m_name && m_list != b.m_list && m_type != b.m_type;
}

virtual size_t printTo(Print& p) const{
	size_t i_size = 0;
	i_size += p.print("MessageList: <");
	i_size += p.print("id: ");
	i_size += p.print(m_id);
	i_size += p.print("name: ");
	i_size += p.print(m_name);
	i_size += p.print("type: ");
	i_size += p.print(m_type);
	// i_size += p.print("list: ");
	// i_size += p.print(m_list);
	i_size += p.print(">");
	return i_size;
}
protected:
int m_id = -1;
Note m_name;
Note m_type;

PrimitiveList<Note> m_list;
ByteArray m_array;
};

}

#endif