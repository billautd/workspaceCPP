#pragma once
#include "Component.h"
#include "SDL.h"
#include <string>

class TextLabelComponent : public Component
{
private:
	SDL_Rect position{};
	const std::string text{ "" };
	const std::string fontFamily{ "" };
	const SDL_Color color{};
	SDL_Texture* texture{ nullptr };
public:
	TextLabelComponent(const unsigned int x, const unsigned int y, const std::string text, const std::string fontFamily, const SDL_Color color);

	void Init() override;
	void Render() const override;
};
