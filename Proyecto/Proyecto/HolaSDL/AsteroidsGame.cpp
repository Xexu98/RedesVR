#include "AsteroidsGame.h"
#include "InputHandler.h"

#include "Logger.h"


using namespace std;


AsteroidsGame::AsteroidsGame() :
		SDLGame("Asteroids", _WINDOW_WIDTH_, _WINDOW_HEIGHT_),
		 fighter_(this),player2_(this),asteroids_(this), 
	bullets_(this), 
	bulletsP2_(this),
	gameMgr_(this),blackHoles_(this)
{
	initGame();
}

AsteroidsGame::~AsteroidsGame() {
	closeGame();
}

void AsteroidsGame::initGame() {

	//init singletton class Logger before GameManager.
	Logger::getInstance()->initInstance("log.txt"); //solo se inicializa una vez


	//actors_.push_back(&demoContainer_);
	actors_.push_back(&fighter_);
	actors_.push_back(&player2_);
	actors_.push_back(&asteroids_);
	actors_.push_back(&bullets_);
	actors_.push_back(&bulletsP2_);
	//actors_.push_back(&blackHoles_);
	actors_.push_back(&gameMgr_);
	addObserver(&fighter_);
	addObserver(&player2_);
	addObserver(&asteroids_);
	addObserver(&bullets_);
	addObserver(&bulletsP2_);
	//addObserver(&blackHoles_);
	addObserver(&gameMgr_);
	
}

void AsteroidsGame::closeGame() {
}

void AsteroidsGame::start() {
	exit_ = false;

	while (!exit_) {
		Uint32 startTime = SDL_GetTicks();
		handleInput(startTime);
		update(startTime);
		render(startTime);

		Uint32 frameTime = SDL_GetTicks() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}

void AsteroidsGame::stop() {
	exit_ = true;
}

void AsteroidsGame::handleInput(Uint32 time) {
	/*SDL_Event event;
	while (SDL_PollEvent(&event)) {*/
		if (InputHandler::getInstance()->isAnyKeyDown()) {
			if (InputHandler::getInstance()->isKeyDown(SDLK_ESCAPE)) {
				exit_ = true;
			}
			// Pressing f to toggle fullscreen.
			if (InputHandler::getInstance()->isKeyDown(SDLK_f)) {
				int flags = SDL_GetWindowFlags(window_);
				if (flags & SDL_WINDOW_FULLSCREEN) {
					SDL_SetWindowFullscreen(window_, 0);
				}
				else {
					SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
				}
			}
			}
		/*}*/
		InputHandler::getInstance()->update();
		for (GameObject* o : actors_) {
			o->handleInput(time);
		}
	//}
}

void AsteroidsGame::update(Uint32 time) {
	for (GameObject* o : actors_) {
		o->update(time);
	}
}

void AsteroidsGame::render(Uint32 time) {
	SDL_SetRenderDrawColor(getRenderer(), COLOR(0x00AAAAFF));
	SDL_RenderClear(getRenderer());

	for (GameObject* o : actors_) {
		o->render(time);
	}

	SDL_RenderPresent(getRenderer());
}

Player* AsteroidsGame::getFighter()
{
	return &fighter_;
}

