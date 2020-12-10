#include "DungeonHero.h"

#include "EventMouse.h"
#include "EventStep.h"
#include "EventView.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "Bullet.h"
#include "Fireball.h"
#include "GameUtility.h"
#include <ViewObject.h>
#include "Equipped.h"
#include "StringEvent.h"
#include "Boss.h"
#include "GameOver.h"
#include "EventPlayer.h"

//CONSTRUCTOR
DungeonHero::DungeonHero() {
	setType("Hero");
	setSprite("HeroIdleGun");
	this->getAnimation().getSprite()->setTransparency(' ');

	//register interests
	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::STEP_EVENT);
	registerInterest(df::MSE_EVENT);
	registerInterest(df::COLLISION_EVENT);

	//set init position
	//df::Vector p(42, WM.getBoundary().getVertical() / 2);
	df::Vector p(15, 86);
	setPosition(p);

	//set init variables
	fire_slowdown = 15;
	fire_countdown = fire_slowdown;
	move_slowdown = 1;
	move_countdown = move_slowdown;
	hp = 100;
	ammo = 20;
	currentDir = 4; //1 = up
					//2 = down
					//3 = left
					//4 = right
	equipped = 0; //0 = gun
				  //1 = magic
	hasFireball = false; //true when fireball pickup is obtained
	bossDrawn = false;

	//mouse pointer
	p_reticle = new Reticle();
	p_reticle->draw();

	//play the background music
	df::Music* p_music = RM.getMusic("BGM");
	p_music->play();
	moveSpriteTimer = 2;
}

//DESTRUCTOR
DungeonHero::~DungeonHero(){
	// Create GameOver object
	new GameOver;

	// Mark Reticle for deletion
	WM.markForDelete(p_reticle);
}

//EVENT HANDLER
int DungeonHero::eventHandler(const df::Event* p_e){
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_keyboard_event =
			dynamic_cast <const df::EventKeyboard*> (p_e);
		kbd(p_keyboard_event);
		return 1;
	}
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}
	if (p_e->getType() == df::MSE_EVENT) {
		const df::EventMouse* p_mouse_event =
			dynamic_cast <const df::EventMouse*> (p_e);
		mouse(p_mouse_event);
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision*> (p_e);
		collide(p_collision_event);
		return 1;
	}
	return 0;
}

// DRAW 
int DungeonHero::draw() {
	//return DM.drawCh(getPosition(), 'H', df::BLUE);
	return Object::draw();
}

//KEYBOARD STUFF
void DungeonHero::kbd(const df::EventKeyboard* p_keyboard_event){

	switch (p_keyboard_event->getKey()) {

	case df::Keyboard::Q:  // Q quits to start menu
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			WM.markForDelete(this);
		break;

	case df::Keyboard::W:       // up
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			currentDir = 1;
			move(-0.5);
		break;
	case df::Keyboard::S:       // down
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			currentDir = 2;
			move(0.5);
		break;
	case df::Keyboard::A:		//left
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			currentDir = 3;
			advance(-1);
		break;
	case df::Keyboard::D:       // right
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			currentDir = 4;
			advance(1);
		break;
	/*case df::Keyboard::SPACE:
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			fire();
			break;*/
	case df::Keyboard::E:
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			if (equipped == 0 && hasFireball) {
				equipped = 1;

				FireballEvent fireb;
				WM.onEvent(&fireb);
			}
			else {
				equipped = 0;
				GunEvent gun;
				WM.onEvent(&gun);
			}
		break;
	default: //other key pressed
		return;
	};

	return;
}

//MOVE THE HERO UP OR DOWN
void DungeonHero::move(float dir){
	// See if time to move.
	if (move_countdown > 0)
		return;
	move_countdown = move_slowdown;

	if (moveSpriteTimer >= 6) {
		if (equipped == 0)
			setSprite("HeroWalkingGun");
		else
			setSprite("HeroWalkingFire");
		this->getAnimation().getSprite()->setTransparency(' ');
		moveSpriteTimer = 0;
	}

	df::Vector new_pos(getPosition().getX(), getPosition().getY() + dir);

	int checkDir = 0;
	if (dir < 0)
		checkDir = -1;
	else
		checkDir = 1;

	if (checkOverlapMap(this, new_pos, checkDir) == true) {
		return;	// overlaps, doesn't move, else continue
	}

	/*if (new_pos.getX() >= 94 && new_pos.getX() <= 98 && new_pos.getY() >= 23 && new_pos.getY() <= 40 && bossDrawn == false) {
		//draw the boss and start the boss music
		new Boss(35, 77);
		bossDrawn = true;
	}*/

	if ((new_pos.getY() > -1) &&
		(new_pos.getY() < WM.getBoundary().getVertical() - 1))
		WM.moveObject(this, new_pos);
	
	WM.moveObject(this, new_pos);
	moveSpriteTimer = 0;
}

