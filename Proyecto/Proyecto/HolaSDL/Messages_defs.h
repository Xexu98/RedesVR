#pragma once

#include <vector>
#include "Vector2D.h"
#include "GameObject.h"

// you can replace these lines by corresponding
// includes once the classes are defined

class Asteroid;
class Bullet;
class BlackHole;
class BulletP2;


namespace msg {

struct Message {
	Message(msg::MessageType type, msg::ObjectId sender, msg::ObjectId destination) :
			type_(type), sender_(sender), destination_(destination) {
	}

	msg::MessageType type_;
	msg::ObjectId sender_;
	msg::ObjectId destination_;
};

struct Shoot: public msg::Message {
	Shoot(msg::ObjectId sender, msg::ObjectId destination, Vector2D pos, Vector2D dir, int type) :
	Message(msg::PLAYER_SHOOT, sender, destination), pos_(pos), dir_(dir), type_(type) {
	}

	Vector2D pos_;
	Vector2D dir_;
	int type_;
};

struct ShootP2 : public msg::Message {
	ShootP2(msg::ObjectId sender, msg::ObjectId destination, Vector2D pos, Vector2D dir, int type) :
		Message(msg::PLAYER2_SHOOT, sender, destination), pos_(pos), dir_(dir), type_(type) {
	}

	Vector2D pos_;
	Vector2D dir_;
	int type_;
};


struct BulletAsteroidCollision: public msg::Message {
	BulletAsteroidCollision(msg::ObjectId sender, msg::ObjectId destination, Bullet* bullet, Asteroid* asteroid) :
	Message(msg::BULLET_ASTEROID_COLLISION, sender, destination), bullet_(bullet), asteroid_(asteroid)  {
	}

	Bullet* bullet_;
	Asteroid* asteroid_;
};
struct BulletBlackHoleCollision : public msg::Message {
	BulletBlackHoleCollision(msg::ObjectId sender, msg::ObjectId destination, Bullet* bullet, BlackHole* bh) :
		Message(msg::BULLET_BLACKHOLE_COLLISION, sender, destination), bullet_(bullet), blackhole_(bh) {
	}

	Bullet* bullet_;
	BlackHole* blackhole_;

};
struct BulletP2PlayerCollision : public msg::Message {
	BulletP2PlayerCollision(msg::ObjectId sender, msg::ObjectId destination, BulletP2* bullet, GameObject* player) :
		Message(msg::BULLETP2_PLAYER_COLLISION, sender, destination), bullet_(bullet), player_(player) {
	}

	BulletP2* bullet_;
	GameObject* player_;
};

struct BulletPlayer2Collision : public msg::Message {
	BulletPlayer2Collision(msg::ObjectId sender, msg::ObjectId destination, Bullet* bullet, GameObject* player2) :
		Message(msg::BULLET_PLAYER2_COLLISION, sender, destination), bullet_(bullet), player2_(player2) {
	}

	Bullet* bullet_;
	GameObject* player2_;
};

struct BlackHoleAsteroidCollision : public msg::Message {
	BlackHoleAsteroidCollision(msg::ObjectId sender, msg::ObjectId destination, BlackHole* bh, Asteroid* asteroid) :
		Message(msg::BLACKHOLE_ASTEROID_COLLISION, sender, destination), blackhole_(bh), asteroid_(asteroid) {
	}

	BlackHole* blackhole_;
	Asteroid* asteroid_;
};

struct FighterAsteroidCollisionMsg: public msg::Message {
	FighterAsteroidCollisionMsg(msg::ObjectId sender, msg::ObjectId destination, GameObject* fighter, Asteroid* asteroid) :
	Message(msg::FIGHTER_ASTEROID_COLLISION, sender, destination), fighter_(fighter), asteroid_(asteroid)  {
	}

	GameObject* fighter_;
	Asteroid* asteroid_;
};

struct FighterBlackHoleCollisionMsg: public msg::Message {
	FighterBlackHoleCollisionMsg(msg::ObjectId sender, msg::ObjectId destination, GameObject* fighter, BlackHole* blackhole) :
		Message(msg::FIGHTER_BLACKHOLE_COLLISION, sender, destination), fighter_(fighter), blackhole_(blackhole) {
	}

	GameObject* fighter_;
	BlackHole* blackhole_;
};

struct AsteroidDestroyed: public msg::Message {
	AsteroidDestroyed(msg::ObjectId sender, msg::ObjectId destination, int points) :
	Message(msg::ASTEROID_DESTROYED, sender, destination), points_(points)  {
	}

	int points_;
};

struct PlayerInfo : public msg::Message {
	PlayerInfo(msg::ObjectId sender, msg::ObjectId destination, GameObject* player) :
	Message(msg::PLAYER_INFO, sender, destination), player_(player)  {
	}

	GameObject*  player_;
};

struct PlayerInfo2 : public msg::Message {
	PlayerInfo2(msg::ObjectId sender, msg::ObjectId destination, GameObject* player2) :
		Message(msg::PLAYER2_INFO, sender, destination), player2_(player2) {
	}

	GameObject*  player2_;
};
struct BulletsInfoMsg: public msg::Message {
	BulletsInfoMsg(msg::ObjectId sender, msg::ObjectId destination, const std::vector<Bullet*>* bullets) :
	Message(msg::BULLETS_INFO, sender, destination), bullets_(bullets)  {
	}
	const std::vector<Bullet*>*  bullets_;
};

struct BulletsP2InfoMsg : public msg::Message {
	BulletsP2InfoMsg(msg::ObjectId sender, msg::ObjectId destination, const std::vector<BulletP2*>* bullets) :
		Message(msg::BULLETSP2_INFO, sender, destination), bullets_(bullets) {
	}
	const std::vector<BulletP2*>*  bullets_;
};

struct AsteroidsInfo: public msg::Message {
	AsteroidsInfo(msg::ObjectId sender, msg::ObjectId destination, const std::vector<Asteroid*>* asteroids) :
	Message(msg::ASTEROIDS_INFO, sender, destination), asteroids_(asteroids)  {
	}
	const std::vector<Asteroid*>*  asteroids_;
};
struct BlackHoleInfo : public msg::Message {
	BlackHoleInfo(msg::ObjectId sender, msg::ObjectId destination, const std::vector<BlackHole*>* blackholes) :
		Message(msg::BLACKHOLE_INFO, sender, destination), blackHoles_(blackholes) {
	}
	const std::vector<BlackHole*>*  blackHoles_;
};

};
