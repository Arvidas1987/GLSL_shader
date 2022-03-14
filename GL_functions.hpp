#ifndef _GL_FUNTIONS_HPP_
#define _GL_FUNTIONS_HPP_

///////////////////////////////////////////////////////////////////////////////
//                   GL_check_error()
//	Wypisanie funkcji, pliku i linijki, a nastepnie tresc bledu OpenGL.
//	function to nazwa funkcji w ktorej wystapil blad.
//	file 	 to nazwa pliku w ktorym wystapil blad.
//	line 	 to linijka w ktorym wystapil blad.
///////////////////////////////////////////////////////////////////////////////
void GL_check_error(const char* function, const char* file, unsigned int line);

#ifdef _VISUAL_STUDIO_
#	define _BREAKPOINT_ __debugbreak();
#else
#	define _BREAKPOINT_
#endif // _VISUAL_STUDIO_

#ifdef _DEBUG_
// use it to debug any gl* function
#	define GL_DEBUG_MACRO( x )\
                _BREAKPOINT_\
                x;\
                GL_check_error( #x, __FILE__, __LINE__);
#else
#	define GL_DEBUG_MACRO( x )\
                x;
#endif // _DEBUG_

#endif // _GL_FUNTIONS_HPP_
