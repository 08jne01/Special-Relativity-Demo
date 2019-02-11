#version 460 core
layout (location = 0) in vec3 vertexPositions;

out vec2 fragCoord;

void main()

{
	gl_Position = vec4(vertexPositions, 1.0);
	fragCoord = vertexPositions.xy;
}