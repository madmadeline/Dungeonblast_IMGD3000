
#include "Event.h"

const std::string STRING_EVENT = "stringevent";

const std::string FIREBALL_EVENT = "fireballevent";
const std::string GUN_EVENT = "gunevent";

class StringEvent : public df::Event {
public:
	StringEvent();
};

class FireballEvent : public df::Event {
public:
	FireballEvent();
};

class GunEvent : public df::Event {
public:
	GunEvent();
};
