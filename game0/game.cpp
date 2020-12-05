//
// game.cpp
// 

#include "GameManager.h"
#include "LogManager.h"
#include <ResourceManager.h>
#include "DungeonHero.h"
#include "Goblin.h"

int main(int argc, char *argv[]) {

  // Start up game manager.
  if (GM.startUp())  {
    LM.writeLog("Error starting game manager!");
    GM.shutDown();
    return 0;
  }

  // Set flush of logfile during development (when done, make false).
  LM.setFlush(true);

  new DungeonHero;
  new Goblin;

  GM.run();

  // Shut everything down.
  GM.shutDown();
}

