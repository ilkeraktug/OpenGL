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

uniform mat4 u_Proj;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D ssaoNoise;

uniform float bias;
uniform float radius;

//const float bias = 0.025;
//const float radius = 0.5;

uniform vec3 samplers[64];

vec2 noiseSize = vec2(1280 / 4, 768 / 4);


void main()
{
	vec3 fragPos = texture(gPosition, v_TexCoords).xyz;
	vec3 normal = texture(gNormal, v_TexCoords).xyz;
	
	vec3 randomVector = texture(ssaoNoise, v_TexCoords * noiseSize).xyz;

	vec3 tangent = vec3(randomVector - normal * dot(randomVector, normal));
	vec3 bitangent = cross(tangent, normal);

	mat3 TBN = mat3(tangent, bitangent, normal);

	float occlusion = 0.0f;
	for (int i = 0; i < 64; i++)
	{
		vec3 _sample = TBN * samplers[i]; // to view space;
		_sample = fragPos + _sample * radius;

		vec4 offset = vec4(_sample, 1.0f);
		offset = u_Proj * offset;
		offset.xyz /= offset.w;

		offset.xyz = offset.xyz * 0.5f + 0.5f;

		float sampleDepth = texture(gPosition, offset.xy).z;

		occlusion += sampleDepth >= _sample.z + bias ? 1.0f : 0.0f;
	}

	outColor = 1.0f - (occlusion / 64.0f);
}