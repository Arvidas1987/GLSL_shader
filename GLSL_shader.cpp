#include "GLSL_shader.hpp"
#include <iostream>


//-----------------------------------------------------------------------------
//                     konstruktor domyslny
//                     implicit ctor
//-----------------------------------------------------------------------------
GLSL_shader::GLSL_shader():m_program(0), m_debug(false)
{
    m_program = glCreateProgram();
}

//-----------------------------------------------------------------------------
//                     destruktor
//-----------------------------------------------------------------------------
GLSL_shader::~GLSL_shader()
{
    glDeleteProgram( m_program );
}

//-----------------------------------------------------------------------------
//                     compile_shader()
//-----------------------------------------------------------------------------
void GLSL_shader::compile_shader( GLenum shader_type,
                                  const GLchar *const *string )
{
    //utworzenie i kompilacja shadera <shader_type>
    GLuint temp_shader = glCreateShader(shader_type);
    glShaderSource(temp_shader, 1, string, nullptr);
    glCompileShader(temp_shader);

    if( m_debug ){
        GLint check_compilation_of_shader_status;
        glGetShaderiv( temp_shader, GL_COMPILE_STATUS, &check_compilation_of_shader_status );
        if( check_compilation_of_shader_status != GL_TRUE ){
            std::cout << "Niepoprawna kompilacja shadera:" << *string << ".\n";

            GLint log_length;
            glGetShaderiv( temp_shader, GL_INFO_LOG_LENGTH, &log_length );
            char *log = new char[log_length];
            glGetShaderInfoLog( temp_shader, log_length, nullptr, log );
            std::cout << log <<std::endl;
            delete[] log;
        }
    }


    glAttachShader(m_program, temp_shader);
    glLinkProgram(m_program);

    //usuniecie shaderow, bo znajduja sie juz w programie
    glDeleteShader(temp_shader);
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
    m_debug = true;
}
