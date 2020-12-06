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

void loadResources(void) {
    RM.loadSprite("Sprites/map-char.txt", "MapTest");
}

int main(int argc, char *argv[]) {

  // Start up game manager.
  if (GM.startUp())  {
    LM.writeLog("Error starting game manager!");
    GM.shutDown();
    return 0;
  }
  
  // setting world to be size of map sprite
  WM.setBoundary(df::Box(df::Vector(0, 0), 88, 50));
  loadResources();

  // test map obj collisions
  for (int i = 0; i < 88; i++) {
      for (int j = 0; j < 50; j++) {
          if (!(i > 40 && i < 50) && !(j > 23 && j < 27)) {
              new Map(df::Vector(i, j));
          }
      }
  }

  // Set flush of logfile during development (when done, make false).
  LM.setFlush(true);

  //GAME_MAP.getInstance();
  DungeonHero* hero = new DungeonHero;
  WM.setViewFollowing(hero);
  new Goblin;

  GM.run();

  // Shut everything down.
  GM.shutDown();
}

