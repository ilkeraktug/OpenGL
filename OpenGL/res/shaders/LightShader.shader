#vertex shader

#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoords;


void main()
{
};


#fragment shader

#version 330 core
layout(location = 0) out vec4 color;

in VS_OUT
{
	vec3 FragPos;
	vec4 LightSpace;

	vec3 Normal;
	vec2 TexCoords;
} fs_in;

uniform sampler2D depthTexture;
uniform sampler2D diffuseTexture;

uniform vec3 u_CamPos;
uniform vec3 u_LightPos;

float CalculateShadow(vec4 lightSpace, float bias)
{
	vec3 projection = lightSpace.xyz / lightSpace.w;

	projection = projection * 0.5f + 0.5f;

	float depthValue = texture(depthTexture, projection.xy).r;
	float currentDepthValue = projection.z;

	if (projection.z > 1.0f)
		return 0.0f;

	return (currentDepthValue - bias) < depthValue ? 0.0f : 1.0f;
}

float shadow(vec4 lightSpace, float bias)
{
	vec3 projection = lightSpace.xyz / lightSpace.w;

	projection = projection * 0.5f + 0.5f;

	float shadow = 0.0f;
	vec2 size = 1.0f / textureSize(depthTexture, 0);

	float currentDepthValue = projection.z;

	for (int x = -1; x <= 1; ++x)
	{
		for (int y = -1; y <= 1; ++y)
		{
			float depthValue = texture(depthTexture, projection.xy + vec2(x, y) * size).x;

			shadow += (currentDepthValue - bias) < depthValue ? 0.0f : 1.0f;
		}
	}

	if (projection.z > 1.0f)
		return 0.0;

	return shadow /= 9;
}

void main()
{
	vec3 ligthDir = normalize(u_LightPos - fs_in.FragPos);
	vec3 viewDir = normalize(u_CamPos - fs_in.FragPos);

	vec3 reflectDir = reflect(-ligthDir, fs_in.Normal);
	vec3 halfwayDir = normalize(ligthDir + viewDir);

	vec3 lightColor = vec3(1.0f);
	vec3 texColor = texture(diffuseTexture, fs_in.TexCoords).xyz;

	vec3 ambient = 0.4f * texColor;

	float biass = max(0.05 * (1 - dot(fs_in.Normal, ligthDir)), 0.005);

	float diffuseStr = max(dot(ligthDir, fs_in.Normal), 0.0f);
	vec3 diffuse = diffuseStr * lightColor;

	float specularStr = pow(max(dot(halfwayDir, fs_in.Normal), 0.0f), 64.0);
	vec3 specular = specularStr * lightColor;

	vec3 outColor = (ambient + (1.0 - shadow(fs_in.LightSpace, biass)) * (diffuse + specular)) * texColor;
	color = vec4(outColor, 1.0f);
};
