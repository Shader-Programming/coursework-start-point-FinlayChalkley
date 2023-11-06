#pragma once
#include "lights/light.h"
#include "Shader.h"

class SpotLight : public light {

public:
	SpotLight(glm::vec3 colour, glm::vec3 position, glm::vec3 constants, glm::vec3 dir, glm::vec2 radii);
	~SpotLight() {};
	void setLightUniforms(Shader* shader);

	// setters
	void setPosition(glm::vec3& pos) { m_position = pos; }
	void setConstants(glm::vec3& constants) { m_constants = constants; }
	void setDirection(glm::vec3& dir) { m_direction = dir; }
	void setRadii(glm::vec2& r) { m_radii = r; }
	//getters
	glm::vec3& getPosition() { return m_position; }
	glm::vec3& getConstants() { return m_constants; }
	glm::vec3& getDirection() { return m_direction; }
	glm::vec2& getRadii() { return m_radii; }

private:
	glm::vec3 m_position;
	glm::vec3 m_constants;
	glm::vec3 m_direction;
	glm::vec2 m_radii;
};