#include "WorldManager.h"
#include "Map.h"
#include <cmath>
#include "Utility.h"

#include "GameUtility.h"

bool checkOverlapMap(df::Object* p_o, df::Vector new_pos, int dir) {
	// should result in box_pos being top left of object's sprite
	// and obj_box being the given object's box (for w and h)
	df::Box obj_box = p_o->getBox();

	df::Vector box_corner = obj_box.getCorner();
	
	int box_w = (int)obj_box.getHorizontal();
	int box_h = (int)obj_box.getVertical();
	int box_x = (int)new_pos.getX() + box_corner.getX();
	int box_y = (int)floorf(new_pos.getY() + box_corner.getY()) + 1;

	// dir: 1 = up, -1 = down, 2 = left, -2 = right
	/*if (dir == 1)
		box_y = (int)floorf(new_pos.getY() + box_corner.getY());
	else if (dir == -1)
		box_y = (int)ceilf(new_pos.getY() + box_corner.getY());
	else if (dir == 2)
		box_x = (int)floorf(new_pos.getX());
	else if (dir == -2)
		box_x = (int)ceilf(new_pos.getX());*/
	df::Object* p_map = NULL;
	df::ObjectList object_list = WM.getAllObjects(true);
	df::ObjectListIterator i(&object_list);
	for (i.first(); !i.isDone(); i.next()) {
		df::Object* p_o = i.currentObject();
		if (p_o->getType() == "Map") {
			p_map = p_o;
			continue;
		}
	}
	if (p_map == NULL)
		return true;

	std::string map_str = p_map->getAnimation().getSprite()->getFrame(0).getString();
	int map_w = p_map->getAnimation().getSprite()->getFrame(0).getWidth();

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

