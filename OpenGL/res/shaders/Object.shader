#vertex shader

#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TextureCoordinates;

out vec3 v_Normal;
out vec4 v_FragmentPosition;
out vec2 v_TextureCoordinates;

uniform mat4 u_Proj;
uniform mat4 u_View;
uniform mat4 u_Model;

uniform mat3 u_NormalTransform;
void main()
{
	gl_Position = u_Proj * u_View * u_Model * a_Position;
	
	v_Normal = u_NormalTransform * a_Normal;
	v_FragmentPosition = u_Model * a_Position;

	v_TextureCoordinates = a_TextureCoordinates;
};


#fragment shader

#version 330 core
layout(location = 0) out vec4 outColor;

struct DirLight 
{
	vec4 Direction;

	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
};

struct PointLight
{
	vec4 Position;

	float Constant;
	float Linear;
	float Quadratic;

	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
};

struct SpotLight
{
	vec4 Position;
	vec3 Direction;

	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;

	float Constant;
	float Linear;
	float Quadratic;

	float CutoffAngle;
	float OuterCutoffAngle;
};

struct Camera
{
	vec4 Position;
};

struct Material 
{
	sampler2D Diffuse;
	sampler2D Specular;

	float Shininess;
};

in vec3 v_Normal;
in vec4 v_FragmentPosition;
in vec2 v_TextureCoordinates;

uniform Camera u_Camera;
uniform Material u_Material;

uniform DirLight u_DirLight;
uniform PointLight u_PointLight;
uniform SpotLight u_SpotLight;

vec3 calculateDirectLighting(DirLight lightSource, vec3 normal, vec3 viewDirection, vec3 fragmentPosition);
vec3 calculatePointLighting(PointLight lightSource, vec3 normal, vec3 viewDirection, vec3 fragmentPosition);
vec3 calculateSpotLighting(SpotLight lightSource, vec3 normal, vec3 viewDirection, vec3 fragmentPosition);

void main()
{
	vec3 viewDirection = normalize(vec3(u_Camera.Position) - vec3(v_FragmentPosition));

	outColor = vec4(calculateSpotLighting(u_SpotLight, v_Normal, viewDirection, vec3(v_FragmentPosition)), 1.0f);
	outColor += vec4(calculatePointLighting(u_PointLight, v_Normal, viewDirection, vec3(v_FragmentPosition)), 1.0f);
	outColor += vec4(calculateDirectLighting(u_DirLight, v_Normal, viewDirection, vec3(v_FragmentPosition)), 1.0f);
};


vec3 calculateDirectLighting(DirLight lightSource, vec3 normal, vec3 viewDirection, vec3 fragmentPosition)
{
	vec3 lightDirection = normalize(-vec3(lightSource.Direction));
	vec3 ambient = lightSource.Ambient * vec3(texture(u_Material.Diffuse, v_TextureCoordinates));

	float diffuseStrength = max(dot(lightDirection, normal), 0.0f);
	vec3 diffuse = lightSource.Diffuse * vec3(texture(u_Material.Diffuse, v_TextureCoordinates)) * diffuseStrength;

	vec3 reflectDirection = reflect(lightDirection, normal);
	float specularStrength = pow(max(dot(viewDirection, reflectDirection), 0.0f), u_Material.Shininess);
	vec3 specular = lightSource.Specular * vec3(texture(u_Material.Specular, v_TextureCoordinates)) * specularStrength;

	return ambient + diffuse + specular;
}

vec3 calculatePointLighting(PointLight lightSource, vec3 normal, vec3 viewDirection, vec3 fragmentPosition)
{
	vec3 lightDirection = normalize(-vec3(lightSource.Position) - fragmentPosition);

	float diffuseStrength = max(dot(lightDirection, normal), 0.0f);

	vec3 reflectDirection = reflect(lightDirection, normal);
	float specularStrength = pow(max(dot(viewDirection, reflectDirection), 0.0f), u_Material.Shininess);
	
	float distance = length(vec3(lightSource.Position) - fragmentPosition);
	float attenuation = (1.0f) / (lightSource.Constant + lightSource.Linear * distance + lightSource.Quadratic * (distance * distance));

	vec3 ambient = lightSource.Ambient * vec3(texture(u_Material.Diffuse, v_TextureCoordinates));
	vec3 diffuse = lightSource.Diffuse * vec3(texture(u_Material.Diffuse, v_TextureCoordinates)) * diffuseStrength * attenuation;
	vec3 specular = lightSource.Specular * vec3(texture(u_Material.Specular, v_TextureCoordinates)) * specularStrength * attenuation;

	return ambient + diffuse + specular;
}

vec3 calculateSpotLighting(SpotLight lightSource, vec3 normal, vec3 viewDirection, vec3 fragmentPosition)
{
	vec3 lightDirection = normalize(-vec3(lightSource.Position) - fragmentPosition);
	
	float diffuseStrength = max(dot(lightDirection, normal), 0.0f);

	vec3 reflectDirection = reflect(-lightDirection, normal);
	float specularStrength = pow(max(dot(viewDirection, reflectDirection), 0.0f), u_Material.Shininess);
		
	float distance = length(vec3(lightSource.Position) - fragmentPosition);
	float attenuation = (1.0f) / (lightSource.Constant + lightSource.Linear * distance + lightSource.Quadratic * (distance * distance));

	float theta = dot(lightDirection, normalize(-lightSource.Direction));
	float epsilon = lightSource.CutoffAngle - lightSource.OuterCutoffAngle;
	float intensity = clamp((theta - lightSource.OuterCutoffAngle) / (epsilon), 0.0f, 1.0f);

	vec3 ambient = lightSource.Ambient * vec3(texture(u_Material.Diffuse, v_TextureCoordinates));
	vec3 diffuse = lightSource.Diffuse * vec3(texture(u_Material.Diffuse, v_TextureCoordinates)) * diffuseStrength * attenuation * intensity;
	vec3 specular = lightSource.Specular * vec3(texture(u_Material.Specular, v_TextureCoordinates)) * specularStrength * attenuation * intensity;

	return ambient + diffuse + specular;
}