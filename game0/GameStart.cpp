
// Engine includes
#include "EventKeyboard.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
// Game includes
#include "GameStart.h"
#include "Goblin.h"
#include "DungeonHero.h"
#include "Boss.h"
#include "FireballPickup.h"
#include "HealthPickup.h"
#include "BulletPickup.h"
#include "Map.h"
#include "Equipped.h"


GameStart::GameStart() {
	setType("GameStart");
	
	setViewString("Press P to start, Q to quit");
	setColor(df::YELLOW);

	// Play start music
	p_music = RM.getMusic("BGM");
	playMusic();

	// Link to "gamestart" sprite
	setSprite("gamestart");

	// Put in center of window
	setLocation(df::CENTER_CENTER);

	// Register for step event
	registerInterest(df::KEYBOARD_EVENT);
}

int GameStart::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::KEYBOARD_EVENT) {
		df::EventKeyboard* p_keyboard_event = (df::EventKeyboard*) p_e;
		switch (p_keyboard_event->getKey()) {
		case df::Keyboard::P:  // play
			start();
			break;

		case df::Keyboard::Q:  // quit
			GM.setGameOver();
			break;

		default:  // Key is not handled
			break;
		}
		return 1;
	}
	return 0;
}

void GameStart::start() {
	// Pause start music
	p_music->pause();

	// get map
	GAME_MAP.getInstance();

	// Spawn player
	DungeonHero* hero = new DungeonHero;
	WM.setViewFollowing(hero);

	//view objects
	df::ViewObject* vo_hp = new df::ViewObject; //health counter
	vo_hp->setLocation(df::TOP_LEFT);
	vo_hp->setViewString("Health:");
	vo_hp->setValue(100);
	vo_hp->setColor(df::YELLOW);

	df::ViewObject* vo_am = new df::ViewObject; //ammo counter
	vo_am->setLocation(df::TOP_CENTER);
	vo_am->setViewString("Ammo:");
	vo_am->setValue(20);
	vo_am->setColor(df::YELLOW);

	new Equipped;


	// SPAWN ENEMIES
	// INCLUDING BOSSES

	// dir: 1 = up, -1 = down, 2 = left, -2 = right
	//new Goblin(27, 66, 1);

	new Goblin(83 * 3, 3 * 2, 2);
	new Goblin(53 * 3, 8 * 2, -1);
	new Goblin(45 * 3, 10 * 2, -1);
	new Goblin(70 * 3, 12 * 2, 2);
	new Goblin(37 * 3, 20 * 2, 2);
	new Goblin(62 * 3, 22 * 2, 2);
	new Goblin(62 * 3, 25 * 2, -2);
	new Goblin(79 * 3, 37 * 2, -2);
	new Goblin(39 * 3, 39 * 2 - 1, 2);
	new Goblin(40 * 3, 32 * 2, -2);
	new Goblin(45 * 3, 30 * 2, -2);
	new Goblin(50 * 3, 28 * 2, -2);
	new Goblin(75 * 3, 42 * 2, 2);
	new Goblin(27 * 3, 46 * 2, -2);
	new Goblin(8 * 3, 32 * 2, 1);
	new Goblin(26 * 3, 28 * 2, 1);

	new Boss(220, 48);

	// some pickups
	new HealthPickup(df::Vector(75 * 3, 7 * 2));
	new HealthPickup(df::Vector(77 * 3, 7 * 2));
	new HealthPickup(df::Vector(20 * 3, 30 * 2));
	new HealthPickup(df::Vector(80 * 3, 42 * 2));

	new FireballPickup(df::Vector(49 * 3, 14 * 2));
	new FireballPickup(df::Vector(77 * 3, 33 * 2));
	new FireballPickup(df::Vector(14 * 3, 32 * 2));

	new BulletPickup(df::Vector(45 * 3, 7 * 2));
	new BulletPickup(df::Vector(45 * 3, 7 * 2));
	new BulletPickup(df::Vector(74 * 3, 33 * 2));
	new BulletPickup(df::Vector(75 * 3, 33 * 2));
	new BulletPickup(df::Vector(82 * 3, 42 * 2));
	new BulletPickup(df::Vector(52 * 3, 42 * 2));
	new BulletPickup(df::Vector(8 * 3, 38 * 2));

	// When game starts, become inactive
	setActive(false);
}

// Override default draw so as not to display "value"
int GameStart::draw() {
	return df::Object::draw();
}

void GameStart::playMusic() {
	p_music->play();
}

