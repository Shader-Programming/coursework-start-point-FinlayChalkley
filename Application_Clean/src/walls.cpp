#include "walls.h"

Plane::Plane(unsigned int diffuseMap, float shine, unsigned int specularMap) : 
	m_diffuseTexture(diffuseMap),
	m_shine(shine),
	m_specularTexture(specularMap)
{
	makeVAO();
	resetTransform();
}

void Plane::setPlaneMaterialValues(Shader* shader)
{
	shader->use();
	//shader->setVec3("cubeColour", m_colour);
	//shader->setFloat("specStrength", m_specularStrength);
	shader->setFloat("shine", m_shine);
	shader->setInt("diffuseMap", 2);
	shader->setInt("specularMap", 3);

	glBindTextureUnit(2, m_diffuseTexture);
	glBindTextureUnit(3, m_specularTexture);
}

void Plane::makeVAO()
{
	unsigned int VBO, EBO;
	glCreateBuffers(1, &VBO);
	glNamedBufferStorage(VBO, sizeof(float) * vertexData.size(), vertexData.data(), GL_DYNAMIC_STORAGE_BIT);// size of float array

	glCreateBuffers(1, &EBO); // create element buffer
	glNamedBufferStorage(EBO, sizeof(unsigned int) * floorIndices.size(), floorIndices.data(), GL_DYNAMIC_STORAGE_BIT);


	glCreateVertexArrays(1, &m_VAO2);
	glVertexArrayVertexBuffer(m_VAO2, 0, VBO, 0, sizeof(float) * 8); // size of stride information
	glVertexArrayElementBuffer(m_VAO2, EBO); // add EBO to VAO

	glEnableVertexArrayAttrib(m_VAO2, 0);
	glEnableVertexArrayAttrib(m_VAO2, 1);
	glEnableVertexArrayAttrib(m_VAO2, 2);


	glVertexArrayAttribFormat(m_VAO2, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribFormat(m_VAO2, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
	glVertexArrayAttribFormat(m_VAO2, 2, 2, GL_FLOAT, GL_FALSE, 0);

	glVertexArrayAttribBinding(m_VAO2, 0, 0);
	glVertexArrayAttribBinding(m_VAO2, 1, 0);
	glVertexArrayAttribBinding(m_VAO2, 2, 0);
}
