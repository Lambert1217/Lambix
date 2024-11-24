#version 460 core

layout(location = 0) in vec3 position; // 输入顶点位置
layout(location = 1) in vec4 color;    // 输入顶点颜色

out vec4 vs_color; // 输出到片段着色器的颜色

void main() {
    gl_Position = vec4(position, 1.0); // 将顶点位置传递给gl_Position，构成齐次坐标
    vs_color = color; // 将颜色值传递给片段着色器
}
