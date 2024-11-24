#version 460 core

in vec4 vs_color; // 从顶点着色器中接收颜色
out vec4 FragColor; // 输出颜色

void main() {
    FragColor = vs_color; // 将顶点颜色直接输出为片段颜色
}
