#vertex shader

#version 330 core

layout(location = 0) in vec4 a_Position;

out vec3 v_TexCoord;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * a_Position;
	v_TexCoord = vec3(a_Position);
};


#fragment shader

#version 330 core
layout(location = 0) out vec4 color;

in vec3 v_TexCoord;

uniform vec4 u_Color;
uniform samplerCube u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = texColor;
};
