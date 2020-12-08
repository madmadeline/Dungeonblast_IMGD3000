#include "Equipped.h"
#include "EventStep.h"
#include "StringEvent.h"

Equipped::Equipped() {
	setLocation(df::TOP_RIGHT);
	setViewString("Equipped: Gun");
	setColor(df::YELLOW);
	registerInterest(FIREBALL_EVENT);
	registerInterest(GUN_EVENT);
}

int Equipped::eventHandler(const df::Event* p_e) {
	//Look for change in viewString
	if (p_e->getType() == FIREBALL_EVENT) {
		setViewString("Equipped: Fireball");
	}
	if (p_e->getType() == GUN_EVENT) {
		setViewString("Equipped: Gun");
	}
	return 0;
}