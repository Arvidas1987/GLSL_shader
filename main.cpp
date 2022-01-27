/*
Linker (in this order):
// glfw + glew
-lglfw3
-lgdi32

-lglew32s
-lglu32
-lopengl32 // musi byc za -lglu32 oraz -lglew32

if "undefined reference..."
    Project build options -> Linker settings -> Link libraries -> add:
    - libglfw3.a
    - libgdi32.a

    // glew and opengl order
    - glew32s.lib
    - libglu32.a
    - libopengl32.a
*/
#
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#
#include <iostream>
#define WRITELN(x) std::cout << x << "\n";
#define NEWLN() std::cout << "\n";
#

static const char * vs_source[] ={
    R"glsl(
        "#version 420 core
            void main(void){
                gl_Position = vec4(0.0, 0.0, 0.5, 1.0);
            }
        )glsl"
};

static const char * fs_source[] = {
    R"glsl(
        #version 420 core
        out vec4 color;
        void main(void){
            color = vec4(0.0, 0.8, 1.0, 1.0);
        }
    )glsl"
};

void compile_shader( const GLuint &program,
                        GLenum shader_type,
                        const GLchar *const* string )
{
//utworzenie i kompilacja shadera <shader_type>
GLuint temp_shader = glCreateShader(shader_type);
glShaderSource(temp_shader, 1, string, nullptr);
glCompileShader(temp_shader);

glAttachShader(program, temp_shader);
glLinkProgram(program);

//usuniecie shaderow, bo znajduja sie juz w programie
glDeleteShader(temp_shader);

}

int GLFW_init()
{
    /* Initialize the GLFW library */
    if ( glfwInit() == GLFW_FALSE ){
        WRITELN( "[PL] Problem z inicjalizacja GLFW." )
        WRITELN( "[EN] GLFW initialization issue." )
        //WRITELN( "\t|-> " << glewGetErrorString(GLEW_init_error) )NEWLN()
        return -1;
    } else {
        WRITELN( "[PL] Inicjalizacja GLFW:  OK" );
        WRITELN( "[EN] GLFW inicjalization: OK" );
        NEWLN()
        return 0;
    }
}

int GLEW_init()
{
    ///* Initialize the GLEW library *///
    ////do dzialania biblioteki GLEW musi byc znany kontekst OpenGL
    GLenum GLEW_init_error = glewInit();
    //WRITELN(GLEW_init_error) // wypisanie numeru bledu GLEW_init_error
    if ( GLEW_init_error != GLEW_OK )
    {
        WRITELN( "[PL] Problem z inicjalizacja GLEW." )
        WRITELN( "[EN] GLEW initialization issue." )
        WRITELN( "\t|-> " << glewGetErrorString(GLEW_init_error) )
        WRITELN( "\t|-> " << "[PL] Do dzialania biblioteki GLEW, musi byc znany kontekst OpenGL" )
        WRITELN( "\t|-> " << "[EN] GLEW library has to know OpenGL context." )
        NEWLN()
        return -1;
    } else {
        WRITELN( "[PL] Inicjalizacja GLEW:  OK" );
        WRITELN( "[EN] GLEW inicjalization: OK" );
        NEWLN()
        return 0;
    }
}

int main()
{
    GLFW_init();


    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow( 640, 480, "GLFW_64bits", NULL, NULL );
    if ( window == nullptr ) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLEW_init();

GLuint programm =  glCreateProgram();
compile_shader( programm, GL_VERTEX_SHADER, vs_source );
compile_shader( programm, GL_FRAGMENT_SHADER, fs_source );

    /* Loop until the user closes the window */
    while ( !glfwWindowShouldClose(window) )
    {
        /* Render here */
        glClearColor( 0.5f, 0.5f, 0.5f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );


        glUseProgram(programm);
        glPointSize(40.0f);
        glDrawArrays(GL_POINTS, 0, 1);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
/*******************************************/

