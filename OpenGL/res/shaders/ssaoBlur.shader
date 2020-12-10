#vertex shader

#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec2 a_TexCoords;

out vec2 v_TexCoords;

void main()
{
	gl_Position = a_Position;

	v_TexCoords = a_TexCoords;
}

#fragment shader

#version 330 core

layout(location = 0) out float outColor;

in vec2 v_TexCoords;

uniform sampler2D ssaoTexture;

void main()
{
	vec2 texelSize = 1.0f / vec2(textureSize(ssaoTexture, 0));

	float result = 0.0f;
	for (int x = -2; x < 2; ++x)
	{
		for (int y = -2; y < 2; ++y)
		{
			vec2 offset = vec2(float(x), float(y)) * texelSize;
			result += texture(ssaoTexture, v_TexCoords + offset).r;
		}
	}
	outColor = result / 16.0f;
}