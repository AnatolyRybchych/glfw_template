#ifndef __TEXTURES_H_
#define __TEXTURES_H_

#include "texture2d.h"

enum TEXTURE{
    TEXTURE_DIRT_DEF,

    TEXTURES_COUNT,
};

extern GLuint Textures[TEXTURES_COUNT];
extern char *TextureSources[TEXTURES_COUNT];

void load_textures();

#endif