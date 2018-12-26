#version 450 core

out vec4 FragColor;

in vec4 vertexColor;
in vec2 texCoords;
uniform sampler2D u_texture;
void main()
{
FragColor = texture(u_texture, texCoords) ;
}