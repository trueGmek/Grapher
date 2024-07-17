#version 330 core
layout(location = 0) in vec3 aPos;

uniform vec4 uColor;
uniform mat4 MVP;

out VS_OUT {
    vec4 color;
} vs_out;

void main() {
    gl_Position = MVP * vec4(aPos, 1.0f);
    vs_out.color = uColor;
}
