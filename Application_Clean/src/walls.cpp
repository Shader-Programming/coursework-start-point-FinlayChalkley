#include "walls.h"

Plane::Plane(glm::vec3 col, float shine, float specStrength) : 
	m_colour(col), 
	m_shine(shine), 
	m_specularStrength(specStrength)
{
	makeVAO();
	resetTransform();
}

void Plane::setPlaneMaterialValues(Shader* shader)
{
	shader->use();
	shader->setVec3("cubeColour", m_colour);
	shader->setFloat("shine", m_shine);
	shader->setFloat("specStrength", m_specularStrength);
}

void Plane::makeVAO()
{
	unsigned int VBO, EBO;
	glCreateBuffers(1, &VBO);
	glNamedBufferStorage(VBO, sizeof(float) * vertexData.size(), vertexData.data(), GL_DYNAMIC_STORAGE_BIT);// size of float array

	glCreateBuffers(1, &EBO); // create element buffer
	glNamedBufferStorage(EBO, sizeof(unsigned int) * floorIndices.size(), floorIndices.data(), GL_DYNAMIC_STORAGE_BIT);


	glCreateVertexArrays(1, &m_VAO2);
	glVertexArrayVertexBuffer(m_VAO2, 0, VBO, 0, sizeof(float) * 6); // size of stride information
	glVertexArrayElementBuffer(m_VAO2, EBO); // add EBO to VAO

	glEnableVertexArrayAttrib(m_VAO2, 0);
	glEnableVertexArrayAttrib(m_VAO2, 1);


	glVertexArrayAttribFormat(m_VAO2, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribFormat(m_VAO2, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));

	glVertexArrayAttribBinding(m_VAO2, 0, 0);
	glVertexArrayAttribBinding(m_VAO2, 1, 0);
}
