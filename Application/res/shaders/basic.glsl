#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 TexCoord;

out vec2 v_TexCoord;

uniform mat4 u_ModelViewProjectionMatrix;

void main()
{
	v_TexCoord = TexCoord;
	gl_Position = u_ModelViewProjectionMatrix * position; // Multiplication order matters here!
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = texColor;
};
