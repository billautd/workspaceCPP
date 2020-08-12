#pragma once
class Animation {
private:
	unsigned int index{ 0 };
	unsigned int numFrames{ 0 };
	unsigned int animationSpeed{ 0 };
public:
	Animation() = default;
	~Animation() = default;
	Animation(unsigned int index, unsigned int numFrames, unsigned int animationSpeed);
	unsigned int GetIndex() const { return index; }
	unsigned int GetNumFrames() const { return numFrames; }
	unsigned int GetAnimationSpeed() const { return animationSpeed; }
};