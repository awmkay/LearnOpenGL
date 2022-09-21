#version 330 core
out vec4 FragColor;

in vec2 textureCoords;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main() {
	FragColor = mix(texture(texture0, textureCoords), texture(texture1, textureCoords), 0.2);
}
