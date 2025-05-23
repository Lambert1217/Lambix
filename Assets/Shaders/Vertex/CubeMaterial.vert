// CubeMaterial.vert
#version 460 core
layout(location = 0) in vec3 a_Position;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 v_UV;

void main()
{
    v_UV = a_Position;
    vec4 pos = u_Projection * u_View * u_Model * vec4(a_Position, 1.0);
    gl_Position = pos.xyww;
}
