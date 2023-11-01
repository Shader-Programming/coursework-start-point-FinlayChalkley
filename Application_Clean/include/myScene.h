#pragma once
#include "Scene.h"
#include "Shader.h"
#include "lights/DirectionalLight.h"
#include "cube.h"



class MyScene : public Scene
{
public:
	MyScene(GLFWwindow* window, InputHandler* H);
	~MyScene() {};
	void update(float dt) override;

private:
		
	Shader* m_myShader;
	DirectionalLight* m_directionalLight;
	Cube* m_cube;

	void render();
};

