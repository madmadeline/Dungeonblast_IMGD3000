#include "EventKeyboard.h"
#include "EventMouse.h"
#include "Object.h"
#include "EventCollision.h"
#include "Reticle.h"

class DungeonHero : public df::Object {

private:
	int fire_slowdown;
	int fire_countdown;
	int move_slowdown;
	int move_countdown;
	int hp;
	int ammo;
	int currentDir;
	int equipped;
	bool hasFireball;

	void kbd(const df::EventKeyboard* p_keyboard_event);
	void move(float dir);
	void advance(int dir);
	void fire(df::Vector target);
	void mouse(const df::EventMouse* p_mouse_event);
	void step();
	void collide(const df::EventCollision* p_c);
	int draw(void);
	bool bossDrawn;

	Reticle* p_reticle;

public:
	DungeonHero();
	~DungeonHero();
	int eventHandler(const df::Event* p_e);
};
