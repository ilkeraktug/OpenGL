#vertex shader
#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoorsd;

uniform mat4 u_Proj;
uniform mat4 u_View;
uniform mat4 u_Model;

void main()
{
	gl_Position = u_Proj * u_View * u_Model * a_Position;
}

#fragment shader

#version 330 core

layout(location = 0) out vec4 outColor;
layout(location = 1) out vec4 brightColor;

uniform vec3 u_LightColor;

void main()
{
	outColor = vec4(u_LightColor, 1.0f);

	float brightness = dot(u_LightColor, vec3(0.2126, 0.7152, 0.0722));

	if (brightness >= 1)
		brightColor = outColor;
	else
		brightColor = vec4(vec3(0.0f), 1.0f);
}