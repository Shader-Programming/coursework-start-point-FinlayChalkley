#pragma once
#include "lights/light.h"
#include "Shader.h"

class PointLight : public light {

public:
	PointLight(glm::vec3 colour, glm::vec3 position, glm::vec3 constants);
	~PointLight() {};
	void setLightUniforms(Shader* shader, int i);

	// setters
	void setPosition(glm::vec3& pos) { m_position = pos; }
	void setConstants(glm::vec3& constants) { m_constants = constants; }
	//getters
	glm::vec3& getPosition() { return m_position; }
	glm::vec3& getConstants() { return m_constants; }

private:
	glm::vec3 m_position;
	glm::vec3 m_constants;
};
