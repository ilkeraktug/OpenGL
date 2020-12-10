#vertex shader

#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TextureCoordinates;

out vec3 v_Normals;
out vec2 v_TexCoords;

out vec4 v_FragmentPos;

uniform mat4 u_Proj;
uniform mat4 u_View;
uniform mat4 u_Model;

void main()
{
	gl_Position = u_Proj * u_View * u_Model * a_Position;

	v_Normals = normalize(a_Normal);

	v_TexCoords = a_TextureCoordinates;

	v_FragmentPos = u_Model * a_Position;
};


#fragment shader

#version 330 core
layout(location = 0) out vec4 color;

in vec3 v_Normals;
in vec2 v_TexCoords;

in vec4 v_FragmentPos;

struct Light {
	vec3 Position;
};

struct Material {
	sampler2D Diffuse;
	sampler2D Specular;
};

uniform Light u_Light;
uniform Material u_Material;

void main()
{
	float ambientStr = 0.5f;
	vec3 ambient = ambientStr * vec3(texture(u_Material.Diffuse, v_TexCoords));

	vec3 lightDirection = normalize(-vec3(u_Light.Position) - vec3(v_FragmentPos));

	float diffuseStrength = max(dot(lightDirection, v_Normals), 0.0f);
	vec3 diffuse = diffuseStrength * vec3(texture(u_Material.Diffuse, v_TexCoords));

	vec3 reflectDirection = reflect(lightDirection, v_Normals);
	float specularStrength = pow(max(dot(vec3(0.0f), reflectDirection), 0.0f), 16.0f);
	vec3 specular = specularStrength * vec3(texture(u_Material.Specular, v_TexCoords));

	//color = vec4(diffuse, 1.0f) + vec4(ambient, 1.0f) + vec4(specular, 1.0f);
	color = vec4(1.0f);
};

