#include "myScene.h"
#include <ctime> 
#include <iostream> 
#include <random> 
using namespace std;


MyScene::MyScene(GLFWwindow* window, InputHandler* H) : Scene(window, H) 
{
	m_camera = new FirstPersonCamera();
	m_camera->attachHandler(m_window, m_handler);
	m_myShader = new Shader("..\\Shaders\\vertexShader.glsl", "..\\shaders\\fragShader.glsl");
	m_directionalLight = new DirectionalLight(glm::vec3(1.0), glm::vec3(-1.0f, -1.0f, 0.0f));
	m_directionalLight->setLightUniforms(m_myShader);
	
	for (int i = 0; i < 50; i++) {
		m_pointLight = new PointLight(rand(glm::vec3(-5.0, -5.0, -5.0), glm::vec3(5.0,5.0,5.0)), rand(glm::vec3(-5.0, -5.0, -5.0), glm::vec3(5.0,5.0,5.0)), rand(glm::vec3(-5.0, -5.0, - 5.0), glm::vec3(5.0,5.0,5.0)));
		m_pointLight->setLightUniforms(m_myShader, i);
	}
	

	m_spotLight = new SpotLight(glm::vec3(0.5, 1.0, 1.0), glm::vec3(0.0, 7.0, 0.0), glm::vec3(1.0, 0.027, 0.0028), glm::vec3(0.0, -1.0, 0.0), glm::vec2((glm::cos(glm::radians(12.5f))), glm::cos(glm::radians(17.5f))));
	m_spotLight->setLightUniforms(m_myShader);

	m_cube = new Cube(cubeDiff, 64, cubeSpec, cubenorm);
	m_cube->setCubeMaterialValues(m_myShader);
	
	m_walls = new Plane(floorDiff, 64, floorSpec, floornorm);
	m_walls->setPlaneMaterialValues(m_myShader);
	
	
	


}


void MyScene::update(float dt)
{
	m_camera->update(dt);
	render();
}
glm::vec3 MyScene::rand(glm::vec3 lower, glm::vec3 upper)
{
	std::random_device rd;
	std::mt19937 mt(rd());


	std::uniform_real_distribution<float>distribx(lower.x, upper.x);
	std::uniform_real_distribution<float>distriby(lower.y, upper.y);
	std::uniform_real_distribution<float>distribz(lower.z, upper.z);
	glm::vec3 randVec = glm::vec3(distribx(mt), distriby(mt), distribz(mt));
	return randVec;
}



void MyScene::render()
{

	m_myShader->use();
	//set uniforms
	m_myShader->setMat4("View", m_camera->getViewMatrix());
	m_myShader->setMat4("Projection", m_camera->getProjectionMatrix());
	m_myShader->setVec3("viewPos", m_camera->getPosition());

	
	glBindVertexArray(m_walls->getVAO());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, floorDiff);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, floorSpec);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, floornorm);
	m_walls->setTransform(m_myShader);
	glDrawElements(GL_TRIANGLES, m_walls->getIndicesCount(), GL_UNSIGNED_INT, 0);
	
	
	glBindVertexArray(m_cube->getVAO());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,cubeDiff);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, cubeSpec);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, cubenorm);
	m_cube->setTransform(m_myShader);
	glDrawElements(GL_TRIANGLES, m_cube->getIndecesCount(), GL_UNSIGNED_INT, 0);
	//second cube
	m_cube->translate(glm::vec3(5.0, 0.0, 0.0));
	m_cube->rotate((float)(glfwGetTime() * 0.5), glm::vec3(1.0, 0.0, 0.0));
	m_cube->setTransform(m_myShader);
	glDrawElements(GL_TRIANGLES, m_cube->getIndecesCount(), GL_UNSIGNED_INT, 0);
	m_cube->resetTransform();
	
	// moving the cube
	/*
	if (m_handler->keyHasBeenPressed()) {
		if (m_handler->isKeyPressed(GLFW_KEY_W)) {
			m_model = glm::translate(m_model, glm::vec3(0.0, 2.0, 0.0));
		}
		if (m_handler->isKeyPressed(GLFW_KEY_S)) {
			m_model = glm::translate(m_model, glm::vec3(0.0, -2.0, 0.0));
		}
		if (m_handler->isKeyPressed(GLFW_KEY_A)) {
			m_model = glm::translate(m_model, glm::vec3(-2.0, 0.0, 0.0));
		}
		if (m_handler->isKeyPressed(GLFW_KEY_D)) {
			m_model = glm::translate(m_model, glm::vec3(2.0, 0.0, 0.0));
		}
		if (m_handler->isKeyPressed(GLFW_KEY_X)) {
			m_model = glm::rotate(m_model, (float)(glfwGetTime() * 0.5), glm::vec3(1.0, 0.0, 0.0));
		}
	}
	*/
	
	
}
