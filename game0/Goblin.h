
#include "Object.h"
#include "EventCollision.h"

class Goblin : public df::Object {
private:
	int draw();
	void hit(const df::EventCollision* p_c);
	int hp;
	int dir;
	int move_slowdown;
	int move_countdown;
public:
	Goblin(int x, int y, int d);
	~Goblin();
	void step();
	int eventHandler(const df::Event* p_e);
	void move(int d);
};