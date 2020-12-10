#pragma once

#include "Event.h"

const std::string PLAYER_EVENT = "playerevent";

class PlayerEvent : public df::Event {

private:
	df::Vector player_pos;

public:
	PlayerEvent(df::Vector pos);
	void setPos(df::Vector pos);
	df::Vector getPos() const;
};
