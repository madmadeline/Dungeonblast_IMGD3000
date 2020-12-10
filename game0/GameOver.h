#pragma once

// Engine includes
#include "ViewObject.h"
// Game includes


class GameOver : public df::ViewObject {
private:
	int time_to_live;
	void step();
	int draw();

public:
	GameOver();
	~GameOver();
	int eventHandler(const df::Event* p_e);
};

