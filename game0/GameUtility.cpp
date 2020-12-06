#include "WorldManager.h"
#include "Map.h"

#include "GameUtility.h"

bool checkOverlapMap(df::Object* p_o, df::Vector new_pos) {
	// should result in box_pos being top left of object's sprite
	// and obj_box being the given object's box (for w and h)
	df::Box obj_box = p_o->getBox();
	//df::Vector box_pos = p_o->getPosition();
	int box_x = (int)new_pos.getX();
	int box_y = (int)new_pos.getY();
	int box_w = (int)obj_box.getHorizontal();
	int box_h = (int)obj_box.getVertical();

	std::string map_str = GAME_MAP.getAnimation().getSprite()->getFrame(0).getString();
	int map_w = GAME_MAP.getAnimation().getSprite()->getFrame(0).getWidth();

	for (int i = box_x; i < (box_x + box_w); i++) {
		for (int j = box_y - 1; j < (box_y + box_h - 1); j++) {
			char c = map_str[i + (j * map_w)];
			if (c != ' ') {
				return true;
			}
		}
	}
	return false;
}
