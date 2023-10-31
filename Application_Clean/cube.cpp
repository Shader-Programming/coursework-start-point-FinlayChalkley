#include "cube.h"


Cube::Cube(glm::vec3 col, float shine, float specStrength) : m_colour(col), m_shine(shine), m_specularStrength(specStrength) {
	makeVAO();
	resetTransform();
}

Cube::~Cube() {

}

void Cube::setCubeMaterialValues(Shader* shader) {
	shader->use();
	shader->setVec3("cubeColour", m_colour);
	shader->setFloat("shine", m_shine);
	shader->setFloat("specStrength", m_specularStrength);
}