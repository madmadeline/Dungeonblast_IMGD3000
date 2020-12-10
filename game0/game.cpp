//
// game.cpp
// 

#include "GameManager.h"
#include "LogManager.h"
#include <ResourceManager.h>
#include "DungeonHero.h"
#include "Goblin.h"
#include "Map.h"
#include "BulletPickup.h"
#include "FireballPickup.h"
#include "ViewObject.h"
#include "HealthPickup.h"

#include "WorldManager.h"
#include "Equipped.h"
#include "Boss.h"


void loadResources(void) {
    //RM.loadSprite("Sprites/map2.txt", "MapTest");
    RM.loadSprite("Sprites/map-test.txt", "MapTest");
    //RM.loadSprite("Sprites/hero-spr.txt", "Hero");
    RM.loadSprite("Sprites/hero-idle-fire.txt", "HeroIdleFire");
    RM.loadSprite("Sprites/hero-idle-gun.txt", "HeroIdleGun");
    RM.loadSprite("Sprites/hero-walking-fire.txt", "HeroWalkingFire");
    RM.loadSprite("Sprites/hero-walking-gun.txt", "HeroWalkingGun");
    RM.loadSprite("Sprites/goblin-spr.txt", "Goblin");
}

int main(int argc, char *argv[]) {

  // Start up game manager.
  if (GM.startUp())  {
    LM.writeLog("Error starting game manager!");
    GM.shutDown();
    return 0;
  }
  
  // setting world to be size of map sprite
  WM.setBoundary(df::Box(df::Vector(0, 0), 60, 30));
  loadResources();

  // Set flush of logfile during development (when done, make false).
  LM.setFlush(true);

  //boss
  //new Boss(35,77); //put in the boss room, coords will change with new map config

  // some pickups
  new BulletPickup(df::Vector(15, 33));
  new FireballPickup(df::Vector(9, 38));
  new HealthPickup(df::Vector(21, 31));

  GM.run();

  // Shut everything down.
  GM.shutDown();
}

