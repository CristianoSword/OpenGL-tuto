#version 210

out vec4 fColor;

in vec4 vertexColor;

void main()
{
	fColor = vertexColor;
}