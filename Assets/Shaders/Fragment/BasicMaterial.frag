// BasicMaterial.frag  Lambert光照
#version 460 core
// 从顶点着色器传入的纹理坐标
in vec2 v_UV;
// 从顶点着色器传入的世界空间下的顶点位置
in vec3 v_WorldPos;
// 从顶点着色器传入的世界空间下的顶点法线
in vec3 v_Normal;

// 漫反射纹理
uniform sampler2D u_DiffuseMap;
// 基础颜色
uniform vec4 u_BaseColor;

// UBO头部信息
struct lbLightingHeader
{
    ivec4 lightCounts; // x:方向光 y:点光 z:聚光 w:总光源数
    vec3 ambient;      // RGB: 环境光颜色
    float ambientIntensity; // 环境光强度
};

// 方向光数据数组
struct lbDirectionalLightData
{
    vec3 color;     // 颜色
    float intensity; // 强度
    vec3 direction; // 方向
    float padding;   // 填充
};
// 点光数据数组
struct lbPointLightData
{
    vec3 color;    // 颜色
    float intensity;    // 强度
    vec3 position; // 位置
    float MinRange;     // 衰减起始距离
    vec3 padding;  // 填充
    float Range;        // 最大作用距离
};
// 聚光数据数组
struct lbSpotLightData
{
    vec3 color;     // 颜色
    float intensity;     // 强度
    vec3 direction; // 方向
    float MinRange;      // 衰减起始距离
    vec3 position;  // 位置
    float Range;         // 最大作用距离
    float MinAngle;      // 内锥角（角度）
    float Angle;         // 外锥角（角度）
    vec2 padding;   // 填充
};
// 光照相关的统一缓冲区对象
layout (std140, binding = 1) uniform u_LightingUBO
{
    // UBO头部信息
    lbLightingHeader header;
    // 方向光数据数组
    lbDirectionalLightData DirectionalLights[4];
    // 点光数据数组
    lbPointLightData PointLights[256];
    // 聚光数据数组
    lbSpotLightData SpotLights[256];
};

out vec4 FragColor;

// 计算方向光漫反射
vec3 CalcDirectionalLight(lbDirectionalLightData light, vec3 normal)
{
    vec3 lightDir = -light.direction;
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * light.color * light.intensity;
    return diffuse;
}

// 计算点光漫反射
vec3 CalcPointLight(lbPointLightData light, vec3 normal, vec3 fragPos)
{
    vec3 lightDir = light.position - fragPos;
    float dist = length(lightDir);
    lightDir = normalize(lightDir);

    float diff = max(dot(normal, lightDir), 0.0);
    // 计算衰减
    float attenuation = 1.0;
    if (dist >= light.MinRange && dist <= light.Range) {
        // 在衰减范围内进行线性衰减计算
        attenuation = (light.Range - dist) / (light.Range - light.MinRange);
    } else if (dist > light.Range) {
        // 超出最大作用距离，光照强度为 0
        attenuation = 0.0;
    }
    vec3 diffuse = diff * light.color * light.intensity * attenuation;
    return diffuse;
}

// 计算聚光漫反射
vec3 CalcSpotLight(lbSpotLightData light, vec3 normal, vec3 fragPos)
{
    vec3 lightDir = light.position - fragPos;
    float dist = length(lightDir);
    lightDir = normalize(lightDir);

    float theta = dot(lightDir, -light.direction);
    float epsilon = cos(radians(light.MinAngle)) - cos(radians(light.Angle));
    float intensity = clamp((theta - cos(radians(light.Angle))) / epsilon, 0.0, 1.0);

    float diff = max(dot(normal, lightDir), 0.0);
    // 计算衰减
    float attenuation = 1.0;
    if (dist >= light.MinRange && dist <= light.Range) {
        // 在衰减范围内进行线性衰减计算
        attenuation = (light.Range - dist) / (light.Range - light.MinRange);
    } else if (dist > light.Range) {
        // 超出最大作用距离，光照强度为 0
        attenuation = 0.0;
    }
    vec3 diffuse = diff * light.color * light.intensity * intensity * attenuation;
    return diffuse;
}

void main()
{
    vec3 normal = normalize(v_Normal);

    // 表面颜色
    vec3 SurfaceColor = texture(u_DiffuseMap, v_UV).rgb * u_BaseColor.rgb;

    // 光源颜色
    vec3 LightColor = header.ambient * header.ambientIntensity;

    // 计算方向光
    for (int i = 0; i < header.lightCounts.x; ++i)
    {
        LightColor += CalcDirectionalLight(DirectionalLights[i], normal);
    }

    // 计算点光
    for (int i = 0; i < header.lightCounts.y; ++i)
    {
        LightColor += CalcPointLight(PointLights[i], normal, v_WorldPos);
    }

    // 计算聚光
    for (int i = 0; i < header.lightCounts.z; ++i)
    {
        LightColor += CalcSpotLight(SpotLights[i], normal, v_WorldPos);
    }

    // 直接叠加环境光和其他光源的贡献
    vec3 finalColor = LightColor * SurfaceColor;

    FragColor = vec4(finalColor, u_BaseColor.a);
}
