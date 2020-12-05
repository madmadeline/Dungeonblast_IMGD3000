#include "EventKeyboard.h"
#include "EventMouse.h"
#include "Object.h"
#include "EventCollision.h"

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

	void kbd(const df::EventKeyboard* p_keyboard_event);
	void move(int dir);
	void advance(int dir);
	void fire();
	void mouse(const df::EventMouse* p_mouse_event);
	void step();
	void collide(const df::EventCollision* p_c);
	int draw(void);

public:
	DungeonHero();
	~DungeonHero();
	int eventHandler(const df::Event* p_e);
};