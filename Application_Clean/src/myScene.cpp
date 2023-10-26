#include "myScene.h"

MyScene::MyScene(GLFWwindow* window, InputHandler* H) : Scene(window, H) 
{
	m_camera = new FirstPersonCamera();
	m_camera->attachHandler(m_window, m_handler);
	m_myShader = new Shader("..\\Shaders\\vertexShader.glsl", "..\\shaders\\fragShader.glsl");
	makeVAO();
}

void MyScene::update(float dt)
{
	m_camera->update(dt);
	render();
}

void MyScene::makeVAO()
{
	glCreateBuffers(1, &VBO);
	glNamedBufferStorage(VBO, sizeof(float) * vertexData.size(), vertexData.data(), GL_DYNAMIC_STORAGE_BIT);// size of float array
	
	glCreateBuffers(1, &EBO); // create element buffer
	glNamedBufferStorage(EBO, sizeof(unsigned int) * cubeIndices.size(), cubeIndices.data(), GL_DYNAMIC_STORAGE_BIT);


	glCreateVertexArrays(1, &VAO);
	glVertexArrayVertexBuffer(VAO, 0, VBO, 0, sizeof(float) * 3); // size of stride information
	glVertexArrayElementBuffer(VAO, EBO); // add EBO to VAO

	glEnableVertexArrayAttrib(VAO, 0);
	//glEnableVertexArrayAttrib(VAO, 1);
	

	glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0); 
	//glVertexArrayAttribFormat(VAO, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));

	glVertexArrayAttribBinding(VAO, 0, 0);
	//glVertexArrayAttribBinding(VAO, 1, 0);

}

void MyScene::render()
{
	m_model = glm::mat4(1.0f);
	//update view and projection matrices
	m_prjection = m_camera->getProjectionMatrix();
	m_view = m_camera->getViewMatrix();
	
	m_myShader->use();
	//set uniforms
	m_myShader->setMat4("View", m_view);
	m_myShader->setMat4("Projection", m_prjection);
	m_myShader->setMat4("Model", m_model);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, cubeIndices.size(), GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, 6);

	// moving the cube
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
	m_myShader->setMat4("Model", m_model);
	glDrawElements(GL_TRIANGLES, cubeIndices.size(), GL_UNSIGNED_INT, 0);
	
	//draw another cube
	//update the model matrix
	m_model = glm::translate(m_model, glm::vec3(5.0, 0.0, 0.0));
	//rotate
	m_model = glm::rotate(m_model, (float)(glfwGetTime() * 0.5), glm::vec3(1.0, 0.0, 0.0));
	// pass updated uniform to shader
	m_myShader->setMat4("Model", m_model);
	// another draw call
	glDrawElements(GL_TRIANGLES, cubeIndices.size(), GL_UNSIGNED_INT, 0);
	
}
