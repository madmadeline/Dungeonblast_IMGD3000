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
#include "Music.h"

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
    RM.loadSprite("Sprites/dragon-spr.txt", "Dragon");
    RM.loadMusic("Sounds/BackgroundMusic.wav", "BGM");
    RM.loadSound("Sounds/DragonRoar.wav", "Roar");
    RM.loadSound("Sounds/EnemyDeath.wav", "Death");
    RM.loadSound("Sounds/Fireball.wav", "Shoot");
    RM.loadSound("Sounds/GameOver.wav", "Gameover");
    RM.loadSound("Sounds/GameWin.wav", "Win");
    RM.loadSound("Sounds/HealthPickup.wav", "Health");
    RM.loadSound("Sounds/Iceball.wav", "Fireball");
    RM.loadSound("Sounds/WeaponPickup.mp3", "Ammo");
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

  // initialize game world objs:
  // map
  GAME_MAP.getInstance();

  // player
  DungeonHero* hero = new DungeonHero;
  WM.setViewFollowing(hero);

  // some enemies
  /*new Goblin(9, 32, 1);
  new Goblin(21, 27, -1);
  new Goblin(34, 47, -2);
  new Goblin(37, 39, 2);*/
  //new Goblin(12, 5, -1);
  //new Goblin(12, 18, 2);
  new Boss(12, 5);

  //boss
  //new Boss(35,77); //put in the boss room, coords will change with new map config

  // some pickups
  new BulletPickup(df::Vector(15, 33));
  new FireballPickup(df::Vector(9, 38));
  new HealthPickup(df::Vector(21, 31));

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

  Equipped eq;

  GM.run();

  // Shut everything down.
  GM.shutDown();
}
