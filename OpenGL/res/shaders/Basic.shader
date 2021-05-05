#vertex shader
#version 330 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoords;

uniform mat4 u_MVP;

out vec2 v_TexCoords;

void main()
{
	gl_Position = vec4(a_Position, 0.0f, 1.0f);

	v_TexCoords = a_TexCoords;
}

#fragment shader

#version 330 core
layout(location = 0) out vec4 outColor;

in vec2 v_TexCoords;
uniform sampler2D u_Texture;


void main()
{

	outColor = texture(u_Texture, v_TexCoords);

}