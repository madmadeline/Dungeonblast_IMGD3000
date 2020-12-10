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
#include "GameStart.h"


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
    RM.loadSprite("Sprites/gamestart-spr.txt", "gamestart");
    RM.loadSprite("Sprites/gameover-spr.txt", "gameover");


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

  new GameStart();


  GM.run();

  // Set flush of logfile during development (when done, make false).
  LM.setFlush(true);


  // Shut everything down.
  GM.shutDown();
}

