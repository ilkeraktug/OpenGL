#vertex shader

#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TextureCoordinates;

uniform mat4 u_Model;

void main()
{
	gl_Position = u_Model * a_Position;
};

#geometry shader

#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 18) out;


uniform mat4 u_ShadowMat[6];

out vec4 v_FragPos;

void main()
{
	for (int face = 0; face < 6; face++)
	{
		gl_Layer = face;
		for (int i = 0; i < 3; i++)
		{
			v_FragPos = gl_in[i].gl_Position;
			gl_Position = u_ShadowMat[face] * v_FragPos;
			EmitVertex();	
		}
		EndPrimitive();
	}
}

#fragment shader

#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_FragPos;

uniform vec3 u_LightPos;
uniform float u_FarPlane;

void main()
{
	float lightDistance = length(u_LightPos - vec3(v_FragPos));

	lightDistance /= u_FarPlane;

	gl_FragDepth = lightDistance;

	//color = vec4(vec3(gl_FragDepth), 1.0f);
};
