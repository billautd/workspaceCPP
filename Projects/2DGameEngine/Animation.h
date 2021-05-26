#pragma once
class Animation {
private:
	const unsigned int index{ 0 };
	const unsigned int numFrames{ 0 };
	const unsigned int animationSpeed{ 0 };
public:
	Animation(const unsigned int index, const unsigned int numFrames, const unsigned int animationSpeed) : index(index), numFrames(numFrames), animationSpeed(animationSpeed) {}
	const unsigned int GetNumFrames() const { return numFrames; }
	const unsigned int GetIndex() const { return index; }
	const unsigned int GetAnimationSpeed() const { return animationSpeed; }
};