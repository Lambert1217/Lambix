#version 460 core

out vec2 vs_uv; // 输出到片段着色器的颜色

layout(location = 0) in vec3 position; // 输入顶点位置
layout(location = 1) in vec2 uv;    // 输入顶点颜色

uniform mat4 MVP;

void main() {
    gl_Position = MVP * vec4(position, 1.0f); // 将顶点位置传递给gl_Position，构成齐次坐标
    vs_uv = uv; // 将颜色值传递给片段着色器
}
