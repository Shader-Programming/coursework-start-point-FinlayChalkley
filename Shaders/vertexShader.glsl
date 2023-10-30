#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec3 normal;
out vec3 posInWS; // pass position in world to frag shader
void main(){

    normal = aNormal;

    vec4 worldSpace = Model * vec4(apos, 1.0);
    posInWS - worldspace.xyz;
    gl_Position = Projection * View * worldSpace ;

}