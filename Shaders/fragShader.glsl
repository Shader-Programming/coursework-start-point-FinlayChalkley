#version 330 core

uniform vec3 viewPos;
uniform vec3 cubeColour;
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
// material properties 
uniform sampler2D diffuseMap;
uniform sampler2D specularMap;
uniform sampler2D normalMap;
uniform float shine;


out vec4 FragColor;
in vec3 normal;
in vec3 posInWS;
in vec2 uv;
in mat3 TBN;

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
vec3 getSpotLight();
vec3 aces(vec3 x);

void main(){
    n = texture(normalMap, uv).rgb;
    n = n*2.0 - 1.0;
    n = normalize(TBN*n);
    vec3 result = getDirectionalLight();
    result += getPointLight();
    //vec3 result = getSpotLight(); // doesn't work
    result = aces(result);
    FragColor = vec4(result, 1.0);
}

vec3 getDirectionalLight() {
    vec3 objCol = texture(diffuseMap, uv).rgb;
    float specStrength = texture(specularMap, uv).r;

    // ambient
    vec3 ambient = objCol * lightColour * ambientFactor;

    //diffuse
    float diffuseFactor = dot(n, -lightDirection);
    diffuseFactor = max(diffuseFactor, 0.0f);
    vec3 diffuse = objCol * lightColour * diffuseFactor;

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
    vec3 objCol = texture(diffuseMap, uv).rgb;
    float specStrength = texture(specularMap, uv).r;

    vec3 totalDiffuse = vec3(0.0);
    vec3 totalSpecular = vec3(0.0);

    for (int i = 0; i < numPL; i++) {
        float distance = length(pointArray[i].position - posInWS);
        float attn = 1.0 / (pointArray[i].constants.x + (pointArray[i].constants.y*distance) + (pointArray[i].constants.z*(distance*distance)));

        vec3 lightDir = normalize((pointArray[i].position - posInWS));

        //diffuse
        float diffuseFactor = dot(n, -lightDir);
        diffuseFactor = max(diffuseFactor, 0.0f);
        vec3 diffuse = objCol * pointArray[i].colour * diffuseFactor;
    
        //specular
        vec3 viewDir = normalize(viewPos - posInWS); // posInWS comes from vertex shader
        vec3 H = normalize(-pointArray[i].position + viewDir);
        float specLevel = dot(n, H);
        specLevel = max(specLevel, 0.0); //make sure value is > 0
        specLevel = pow(specLevel, shine); // exponent, float variable
        vec3 specular = pointArray[i].colour * specLevel * specStrength;
        specular = specular * attn;
        diffuse = diffuse * attn;
        
        //totalDiffuse += diffuse;
        //totalSpecular += specular;

        return diffuse + specular;
        // multiple point lights work when the attn value is not used. but when it is used the screen appears black with no picture.
    }
    
    //return totalDiffuse + totalSpecular;
    
    

}

vec3 getSpotLight() {

    vec3 objCol = texture(diffuseMap, uv).rgb;
    float specStrength = texture(specularMap, uv).r;

    
    float theta = dot(-sDirection, normalize(sDirection));
    float denom = (sRadii.x - sRadii.y);
    float intensity = (theta - sRadii.y) / denom;
    intensity = clamp(intensity, 0.0f, 1.0f);
 
    //diffuse
    float diffuseFactor = dot(n, -sDirection);
    diffuseFactor = max(diffuseFactor, 1.0f);
    vec3 diffuse = objCol * slightColour * diffuseFactor;
    //diffuse = diffuse * intensity;

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

vec3 aces(vec3 x) {
    const float a = 2.51;
    const float b = 0.03;
    const float c = 2.43;
    const float d = 0.59;
    const float e = 0.14;
    return clamp((x * (a * x + b)) / (x * (c * x + d) + e), 0.0, 1.0);

}

