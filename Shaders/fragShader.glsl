#version 330 core

uniform vec3 viewPos;
uniform vec3 cubeColour;
uniform float shine;
uniform float specStrength;
//point light uniforms
uniform vec3 plightPosition;
uniform vec3 plightcolour;
uniform vec3 pAttentuation;
//directional light uniforms
uniform vec3 lightColour;
uniform vec3 lightDirection;
uniform float ambientFactor;
//spotLight uniforms
uniform vec3 slightPosition;
uniform vec3 slightColour;
uniform vec3 sAttentuation;
uniform vec3 sDirection;
uniform vec2 sRadii;

out vec4 FragColor;
in vec3 normal;
in vec3 posInWS;

struct PointLight {
    vec3 colour;
    vec3 position;
    vec3 constants;
};

#define numPL 2
uniform PointLight[numPL];


vec3 n = normalize(normal);
vec3 viewDir = normalize(viewPos - posInWS); // posInWS comes from vertex shader

vec3 getDirectionalLight() {
    // ambient
    vec3 ambient = cubeColour * lightColour * ambientFactor;

    //diffuse
    float diffuseFactor = dot(n, -lightDirection);
    diffuseFactor = max(diffuseFactor, 0.0f);
    vec3 diffuse = cubeColour * lightColour * diffuseFactor;

    //blinn phong specular
    vec3 viewDir = normalize(viewPos - posInWS); // posInWS comes from vertex shader
    vec3 H = normalize(-lightDirection + viewDir);
    float specLevel = dot(n, H);
    specLevel = max(specLevel, 0.0); //make sure value is > 0
    specLevel = pow(specLevel, shine); // exponent, float variable
    vec3 specular = lightColour * specLevel * specStrength;

    return ambient + diffuse + specular;

}
vec3 getPointLight() {
    //attn
    float distance = length(plightPosition - posInWS);
    float attn = 1.0 / (pAttentuation.x + (pAttentuation.y*distance) + (pAttentuation.z*(distance*distance)));

    vec3 lightDir = normalize((plightPosition - posInWS));

    //diffuse
    float diffuseFactor = dot(n, -plightPosition);
    diffuseFactor = max(diffuseFactor, 0.0f);
    vec3 diffuse = cubeColour * plightcolour * diffuseFactor;
    diffuse = diffuse * attn;
    //specular
    vec3 viewDir = normalize(viewPos - posInWS); // posInWS comes from vertex shader
    vec3 H = normalize(-plightPosition + viewDir);
    float specLevel = dot(n, H);
    specLevel = max(specLevel, 0.0); //make sure value is > 0
    specLevel = pow(specLevel, shine); // exponent, float variable
    vec3 specular = plightcolour * specLevel * specStrength;
    specular = specular * attn;


    return diffuse + specular;
}

vec3 getSpotLight() {
    float theta = dot(-sDirection, normalize(sDirection));
    float denom = (sRadii.x - sRadii.y);
    float intensity = (theta - sRadii.y) / denom;
    intensity = clamp(intensity, 0.0, 1.0);
    //diffuse
    float diffuseFactor = dot(n, -slightPosition);
    diffuseFactor = max(diffuseFactor, 0.0f);
    vec3 diffuse = cubeColour * slightColour * diffuseFactor;
    diffuse = diffuse * intensity;
    //specular
    vec3 viewDir = normalize(viewPos - posInWS); // posInWS comes from vertex shader
    vec3 H = normalize(-slightPosition + viewDir);
    float specLevel = dot(n, H);
    specLevel = max(specLevel, 0.0); //make sure value is > 0
    specLevel = pow(specLevel, shine); // exponent, float variable
    vec3 specular = slightColour * specLevel * specStrength;
    specular = specular * intensity;

    return diffuse + specular;
}


void main(){
    vec3 result = getDirectionalLight();
    result += getPointLight();
    FragColor = vec4(result, 1.0);

}