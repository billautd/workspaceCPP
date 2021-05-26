#include "TextLabelComponent.h"
#include "SDL_ttf.h"
#include "Game.h"

TextLabelComponent::TextLabelComponent(const unsigned int x, const unsigned int y,
	const std::string text, const std::string fontFamily, const SDL_Color color) :
	text(text), fontFamily(fontFamily), color(color) {
	position.x = x;
	position.y = y;
}

void TextLabelComponent::Init() {
	SDL_Surface* surface = TTF_RenderText_Blended(Game::assetManager.GetFont(fontFamily), text.c_str(), color);
	texture = SDL_CreateTextureFromSurface(Game::renderer.get(), surface);
	SDL_FreeSurface(surface);
	SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
}

void TextLabelComponent::Render() const {
	Game::assetManager.DrawFont(texture, &position);
}


