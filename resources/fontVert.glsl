#version 330
in vec3 position;
in vec4 color;
in vec2 coord;
in mat4 font_matrix;
out vec2 UV;
void main()
{
	UV = coord;
	vColor = color;
	gl_Position = vec4(position,0.0,1.0);
}