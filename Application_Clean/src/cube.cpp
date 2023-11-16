#include "cube.h"


Cube::Cube(glm::vec3 col, float shine, float specStrength) : m_colour(col), m_shine(shine), m_specularStrength(specStrength) {
	makeVAO();
	resetTransform();
}

Cube::~Cube() {

}

void Cube::setCubeMaterialValues(Shader* shader) {
	shader->use();
	shader->setVec3("cubeColour", m_colour);
	shader->setFloat("shine", m_shine);
	shader->setFloat("specStrength", m_specularStrength);
}

void Cube::rotate(float angle, glm::vec3 axis)
{
	m_transform = glm::rotate(m_transform, angle, axis);
}

void Cube::scale(float scaleFactor, glm::vec3 axis)
{
	m_transform = glm::scale(m_transform, axis);
}

void Cube::translate(glm::vec3 translation)
{
	m_transform = glm::translate(m_transform, translation);
}

void Cube::makeVAO()
{
	unsigned int VBO, EBO;
	glCreateBuffers(1, &VBO);
	glNamedBufferStorage(VBO, sizeof(float) * vertexData.size(), vertexData.data(), GL_DYNAMIC_STORAGE_BIT);// size of float array

	glCreateBuffers(1, &EBO); // create element buffer
	glNamedBufferStorage(EBO, sizeof(unsigned int) * cubeIndices.size(), cubeIndices.data(), GL_DYNAMIC_STORAGE_BIT);


	glCreateVertexArrays(1, &m_VAO);
	glVertexArrayVertexBuffer(m_VAO, 0, VBO, 0, sizeof(float) * 6); // size of stride information
	glVertexArrayElementBuffer(m_VAO, EBO); // add EBO to VAO

	glEnableVertexArrayAttrib(m_VAO, 0);
	glEnableVertexArrayAttrib(m_VAO, 1);


	glVertexArrayAttribFormat(m_VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribFormat(m_VAO, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));

	glVertexArrayAttribBinding(m_VAO, 0, 0);
	glVertexArrayAttribBinding(m_VAO, 1, 0);
}

