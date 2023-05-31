
#ifndef ame_Hardware_Defined

	#if defined(__MINGW32__) || defined(_WIN32) || defined(__CYGWIN32__) || defined(_MSC_VER)
		#ifndef ame_Level_Defined
			#define ame_Level_15
			#define ame_Level_Defined
		#endif
		#ifndef ame_Enviroment_Defined
			#define ame_Windows
			#define ame_Enviroment_Defined
		#endif
		#ifndef ame_Enviroment_Name
			#define ame_Enviroment_Name "Windows"
		#endif
	#endif

#endif