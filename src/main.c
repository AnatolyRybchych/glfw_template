#include<stdio.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stdlib.h>
#include<string.h>

#include "../include/shader_program.h"
#include "../include/shaders.h"
#include "../include/texture2d.h"
#include "../include/textures.h"
#include "../include/gl_camera.h"


#define DEFAULT_WINDOW_TITLE "Window"
#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600


void exit_error(char* msg);
void error_callback(int error, const char* description);
void window_size_callback(GLFWwindow* window, int width, int height);
void render();
void init();

int main(int argc, char* argv[])
{
    if (!glfwInit()) exit_error("Cannot init glfw");

    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_SAMPLES, 4);
    GLFWwindow* window = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, DEFAULT_WINDOW_TITLE, NULL, NULL);
    if (!window) exit_error("Cannot create glfw window");

    glfwMakeContextCurrent(window);
    gladLoadGL();

    init();

    //glEnable(GL_MULTISAMPLE);

    glfwSetWindowSizeCallback(window, window_size_callback);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.3, 0.3, 0.3, 1);

        render();
        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void exit_error(char* msg)
{

    fprintf(stderr,"ERROR:%s\n",msg);
    glfwTerminate();
    exit(EXIT_FAILURE);
}

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width,height);
}
float angle = 0.0f;
void render()
{
    
    gl_camera.push_state();

    glUseProgram(ShaderPrograms[DEFAULT_SHADER_PROGRAM]);
    gl_camera.uniform(glGetUniformLocation(ShaderPrograms[DEFAULT_SHADER_PROGRAM], "MVP"));
    gl_camera.pop_state();

    glBegin(GL_TRIANGLES);

    glVertex3f(-1.0f, 1.0f, 0.0f);      glColor4f(0.8f, 0.4f, 0.2f, 1.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);       glColor4f(0.8f, 0.8f, 0.2f, 1.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);      glColor4f(0.8f, 0.2f, 0.4f, 1.0f);

    glVertex3f(-1.0f, 1.0f, 0.0f);      glColor4f(0.8f, 0.4f, 0.2f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);       glColor4f(0.8f, 0.8f, 0.2f, 1.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);      glColor4f(0.8f, 0.2f, 0.4f, 1.0f);

    glEnd();
}



void init()
{
    init_shaders();
    link_shader_programs();
    load_textures();
    
    glUseProgram(ShaderPrograms[DEFAULT_SHADER_PROGRAM]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Textures[TEXTURE_DIRT_DEF]);

    glUniform1i(glGetUniformLocation(ShaderPrograms[DEFAULT_SHADER_PROGRAM],"tex1"), 0);
}