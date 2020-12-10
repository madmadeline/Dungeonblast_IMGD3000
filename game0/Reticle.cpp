#include "EventMouse.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include "Reticle.h"
#include <LogManager.h>

Reticle::Reticle() {
    setType("Reticle");
    setSolidness(df::SPECTRAL);
    setAltitude(df::MAX_ALTITUDE); //altitude determines layering of objects, draw on top

    // Reticle moves with mouse
    registerInterest(df::MSE_EVENT);

   df::Vector p(WM.getBoundary().getHorizontal() / 2,
        WM.getBoundary().getVertical() / 2);

    setPosition(p);
}

int Reticle::eventHandler(const df::Event* p_e) {

    if (p_e->getType() == df::MSE_EVENT) {
        const df::EventMouse* p_mouse_event = dynamic_cast <const df::EventMouse*> (p_e);
        if (p_mouse_event->getMouseAction() == df::MOVED) {
            // Change location to new mouse position.
            //df::Vector viewPos = p_mouse_event->getMousePosition();
            //setPosition(df::viewToWorld(viewPos));
            setPosition(p_mouse_event->getMousePosition());
            return 1;
        }
    }
    return 0;
}

// Draw reticle on window.
int Reticle::draw() {
    LM.writeLog("DRAWING THE RETICLE");
    //df::Vector viewPos = worldToView(this->getPosition());
    //return DM.drawCh(worldToView(getPosition()), RETICLE_CHAR, df::RED);
    return DM.drawCh(df::viewToWorld(getPosition()), RETICLE_CHAR, df::RED);
}
