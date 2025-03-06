// BasicMaterial.frag
#version 460 core

// 方向光结构体 (必须与C++结构体内存对齐)
struct DirectionalLight {
    vec4 direction;     // XYZ:方向, W:未使用
    vec4 color;         // RGB:颜色, A:强度
};
// 点光源结构体
struct PointLight {
    vec4 position;      // XYZ:位置, W:范围
    vec4 color;         // RGB:颜色, A:强度
    vec4 attenuation;   // x:常数衰减 y:线性衰减 z:二次衰减
};
// 聚光灯结构体
struct SpotLight {
    vec4 position;      // XYZ:位置, W:范围
    vec4 direction;     // XYZ:方向, W:内锥角余弦
    vec4 color;         // RGB:颜色, A:强度
    vec4 spotParams;    // x:外锥角余弦 y:衰减 zw:未使用
};

layout(std140, binding = 1) uniform LightingUBO {
    // 头部信息
    ivec4 lightCounts;  // x:方向光 y:点光 z:聚光 w:总光源
    vec4 ambient;       // RGB:环境光颜色 A:强度

    DirectionalLight directionalLights[4];
    PointLight pointLights[16];
    SpotLight spotLights[8];
} ubo;

// 材质属性
uniform sampler2D u_DiffuseMap;
uniform sampler2D u_NormalMap;
uniform vec4 u_BaseColor;
uniform struct PBR {
    vec3 albedo;
    float metallic;
    float roughness;
    float ao;
} u_PBR;

// 输入变量
in vec3 v_FragPos;
in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_Tangent;
in vec3 v_Bitangent;

out vec4 FragColor;

// PBR光照计算函数
vec3 CalculatePBR(vec3 normal, vec3 viewDir, vec3 lightDir, vec3 radiance)
{
    // 基础参数
    float NdotL = max(dot(normal, lightDir), 0.0);
    vec3 H = normalize(viewDir + lightDir);

    // 法线分布函数 (Trowbridge-Reitz GGX)
    float a = u_PBR.roughness * u_PBR.roughness;
    float a2 = a * a;
    float NdotH = max(dot(normal, H), 0.0);
    float NDF = a2 / (3.14159 * pow(NdotH * NdotH * (a2 - 1.0) + 1.0, 2.0));

    // 菲涅尔方程 (Fresnel-Schlick近似)
    vec3 F0 = mix(vec3(0.04), u_PBR.albedo, u_PBR.metallic);
    vec3 F = F0 + (1.0 - F0) * pow(1.0 - max(dot(H, viewDir), 0.0), 5.0);

    // 几何函数 (Smith-Schlick GGX)
    float k = pow(u_PBR.roughness + 1.0, 2.0) / 8.0;
    float G = 1.0 / ((NdotL * (1.0 - k) + k) * (max(dot(normal, viewDir), 0.0) * (1.0 - k) + k));

    // 组合BRDF
    vec3 numerator = NDF * F * G;
    float denominator = 4.0 * max(dot(normal, viewDir), 0.0) * NdotL;
    vec3 specular = numerator / max(denominator, 0.001);

    // 能量守恒
    vec3 kD = (1.0 - F) * (1.0 - u_PBR.metallic);

    return (kD * u_PBR.albedo / 3.14159 + specular) * radiance * NdotL;
}

void main()
{
    // 法线处理逻辑 --------------------------------------------------
    vec3 normal;
    if (textureSize(u_NormalMap, 0).x > 1) // 存在法线贴图
    {
        vec3 tangentNormal = texture(u_NormalMap, v_TexCoord).rgb * 2.0 - 1.0;
        mat3 TBN = mat3(normalize(v_Tangent), 
                        normalize(v_Bitangent), 
                        normalize(v_Normal));
        normal = normalize(TBN * tangentNormal);
    }
    else // 无法线贴图时使用顶点法线
    {
        normal = normalize(v_Normal);
    }

    // 基础颜色
    vec4 baseColor = texture(u_DiffuseMap, v_TexCoord) * u_BaseColor;

    // 观察方向
    vec3 viewDir = normalize(-v_FragPos);

    // 环境光照
    vec3 ambient = ubo.ambient.rgb * ubo.ambient.a * u_PBR.albedo * u_PBR.ao;
    vec3 lighting = ambient;

    // 方向光计算
    for(int i = 0; i < ubo.lightCounts.x; ++i)
    {
        vec3 lightDir = normalize(-ubo.directionalLights[i].direction.xyz);
        vec3 radiance = ubo.directionalLights[i].color.rgb * ubo.directionalLights[i].color.a;
        lighting += CalculatePBR(normal, viewDir, lightDir, radiance);
    }

    // 点光源计算
    for(int i = 0; i < ubo.lightCounts.y; ++i)
    {
        vec3 lightDir = ubo.pointLights[i].position.xyz - v_FragPos;
        float distance = length(lightDir);
        lightDir = normalize(lightDir);
        float attenuationFactor = 1.0 / (ubo.pointLights[i].attenuation.x + 
                                         ubo.pointLights[i].attenuation.y * distance + 
                                         ubo.pointLights[i].attenuation.z * distance * distance);
        vec3 radiance = ubo.pointLights[i].color.rgb * ubo.pointLights[i].color.a * attenuationFactor;
        lighting += CalculatePBR(normal, viewDir, lightDir, radiance);
    }

    // 最终颜色合成
    FragColor = vec4(lighting * baseColor.rgb, baseColor.a);
}
