// CubeMaterial.frag
#version 460 core

in vec3 v_UV;

uniform samplerCube u_CubeMap;

out vec4 FragColor;

void main()
{
    FragColor = texture(u_CubeMap, v_UV);
}
