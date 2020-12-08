#include "StringEvent.h"

StringEvent::StringEvent() {
	setType(STRING_EVENT);
};

FireballEvent::FireballEvent() {
	setType(FIREBALL_EVENT);
}

GunEvent::GunEvent() {
	setType(GUN_EVENT);
}