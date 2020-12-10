#vertex shader

#version 330 core
	
layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec2 a_TextureCoordinates;
layout(location = 2) in vec3 a_Normal;

out vec3 v_Normal;

out VS_OUT {
	vec2 texCoords;
    mat3 normalMatrix;
    vec3 fragPos;
} vs_out;

uniform mat4 u_View;
uniform mat4 u_Model;
uniform mat4 u_Proj;
void main()
{
    gl_Position = u_Proj * u_View * u_Model * a_Position;

    vs_out.normalMatrix = mat3(transpose(inverse(u_View * u_Model)));

    vs_out.texCoords = a_TextureCoordinates;

    vs_out.fragPos = vec3(u_Model * a_Position);
};

#geometry shader
#version 330 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in VS_OUT{
    vec2 texCoords;
    mat3 normalMatrix;
    vec3 fragPos;
} gs_in[];

out vec3 v_FragPos;
out vec2 v_TexCoords;
out vec3 v_Normal;

vec3 GetNormal()
{
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}

void main() 
{
    v_Normal = GetNormal();

    gl_Position = gl_in[0].gl_Position;
    v_TexCoords = gs_in[0].texCoords;
    v_FragPos = gs_in[0].fragPos;
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    v_TexCoords = gs_in[1].texCoords;
    v_FragPos = gs_in[1].fragPos;
    EmitVertex();

    gl_Position = gl_in[2].gl_Position;
    v_TexCoords = gs_in[2].texCoords;
    v_FragPos = gs_in[2].fragPos;
    EmitVertex();

    EndPrimitive();
}

#fragment shader

#version 330 core
layout(location = 0) out vec4 color;

in vec3 v_FragPos;
in vec2 v_TexCoords;
in vec3 v_Normal;

struct Material {
	sampler2D Diffuse;
};

uniform Material u_Material;

uniform vec3 u_LightPosition;
uniform vec3 u_CamPosition;
uniform bool blinn;

void main()
{
	float ambientStr = 0.1f;
	vec3 texColor = vec3(texture(u_Material.Diffuse, v_TexCoords));
	vec3 ambient = ambientStr * texColor;

	vec3 lightDir = -normalize(u_LightPosition - v_FragPos);
	float diffuseStr = max(dot(lightDir, v_Normal), 0.0f);
	vec3 diffuse = diffuseStr * texColor;

    vec3 viewDir = normalize(u_CamPosition - v_FragPos);
    float specularStr = 0.0f;
	if(blinn)
	{
        vec3 halfwayDir = normalize(lightDir + viewDir);
        specularStr = pow(max(dot(halfwayDir, v_Normal), 0.0f), 32.0f);
  	}
    else
    {
        vec3 refDir = reflect(-lightDir, v_Normal);
        specularStr = pow(max(dot(refDir, viewDir), 0.0f), 16.0f);
    }
    vec3 specular = vec3(0.3f) * specularStr;
    color = vec4(ambient + diffuse + specular, 1.0f);
};
