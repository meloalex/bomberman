#include "HUD.h"

HUD::HUD()
{
	heart = myType::Rect(SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE * 2, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);
}

HUD::~HUD()
{
}

void HUD::Update(int _scorePlayerOne, int _scorePlayerTwo, int _livesPlayerOne, int _livesPlayerTwo, float _time) 
{
	// Scores
	std::string playerOneScore = "PL1: " + std::to_string(_scorePlayerOne);
	std::string playerTwoScore = "PL2: " + std::to_string(_scorePlayerTwo);

	Renderer::Instance()->LoadTextureText("gameOver", myType::Text(playerOneScore, myType::Color(0, 0, 0, 255), "playerOneScore"));
	Renderer::Instance()->LoadTextureText("gameOver", myType::Text(playerTwoScore, myType::Color(0, 0, 0, 255), "playerTwoScore"));

	myType::Vector2 scorePlayerOneTextSize = Renderer::Instance()->GetTextureSize("playerOneScore");
	myType::Vector2 scorePlayerTwoTextSize = Renderer::Instance()->GetTextureSize("playerTwoScore");

	playerOneScoreTextPosition = myType::Rect(PLAYER_SCORE_TEXT_POSITION_X, HUD_HEIGHT / 2 - scorePlayerOneTextSize.y /2, scorePlayerOneTextSize);
	playerTwoScoreTextPosition = myType::Rect(SCREEN_WIDTH - PLAYER_SCORE_TEXT_POSITION_X * 6, HUD_HEIGHT / 2 - scorePlayerTwoTextSize.y / 2, scorePlayerTwoTextSize);
	
	// Lives
	if (_livesPlayerOne != playerOneLives.size())
	{
		playerOneLives.clear();

		for (int i = 0; i < _livesPlayerOne; i++)
			playerOneLives.push_back(myType::Rect(PLAYER_LIVES_POSITION_X + (heart.w * i), HUD_HEIGHT / 2 - heart.h / 2, 50, 50));
	}

	if (_livesPlayerTwo != playerTwoLives.size())
	{
		playerTwoLives.clear();

		for (int i = 0; i < _livesPlayerTwo; i++)
			playerTwoLives.push_back(myType::Rect(SCREEN_WIDTH - PLAYER_SCORE_TEXT_POSITION_X * 8 - (heart.w * i), HUD_HEIGHT / 2 - heart.h / 2, 50, 50));
	}

	// Time
	int minutes, seconds;
	ConvertTime(static_cast<int>(_time), minutes, seconds);
	std::string timeFormated = std::to_string(minutes) + ":" + std::to_string(seconds);

	Renderer::Instance()->LoadTextureText("gameOver", myType::Text(timeFormated, myType::Color(0, 0, 0, 255), "time"));
	myType::Vector2 timeTextSize = Renderer::Instance()->GetTextureSize("time");
	timeRect = myType::Rect(HUD_WIDTH/2 - timeTextSize.x/2, HUD_HEIGHT/2 - timeTextSize.y/2, timeTextSize);
}

void HUD::Draw()
{
	// Scores
	Renderer::Instance()->PushImage("playerOneScore", playerOneScoreTextPosition);
	Renderer::Instance()->PushImage("playerTwoScore", playerTwoScoreTextPosition);

	// Player One Lives
	for (int i = 0; i < playerOneLives.size(); i++)
		Renderer::Instance()->PushSprite("playerOne", heart, playerOneLives[i]);

	// Player Two Lives
	for (int i = 0; i < playerTwoLives.size(); i++)
		Renderer::Instance()->PushSprite("playerTwo", heart, playerTwoLives[i]);

	// Time
	Renderer::Instance()->PushImage("time", timeRect);
}

void HUD::ConvertTime(int time, int& minutes, int& seconds)
{
	minutes = (time % 3600) / 60;
	seconds = time % 60;
}