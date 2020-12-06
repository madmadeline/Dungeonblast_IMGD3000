#pragma once

#include "Object.h"
#include "EventCollision.h"

class Fireball : public df::Object {
private:
	void out();
	void hit(const df::EventCollision* p_collision_event);

public:
	Fireball(df::Vector hero_pos);
	int draw();
	int eventHandler(const df::Event* p_e);
	void collide(const df::EventCollision* p_c);
};