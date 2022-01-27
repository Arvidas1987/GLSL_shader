#include "GLSL_shader.hpp"

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
}

//-----------------------------------------------------------------------------
//                     compile_shader()
//-----------------------------------------------------------------------------
void GLSL_shader::compile_shader( GLenum shader_type,
                                  const GLchar *const* string )
{
    //utworzenie i kompilacja shadera <shader_type>
    GLuint temp_shader = glCreateShader(shader_type);
    glShaderSource(temp_shader, 1, string, nullptr);
    glCompileShader(temp_shader);

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
