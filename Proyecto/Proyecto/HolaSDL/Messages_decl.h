#pragma once

namespace msg {

enum ObjectId {
	None,  	// special value indicating no object (or more precisely component)
	Broadcast,   // special value indicating all objects
	Ball,
	Player,
	Player2,
	Asteroids,
	BulletsShooter,
	FighterGun, 
	BlackHoles
};

enum MessageType {
	GAME_START,
	GAME_OVER,
	ROUND_START,
	ROUND_OVER,
	PLAYER_SHOOT,
	PLAYER2_SHOOT,
	BULLET_ASTEROID_COLLISION,
	BULLET_BLACKHOLE_COLLISION,
	BLACKHOLE_ASTEROID_COLLISION,
	FIGHTER_ASTEROID_COLLISION,
	FIGHTER_BLACKHOLE_COLLISION,
	ASTEROID_DESTROYED,
	NO_MORE_FIGHTER_LIVES,
	NO_MORE_ASTEROIDS,	
	NO_LIFE_PLAYER,
	NO_LIFE_PLAYER2,
	PLAYER_INFO,
	PLAYER2_INFO,
	BULLETS_INFO,
	BULLETSP2_INFO,
	ASTEROIDS_INFO,
	BLACKHOLE_INFO,
	BULLET_PLAYER2_COLLISION,
	BULLETP2_PLAYER_COLLISION,
	NEXTROUND
};

struct Message;

};
