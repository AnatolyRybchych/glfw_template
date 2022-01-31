#version 110

varying vec4 pos;

void main()
{
    pos = gl_Vertex;

    gl_Position = gl_Vertex;
}