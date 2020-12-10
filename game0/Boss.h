#include "Object.h"
#include "EventCollision.h"

class Boss : public df::Object {
private:
	int draw();
	void hit(const df::EventCollision* p_c);
	int hp;
	int move_slowdown;
	int move_countdown;
	int dir;
	df::Vector target;
	int fire_slowdown;
	int fire_countdown;
public:
	Boss(int x, int y);
	~Boss();
	void step();
	int eventHandler(const df::Event* p_e);
	void move(int d);
	void fire();
};