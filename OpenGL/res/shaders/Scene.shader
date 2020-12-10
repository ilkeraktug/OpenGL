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

struct Light
{
	vec3 Position;
	vec3 Color;

	float Linear;
	float Quadratic;
};

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

uniform Light u_Light[32];
uniform vec3 u_CamPosition;

void main()
{
	vec3 fragPos = texture(gPosition, v_TexCoords).rgb;
	vec3 normal = texture(gNormal, v_TexCoords).rgb;
	vec3 diffuseColor = texture(gAlbedoSpec, v_TexCoords).rgb;
	float specularColor = texture(gAlbedoSpec, v_TexCoords).a;

	vec3 viewDir = normalize(u_CamPosition - fragPos);

	vec3 light = 0.1 * diffuseColor;
	for (int i = 0; i < 32; i++)
	{
		vec3 ligthDir = normalize(u_Light[i].Position - fragPos);
		vec3 halfwayDir = normalize(ligthDir + viewDir);

		float diffuseStr = max(dot(ligthDir, normal), 0.0f);
		vec3 diffuse = diffuseColor * diffuseStr * u_Light[i].Color;

		float specularStr = pow(max(dot(halfwayDir, normal), 0.0f), 16.0f);
		vec3 specular = specularColor * specularStr * u_Light[i].Color;

		float distance = length(u_Light[i].Position - fragPos);
		float attenuation = 1.0 / (1.0 + u_Light[i].Linear * distance + u_Light[i].Quadratic * distance * distance);

		diffuse *= attenuation;
		specular *= attenuation;

		light += diffuse + specular;
	}

	outColor = vec4(light, 1.0f);
}