#pragma once
#include "Container.h"
#include "GameCrtlIC.h"
#include "ScoreViewerGC.h"
#include "LivesViewerGC.h"
#include "GameStatusViewGC.h"
#include "FighterAsteroidCollision.h"
#include "BulletsAsteroidsCollision.h"
#include "AsteroidBlackHoleCollision.h"
#include "FighterBlackHoleCollision.h"
#include "BulletBlackHoleCollision.h"
#include "BulletsP2PlayerCollision.h"
#include "BulletPlayer2Collision.h"


class GameManager:public Container
{
public:

	GameManager(SDLGame* game);
	virtual ~GameManager();
	
	bool getRun() { return running_; }
	bool getOver() { return gameOver_; }
	bool getNextRound() { return nextRound_; }
	bool getGameWin() { return gameWin_; }
	int getScore() { return score_; }
	int getLives() { return lives_; }
	int getWinner() { return winner_; }
	virtual void receive(const void* senderObj, const msg::Message& msg);


	int getVictoryCount();

private:
	
	static int const maxLives_ = 3;
	bool running_;
	bool gameOver_;
	bool nextRound_;
	bool gameWin_;
	int score_;
	int lives_;
	int winner_; //0 = none, 2 = player2, 1 = player; 
	int roundsP1 = 0;
	int roundsP2 = 0;

	int victoryCount_;

	//components of gamemanager

	GameCrtlIC gameCrtl_;
	ScoreViewerGC scoreView_;
	GameStatusViewGC gameStatusView_;
	LivesViewerGC livesView_;
	FighterAsteroidCollision fighterAsteroidCollision_;
	BulletsAsteroidsCollision bulletsAsteroidsCollision_;
	FighterBlackHoleCollision fighterBlackHoleCollision_;
	AsteroidBlackHoleCollision asteroidBlackHoleCollision_;
	BulletBlackHoleCollision bullestBlackHoleCollision_;
	BulletPlayer2Collision bulletPlayer2Collision_;
	BulletsP2PlayerCollision bulletP2PlayerCollision_;
};

