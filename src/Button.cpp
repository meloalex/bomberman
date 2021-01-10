#include "Button.h"

Button::Button()
{
	isCentered = false;
	isHover = false;
}


Button::~Button()
{

}

Button::Button(std::string id, std::string text, myType::Vector2 pos, myType::Color normal, myType::Color hovered, std::string font)
{
	// Load Text Textures
	Renderer::Instance()->LoadTextureText(font, myType::Text(text, normal, text + "_button"));
	Renderer::Instance()->LoadTextureText(font, myType::Text(text, hovered, text + "_button_hover"));

	texture = text + "_button";
	hoverTexture = text + "_button_hover";

	// Create Rectangle
	myType::Vector2 textureSize = Renderer::Instance()->GetTextureSize(text + "_button");
	rect = myType::Rect(position, textureSize);

	isHover = false;
	isCentered = false;

	this->id = id;

	// Create and push rect
	Renderer::Instance()->LoadRect(id, rect);
}

Button::Button(std::string id, std::string text, myType::Vector2 pos, myType::Color normal, myType::Color hovered, std::string font, bool center)
{
	// Save Data
	textFont = font;
	c_normal = normal;
	c_hovered = hovered;
	position = pos;

	// Load Text Textures
	Renderer::Instance()->LoadTextureText(font, myType::Text(text, normal, text + "_button"));
	Renderer::Instance()->LoadTextureText(font, myType::Text(text, hovered, text + "_button_hover"));

	texture = text + "_button";
	hoverTexture = text + "_button_hover";

	// Create Rectangle
	myType::Vector2 textureSize = Renderer::Instance()->GetTextureSize(text + "_button");
	if (isCentered) rect = myType::Rect(myType::Vector2(SCREEN_WIDTH / 2 - textureSize.x / 2, position.y), textureSize);
	else rect = myType::Rect(position, textureSize);

	isHover = false;
	isCentered = center;
	this->id = id;

	// Create and push rect
	Renderer::Instance()->LoadRect(id, rect);
}

void Button::Update(myType::Vector2 mousePosition)
{
	if (myType::VectorRectCollision(mousePosition, rect)) isHover = true;
	else isHover = false;
}

void Button::Draw()
{
	if (isHover) Renderer::Instance()->PushImage(hoverTexture, id);
	else Renderer::Instance()->PushImage(texture, id);
}

bool Button::isPressed(myType::Vector2 mousePosition, bool p) {
	return myType::VectorRectCollision(mousePosition, rect) && p;
}

void Button::UpdateText(std::string newText)
{
	// Load Text Textures
	texture = newText + "_button";
	hoverTexture = newText + "_button_hover";

	Renderer::Instance()->LoadTextureText(textFont, myType::Text(newText, c_normal, texture));
	Renderer::Instance()->LoadTextureText(textFont, myType::Text(newText, c_hovered, hoverTexture));

	// Create Rectangle
	myType::Vector2 textureSize = Renderer::Instance()->GetTextureSize(texture);
	if (isCentered) rect = myType::Rect(myType::Vector2(SCREEN_WIDTH / 2 - textureSize.x / 2, position.y), textureSize);
	else rect = myType::Rect(position, textureSize);

	isHover = false;
}