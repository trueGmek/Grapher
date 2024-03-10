#version 330 core
layout(location = 0) in vec3 aPos;

uniform vec4 uColor;

out vec4 aColor;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
    aColor = uColor;
}
