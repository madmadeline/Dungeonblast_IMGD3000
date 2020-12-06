//
// game.cpp
// 

#include "GameManager.h"
#include "LogManager.h"
#include <ResourceManager.h>
#include "DungeonHero.h"
#include "Goblin.h"
#include "Map.h"

#include "WorldManager.h"

int main(int argc, char *argv[]) {

  // Start up game manager.
  if (GM.startUp())  {
    LM.writeLog("Error starting game manager!");
    GM.shutDown();
    return 0;
  }
  
  // setting world to be size of map sprite
  WM.setBoundary(df::Box(df::Vector(0, 0), 88, 50));

  // Set flush of logfile during development (when done, make false).
  LM.setFlush(true);

  new Map;
  DungeonHero* hero = new DungeonHero;
  WM.setViewFollowing(hero);
  new Goblin;

  GM.run();

  // Shut everything down.
  GM.shutDown();
}

