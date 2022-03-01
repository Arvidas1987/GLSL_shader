#include "GLSL_shader.hpp"
#include <iostream>
#include <string>
#include <utility> // for std::move()

bool GLSL_shader::static_GLSL_shader_debug = false;

std::string  get_shader_info_log( GLuint shader )
{
    std::string temp;
    GLint log_length;
    glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &log_length );

    char *shader_info_log = new char[log_length+1];
    glGetShaderInfoLog( shader, log_length, nullptr, shader_info_log );
    shader_info_log[log_length]='\0';

    temp.append( shader_info_log );
    temp.shrink_to_fit();

    delete[] shader_info_log;

    return std::move(temp);
}

//-----------------------------------------------------------------------------
//                     konstruktor domyslny
//                     implicit ctor
//-----------------------------------------------------------------------------
GLSL_shader::GLSL_shader():m_program(0)
{
    m_program = glCreateProgram();
}

//-----------------------------------------------------------------------------
//                     destruktor
//-----------------------------------------------------------------------------
GLSL_shader::~GLSL_shader()
{
    glDeleteProgram( m_program );

    if ( static_GLSL_shader_debug ){
        GLint is_program_delete_status_false;
        glGetProgramiv(m_program, GL_DELETE_STATUS, &is_program_delete_status_false);

        if ( is_program_delete_status_false == GL_FALSE ){
            std::cout << "Nie wywolano funkcji 'glDeleteProgram()'\n";
        } else {
            std::cout << "Wywolano funkcje 'glDeleteProgram()'\n";
        }
    }
}

//-----------------------------------------------------------------------------
//                     compile_shader()
//-----------------------------------------------------------------------------
void GLSL_shader::compile_shader( GLenum shader_type,
                                  const GLchar *const *shader_source_string )
{
    std::string Error_messages;

    //utworzenie i kompilacja shadera <shader_type>
    GLuint temp_shader = glCreateShader(shader_type);
    glShaderSource(temp_shader, 1, shader_source_string, nullptr);

    glCompileShader(temp_shader);

    if( static_GLSL_shader_debug ){
        GLint is_compile_shader_status_false;
        glGetShaderiv( temp_shader, GL_COMPILE_STATUS, &is_compile_shader_status_false );

        if( is_compile_shader_status_false == GL_FALSE ){
            Error_messages.append( "Niepoprawna kompilacja shadera: " )
                          .append( *shader_source_string )//tu jest dobrze
                          .append( "\n" )
                          .append( get_shader_info_log( temp_shader ) )
                          .append( "\n" );
        }
    }

    glAttachShader(m_program, temp_shader);

    glLinkProgram(m_program);
    if( static_GLSL_shader_debug ){
        GLint is_link_shader_status_false;
        glGetShaderiv( temp_shader, GL_LINK_STATUS, &is_link_shader_status_false );

        if( is_link_shader_status_false == GL_FALSE ){
            Error_messages.append( "Niepoprawna konsolidacja shadera.\n" )
                          .append( get_shader_info_log( temp_shader ) )
                          .append( "\n" );
        }
    }

    if( static_GLSL_shader_debug ){
        glValidateProgram(m_program);
        GLint is_validate_program_status_false;
        glGetShaderiv( temp_shader, GL_VALIDATE_STATUS, &is_validate_program_status_false );

        if( is_validate_program_status_false == GL_FALSE ){
            Error_messages.append( "Niepoprawna walidacja programu.\n")
                          .append( get_shader_info_log( temp_shader ) )
                          .append( "\n" );
        }
    }
    //usuniecie shaderow, bo znajduja sie juz w programie
    glDeleteShader(temp_shader);

    Error_messages.shrink_to_fit();
    std::cout << Error_messages;
}

//-----------------------------------------------------------------------------
//                          useProgram()
//-----------------------------------------------------------------------------
void GLSL_shader::use_program(){
    glUseProgram( m_program );
}

//-----------------------------------------------------------------------------
//                          debug()
//-----------------------------------------------------------------------------
void GLSL_shader::debug(){
    static_GLSL_shader_debug = !static_GLSL_shader_debug;
}
