// BasicMaterial.vert  Lambert光照
#version 460 core
// 顶点位置
layout(location = 0) in vec3 a_Position;
// 顶点法线
layout(location = 1) in vec3 a_Normal;
// 纹理坐标
layout(location = 3) in vec2 a_UV;

// 模型矩阵
uniform mat4 u_Model;
// 视图矩阵
uniform mat4 u_View;
// 投影矩阵
uniform mat4 u_Projection;

// 传递给片段着色器的纹理坐标
out vec2 v_UV;
// 传递给片段着色器的世界空间下的顶点位置
out vec3 v_WorldPos;
// 传递给片段着色器的世界空间下的顶点法线
out vec3 v_Normal;
// 传递给片段着色器的顶点颜色
out vec4 v_Color;

void main()
{
    v_UV = a_UV;
    v_WorldPos = vec3(u_Model * vec4(a_Position, 1.0));
    v_Normal = a_Normal;
    mat4 MVP = u_Projection * u_View * u_Model;
    gl_Position = MVP * vec4(a_Position, 1.0);
}

