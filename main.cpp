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

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if ( glfwInit() == GLFW_FALSE )
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow( 640, 480, "GLFW_64bits", NULL, NULL );
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

    /* Loop until the user closes the window */
    while ( !glfwWindowShouldClose(window) )
    {
        /* Render here */
        glClearColor( 0.5f, 0.5f, 0.5f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
/*******************************************/