//MOVE THE HERO LEFT OR RIGHT
void DungeonHero::advance(int dir) {
	//see if time to move
	if (move_countdown > 0)
		return;
	move_countdown = move_slowdown;

	if (moveSpriteTimer >= 6) {
		if (equipped == 0)
			setSprite("HeroWalkingGun");
		else
			setSprite("HeroWalkingFire");
		this->getAnimation().getSprite()->setTransparency(' ');
		moveSpriteTimer = 0;
	}

	df::Vector new_pos(getPosition().getX() + dir, getPosition().getY());

	int checkDir = 0;
	if (dir < 0)
		checkDir = 2;
	else
		checkDir = -2;

	/// 
	/// NEED TO CHANGE THIS ACCORDING TO FINAL MAP
	/// 
	/*if (new_pos.getX() >= 94 && new_pos.getX() <= 98 && new_pos.getY() >= 23 && new_pos.getY() <= 40 && bossDrawn == false) {
		//draw the boss and start the boss music
		new Boss(73, 25);
		bossDrawn = true;
	}*/

	if (checkOverlapMap(this, new_pos, checkDir) == true) {
		return;	// overlaps, doesn't move, else continue
	}

	if ((new_pos.getX() > -1) &&
		(new_pos.getX() < WM.getBoundary().getHorizontal() - 1))
		WM.moveObject(this, new_pos);
}

//FIRE BULLET/MAGIC
void DungeonHero::fire(df::Vector target) {
	if (fire_countdown > 0)
		return;
	fire_countdown = fire_slowdown;

	df::Vector v = target - getPosition();
	v.normalize();
	v.scale(1);

	if (equipped == 0) {
		//gun equipped
		if (ammo <= 0) {
			//dont fire
			return;
		}
		Bullet* p = new Bullet(getPosition());
		p->setVelocity(v);
		// Play "bullet" sound.
		df::Sound* p_sound = RM.getSound("Shoot");
		p_sound->play();
		ammo--;
		df::EventView ev("Ammo:", -1, true);
		WM.onEvent(&ev);
	}
	else if (equipped == 1) {
		//magic equipped
		df::Sound* p_sound = RM.getSound("Fireball");
		p_sound->play();
		Fireball* p = new Fireball(getPosition());
		p->setVelocity(v);
	}

}

//MOUSE EVENT
void DungeonHero::mouse(const df::EventMouse* p_mouse_event) {
	//pressed button?
	if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
		(p_mouse_event->getMouseButton() == df::Mouse::LEFT))
		fire(df::viewToWorld(p_mouse_event->getMousePosition()));
}

//STEP EVENT STUFF
void DungeonHero::step(){

	//send current position to interested objects
	PlayerEvent p(getPosition());
	WM.onEvent(&p);

	move_countdown--;
	if (move_countdown < 0) {
		move_countdown = 0;
	}
	fire_countdown--;
	if (fire_countdown < 0) {
		fire_countdown = 0;
	}

	if (moveSpriteTimer >= 6) {
		if (equipped == 0)
			setSprite("HeroIdleGun");
		else
			setSprite("HeroIdleFire");
		this->getAnimation().getSprite()->setTransparency(' ');
	}
	else
		moveSpriteTimer++;
}

//COLLISION EVENT STUFF
void DungeonHero::collide(const df::EventCollision* p_c) {
	//if hero on enemy, decrease hero hp.
	if (((p_c->getObject1()->getType()) == "Goblin") ||
		((p_c->getObject2()->getType()) == "Goblin")) {
		hp -= 20;
		df::EventView ev("Health:", -20, true);
		df::Sound* p_sound = RM.getSound("Death");
		p_sound->play();
		WM.onEvent(&ev);
		if (hp <= 0) {
			//game over
			DungeonHero::~DungeonHero();
		}
	}
	else if (((p_c->getObject1()->getType()) == "bulletPickup") ||
		((p_c->getObject2()->getType()) == "bulletPickup")) {
		ammo += 10;
		//df::Sound* p_sound = RM.getSound("Ammo");
		//p_sound->play();
		df::EventView ev("Ammo:", 10, true);
		WM.onEvent(&ev);
	}
	else if (((p_c->getObject1()->getType()) == "fireballPickup") ||
		((p_c->getObject2()->getType()) == "fireballPickup")) {
		//df::Sound* p_sound = RM.getSound("Fireball");
		//p_sound->play();
		hasFireball = true;
		df::EventView ev("Magic:", 1, true);
		WM.onEvent(&ev);
	}
	else if (((p_c->getObject1()->getType()) == "healthPickup") ||
		((p_c->getObject2()->getType()) == "healthPickup")) {
		hp += 20;
		df::Sound* p_sound = RM.getSound("Health");
		p_sound->play();
		df::EventView ev("Health:", 20, true);
		WM.onEvent(&ev);
	}
	else if (((p_c->getObject1()->getType()) == "Boss") ||
		((p_c->getObject2()->getType()) == "Boss")) {
		hp -= 20;
		df::EventView ev("Health:", -20, true);
		WM.onEvent(&ev);
		if (hp <= 0) {
			//game over
			DungeonHero::~DungeonHero();
		}
	}
	else if (((p_c->getObject1()->getType()) == "Fireball") ||
		((p_c->getObject2()->getType()) == "Fireball")) {
		hp -= 20;
		df::EventView ev("Health:", -20, true);
		WM.onEvent(&ev);
		if (hp <= 0) {
			//game over
			DungeonHero::~DungeonHero();
		}
	}
}

