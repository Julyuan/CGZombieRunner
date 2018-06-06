#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture_diffuse;
void main()
{
//    FragColor = vec4(ourColor,1.0);
    FragColor = texture(texture_diffuse, TexCoord);
}