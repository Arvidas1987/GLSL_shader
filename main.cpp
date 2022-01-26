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


GLuint compile_shaders()
{
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

//utworzenie i kompilacja shadera wiercholkow
GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertex_shader, 1, vs_source, nullptr);
glCompileShader(vertex_shader);

//utworzenie i kompilacja shadera fragmentow
GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragment_shader, 1, fs_source, nullptr);
glCompileShader(fragment_shader);

//utworzenie programu, dodanie shaderow i ich polaczenie
GLuint program = glCreateProgram();
glAttachShader(program, vertex_shader);
glAttachShader(program, fragment_shader);
glLinkProgram(program);

//usuniecie shaderow, bo znajduja sie juz w programie
glDeleteShader(vertex_shader);
glDeleteShader(fragment_shader);

return program;
}


int main()
{

    /* Initialize the library */
    if ( glfwInit() == GLFW_FALSE ){
        WRITELN( "[PL] Problem z inicjalizacja GLFW." )
        WRITELN( "[EN] GLFW initialization issue." )
        //WRITELN( "\t|-> " << glewGetErrorString(GLEW_init_error) )NEWLN()
        return -1;
    } else {
        WRITELN( "[PL] Inicjalizacja GLFW:  OK" );
        WRITELN( "[EN] GLFW inicjalization: OK" );
        NEWLN()
        //return 0;
    }

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow( 640, 480, "GLFW_64bits", NULL, NULL );
    if ( window == nullptr )
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

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
        //return 0;
    }




GLuint programm = compile_shaders();

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

