#include "GL_functions.hpp"
#
#define GLEW_STATIC
#include <GL/glew.h>
#
#include "macro_iostream.hpp" // WRITELN()

//-----------------------------------------------------------------------------
//						GL_check_error()
//-----------------------------------------------------------------------------
void GL_check_error(const char* function, const char* file, unsigned int line){

    GLenum error_number = glGetError();

    if( error_number != GL_NO_ERROR ){
        WRITELN( std::hex << "Error nr: 0x" << error_number )
        WRITELN( function << " -> "<< file << ": " << line )

        switch( error_number ){
            case GL_TABLE_TOO_LARGE:
                WRITELN("\tGL_TABLE_TOO_LARGE:");
                WRITELN("\t[EN]The specified table exceeds the implementation's maximum supported table size.");
                WRITELN("\t    The offending command is ignored and has no other side effect than to set the error flag.");
                break;
            case GL_CONTEXT_LOST:// openGL4.5 or ARB_KHR_robustness
                WRITELN("GL_CONTEXT_LOST:");
                WRITELN("[PL]Utrata kontekstu renderingu i jego reset.");
                break;
            case GL_INVALID_ENUM:
                WRITELN("\tGL_INVALID_ENUM:");
                WRITELN("\t[PL]Dla argumentu wyliczeniowego okreslono niedopuszczalna wartosc.");
                WRITELN("\t    Polecenie jest ignorowane i nie ma innego efektu ubocznego niz ustawienie flagi bledu.");
                WRITELN("\t[EN]An unacceptable value is specified for an enumerated argument.");
                WRITELN("\t    The offending command is ignored and has no other side effect than to set the error flag.");
                break;
            case GL_INVALID_VALUE:
                WRITELN("\tGL_INVALID_VALUE:");
                WRITELN("\t[PL]Argument liczbowy poza zakresem.");
                WRITELN("\t[EN]A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.");
                break;
            case GL_INVALID_OPERATION:
                WRITELN("\tGL_INVALID_OPERATION:");
                WRITELN("\t[PL]Nielegalna operacja w bierzacym stanie.");
                WRITELN("\t[EN]The specified operation is not allowed in the current state.");
                WRITELN("\t    The offending command is ignored and has no other side effect than to set the error flag.");
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
            //case GL_INVALID_FRAMEBUFFER_OPERATION_EXT:
                WRITELN("\tGL_INVALID_FRAMEBUFFER_OPERATION:");
                WRITELN("\t[PL]Niekompletny obiekt bufora ramki.");
                WRITELN("\t[EN]The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag.");
                break;
            case GL_OUT_OF_MEMORY:
                WRITELN("\tGL_OUT_OF_MEMORY:");
                WRITELN("\t[PL]Brak pamieci do wykonania polecenia.");
                WRITELN("\t[EN]There is not enough memory left to execute the command.");
                WRITELN("\t    The state of the GL is undefined, except for the state of the error flags, after this error is recorded.");
                break;
            case GL_STACK_OVERFLOW:
                WRITELN("\tGL_STACK_OVERFLOW:");
                WRITELN("\t[PL]Nadmiar stosu.");
                WRITELN("\t[EN]An attempt has been made to perform an operation that would cause an internal stack to overflow.");
                break;
            case GL_STACK_UNDERFLOW:
                WRITELN("\tGL_STACK_UNDERFLOW:");
                WRITELN("\t[PL]Niedomiar stosu.");
                WRITELN("\t[EN]An attempt has been made to perform an operation that would cause an internal stack to underflow.");
                break;
            case GL_NO_ERROR:
            /*
                WRITELN("\tGL_NO_ERROR:");
                WRITELN("\t[PL]Zaden blad nie zostal zarejestrowany. Wartosc tej symbolicznej stalej jest");
                WRITELN("\tzagwarantowana na 0.");
                WRITELN("\t[En]No error has been recorded. The value of this symbolic constant is guaranteed");
                WRITELN("\tto be 0.");
            */
                break;
            default:
                WRITELN("\t[PL]Nieznany blad.");
                WRITELN("\t[EN]Unnoun error.");
                break;
        }
        //abort();
        //exit(0);
    }
}
