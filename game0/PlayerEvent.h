#pragma once

#include "Event.h"

const std::string PLAYER_EVENT = "playerevent";

class PlayerEvent : public df::Event {

private:
	

public:
	PlayerEvent(df::Vector pos);
	df::Vector player_pos;
	void setPos(df::Vector pos);
	df::Vector getPos() const;
};
