
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


	// TODO: SPAWN ENEMIES
	// INCLUDING BOSSES

	//new Boss(220, 48);


	// some pickups
	//

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

