#version 330
in vec2 position;
in vec2 coord;
out vec2 UV;
void main()
{
	UV = coord;
	gl_Position = vec4(position,0.0,1.0);
}