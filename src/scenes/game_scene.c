#include "../../include/scenes/game_scene.h"
#define TEXTURES_DIR "build/out/sprites/"

enum GAME_SCENE_TEXTURE{
    TEXTURE_DIRT_DEF,

    TEXTURES_COUNT,
};

static GLuint Textures[TEXTURES_COUNT];
static const char *TextureSources[TEXTURES_COUNT] = {
    [TEXTURE_DIRT_DEF] = TEXTURES_DIR"def.bmp",
};


static void init()
{
    load_textures(TextureSources, Textures, TEXTURES_COUNT);

    glUseProgram(ShaderPrograms[DEFAULT_SHADER_PROGRAM]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Textures[TEXTURE_DIRT_DEF]);

    glUniform1i(glGetUniformLocation(ShaderPrograms[DEFAULT_SHADER_PROGRAM],"tex1"), 0);
};

static void render(RenderContext *context)
{
    gl_camera.push_state();

    glUseProgram(ShaderPrograms[DEFAULT_SHADER_PROGRAM]);
    //gl_camera.scalef(0.1);
    gl_camera.uniform(glGetUniformLocation(ShaderPrograms[DEFAULT_SHADER_PROGRAM], "MVP"));
    gl_camera.pop_state();

    glBegin(GL_TRIANGLES);

    glVertex3f(-1.0f, 1.0f, 0.0f); 
    glVertex3f(1.0f, 1.0f, 0.0f);  
    glVertex3f(1.0f, -1.0f, 0.0f); 

    glVertex3f(-1.0f, 1.0f, 0.0f); 
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f); 

    glEnd();
}

static void close()
{
    glDeleteTextures(TEXTURES_COUNT, Textures);
}

Scene GameScene = {
    .init = init,
    .on_frame = render,
    .close = close,
};