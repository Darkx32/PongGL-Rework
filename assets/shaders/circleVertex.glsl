#version 450 core
layout (location = 0) in vec2 position;

out vec2 aPosition;
out vec4 aColor;
out float aRadius;

uniform mat4 uTransform;
uniform vec3 uColor;
uniform vec2 uPosition;
uniform float uRadius;

void main()
{
	gl_Position = uTransform * vec4(position, 0.0, 1.0);

	aColor = vec4(uColor, 1.0);
	aPosition = position;
	aRadius = uRadius;
}