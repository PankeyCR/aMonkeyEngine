
#ifndef NoteHelper_hpp
#define NoteHelper_hpp
#define NoteHelper_AVAILABLE 

#include "Note.hpp"
#include "PrimitiveList.hpp"

#ifdef ame_Windows

#endif

#ifdef ame_ArduinoIDE
	#include "IPAddress.h"
#endif

namespace ame{
	#if defined(ame_ArduinoIDE)

	#if defined(Note_AVAILABLE)
	
	IPAddress toIPAddress(const Note& a_note){
		IPAddress ip;
		ip.fromString(a_note.toString());
		return ip;
	}
	
	int toIPAddress(const Note& a_note, int a_position){
		IPAddress ip;
		ip.fromString(a_note.toString());
		return ip[a_position];
	}
	
	bool isIP(const Note& a_note){
		IPAddress ip;
		ip.fromString(a_note.toString());
		if(ip[0] >= 0 && ip[1] >= 0 && ip[2] >= 0 && ip[3] >= 0){
			return true;
		}
		return false;
	}
	
	PrimitiveList<Note> splitNote(const Note& a_note, char a_split){
		PrimitiveList<Note> i_list;
		Note i_note;
		for(int x = 0; x < a_note.length(); x++){
			char f_char = a_note.get(x);
			if(f_char == a_split){
				i_list.add(i_note);
				i_note = "";
				continue;
			}
			i_note += f_char;
		}
		return i_list;
	}
	
	PrimitiveList<Note> splitFirstNote(int a_size, const Note& a_note, char a_split){
		PrimitiveList<Note> i_list;
		Note i_note;
		int i_size = 1;
		for(int x = 0; x < a_note.length(); x++){
			char f_char = a_note.get(x);
			if(f_char == a_split && a_size < i_size){
				i_list.add(i_note);
				i_note = "";
				i_size++;
				continue;
			}
			i_note += f_char;
		}
		if(!i_note.isEmpty()){
			i_list.add(i_note);
		}
		return i_list;
	}
	
	#else
	
	IPAddress toIPAddress(const Note& a_note){
		IPAddress ip;
		ip.fromString(a_note);
		return ip;
	}
	
	int toIPAddress(const Note& a_note, int a_position){
		IPAddress ip;
		ip.fromString(a_note);
		return ip[a_position];
	}
	
	bool isIP(const Note& a_note){
		IPAddress ip;
		ip.fromString(a_note);
		if(ip[0] >= 0 && ip[1] >= 0 && ip[2] >= 0 && ip[3] >= 0){
			return true;
		}
		return false;
	}
	
	PrimitiveList<Note> splitNote(const Note& a_note, char a_split){
		PrimitiveList<Note> i_list;
		Note i_note;
		for(int x = 0; x < a_note.length(); x++){
			char f_char = a_note.charAt(x);
			if(f_char == a_split){
				i_list.add(i_note);
				i_note = "";
				continue;
			}
			i_note += f_char;
		}
		return i_list;
	}
	
	PrimitiveList<Note> splitFirstNote(int a_size, const Note& a_note, char a_split){
		PrimitiveList<Note> i_list;
		Note i_note;
		int i_size = 1;
		for(int x = 0; x < a_note.length(); x++){
			char f_char = a_note.charAt(x);
			if(f_char == a_split && a_size < i_size){
				i_list.add(i_note);
				i_note = "";
				i_size++;
				continue;
			}
			i_note += f_char;
		}
		if(!i_note.isEmpty()){
			i_list.add(i_note);
		}
		return i_list;
	}
		
	#endif
		
	#endif
}

#endif