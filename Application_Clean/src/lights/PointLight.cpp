#include "lights/PointLight.h"

PointLight::PointLight(glm::vec3 colour, glm::vec3 position, glm::vec3 constants):
	light(colour),
	m_position(position),
	m_constants(constants)
{}

void PointLight::setLightUniforms(Shader* shader)
{
	shader->use();
	shader->setVec3("PointLight[0].pattenuation", m_constants);
	shader->setVec3("PointLight[0].plightPosition", m_position);
	shader->setVec3("PointLight[0].plightcolour", m_colour);
}
