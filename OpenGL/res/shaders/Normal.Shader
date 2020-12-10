#vertex shader

#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec2 a_TextureCoordinates;
layout(location = 2) in vec3 a_Normal;

out vec3 v_Normal;

out VS_OUT{
    vec2 texCoords;
    mat3 normalMatrix;
    vec3 fragPos;
} vs_out;

uniform mat4 u_View;
uniform mat4 u_Model;

void main()
{
    gl_Position = u_View * u_Model * a_Position;

    vs_out.normalMatrix = mat3(transpose(inverse(u_View * u_Model)));

    vs_out.texCoords = a_TextureCoordinates;

    vs_out.fragPos = vec3(u_Model * a_Position);
};

#geometry shader
#version 330 core
layout(triangles) in;
layout(line_strip, max_vertices = 6) out;

in VS_OUT{
    vec2 texCoords;
    mat3 normalMatrix;
    vec3 fragPos;
} gs_in[];

uniform mat4 u_Proj;

vec3 GetNormal()
{
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}

void VisualizeNormal(int index)
{
    float mag = 0.4f;

    gl_Position = u_Proj * gl_in[index].gl_Position;
    EmitVertex();
    gl_Position = u_Proj * (gl_in[index].gl_Position + vec4(GetNormal(), 0.0f) * mag);
    EmitVertex();

    EndPrimitive();
}

void main()
{

    VisualizeNormal(0);
    VisualizeNormal(1);
    VisualizeNormal(2);
   
}

#fragment shader

#version 330 core
layout(location = 0) out vec4 color;

void main()
{
    color = vec4(1.0f, 0.5f, 0.31f, 1.0f);
};
