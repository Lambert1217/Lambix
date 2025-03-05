// BasicMaterial.frag
#version 460 core
in vec3 v_Normal;
in vec2 v_TexCoord;
in vec3 v_FragPos;

uniform vec4 u_BaseColor;
uniform float u_Metallic;
uniform float u_Roughness;
uniform sampler2D u_DiffuseMap;

// 简化版光照计算
vec3 CalculateLighting(vec3 normal, vec3 viewDir)
{
    // 模拟环境光照
    vec3 ambient = vec3(0.1f);
    
    // 模拟平行光
    vec3 lightDir = normalize(vec3(0.5f, 1.0f, 0.7f));
    float diff = max(dot(normal, lightDir), 0.0f);
    vec3 diffuse = diff * vec3(0.8f);
    
    // 基础PBR反射计算
    float metallic = clamp(u_Metallic, 0.0f, 1.0f);
    float roughness = clamp(u_Roughness, 0.04f, 1.0f);
    
    vec3 F0 = mix(vec3(0.04f), u_BaseColor.rgb, metallic);
    vec3 F = F0 + (1.0f - F0) * pow(1.0f - max(dot(viewDir, lightDir), 0.0f), 5.0f);
    
    return ambient + (diffuse * (1.0f - metallic) + F) * roughness;
}

out vec4 FragColor;

void main()
{
    // 从材质获取基础颜色
    vec4 baseColor = texture(u_DiffuseMap, v_TexCoord) * u_BaseColor;
    
    // 计算观察方向
    vec3 viewDir = normalize(-v_FragPos);
    
    // 法线处理
    vec3 normal = normalize(v_Normal);
    
    // 应用光照计算
    vec3 result = CalculateLighting(normal, viewDir);
    
    FragColor = vec4(result * baseColor.rgb, baseColor.a);
}
