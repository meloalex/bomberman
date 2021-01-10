#pragma once
#include "Renderer.h"
#include "Types.h"


class Button
{
private:
	std::string id;
	std::string texture;
	std::string hoverTexture;
	myType::Rect rect;
	std::string textFont;
	myType::Color c_normal, c_hovered;
	bool isHover, isCentered;
	myType::Vector2 position;

public:
	Button();
	~Button();
	Button(std::string id, std::string text, myType::Vector2 pos, myType::Color normal, myType::Color hovered, std::string font);
	Button(std::string id, std::string text, myType::Vector2 pos, myType::Color normal, myType::Color hovered, std::string font, bool center);

	void Update(myType::Vector2 mousePosition);
	bool isPressed(myType::Vector2 mousePosition, bool p);
	void Draw();
	void UpdateText(std::string newText);
};

