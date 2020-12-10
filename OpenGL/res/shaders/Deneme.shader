#vertex shader

#version 330 core
layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoords;

out VS_OUT
{
vec2 TexCoords;
vec3 Normal;

vec3 FragPos;
}vs_out;

layout(std140) uniform matrices
{
	mat4 proj;
	mat4 view;
} mat;

uniform mat4 u_Proj;
uniform mat4 u_View;
uniform mat4 u_Model;

uniform bool u_InverseNormal;

void main()
{
	gl_Position = mat.proj * mat.view * u_Model * a_Position;
	
	mat3 normalMatrix = transpose(inverse(mat3(u_Model)));
	//vec3 n = u_InverseNormal ? -a_Normal : a_Normal;
	vec3 n = a_Normal;

	vs_out.TexCoords = a_TexCoords;
	vs_out.Normal = normalize(normalMatrix * n);
	vs_out.FragPos = vec3(u_Model * a_Position);
}


#fragment shader

#version 330 core
layout(location = 0) out vec4 color;
layout(location = 1) out vec4 brightColor;

struct Light
{
	vec3 Position;
	vec3 Color;
};

in VS_OUT
{
vec2 TexCoords;
vec3 Normal;

vec3 FragPos;
}fs_in;

uniform Light u_Light[4];
uniform vec3 u_CamPosition;

uniform sampler2D diffuseMap;

void main()
{
	vec3 texColor = texture(diffuseMap, fs_in.TexCoords).rgb;
	vec3 normal = normalize(fs_in.Normal);

	vec3 outColor = vec3(0.0f);
	for (int i = 0; i < 4; i++)
	{
		vec3 lightDir = normalize(u_Light[i].Position - fs_in.FragPos);
		vec3 viewDir = normalize(u_CamPosition - fs_in.FragPos);
		vec3 halfwayDir = normalize(lightDir + viewDir);
		float distance = length(u_Light[i].Position - fs_in.FragPos);

		float diffuseStr = max(dot(lightDir, normal), 0.0f);
		vec3 diffuse = u_Light[i].Color * texColor * diffuseStr;
		
		float specularStr = pow(max(dot(viewDir, normal), 0.0f), 32.0f);
		vec3 specular = vec3(0.3f) * specularStr;

		outColor += diffuse;
	}

	float brightness = dot(outColor, vec3(0.2126, 0.7152, 0.0722));
	
	if (brightness > 1.0f)
		brightColor = vec4(outColor, 1.0f);
	else
		brightColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);

	color = vec4(outColor, 1.0f);
}