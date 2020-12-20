#pragma once
#include "Component.h"
#include <functional>

class FirePatternComponent : public Component {
public:
	FirePatternComponent() = default;
	FirePatternComponent(std::function<void(FirePatternComponent*, GLfloat)> pattern) : FirePattern(pattern) {};

	void SetFirePattern(std::function<void(FirePatternComponent*, GLfloat)> pattern) {
		FirePattern = pattern;
	}

	void Update(GLfloat dt) override;
private:
	void defaultFirePattern(GLfloat dt) {};
	std::function<void(FirePatternComponent*, GLfloat)> FirePattern = &FirePatternComponent::defaultFirePattern;
};