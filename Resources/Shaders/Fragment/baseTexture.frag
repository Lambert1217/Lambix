#version 460 core

out vec4 FragColor; // 输出颜色

in vec2 vs_uv; // 从顶点着色器中接收颜色

uniform sampler2D Texture;
uniform vec4 Color;

void main() {
    FragColor = texture(Texture, vs_uv) * Color; // 将顶点颜色直接输出为片段颜色
}
