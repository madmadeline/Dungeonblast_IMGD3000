#include "EventPlayer.h"

PlayerEvent::PlayerEvent(df::Vector pos) {
	setType(PLAYER_EVENT);
	setPos(pos);
}

void PlayerEvent::setPos(df::Vector pos) {
	player_pos = pos;
}

df::Vector PlayerEvent::getPos() const {
	return player_pos;
}
