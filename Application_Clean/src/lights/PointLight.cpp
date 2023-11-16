#include "lights/PointLight.h"

PointLight::PointLight(glm::vec3 colour, glm::vec3 position, glm::vec3 constants):
	light(colour),
	m_position(position),
	m_constants(constants)
{}

void PointLight::setLightUniforms(Shader* shader, int i)
{
	shader->use();
	shader->setVec3("pointArray[i].constants", m_constants);
	shader->setVec3("pointArray[i].position", m_position);
	shader->setVec3("pointArray[i].colour", m_colour);
}
