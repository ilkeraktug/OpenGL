#vertex shader

#version 330 core
layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoords;

uniform mat4 u_Proj;
uniform mat4 u_View;
uniform mat4 u_Model;

void main()
{
    gl_Position = u_Proj * u_View * u_Model * a_Position;
}


#fragment shader

#version 330 core
layout(location = 0) out vec4 outColor;


uniform vec3 lightColor;

void main()
{
    outColor = vec4(lightColor, 1.0f);
}
