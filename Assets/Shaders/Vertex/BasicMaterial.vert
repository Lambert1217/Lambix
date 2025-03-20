// BasicMaterial.vert
#version 460 core
layout(location = 0) in vec3 a_Position;
layout(location = 3) in vec2 a_UV;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec2 v_UV;

void main()
{
    v_UV = a_UV;
    mat4 MVP = u_Projection * u_View * u_Model;
    gl_Position = MVP * vec4(a_Position, 1.0);
}
