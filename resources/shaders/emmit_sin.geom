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

vec4 GetPosition(int i) {
    vec4 basePosition = gl_in[0].gl_Position;

    float z = i * (uUnit + pointSizeNDC) + basePosition.z;
    float x = basePosition.x;
    float argument = sqrt(z * z + x * x);
    float y = uAmplitude * sin(uFrequency * argument + uSpeed * uTime) + basePosition.y;

    return vec4(x, y, z, basePosition.w);
}

vec4 GetColor(int i) {
    vec4 baseColor = gs_in[0].color;
    float offset = float(i) / uVertices;
    return vec4(offset * baseColor.rgb, baseColor.w);
}

void main() {
    pointSizeNDC = 2 * uPointPixelSize / uViewportSize.x;

    for (int i = 0; i < uVertices; i++) {
        gl_PointSize = uPointPixelSize;
        gl_Position = MVP * GetPosition(i);
        fragColor = GetColor(i);
        EmitVertex();
    }

    EndPrimitive();
}
