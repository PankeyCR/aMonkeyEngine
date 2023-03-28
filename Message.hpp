
#ifndef Message_hpp
#define Message_hpp
#define Message_AVAILABLE

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

class Message : public Printable{
public:
Message(){}
Message(const Message& b){
	m_id = b.m_id;
	m_name = b.m_name;
	m_text = b.m_text;
	m_type = b.m_type;
	m_array = b.m_array;
}
Message(Note txt){
	m_text = txt;
}
Message(int i,Note txt){
	m_id = i;
	m_text = txt;
}
Message(Note mname,Note txt){
	m_name = mname;
	m_text = txt;
}
Message(Note mname, Note mType,Note txt){
	m_name = mname;
	m_type = mType;
	m_text = txt;
}
Message(int i, Note mname, Note mType,Note txt){
	m_name = mname;
	m_type = mType;
	m_id = i;
	m_text = txt;
}
Message(ByteArray b){
	m_array = b;
}
Message(int i,ByteArray b){
	m_id = i;
	m_array = b;
}
Message(Note mname,ByteArray b){
	m_name = mname;
	m_array = b;
}
Message(Note mname, Note mType,ByteArray b){
	m_name = mname;
	m_type = mType;
	m_array = b;
}
Message(int i, Note mname, Note mType,ByteArray b){
	m_name = mname;
	m_type = mType;
	m_id = i;
	m_array = b;
}
// Message(Note txt){
	// m_text = txt;
// }
// Message(int i,Note txt){
	// m_id = i;
	// m_text = txt;
// }
// Message(Note mType,Note txt){
	// m_type = mType;
	// m_text = txt;
// }
// Message(Note mType,int i,Note txt){
	// m_type = mType;
	// m_id = i;
	// m_text = txt;
// }
virtual ~Message(){}

virtual int id()const{
	return m_id;
}
virtual Note name()const{
	return m_name;
}
virtual Note text()const{
	return m_text;
}
virtual Note type()const{
	return m_type;
}
virtual ByteArray array()const{
	return m_array;
}
// virtual Note textNote(){
	// return m_text.toNote();
// }
// virtual Note typeNote(){
	// return m_type.toNote();
// }

virtual void id(int i){
	m_id = i;
}
virtual void name(Note n){
	m_name = n;
}
virtual void text(Note t){
	m_text = t;
}
virtual void type(Note t){
	m_type = t;
}
virtual void array(ByteArray t){
	m_array = t;
}
// virtual void text(const Note& t){
	// m_text = t;
// }
// virtual void type(const Note& t){
	// m_type = t;
// }
// virtual void operator=(const Note& b){
	// m_text = b;
// }
virtual void operator=(const Note& b){
	m_text = b;
}
virtual void operator=(const Message& b){
	m_id = b.m_id;
	m_name = b.m_name;
	m_text = b.m_text;
	m_type = b.m_type;
}
virtual bool operator==(const Message& b){
	return m_id == b.m_id && m_name == b.m_name && m_text == b.m_text && m_type == b.m_type;
}
virtual bool operator!=(const Message& b){
	return m_id != b.m_id && m_name != b.m_name && m_text != b.m_text && m_type != b.m_type;
}

virtual size_t printTo(Print& p) const{
	size_t i_size = 0;
	i_size += p.print("Message: <");
	i_size += p.print("id: ");
	i_size += p.print(m_id);
	i_size += p.print("name: ");
	i_size += p.print(m_name);
	i_size += p.print("type: ");
	i_size += p.print(m_type);
	i_size += p.print("text: ");
	i_size += p.print(m_text);
	i_size += p.print(">");
	return i_size;
}
protected:
int m_id = -1;
Note m_name;
Note m_type;

Note m_text;
ByteArray m_array;
};

}

#endif