#pragma once

// Engine includes
#include "ViewObject.h"
#include "Music.h"
// Game includes


class GameStart : public df::ViewObject {

private:
	void start();
	df::Music* p_music;

public:
	GameStart();
	int eventHandler(const df::Event* p_e);
	int draw();
	void playMusic();
};

