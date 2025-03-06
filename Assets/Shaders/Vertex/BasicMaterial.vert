// BasicMaterial.vert
#version 460 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in vec3 a_Tangent;

// 变换矩阵
uniform mat4 u_ModelViewProjection;
uniform mat4 u_ModelMatrix;

// 输出到片段着色器
out vec3 v_FragPos;
out vec2 v_TexCoord;
out vec3 v_Normal;
out vec3 v_Tangent;
out vec3 v_Bitangent;

void main()
{
    // 世界空间坐标
    v_FragPos = vec3(u_ModelMatrix * vec4(a_Position, 1.0));
    
    // 法线矩阵
    mat3 normalMatrix = transpose(inverse(mat3(u_ModelMatrix)));
    v_Normal = normalMatrix * a_Normal;
    
    // TBN矩阵计算
    v_Tangent = normalMatrix * a_Tangent;
    v_Bitangent = cross(v_Normal, v_Tangent);
    
    // 纹理坐标
    v_TexCoord = a_TexCoord;
    
    gl_Position = u_ModelViewProjection * vec4(a_Position, 1.0);
}
