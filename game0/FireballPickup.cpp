#include "FireballPickup.h"
#include "DisplayManager.h"
#include "WorldManager.h"

FireballPickup::FireballPickup(df::Vector init_pos)
{

	setPosition(init_pos);

	setType("fireballPickup");
}

int FireballPickup::draw()
{
	return DM.drawCh(getPosition(), 'F', df::RED);
}

int FireballPickup::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision*> (p_e);
		collide(p_collision_event);
		return 1;
	}
	return 0;
}

void FireballPickup::collide(const df::EventCollision* p_c)
{
	if (((p_c->getObject1()->getType()) == "Hero") ||
		((p_c->getObject2()->getType()) == "Hero")) {
		WM.markForDelete(this);
	}
}
