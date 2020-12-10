#vertex shader

#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec2 a_TexCoords;
//layout(location = 2) vec3 a_Normal;

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

uniform sampler2D hdrTexture;
uniform bool hdrOn;
uniform float exposure;

void main()
{
	const float gamma = 2.2f;
	vec3 hdrColor = texture(hdrTexture, v_TexCoords).rgb;

	if (hdrOn)
	{
		vec3 result = vec3(1.0f) - exp(-hdrColor * exposure);
		result = pow(result, vec3(1.0f) / gamma);
		outColor = vec4(result, 1.0f);
	}
	else
	{
		vec3 result = pow(hdrColor, vec3(1.0f) / gamma);
		outColor = vec4(result, 1.0f);
	}
}