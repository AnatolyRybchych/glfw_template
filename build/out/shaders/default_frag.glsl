#version 110

varying vec4 color;
varying vec4 pos;   
varying vec2 tex_pos;

uniform sampler2D tex1;

uniform mat4 MVP;

float line_len(float x, float y ,float x1, float y1)
{
   return sqrt((x - x1)*(x - x1) + (y - y1) * (y - y1));
}

void main()
{
    gl_FragColor = color;
    gl_FragColor = texture2D(tex1, tex_pos);
}