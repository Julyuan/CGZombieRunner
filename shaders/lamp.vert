#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out VS_OUT{
    vec3 color;
} vs_out;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vs_out.color = vec4(0.0,1.0,0.0,1.0);
}