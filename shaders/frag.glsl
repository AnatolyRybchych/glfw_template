#version 110

uniform float time;
varying vec4 pos;

float line_len(float x, float y ,float x1, float y1)
{
   return sqrt((x - x1)*(x - x1) + (y - y1) * (y - y1));
}

void main()
{
    gl_FragColor = vec4(
            (sin(time + pos.y) + 1.0)/3.0 + 0.3, 
            (sin(time + pos.x + 0.3) + 1.0)/3.0 + 0.3, 
            (sin(time+ pos.x * pos.y + 0.7) + 1.0)/3.0 + 0.3, 
            1.0
        );
}