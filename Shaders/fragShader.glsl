#version 330 core

uniform vec3 viewPos;
uniform vec3 cubeColour;
uniform vec3 lightColour;
uniform vec3 lightDirection;

uniform vec3 plightPosition;
uniform vec3 plightcolour;
uniform vec3 pAttentuation;

uniform float ambientFactor;
uniform float shine;
uniform float specStrength;

out vec4 FragColor;
in vec3 normal;
in vec3 posInWS;


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
vec3 getDirectionalLight();
vec3 getPointLight() {
    //attn
    float distance = length(plightPosition - posInWS);
    float attn = 1.0 / (pAttentuation.x + (pAttentuation.y*distance) + (pAttentuation.z*(distance*distance)));

    vec3 lightDir = normalize((plightPosition - posInWS));

    //diffuse
    float diffuseFactor = dot(n, -lightDirection);
    diffuseFactor = max(diffuseFactor, 0.0f);
    vec3 diffuse = cubeColour * lightColour * diffuseFactor;
    diffuse = diffuse* attn;
    //specular
    vec3 viewDir = normalize(viewPos - posInWS); // posInWS comes from vertex shader
    vec3 H = normalize(-lightDirection + viewDir);
    float specLevel = dot(n, H);
    specLevel = max(specLevel, 0.0); //make sure value is > 0
    specLevel = pow(specLevel, shine); // exponent, float variable
    vec3 specular = lightColour * specLevel * specStrength;
    specular = specular*attn;


    return diffuse + specular;
}

void main(){
    vec3 result = getDirectionalLight();
    result += getPointLight();
    FragColor = vec4(result, 1.0);

}