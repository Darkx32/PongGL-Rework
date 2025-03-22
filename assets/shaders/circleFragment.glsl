#version 450 core
out vec4 FragColor;

in vec4 aColor;
in float aRadius;
in vec2 aPosition;

void main()
{
	vec2 uv = aPosition - vec2(0.5);
    float d = length(uv);
	float circle = smoothstep(0.5, 0.48, d);

    FragColor = vec4(aColor.rgb, circle);
}