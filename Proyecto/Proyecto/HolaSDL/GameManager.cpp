#include "GameManager.h"
#include "Messages_defs.h"
#include "Logger.h"


GameManager::GameManager(SDLGame* game) :Container(game),
	livesView_(this),
	scoreView_(this),
	gameStatusView_(this),
	bulletsAsteroidsCollision_(this),
	//part 4: GM Functionality
	fighterAsteroidCollision_(this),
	bullestBlackHoleCollision_(this),
	fighterBlackHoleCollision_(this),
	asteroidBlackHoleCollision_(this),
	bulletP2PlayerCollision_(this),
	bulletPlayer2Collision_(this),
	gameCrtl_(this)
{
	running_ = false;
	gameOver_ = true;
	nextRound_ = false;
	gameWin_ = false;
	score_ = 0;
	lives_ = maxLives_;
	winner_ = 0;

	addC(&livesView_);
	addC(&scoreView_);
	addC(&gameStatusView_);
	addC(&bulletsAsteroidsCollision_);
	//part 4: GM Functionality
	addC(&gameCrtl_);
	addC(&fighterAsteroidCollision_);
	addC(&bullestBlackHoleCollision_);
	addC(&fighterBlackHoleCollision_);
	addC(&asteroidBlackHoleCollision_);
	addC(&bulletP2PlayerCollision_);
	addC(&bulletPlayer2Collision_);
}


GameManager::~GameManager()
{
}

void GameManager::receive(const void* senderObj, const msg::Message& msg)
{
	Container::receive(senderObj, msg);
	switch (msg.type_) {
	case msg::GAME_START:
		gameOver_ = false;
		nextRound_ = false;
		gameWin_ = false;
		victoryCount_ = 0;
		winner_ = 0;
		lives_ = maxLives_;
		roundsP1 = 0;
		roundsP2 = 0;

		Logger::getInstance()->log("New Game"); //write info in ofstream log_
		break;
	case msg::ROUND_START:
		running_ = true;
		gameWin_ = false;
		//getGame()->getServiceLocator()->getAudios()->playMusic(Resources::ImperialMarch, -1);
		//getGame()->getServiceLocator()->getAudios()->resumeMusic();
		Logger::getInstance()->log("Round Start"); //write info in ofstream log_
		break;
	case msg::ASTEROID_DESTROYED:
	{
		int points = static_cast<const msg::AsteroidDestroyed&>(msg).points_;
		score_ += points;
		getGame()->getServiceLocator()->getAudios()->playChannel(Resources::Explosion, 0);
	}
		break;
	case msg::NO_LIFE_PLAYER:
		roundsP2++;
		running_ = false;
		gameOver_ = true;
		winner_ = 2;
		Logger::getInstance()->log("Round End - Player2 Win"); //write info in ofstream log_
		if (roundsP2 == 6) {
			gameWin_ = true;
			getGame()->getServiceLocator()->getAudios()->playChannel(Resources::Cheer, 0);
		}
		else { nextRound_ = true; }
		this->globalSend(this, msg::Message(msg::ROUND_OVER, this->getId(), msg::Broadcast));
		this->globalSend(this, msg::Message(msg::GAME_OVER, this->getId(), msg::Broadcast));

		break;
	case msg::NO_LIFE_PLAYER2:
		roundsP1++;
		running_ = false;
		gameOver_ = true;
		winner_ = 1;
		Logger::getInstance()->log("Round End - Player1 Win"); //write info in ofstream log_
		if (roundsP1 == 6) {
			gameWin_ = true;
			getGame()->getServiceLocator()->getAudios()->playChannel(Resources::Cheer, 0);
		}
		else { nextRound_ = true; }
		this->globalSend(this, msg::Message(msg::ROUND_OVER, this->getId(), msg::Broadcast));
		this->globalSend(this, msg::Message(msg::GAME_OVER, this->getId(), msg::Broadcast));

		break;

	case msg::NO_MORE_ASTEROIDS:
		running_ = false;
		gameOver_ = true;
		winner_ = 1;

		victoryCount_++;
		Logger::getInstance()->log("Round End - Fighter Win"); //write info in ofstream log_
		if (victoryCount_ == 3) {
			score_ = 0;
			gameWin_ = true;
			getGame()->getServiceLocator()->getAudios()->playChannel(Resources::Cheer, 0);
		}
		else{ nextRound_ = true; }
			
		this->globalSend(this,msg::Message(msg::ROUND_OVER,this->getId(),msg::Broadcast));
		this->globalSend(this,msg::Message(msg::GAME_OVER, this->getId(), msg::Broadcast));	
		break;
	case msg::FIGHTER_ASTEROID_COLLISION:
		running_ = false;
		getGame()->getServiceLocator()->getAudios()->playChannel(Resources::Explosion, 0);
		getGame()->getServiceLocator()->getAudios()->pauseMusic();

		this->globalSend(this, msg::Message(msg::ROUND_OVER, this->getId(), msg::Broadcast));
		lives_--;
		Logger::getInstance()->log("Round End.Fighter Die"); //write info in ofstream log_
		if (lives_ <= 0)
		{
			gameOver_ = true;
			winner_ = 2;
			this->globalSend(this, msg::Message(msg::GAME_OVER, this->getId(), msg::Broadcast));
		}
		break;
	case msg::FIGHTER_BLACKHOLE_COLLISION:
		running_ = false;
		getGame()->getServiceLocator()->getAudios()->playChannel(Resources::Explosion, 0);
		getGame()->getServiceLocator()->getAudios()->pauseMusic();
		this->globalSend(this, msg::Message(msg::ROUND_OVER, this->getId(), msg::Broadcast));
		lives_--;
		getGame()->getServiceLocator()->getAudios()->playChannel(Resources::Explosion, 0);
		Logger::getInstance()->log("Round End.Fighter Die"); //write info in ofstream log_
		if (lives_ <= 0)
		{
			gameOver_ = true;
			winner_ = 2;
			getGame()->getServiceLocator()->getAudios()->playChannel(Resources::Boooo, 0);
			this->globalSend(this, msg::Message(msg::GAME_OVER, this->getId(), msg::Broadcast));
		}
		break;
	}
}

int GameManager::getVictoryCount()
{
	return victoryCount_;
}
