#version 330 core

layout(points) in;
layout(points, max_vertices = 32) out;

uniform float time;

in VS_OUT {
    vec4 color;
} gs_in[];

out vec4 fragColor;

const int vertices = 32;
const float x_scale = 4;
const float y_scale = 0.85;

void main() {
    fragColor = gs_in[0].color;

    float fVertices = float(vertices);
    float unit = 2 / fVertices;
    float offset = -0.5 * unit * fVertices + 0.5 * unit;

    for (int i = 0; i < vertices; i++) {
        float x = offset + (i * unit);
        float y = y_scale * sin(x_scale * x + time);
        gl_Position = gl_in[0].gl_Position + vec4(x, y, 0.0, 0.0);
        EmitVertex();
    }

    EndPrimitive();
}
