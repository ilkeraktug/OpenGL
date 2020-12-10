#vertex shader

#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normals;
layout(location = 2) in vec2 a_TexCoords;

out vec3 v_Normal;
out vec2 v_TexCoords;

uniform mat4 u_Proj;
uniform mat4 u_View;
uniform mat4 u_Model;

uniform vec3 u_CameraPosition;

out vec3 v_ReflectVector;
out vec3 v_RefractVector;

void main()
{
	vec4 worldPosition = u_Model * a_Position;
	gl_Position = u_Proj * u_View * worldPosition;

	v_Normal = normalize(a_Normals);

	vec3 viewDirection = normalize(worldPosition.xyz - u_CameraPosition);

	v_ReflectVector = reflect(viewDirection, v_Normal);
	v_RefractVector = refract(viewDirection, v_Normal, 1 / 1.33);

	v_TexCoords = a_TexCoords;
};


#fragment shader

#version 330 core
layout(location = 0) out vec4 color;

in vec3 v_Normal;
in vec2 v_TexCoords;

in vec3 v_ReflectVector;
in vec3 v_RefractVector;

struct Material {
	sampler2D Diffuse;
};

uniform samplerCube u_SkyboxTexture;
uniform Material u_Material;

vec3 lightDirection = normalize(vec3(0.2f, -1.0f, 0.3f));
float ambient = 0.3f;

void main()
{
	color = vec4(1.0f);
};
