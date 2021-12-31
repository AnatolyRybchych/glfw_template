#version 110

varying vec4 color;
varying vec4 pos;
varying vec2 tex_pos;

uniform sampler2D tex1;

uniform mat4 MVP;

void main()
{
    gl_FragColor = color;
    gl_FragColor = texture2D(tex1, tex_pos);
}