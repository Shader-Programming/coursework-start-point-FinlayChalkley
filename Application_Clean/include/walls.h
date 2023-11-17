#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "glm/common.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Shader.h"

class Plane {

public:
	Plane(unsigned int diffuseMap, float shine, unsigned int specularMap, unsigned int normalMap);
	~Plane() {};
	void setPlaneMaterialValues(Shader* shader);
	void setTransform(Shader* shader) { shader->setMat4("Model", m_transform); }
	void resetTransform() { m_transform = glm::mat4(1.0); }

	unsigned int getVAO() { return m_VAO2; }
	glm::mat4& getModelMatrix() { return m_transform; }
	unsigned int getIndicesCount() { return floorIndices.size(); }

private:
	const float floorLevel = -2.0f;
	const float floorSize = 7.0f;
	void makeVAO();

	unsigned int m_VAO2;
	glm::mat4 m_transform;
	float m_shine;
	unsigned int m_diffuseTexture;
	unsigned int m_specularTexture;
	unsigned int m_normalTexture;
	glm::vec3 m_colour;

	std::vector<float> vertexData = {
		-floorSize, floorLevel,  -floorSize,     0.0, 1.0, 0.0, 0.0,0.0,1.0f, 0.0f, 0.0f,
		floorSize, floorLevel,  -floorSize,     0.0, 1.0, 0.0, 1.0,0.0,1.0f, 0.0f, 0.0f,
		floorSize, floorLevel,   floorSize,     0.0, 1.0, 0.0, 1.0,1.0,1.0f, 0.0f, 0.0f,
		-floorSize, floorLevel,   floorSize,     0.0, 1.0, 0.0, 0.0,1.0,1.0f, 0.0f, 0.0f };
	std::vector<unsigned int> floorIndices = {
		3,2,1,
		3,1,0
	};
};