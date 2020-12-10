#vertex shader

#version 330 core
layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoords;
layout(location = 3) in vec3 a_Tangent;
layout(location = 4) in vec3 a_BiTangent;

out VS_OUT
{
vec2 TexCoords;

vec3 debugNormal;
vec3 FragPos;
vec3 LigthPos;
vec3 CamPos;
}vs_out;

uniform mat4 u_Proj;
uniform mat4 u_View;
uniform mat4 u_Model;

uniform vec3 u_LigthPosition;
uniform vec3 u_CameraPosition;

void main()
{
	gl_Position = u_Proj * u_View * u_Model * a_Position;

	mat3 normalMatrix = transpose(inverse(mat3(u_Model)));
	vec3 T = normalize(normalMatrix * a_Tangent);
	vec3 N = normalize(normalMatrix * a_Normal);
	vec3 B = normalize(normalMatrix * a_BiTangent);

	mat3 TBN = transpose(mat3(T, B, N));

	vs_out.TexCoords = a_TexCoords;

	vs_out.FragPos = TBN * vec3(u_Model * a_Position);
	vs_out.LigthPos = TBN * u_LigthPosition;
	vs_out.CamPos = TBN * u_CameraPosition;

	vs_out.debugNormal = N;
}


#fragment shader

#version 330 core
layout(location = 0) out vec4 color;

in VS_OUT
{
vec2 TexCoords;

vec3 debugNormal;
vec3 FragPos;
vec3 LigthPos;
vec3 CamPos;
} fs_in;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform sampler2D heightMap;

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{

	float minLayerCount = 8.0f;
	float maxLayerCount = 8.0f;

	float layerCount = mix(minLayerCount, maxLayerCount, dot(vec3(0.0f, 0.0f, 1.0f), viewDir));
	float layerDepth = 1.0f / layerCount;

	float currentLayerDepth = 0.0f;

	vec2 P = viewDir.xy / viewDir.z * 0.07;
	vec2 deltaTexCoords = P / layerCount;

	vec2 f_TexCoords = texCoords;
	float currentMapDepth = texture(heightMap, f_TexCoords).r;

	while (currentLayerDepth < currentMapDepth)
	{
		f_TexCoords -= deltaTexCoords;

		currentLayerDepth += layerDepth;

		currentMapDepth = texture(heightMap, f_TexCoords).r;
	}

	vec2 previousTexCoords = f_TexCoords + deltaTexCoords;

	float afterDepth = currentMapDepth - currentLayerDepth;
	float previousDepth = texture(heightMap, previousTexCoords).r - (currentLayerDepth - layerDepth);

	float weight = afterDepth / (afterDepth - previousDepth);

	return previousTexCoords * weight + f_TexCoords * (1 - weight);
}

void main()
{
	vec3 lightDir = normalize(fs_in.LigthPos - fs_in.FragPos);
	vec3 viewDir = normalize(fs_in.CamPos - fs_in.FragPos);
	vec3 halfwayDir = normalize(lightDir + viewDir);

	vec2 texCoords = ParallaxMapping(fs_in.TexCoords, viewDir);

	vec3 normal = texture(normalMap, texCoords).rgb;
	normal = normalize(normal * 2.0 - 1.0);


	vec3 lightColor = vec3(1.0);
	vec3 ambient = 0.3 * lightColor;

	vec3 texColor = texture(diffuseMap, texCoords).rgb;

	float diffuseStr = max(dot(lightDir, normal), 0.0f);
	vec3 diffuse = diffuseStr * texColor;

	float specularStr = pow(max(dot(halfwayDir, normal), 0.0f), 32.0f);
	vec3 specular = specularStr * vec3(0.4f);

	color = vec4(ambient + diffuse + specular, 1.0f);
}