#pragma once
#include <glm/glm.hpp>


class light {

public:
	light(glm::vec3 colour) : m_colour(colour) {}
	~light() {};
protected:
	glm::vec3& getColour() { return m_colour; }
	void setColour(glm::vec3 col) { m_colour = col; }

	glm::vec3 m_colour;
};