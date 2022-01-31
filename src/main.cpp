#include<iostream>
#include<fstream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

void exit_error(const char* msg);
void error_callback(int error, const char* description);
void window_size_callback(GLFWwindow* window, int width, int height);
std::string read_all_file(std::string filename);
GLuint link_shader_program(GLuint vertex, GLuint fragment);
GLuint compile_shader(std::string source, GLenum shaderType);

GLuint vert;
GLuint frag;
GLuint prog;

void init(GLFWwindow *window)
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    glViewport(0,0,width,height);

    prog = link_shader_program( vert = compile_shader(read_all_file("shaders/vert.glsl"), GL_VERTEX_SHADER), 
                                frag = compile_shader(read_all_file("shaders/frag.glsl"), GL_FRAGMENT_SHADER));

}

void render(double ftime, const GLFWwindow *window)
{
    glUseProgram(prog);
    glUniform1f(glGetUniformLocation(prog, "time"), glfwGetTime());

    glBegin(GL_TRIANGLES);

    glVertex2f(1,1);
    glVertex2f(1,-1);
    glVertex2f(-1,1);

    glVertex2f(-1,-1);
    glVertex2f(1,-1);
    glVertex2f(-1,1);

    glEnd();

    glUseProgram(0);
}

int main(int argc, char* argv[])
{
    double time;
    double ftime;

    if (!glfwInit()) exit_error("Cannot init glfw");
    
    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Window", NULL, NULL);
    glfwMakeContextCurrent(window);    
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwShowWindow(window);

    if(!gladLoadGL()) exit_error("Cannot load glad");

    init(window);

    while (!glfwWindowShouldClose(window))
    {
        double t = glfwGetTime();
        ftime = time - t;
        time = t;

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.3, 0.3, 0.3, 1);

        render(ftime, window);
        
        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }

    return 0;
}

void exit_error(const char* msg)
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

std::string read_all_file(std::string filename)
{
    std::ifstream f(filename);
    std::string str((std::istreambuf_iterator<char>(f)),
                    std::istreambuf_iterator<char>());
    
    return str;
}

GLuint compile_shader(std::string source, GLenum shaderType)
{
    char info_log[GL_INFO_LOG_LENGTH + 1];

    GLuint shader = glCreateShader(shaderType);

    if(!shader)
    {
        fprintf(stderr, "ERROR:%s\n", "cannot create shader");
    }

    char *c_source = const_cast<char*>(source.c_str());

    glShaderSource(shader, 1, (const GLchar *const *)&c_source, NULL);
    
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader,GL_COMPILE_STATUS, &status);
    if(!status) 
    {
        glGetShaderInfoLog(shader, GL_INFO_LOG_LENGTH,NULL, info_log);
        fprintf(stderr, "ERROR:%s\n",info_log);
        glDeleteShader(shader);
        return 0;
    }
    else
    {
        return shader;
    }
}

GLuint link_shader_program(GLuint vertex, GLuint fragment)
{
    char info_log[GL_INFO_LOG_LENGTH + 1];

    GLuint ShaderProgram = glCreateProgram();
    if(!ShaderProgram)
    {
        fprintf(stderr, "ERROR:%s\n","cannot create shader programm");
        return 0;
    }

    glAttachShader(ShaderProgram, vertex);
    glAttachShader(ShaderProgram, fragment);
    glLinkProgram(ShaderProgram);

    GLint status;
    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &status);
    if(!status) 
    {
        glGetProgramInfoLog(ShaderProgram, GL_INFO_LOG_LENGTH,NULL, info_log);
        fprintf(stderr, "ERROR:%s\n",info_log);
        return 0;
    }
    else
    {
        return ShaderProgram;
    }
}