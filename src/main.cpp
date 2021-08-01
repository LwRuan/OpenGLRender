#include <iostream>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "renderer.h"

using namespace ORTR;

RenderOptions renderoptions;
struct LoopData{
    GLFWwindow* window;
    bool show_imgui = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};
LoopData loopdata;

void mainLoop(){
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();


    if(loopdata.show_imgui){
        ImGui::Begin("Render Settings", &loopdata.show_imgui);
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        ImGui::End();
    }

    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(loopdata.window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    ImVec4& clear_color = loopdata.clear_color;
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, 
        clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(loopdata.window);
}

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
    loopdata.window = glfwCreateWindow( renderoptions.resolution.x, renderoptions.resolution.y, "OpenGLRender", NULL, NULL);
    if( loopdata.window == NULL ){
        std::cerr << "Failed to open GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(loopdata.window);
    
    // Init GL3W
    if (gl3wInit()) {
            std::cerr << "failed to initialize OpenGL" << std::endl;
            return -1;
    }
    if (!gl3wIsSupported(3, 2)) {
            std::cerr << "OpenGL 3.2 not supported" << std::endl;
            return -1;
    }

    std::cout << "[Renderer]OpenGL " << glGetString(GL_VERSION) << 
        " GLSL " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(loopdata.window, GLFW_STICKY_KEYS, GL_TRUE);

    // Init ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();
    ImGui_ImplGlfw_InitForOpenGL(loopdata.window, true);
    const char* glsl_version = "#version 150";
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Main Loop
    do{
        mainLoop();
    }while( glfwGetKey(loopdata.window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
        glfwWindowShouldClose(loopdata.window) == 0 );

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(loopdata.window);
    glfwTerminate();
}