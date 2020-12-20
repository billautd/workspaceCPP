#include "FirePatternComponent.h"

void FirePatternComponent::Update(GLfloat dt) {
	Component::Update(dt);
	FirePattern(this, dt);
}