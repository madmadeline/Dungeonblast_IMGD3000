
#include "Object.h"
#include "EventCollision.h"

class Goblin : public df::Object {
private:
	int draw();
	void moveToStart();
	void hit(const df::EventCollision* p_c);
	int hp;
public:
	//Goblin();
	Goblin(int x, int y);
	~Goblin();
	int eventHandler(const df::Event* p_e);
};