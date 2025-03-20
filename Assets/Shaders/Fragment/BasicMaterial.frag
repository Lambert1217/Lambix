// BasicMaterial.frag
#version 460 core

in vec2 v_UV;

uniform sampler2D u_DiffuseMap;
uniform vec4 u_BaseColor;

out vec4 FragColor;

void main()
{
    FragColor = texture(u_DiffuseMap, v_UV) * u_BaseColor;
}
