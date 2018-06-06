#version 330 core
out vec4 FragColor;

in vec3 fcolor;
void main()
{
    FragColor = vec4(fcolor,1.0); // set alle 4 vector values to 1.0
}