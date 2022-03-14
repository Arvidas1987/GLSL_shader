#include "GLSL_shader.hpp"
#include <iostream>
#include <utility> // std::move()
#
#include "GL_functions.hpp" // GL_DEBUG_MACRO()
#
//============================================================================//
bool GLSL_shader::static_GLSL_shader_debug = false;

//-----------------------------------------------------------------------------
//                      get_shader_info_log()
//-----------------------------------------------------------------------------
std::string get_shader_info_log( GLuint shader )
{
    GLint log_length{};
    GL_DEBUG_MACRO( glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &log_length ) )

    char *shader_info_log = new char[log_length+1];
    GL_DEBUG_MACRO( glGetShaderInfoLog( shader, log_length, nullptr, shader_info_log ) )
    shader_info_log[log_length]='\0';

    std::string temp(shader_info_log);
    temp.shrink_to_fit();

    delete[] shader_info_log;

    return temp;
}

//-----------------------------------------------------------------------------
//                     konstruktor domyslny
//                     implicit ctor
//-----------------------------------------------------------------------------
GLSL_shader::GLSL_shader():m_program(0)
{
    GL_DEBUG_MACRO( m_program = glCreateProgram() )
}

//-----------------------------------------------------------------------------
//                     destruktor
//-----------------------------------------------------------------------------
GLSL_shader::~GLSL_shader()
{
    GL_DEBUG_MACRO( glDeleteProgram( m_program ) )
}

//-----------------------------------------------------------------------------
//                     compile_shader()
//-----------------------------------------------------------------------------
void GLSL_shader::compile_shader( const std::string shader_name,
                                  GLenum shader_type,
                                  const GLchar *const *shader_source_string )
{
    std::string Error_messages;

    if( static_GLSL_shader_debug ){
        Error_messages.append("==================== ")
                      .append(shader_name)
                      .append(" ====================\n");
    }


    //utworzenie i kompilacja shadera <shader_type>
    GL_DEBUG_MACRO( GLuint temp_shader = glCreateShader(shader_type) )
    GL_DEBUG_MACRO( glShaderSource(temp_shader, 1, shader_source_string, nullptr) )

    GL_DEBUG_MACRO( glCompileShader(temp_shader) )

    if( static_GLSL_shader_debug ){
        GLint is_compile_shader_status_equals_false;
        GL_DEBUG_MACRO( glGetShaderiv( temp_shader,
                                       GL_COMPILE_STATUS,
                                       &is_compile_shader_status_equals_false ) )

        if( is_compile_shader_status_equals_false == GL_FALSE ){
            Error_messages.append( "Niepoprawna kompilacja shadera: \n" )
                          .append( *shader_source_string )
                          .append( "\n" )
                          .append( std::move( get_shader_info_log( temp_shader ) ) )
                          .append( "\n" );
        }
    }

    GL_DEBUG_MACRO( glAttachShader(m_program, temp_shader) )

    GL_DEBUG_MACRO( glLinkProgram(m_program) )
    if( static_GLSL_shader_debug ){
        GLint is_link_shader_status_equals_false;
        GL_DEBUG_MACRO( glGetShaderiv( temp_shader,
                                       GL_LINK_STATUS,
                                       &is_link_shader_status_equals_false ) )

        if( is_link_shader_status_equals_false == GL_FALSE ){
            Error_messages.append( "Niepoprawna konsolidacja shadera.\n" )
                          .append( std::move( get_shader_info_log( temp_shader ) ) )
                          .append( "\n" );
        }
    }

    if( static_GLSL_shader_debug ){
        GL_DEBUG_MACRO( glValidateProgram(m_program) )
        GLint is_validate_program_status_equals_false;
        GL_DEBUG_MACRO( glGetShaderiv( temp_shader,
                        GL_VALIDATE_STATUS,
                        &is_validate_program_status_equals_false ) )

        if( is_validate_program_status_equals_false == GL_FALSE ){
            Error_messages.append( "Niepoprawna walidacja programu.\n")
                          .append( std::move( get_shader_info_log( temp_shader ) ) )
                          .append( "\n" );
        }
    }
    //usuniecie shaderow, bo znajduja sie juz w programie
    GL_DEBUG_MACRO( glDeleteShader(temp_shader) )

    if( static_GLSL_shader_debug ){
        Error_messages.shrink_to_fit();
        std::cout << Error_messages;
    }
}

//-----------------------------------------------------------------------------
//                          useProgram()
//-----------------------------------------------------------------------------
void GLSL_shader::use_program(){
    GL_DEBUG_MACRO( glUseProgram( m_program ) )
}

//-----------------------------------------------------------------------------
//                          debug()
//-----------------------------------------------------------------------------
void GLSL_shader::debug(){
    static_GLSL_shader_debug = !static_GLSL_shader_debug;
}
