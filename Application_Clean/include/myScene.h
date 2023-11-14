#pragma once
#include "Scene.h"
#include "Shader.h"
#include "lights/DirectionalLight.h"
#include "lights/PointLight.h"
#include "lights/SpotLight.h"
#include "cube.h"
#include "walls.h"



class MyScene : public Scene
{
public:
	MyScene(GLFWwindow* window, InputHandler* H);
	~MyScene() {};
	void update(float dt) override;
	glm::vec3 rand(glm::vec3 lower, glm::vec3 upper);
	int getPointi(int i);

private:
		
	Shader* m_myShader;
	DirectionalLight* m_directionalLight;
	Cube* m_cube;
	PointLight* m_pointLight;
	SpotLight* m_spotLight;
	Plane* m_walls;

	void render();
};

