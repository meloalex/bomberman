#pragma once
#include <sdl/SDL.h>
#include <sdl/SDL_image.h>
#include <sdl/SDL_ttf.h>
#include <string.h>
#include <unordered_map>
#include "Types.h"

#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 704


class Renderer {

private:
	SDL_Renderer *m_renderer = nullptr;
	SDL_Window *m_window = nullptr;
	std::unordered_map<std::string, SDL_Texture*> m_textureData;
	std::unordered_map<std::string, TTF_Font*> m_fontData;
	std::unordered_map<std::string, SDL_Rect*> m_rects;

	static Renderer* renderer;
	Renderer();

public:
	 
	static Renderer* Instance();
	~Renderer();

	 void Clear();
	 void Render();

	 void LoadFont(const myType::Font &font);
	 void LoadTexture(const std::string &id, const std::string &path);
	 void LoadRect(const std::string &idRect, const myType::Rect &rect);
	 myType::Vector2 LoadTextureText(const std::string &fontId, myType::Text text);
	 myType::Vector2 GetTextureSize(const std::string &id);
	 void PushImage(const std::string &id, const std::string& idRect);
	 void PushSprite(const std::string &id,const std::string &idRectSprite,const std::string &idRectPos);
	 void PushRotatedSprite(const std::string &id, const std::string &idRectSprite, const std::string &idRectPos, float angle);
	 void SetRenderDrawColor(int r, int g, int b);
	 void SetRenderDrawColor(const myType::Color &c);
};


