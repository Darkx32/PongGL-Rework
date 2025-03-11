#version 330 core
layout (location = 0) in vec2 position;

out vec3 aColor;

uniform mat4 uTransform;
uniform vec3 uColor;

void main(){
	gl_Position = uTransform * vec4(position, 0.0, 1.0);
	aColor = uColor;
}