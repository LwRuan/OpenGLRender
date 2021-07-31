#include <iostream>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "renderer.h"

using namespace ORTR;

RenderOptions renderoptions;

int main(){
    // Init GLFW
    if(!glfwInit()){
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.2
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

    // Open a window and create its OpenGL context
    GLFWwindow* window;
    window = glfwCreateWindow( renderoptions.resolution.x, renderoptions.resolution.y, "OpenGLRender", NULL, NULL);
    if( window == NULL ){
        std::cerr << "Failed to open GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    // Init GL3W
    if (gl3wInit()) {
            std::cerr << "failed to initialize OpenGL" << std::endl;
            return -1;
    }
    if (!gl3wIsSupported(3, 2)) {
            std::cerr << "OpenGL 3.2 not supported" << std::endl;
            return -1;
    }

    std::cout << "[ORTR]OpenGL " << glGetString(GL_VERSION) << 
        " GLSL " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    do{
        glClear( GL_COLOR_BUFFER_BIT );
        glfwSwapBuffers(window);
        glfwPollEvents();

    }while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0 );
}