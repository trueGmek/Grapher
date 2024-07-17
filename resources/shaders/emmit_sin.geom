#version 330 core

layout(points) in;
layout(points, max_vertices = 32) out;

uniform float uTime;
uniform float uFrequency;
uniform float uSpeed;
uniform float uAmplitude;

in VS_OUT {
    vec4 color;
} gs_in[];

out vec4 fragColor;

const int vertices = 32;

void main() {
    float fVertices = float(vertices);
    float unit = 0.01f;
    // float offset = -0.5 * unit * fVertices + 0.5 * unit;

    for (int i = 0; i < vertices; i++) {
        float x = -1.f + (i * unit) + gl_in[0].gl_Position.x;
        float y = uAmplitude * sin(uFrequency * x + uSpeed * uTime);
        gl_Position = vec4(x, y, 0.0, 1.0);
        fragColor = gs_in[0].color;
        EmitVertex();
    }

    EndPrimitive();
}
