#vertex shader
#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoords;

uniform mat4 u_MVP;

out vec2 v_TexCoords;

void main()
{
	gl_Position = a_Position;

	v_TexCoords = a_TexCoords;
}

#fragment shader

#version 330 core
layout(location = 0) out vec4 outColor;

in vec2 v_TexCoords;
uniform sampler2D u_Texture;


void main()
{

	outColor = vec4(1.0f);

}