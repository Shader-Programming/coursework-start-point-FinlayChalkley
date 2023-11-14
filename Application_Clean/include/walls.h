#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "glm/common.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Shader.h"

class Plane {

public:
	Plane(glm::vec3 col, float shine, float specStrength);
	~Plane() {};
	void setPlaneMaterialValues(Shader* shader);
	void setTransform(Shader* shader) { shader->setMat4("Model", m_transform); }
	void resetTransform() { m_transform = glm::mat4(1.0); }

	unsigned int getVAO() { return m_VAO; }
	glm::mat4& getModelMatrix() { return m_transform; }
	unsigned int getIndicesCount() { return floorIndices.size(); }

private:
	const float floorLevel = -2.0f;
	const float floorSize = 7.0f;
	void makeVAO();

	unsigned int m_VAO;
	glm::mat4 m_transform;
	float m_shine;
	float m_specularStrength;
	glm::vec3 m_colour;

	std::vector<float> vertexData = {
		-floorSize, floorLevel,  -floorSize,     0.0, 1.0, 0.0,
		floorSize, floorLevel,  -floorSize,     0.0, 1.0, 0.0,
		floorSize, floorLevel,   floorSize,     0.0, 1.0, 0.0,
		-floorSize, floorLevel,   floorSize,     0.0, 1.0, 0.0, };
	std::vector<unsigned int> floorIndices = {
		3,2,1,
		3,1,0
	};
};