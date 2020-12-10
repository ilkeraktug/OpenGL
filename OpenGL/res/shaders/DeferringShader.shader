#vertex shader

#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TextureCoordinates;

out VS_OUT
{
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
} vs_out;

out vec4 v_FragmentPos;

uniform mat4 u_Proj;
uniform mat4 u_View;
uniform mat4 u_Model;

uniform bool isInverseNormal;

void main()
{
	gl_Position = u_Proj * u_View * u_Model * a_Position;

	vs_out.Normal = isInverseNormal ? -normalize(a_Normal) : normalize(a_Normal);

	vs_out.TexCoords = a_TextureCoordinates;

	vs_out.FragPos = vec3(u_View * u_Model * a_Position);
};

#fragment shader

#version 330 core

layout(location = 0) out vec3 gPosition;
layout(location = 1) out vec3 gNormal;
layout(location = 2) out vec3 gAlbedo;

in VS_OUT
{
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
} fs_in;

void main()
{
	gPosition = fs_in.FragPos;

	gNormal = normalize(fs_in.Normal);

	gAlbedo = vec3(0.95f);
}