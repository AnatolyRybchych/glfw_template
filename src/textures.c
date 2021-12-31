#include "../include/textures.h"

#define TEXTURES_DIR "build/out/sprites/"

GLuint Textures[TEXTURES_COUNT];
char *TextureSources[TEXTURES_COUNT] = {
    [TEXTURE_DIRT_DEF] = TEXTURES_DIR"def.bmp",
};



void load_textures()
{
    printf("\ntextures initialization{\n");
    for (int curr_tex = 0; curr_tex < TEXTURES_COUNT; curr_tex++)
    {
        Textures[curr_tex] = load_texture2d(TextureSources[curr_tex], NULL, NULL);

        printf("\tTextures[%i] :%s\t-> (%i) ", curr_tex, TextureSources[curr_tex], Textures[curr_tex]);
        if(Textures[curr_tex]) printf("success\n");
        else printf("feiled\n");
    }
    printf("};\n");
}