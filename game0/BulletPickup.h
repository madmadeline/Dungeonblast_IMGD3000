
#include "Object.h"
#include "EventCollision.h"

class BulletPickup : public df::Object {
private:
public:
	BulletPickup(df::Vector init_pos);
	int draw();
	int eventHandler(const df::Event* p_e);
	void collide(const df::EventCollision* p_c);
};