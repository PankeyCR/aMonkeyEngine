
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
	
	int getSplitSize(const Note& a_note, char a_split){
		return a_note.getSplitSize(a_split);
	}
	
	Note splitNote(const Note& a_note, int a_position, char a_split){
		Note i_note;
		bool i_ready_to_capture = false;
		for(int x = 0; x < a_note.length(); x++){
			char f_char = a_note.get(x);
			if(f_char == a_split){
				if(i_ready_to_capture){
					return i_note;
				}
				i_ready_to_capture = true;
				continue;
			}
			if(!i_ready_to_capture){
				continue;
			}
			i_note.addLocalValue(f_char);
		}
		return i_note;
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
			i_note.addLocalValue(f_char);
		}
		if(!i_note.isEmpty()){
			i_list.add(i_note);
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
			i_note.addLocalValue(f_char);
		}
		if(!i_note.isEmpty()){
			i_list.add(i_note);
		}
		return i_list;
	}

	char getChar(const Note& a_value, int a_position){
		return a_value.get(a_position);
	}

	Note addNote(const Note& a_value_1, const Note& a_value_2){
		return a_value_1.addNote(a_value_2);
	}

	void addLocalNote(Note& a_value_1, const Note& a_value_2){
		a_value_1.addLocalNote(a_value_2);
	}

	void addLocalValue(Note& a_value_1, char a_value_2){
		a_value_1.addLocalValue(a_value_2);
	}

	Note addNoteValue(const Note& a_value, char a_char){
		return a_value.addValue(a_char);
	}

	Note getNotePart(const Note& a_value, int a_part){
		return a_value.getArrayPart(a_part);
	}

	bool isNoteEmpty(const Note& a_value){
		return a_value.isEmpty();
	}

	bool toBool(const Note& a_value){
		return a_value.toBool();
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
	
	Note splitNote(const Note& a_note, int a_position, char a_split){
		Note i_note;
		bool i_ready_to_capture = false;
		for(int x = 0; x < a_note.length(); x++){
			char f_char = a_note.charAt(x);
			if(f_char == a_split){
				if(i_ready_to_capture){
					return i_note;
				}
				i_ready_to_capture = true;
				continue;
			}
			if(!i_ready_to_capture){
				return i_note;
			}
			i_note += f_char;
		}
		return i_note;
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
		if(i_note != ""){
			i_list.add(i_note);
		}
		return i_list;
	}
	
	int getSplitSize(const Note& a_note, char a_split){
		int i_split_size = 1;
		for(int x = 0; x < a_note.length(); x++){
			char f_char = a_note.charAt(x);
			if(f_char == a_split){
				i_split_size++;
			}
		}
		return i_split_size;
	}

	char getChar(const Note& a_value, int a_position){
		return a_value.charAt(a_position);
	}

	Note addNote(const Note& a_value_1, const Note& a_value_2){
		return a_value_1 + a_value_2;
	}

	void addLocalNote(Note& a_value_1, const Note& a_value_2){
		a_value_1 = a_value_1 + a_value_2;
	}

	void addLocalValue(Note& a_value_1, char a_value_2){
		a_value_1 += a_value_2;
	}

	Note addNoteValue(const Note& a_value, char a_char){
		return a_value + a_char;
	}

	Note getNotePart(const Note& a_value, int a_part){
		return a_value.substring(a_part);
	}

	bool isNoteEmpty(const Note& a_value){
		return a_value == "";
	}

	bool toBool(const Note& a_value){
		return a_value == "1";
	}
		
	#endif
		
	#endif
	
	#if defined(ame_Windows)
	
	// IPAddress toIPAddress(const Note& a_note){
	// 	IPAddress ip;
	// 	ip.fromString(a_note.toString());
	// 	return ip;
	// }
	
	// int toIPAddress(const Note& a_note, int a_position){
	// 	IPAddress ip;
	// 	ip.fromString(a_note.toString());
	// 	return ip[a_position];
	// }
	
	// bool isIP(const Note& a_note){
	// 	IPAddress ip;
	// 	ip.fromString(a_note.toString());
	// 	if(ip[0] >= 0 && ip[1] >= 0 && ip[2] >= 0 && ip[3] >= 0){
	// 		return true;
	// 	}
	// 	return false;
	// }
	
	int getSplitSize(const Note& a_note, char a_split){
		return a_note.getSplitSize(a_split);
	}
	
	Note splitNote(const Note& a_note, int a_position, char a_split){
		Note i_note;
		bool i_ready_to_capture = false;
		for(int x = 0; x < a_note.length(); x++){
			char f_char = a_note.get(x);
			if(f_char == a_split){
				if(i_ready_to_capture){
					return i_note;
				}
				i_ready_to_capture = true;
				continue;
			}
			if(!i_ready_to_capture){
				continue;
			}
			i_note.addLocalValue(f_char);
		}
		return i_note;
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
			i_note.addLocalValue(f_char);
		}
		if(!i_note.isEmpty()){
			i_list.add(i_note);
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
			i_note.addLocalValue(f_char);
		}
		if(!i_note.isEmpty()){
			i_list.add(i_note);
		}
		return i_list;
	}

	char getChar(const Note& a_value, int a_position){
		return a_value.get(a_position);
	}

	Note addNote(const Note& a_value_1, const Note& a_value_2){
		return a_value_1.addNote(a_value_2);
	}

	void addLocalNote(Note& a_value_1, const Note& a_value_2){
		a_value_1.addLocalNote(a_value_2);
	}

	void addLocalValue(Note& a_value_1, char a_value_2){
		a_value_1.addLocalValue(a_value_2);
	}

	Note addNoteValue(Note& a_value, char a_char){
		return a_value.addValue(a_char);
	}

	Note getNotePart(Note& a_value, int a_part){
		return a_value.getArrayPart(a_part);
	}

	bool isNoteEmpty(const Note& a_value){
		return a_value.isEmpty();
	}

	bool toBool(const Note& a_value){
		return a_value.toBool();
	}

	#endif
}

#endif