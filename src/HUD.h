#pragma once
#include "Renderer.h"
#include <vector>

#define PLAYER_SCORE_TEXT_POSITION_X 25
#define PLAYER_SCORE_TEXT_POSITION_Y 5
#define PLAYER_LIVES_POSITION_X 150
#define PLAYER_LIVES_POSITION_Y 15

class HUD
{
private:
	myType::Rect playerOneScoreTextPosition, playerTwoScoreTextPosition, timeRect;
	myType::Rect heart;
	std::vector<myType::Rect> playerOneLives, playerTwoLives;

	void ConvertTime(int time, int &minutes, int &seconds);
public:
	HUD();
	~HUD();

	void Update(int _scorePlayerOne, int _scorePlayerTwo, int _livesPlayerOne, int _livesPlayerTwo, float _time);
	void Draw();
};

