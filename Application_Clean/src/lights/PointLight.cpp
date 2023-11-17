#include "lights/PointLight.h"

PointLight::PointLight(glm::vec3 colour, glm::vec3 position, glm::vec3 constants):
	light(colour),
	m_position(position),
	m_constants(constants)
{}

void PointLight::setLightUniforms(Shader* shader, int i)
{
	shader->use();
	shader->setVec3("pointArray[0].constants", m_constants);
	shader->setVec3("pointArray[0].position", m_position);
	shader->setVec3("pointArray[0].colour", m_colour);
}
