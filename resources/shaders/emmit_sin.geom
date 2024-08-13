#version 330 core

layout(points) in;
layout(points, max_vertices = 32) out;

uniform mat4 MVP;

uniform float uTime;
uniform float uFrequency;
uniform float uSpeed;
uniform float uAmplitude;
uniform float uVertices;
uniform float uUnit;
uniform float uPointPixelSize;
uniform vec2 uViewportSize;

in VS_OUT {
    vec4 color;
} gs_in[];

out vec4 fragColor;

float pointSizeNDC;

vec4 GetPosition(int i, int j) {
    float z = i * (uUnit);
    float x = j * uUnit;
    float y = uAmplitude * sin(uFrequency * z + uSpeed * uTime);

    return vec4(x, y, z, 0);
}

vec4 GetColor(int i, int j) {
    vec4 baseColor = gs_in[0].color;
    float offset = float(i) / uVertices;
    return vec4(offset * baseColor.rgb, baseColor.w);
}

void main() {
    pointSizeNDC = uPointPixelSize / uViewportSize.x;

    for (int i = 0; i < uVertices; i++) {
        gl_PointSize = uPointPixelSize;
        gl_Position = MVP * GetPosition(i, 0) + gl_in[0].gl_Position;
        fragColor = GetColor(i, 0);
        EmitVertex();
    }

    EndPrimitive();
}
