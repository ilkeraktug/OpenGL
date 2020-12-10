#vertex shader

#version 330 core
layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoords;

out VS_OUT
{

    vec3 Normal;
    vec2 TexCoords;
    vec3 FragPos;
}vs_out;

uniform mat4 u_Proj;
uniform mat4 u_View;
uniform mat4 u_Model;

void main()
{
    gl_Position = u_Proj * u_View * u_Model * a_Position;

    mat3 normalMatrix = transpose(inverse(mat3(u_Model)));
    vs_out.Normal = normalMatrix * a_Normal;
    vs_out.TexCoords = a_TexCoords;
    vs_out.FragPos = vec3(u_Model * a_Position);
}


#fragment shader

#version 330 core
layout(location = 0) out vec3 gPosition;
layout(location = 1) out vec3 gNormal;
layout(location = 2) out vec4 gAlbedoSpec;

in VS_OUT
{
    vec3 Normal;
    vec2 TexCoords;
    vec3 FragPos;
}fs_in;

struct Material
{
    sampler2D Diffuse;
    sampler2D Specular;
};

uniform Material u_Material;

void main()
{
    //gPosition = vec4(fs_in.FragPos, 1.0f);
    gPosition = fs_in.FragPos;
    //gPosition = vec3(1.0f, 0.5f, 0.5f);

    //gNormal = vec4(fs_in.Normal, 1.0f);
    gNormal = normalize(fs_in.Normal);

    gAlbedoSpec.rgb = texture(u_Material.Diffuse, fs_in.TexCoords).rgb;
    gAlbedoSpec.a = texture(u_Material.Specular, fs_in.TexCoords).r;
}
