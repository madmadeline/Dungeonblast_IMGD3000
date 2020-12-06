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

void loadResources(void) {
    RM.loadSprite("Sprites/map-test.txt", "MapTest");
    RM.loadSprite("Sprites/hero-spr.txt", "Hero");
}

int main(int argc, char *argv[]) {

  // Start up game manager.
  if (GM.startUp())  {
    LM.writeLog("Error starting game manager!");
    GM.shutDown();
    return 0;
  }
  
  // setting world to be size of map sprite
  WM.setBoundary(df::Box(df::Vector(0, 0), 98, 50));
  loadResources();

  // test map obj collisions
  /*for (int i = 0; i < 88; i++) {
      for (int j = 0; j < 50; j++) {
          if (!(i > 40 && i < 50) && !(j > 23 && j < 27)) {
              new Map(df::Vector(i, j));
          }
      }
  }*/

  // Set flush of logfile during development (when done, make false).
  LM.setFlush(true);

  GAME_MAP.getInstance();
  DungeonHero* hero = new DungeonHero;
  WM.setViewFollowing(hero);
  new Goblin;
  df::Vector p(12, WM.getBoundary().getVertical() / 2);
  df::Vector p2(72, WM.getBoundary().getVertical() / 2);
  df::Vector p3(50, WM.getBoundary().getVertical() / 3);
  new BulletPickup(p);
  new FireballPickup(p2);
  new HealthPickup(p3);

  //view objects
  df::ViewObject* vo_hp = new df::ViewObject; //health counter
  vo_hp->setLocation(df::TOP_LEFT);
  vo_hp->setViewString("Health:");
  vo_hp->setValue(100);
  vo_hp->setColor(df::YELLOW);

  df::ViewObject* vo_am = new df::ViewObject; //ammo counter
  vo_am->setLocation(df::TOP_CENTER);
  vo_am->setViewString("Ammo:");
  vo_am->setValue(20);
  vo_am->setColor(df::YELLOW);

  df::ViewObject* vo_mg = new df::ViewObject; //magic counter
  vo_mg->setLocation(df::TOP_RIGHT);
  vo_mg->setViewString("Magic:");
  vo_mg->setValue(0);
  vo_mg->setColor(df::YELLOW);


  GM.run();

  // Shut everything down.
  GM.shutDown();
}

