#pragma once

#include <vector>

#include "DemoContainer.h"
#include "SDLGame.h"
#include "GameObject.h"
#include "Player.h"
#include "Player2.h"
#include "Asteroids.h"
#include "Bullets.h"
#include "BulletsP2.h"
#include "BlackHoles.h"
#include "GameManager.h"


class AsteroidsGame: public SDLGame {

public:


	AsteroidsGame();
	virtual ~AsteroidsGame();

	// from SDLGame
	void start();
	void stop();

	Player* getFighter();

private:

	void initGame();
	void closeGame();
	void handleInput(Uint32 time);
	void update(Uint32 time);
	void render(Uint32 time);

	const static int _WINDOW_WIDTH_ = 800;
	const static int _WINDOW_HEIGHT_ = 600;
	bool exit_;
	std::vector<GameObject*> actors_;


	//DemoContainer demoContainer_;

	//Game Objects
	Player fighter_;

	Player2 player2_;

	Asteroids asteroids_;

	Bullets bullets_;

	BulletsP2 bulletsP2_;

	BlackHoles blackHoles_;

	GameManager gameMgr_; /*La clase GameManager es la responsable de empezar el juego, comprobar colisiones, decidir cuándo
acaba y mostrar mensaje sobre su estado:*/
};
