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
	for (int i = 0; i <= 50; i++) {
		mt19937 mt(time(nullptr));
		m_pointLight = new PointLight(glm::vec3(mt(), mt(), mt()), glm::vec3(mt(), mt(), mt()), glm::vec3(mt(), mt(), mt()));
		m_pointLight->setLightUniforms(m_myShader);
	}
	//m_spotLight = new SpotLight(glm::vec3(0.5,1.0,0.0), glm::vec3(0.0,7.0,0.0), glm::vec3(1.0, 0.027,0.0028), glm::vec3(0.0,-1.0,0.0), glm::vec2(glm::cos(glm::radians(12.5))))
	
	m_cube = new Cube(glm::vec3(0.1, 0.2, 0.3), 64, 16);
	m_cube->setCubeMaterialValues(m_myShader);

}

void MyScene::update(float dt)
{
	m_camera->update(dt);
	render();
}
/*
void MyScene::makeVAO()
{
	glCreateBuffers(1, &VBO);
	glNamedBufferStorage(VBO, sizeof(float) * vertexData.size(), vertexData.data(), GL_DYNAMIC_STORAGE_BIT);// size of float array
	
	glCreateBuffers(1, &EBO); // create element buffer
	glNamedBufferStorage(EBO, sizeof(unsigned int) * cubeIndices.size(), cubeIndices.data(), GL_DYNAMIC_STORAGE_BIT);


	glCreateVertexArrays(1, &VAO);
	glVertexArrayVertexBuffer(VAO, 0, VBO, 0, sizeof(float) * 6); // size of stride information
	glVertexArrayElementBuffer(VAO, EBO); // add EBO to VAO

	glEnableVertexArrayAttrib(VAO, 0);
	glEnableVertexArrayAttrib(VAO, 1);
	

	glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0); 
	glVertexArrayAttribFormat(VAO, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));

	glVertexArrayAttribBinding(VAO, 0, 0);
	glVertexArrayAttribBinding(VAO, 1, 0);

}
*/


void MyScene::render()
{

	m_myShader->use();
	//set uniforms
	m_myShader->setMat4("View", m_camera->getViewMatrix());
	m_myShader->setMat4("Projection", m_camera->getProjectionMatrix());
	m_myShader->setVec3("viewPos", m_camera->getPosition());

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
	glBindVertexArray(m_cube->getVAO());
	m_cube->setTransform(m_myShader);
	glDrawElements(GL_TRIANGLES, m_cube->getIndecesCount(), GL_UNSIGNED_INT, 0);
}
