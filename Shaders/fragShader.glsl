#version 330 core

uniform vec3 viewPos;
uniform vec3 cubeColour;
uniform float shine;
uniform float specStrength;
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

#define numPL 50
uniform PointLight pointArray[numPL];


vec3 n = normalize(normal);
vec3 viewDir = normalize(viewPos - posInWS); // posInWS comes from vertex shader
vec3 getDirectionalLight();
vec3 getPointLight();

void main(){
    vec3 result = getDirectionalLight();
    result += getPointLight();
    //result += getSpotLight();
    //result = aces(result);
    FragColor = vec4(result, 1.0);

}

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
    float distance = length(pointArray[0].position - posInWS);
    float attn = 1.0 / (pointArray[0].constants.x + (pointArray[0].constants.y*distance) + (pointArray[0].constants.z*(distance*distance)));

    vec3 lightDir = normalize((pointArray[0].position - posInWS));

    //diffuse
    float diffuseFactor = dot(n, -lightDir);
    diffuseFactor = max(diffuseFactor, 0.0f);
    vec3 diffuse = cubeColour * pointArray[0].colour * diffuseFactor;
    
    //specular
    vec3 viewDir = normalize(viewPos - posInWS); // posInWS comes from vertex shader
    vec3 H = normalize(-pointArray[0].position + viewDir);
    float specLevel = dot(n, H);
    specLevel = max(specLevel, 0.0); //make sure value is > 0
    specLevel = pow(specLevel, shine); // exponent, float variable
    vec3 specular = pointArray[0].colour * specLevel * specStrength;
    //specular = specular * attn;
    //diffuse = diffuse * attn;

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
/*
vec3 aces(vec3 x) {
    const float a = 2.51;
    const float b = 0.03;
    const float c = 2.43;
    const float d = 0.59;
    const float e = 0.14;
    return clamp((x * (a * x + b)) / (x * (c * x + d) + e), 0.0, 1.0);

}
*/
