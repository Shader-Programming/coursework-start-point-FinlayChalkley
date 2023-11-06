#include "SpotLight.h"

SpotLight::SpotLight(glm::vec3 colour, glm::vec3 position, glm::vec3 constants, glm::vec3 dir, glm::vec2 radii):
	light(colour),
	m_position(position),
	m_constants(constants),
	m_direction(dir),
	m_radii(radii)
{}

void SpotLight::setLightUniforms(Shader* shader)
{
	shader->use();
	shader->setVec3("PointLight[0].sattenuation", m_constants);
	shader->setVec3("PointLight[0].slightPosition", m_position);
	shader->setVec3("PointLight[0].slightcolour", m_colour);
	shader->setVec3("PointLight[0].sDirection", m_direction);
	shader->setVec2("PointLight[0].sRadii", m_radii);
}
