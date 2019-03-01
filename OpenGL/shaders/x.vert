#version 450

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec3 aTex;


Uniform mat4 model, view, projection;


out vec3 Normal;
out vec3 FragPos;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	Normal = mat3(transpose(inverse(model))) * aNormal;
	FragPos = vec3(model * vec4(aPos, 1.0));
}	