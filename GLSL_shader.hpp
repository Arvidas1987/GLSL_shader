#ifndef _GLSL_SHADER_HPP_
#define _GLSL_SHADER_HPP_
#
#define GLEW_STATIC
#include <GL/glew.h>
#
class GLSL_shader
{
private:
    GLuint m_program;
public:
    GLSL_shader();
    ~GLSL_shader();

    void compile_shader( GLenum shader_type, const GLchar *const* string );
    void use_program();
};
#
#endif // _GLSL_SHADER_HPP_
