#version 130

uniform mat4 projection, view, model;

in vec2 position;

void main()
{
	// Transform position from pixel coordinates to clipping coordinates
	gl_Position = projection * view * model * vec4(position, 0.0, 1.0);
}
