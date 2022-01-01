#include "../include/window.h"

WindowParameters WindowParams = {
    .size = {
        .height = DEFAULT_WINDOW_HEIGHT,
        .width = DEFAULT_WINDOW_WIDTH,
    },
};

RenderContext RenderCtx = {
    .window_params = &WindowParams,
};

static void (*on_frame)(RenderContext *context);


int init_window(void (*on_frame_proc)(RenderContext *context))
{
    on_frame = on_frame_proc;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_SAMPLES, 4);

    WindowParams.window = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, DEFAULT_WINDOW_TITLE, NULL, NULL);
    if (!WindowParams.window) return 0;

    glfwMakeContextCurrent(WindowParams.window);

    glfwSetWindowSizeCallback(WindowParams.window, window_size_callback);
    return 1;
}

void start_main_loop()
{
    assert(on_frame);

    while (!glfwWindowShouldClose(WindowParams.window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.3, 0.3, 0.3, 1);
        
        gl_camera.push_state();
        gl_camera.scale2f(vec2f(WindowParams.size.height/ WindowParams.size.width, 
                                WindowParams.size.width / WindowParams.size.width));
        on_frame(&RenderCtx);
        gl_camera.pop_state();

        glfwSwapBuffers(WindowParams.window);
        
        glfwPollEvents();
    }
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
    WindowParams.size.width = width;
    WindowParams.size.height = height;
    glViewport(0,0,width,height);
}

