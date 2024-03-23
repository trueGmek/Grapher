#version 330 core
layout(location = 0) in vec3 aPos;

uniform vec4 uColor;
uniform mat4 MVP;

out vec4 aColor;

void main() {
    gl_Position = MVP * vec4(aPos, 1.0f);
    aColor = uColor;
}
