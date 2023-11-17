#include "cube.h"


Cube::Cube(unsigned int diffuseMap, float shine, unsigned int specularMap) :
	m_diffuseTexture(diffuseMap),
	m_specularTexture(specularMap),
	m_shine(shine)
{
	makeVAO();
	resetTransform();
}


Cube::~Cube() {

}

void Cube::setCubeMaterialValues(Shader* shader) {
	shader->use();
	//shader->setVec3("cubeColour", m_colour);
	//shader->setFloat("specStrength", m_specularStrength);
	shader->setFloat("shine", m_shine);
	shader->setInt("diffuseMap", 0);
	shader->setInt("specularMap", 1);

	glBindTextureUnit(0, m_diffuseTexture);
	glBindTextureUnit(1, m_specularTexture);
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
	glVertexArrayVertexBuffer(m_VAO, 0, VBO, 0, sizeof(float) * 8); // size of stride information
	glVertexArrayElementBuffer(m_VAO, EBO); // add EBO to VAO

	glEnableVertexArrayAttrib(m_VAO, 0);
	glEnableVertexArrayAttrib(m_VAO, 1);
	glEnableVertexArrayAttrib(m_VAO, 2);


	glVertexArrayAttribFormat(m_VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribFormat(m_VAO, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
	glVertexArrayAttribFormat(m_VAO, 2, 2, GL_FLOAT, GL_FALSE, 0);

	glVertexArrayAttribBinding(m_VAO, 0, 0);
	glVertexArrayAttribBinding(m_VAO, 1, 0);
	glVertexArrayAttribBinding(m_VAO, 2, 0);
}


