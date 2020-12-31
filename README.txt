==================================================
DUNGEONBLAST

a game by:
Ryan Darcey (rtdarcey@wpi.edu)
Madeline Perry (mmperry@wpi.edu)

Trailer: https://youtu.be/YDCGeJ1q4Rc
==================================================
HOW TO PLAY:

WASD: Move
Left-Click: Fire
E: Switch weapon (if two weapons are available)
Q: Quit

AVAILABLE PICKUPS:

Fireball (F): Unlocks the fireball weapon
Ammo (A): Increases the player's ammo
Health (+): Increases the player's health

==================================================
PLATFORM:
  Dungeonblast was created with the Dragonfly engine through Visual Studio using Windows.

FILES:
  In the main directory, the Dragonfly engine library and SFML can be found. Additionally, the
original map design file is stored here.
  All game-related files created by Team Dungeonblasters is found in the game0 folder. All
visual assets are found in the 'Sprites' folder and audio in the 'Sounds' folder.

CODE STRUCTURE:
  Most of our files are self-explanatory, but some notes should be made about files that are less
so. The basic enemy code can be found under the 'Goblin.cpp' and 'Goblin.h' files since the enemy
was originally planned to be a goblin instead of a spider like it is in the final. 'Equipped.cpp'
and its corresponding .h file handle the view object associated with displaying the current weapon
equipped.

HOW TO COMPILE:
  To compile the game, navigate to the solution file in the game0 folder and open it in Visual
Studio. Compile the code using the F7 command and run with F5. The game should run properly.
