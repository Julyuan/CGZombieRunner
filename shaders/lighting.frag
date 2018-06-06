#version 330 core
out vec4 FragColor;
#define NR_POINTLIGHTS 1
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

struct Material {
    sampler2D texture_diffuse;
    sampler2D texture_specular;
    float shininess;
};

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dirLight;

struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
uniform vec3 viewPos;
uniform PointLight lights[NR_POINTLIGHTS];
uniform Material material;

//uniform sampler2D texture_diffuse;

vec3 DirLightEffects(DirLight light,vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.texture_diffuse, TexCoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.texture_diffuse, TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.texture_specular, TexCoord));
    return (ambient + diffuse + specular);
}

vec3 PointLightEffects(PointLight light, vec3 normal,vec3 fragPos, vec3 viewDir)
{
        vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse,TexCoord));
        float distance    = length(light.position-fragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance +
            		    light.quadratic * (distance * distance));;
        vec3 lightDir = normalize(light.position-fragPos);
        float diff = max(dot(normal,lightDir),0);
        vec3 diffuse = light.diffuse * (diff * vec3(texture(material.texture_diffuse,TexCoord)));
        // specular

        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = light.specular * (spec * vec3(texture(material.texture_specular,TexCoord)));

        ambient *=attenuation;
        diffuse *=attenuation;
        specular*=attenuation;
        vec3 result = ambient + diffuse + specular;
        return result;
}

void main(){
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 norm = normalize(Normal);
    vec3 result;
    result = DirLightEffects(dirLight,norm,viewDir);

    for(int i=0;i< NR_POINTLIGHTS;i++){
        result += PointLightEffects(lights[i],norm,FragPos,viewDir);
    }
    FragColor = vec4(result, 1.0);
}