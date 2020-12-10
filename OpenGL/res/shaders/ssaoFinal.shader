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

layout(location = 0) out vec4 outColor;

in vec2 v_TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;
uniform sampler2D SSAO;

struct Light {
    vec3 Position;
    vec3 Color;

    float Linear;
    float Quadratic;
};

uniform Light u_Light;


void main()
{
    vec3 FragPos = texture(gPosition, v_TexCoords).rgb;
    vec3 Normal = texture(gNormal, v_TexCoords).rgb;
    vec3 Diffuse = texture(gAlbedo, v_TexCoords).rgb;
    float AmbientOcclusion = texture(SSAO, v_TexCoords).r;

    vec3 ambient = vec3(0.3 * Diffuse * AmbientOcclusion);
    vec3 lighting = ambient;
    vec3 viewDir = normalize(-FragPos); // viewpos is (0.0.0)

    vec3 lightDir = normalize(u_Light.Position - FragPos);
    vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Diffuse * u_Light.Color;

    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(Normal, halfwayDir), 0.0), 8.0);
    vec3 specular = u_Light.Color * spec;

    float distance = length(u_Light.Position - FragPos);
    float attenuation = 1.0 / (1.0 + u_Light.Linear * distance + u_Light.Quadratic * distance * distance);
    diffuse *= attenuation;
    specular *= attenuation;
    lighting += diffuse + specular;

    outColor = vec4(lighting, 1.0);
}