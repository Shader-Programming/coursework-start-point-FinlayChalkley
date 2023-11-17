#pragma once
#include "Scene.h"
#include "Shader.h"
#include "lights/DirectionalLight.h"
#include "lights/PointLight.h"
#include "lights/SpotLight.h"
#include "cube.h"
#include "walls.h"
#include "textures/TextureManager.h"
#include <vector>
using namespace std;


class MyScene : public Scene
{
public:
	MyScene(GLFWwindow* window, InputHandler* H);
	~MyScene() {};
	void update(float dt) override;
	glm::vec3 rand(glm::vec3 lower, glm::vec3 upper);

private:
		
	Shader* m_myShader;
	DirectionalLight* m_directionalLight;
	Cube* m_cube;
	SpotLight* m_spotLight;
	Plane* m_walls;
	PointLight* m_pointLight;
	TextureManager* m_texture;
	void render();
};

