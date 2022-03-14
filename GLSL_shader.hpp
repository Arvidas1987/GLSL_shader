#ifndef _GLSL_SHADER_HPP_
#define _GLSL_SHADER_HPP_
#
#define GLEW_STATIC
#include <GL/glew.h>
#
#include <string>
#
class GLSL_shader
{
private:
    GLuint m_program;
    static bool static_GLSL_shader_debug;
public:
    GLSL_shader();
    ~GLSL_shader();

    // [PL] compile_shader: Metoda pobiera zrodlo shadera, kompiluje i dol¹cza do programu
    // [EN] compile_shader: Method getting shader source, compiling and attaching to program
    //
    // shaderType:
    // GL_FRAGMENT_SHADER
    // GL_VERTEX_SHADER
    // GL_GEOMETRY_SHADER
    // GL_COMPUTE_SHADER
    // GL_TESS_CONTROL_SHADER
    // GL_TESS_EVALUATION_SHADER
    void compile_shader( const std::string shader_name,
                         GLenum shader_type,
                         const GLchar *const *shader_source_string );
    void use_program();

    static void debug();
};
#
#endif // _GLSL_SHADER_HPP_
