
#include "ViewObject.h"
#include "Event.h"

class Equipped : public df::ViewObject {
public:
	Equipped();
	int eventHandler(const df::Event* p_e);
};