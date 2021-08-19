# Cell Wars
# INITIAL REQUIREMENTS

-Windows computer  
-IDE compatible with C++14 or newer (for devs only)  
-SFML (for devs only): https://www.sfml-dev.org/download.php

# INTRODUCTION
This is a fun hobby-project of mine originally from 2019 Feb. I always have like the old flash-game Phage Wars. This was my attempt to create something similar to it. I do not intend to release this game.  
In 2021 Aug, I added comments to the code, and uploaded the project to GitHub.

# INSTALLATION
Unzip or unrar the file called "Cell Wars shipped".

# GOAL
There are multiple players in the game, all the opponents are controlled by the computer. You and the computer opponents fight **till only one survives**. The last survivor is the  **winner of the match**. Players are alive until they have viruses left. The more cells one has, the faster they produce viruses. Therefore, **area control** is a key mechanic. In order to take over a cell, one has to **reduce its power to 0**, and send one final virus in that takes the ownership. There are some cells with conditions that make them more favourable than other cells, such as faster ejection speed, production speed, or bigger capacity. There are 15 hand-crafted levels with an increasing difficulty to challenge the players how deadly their virus would be.
# MENUS

All menus have a background with circles (of various sizes, transparencies, and movement speeds) moving around. This one is intented to make them more alive, and pleasurable to watch.  
Below, each menu is discussed.
## Main Menu
Pressing ESC redirects the player to the main menu.  
The main menu consists of 4 different buttons:

**PLAY/CONTINUE:** Clicking on this button opens the highest level available for the player.  
**SELECT LEVEL:** Clicking on this button opens the Level Selection Menu.  
**OPTIONS:** Clicking on this button opens the Options Menu.  
**QUIT GAME:** Clicking on this button closes the application.  
## Play/Continue In-Game Menu
On the top left corner, the current level is visible. In the top right corner, there is a Pause/Continue button. Pressing the button, or hitting the 'P' key pauses/continues the game.  
After a match is finished or the player loses, there is a button in the bottom right corner.

**NEXT**: Clicking on this button opens the Graph Menu.  
## Level Selection Menu
There are 15 buttons in the middle for each level ordered systematically. There might be several transparent buttons. These buttons are transparent because the adherent level has not been unlocked yet. The opaque buttons open the appropriate level.  
There is a Menu button that leads the user back to the Main Menu.
## Options Menu
There are 4 buttons in the middle.

**SHOW FPS:** Clicking on this button turns the fps meter on/off. Default is off.  
**X FPS:** Changes the framerate. The user can swap to 30, 60, 120 or no fps limit. Default is 60.  
**COLOR:** Clicking on this button changes the color of the virus the player has in-game.  
**AUTOPAUSE:** Clicking on this button turns the auto-pause at the beginning of a match on/off. Default is off.  

There is a Menu button that leads the user back to the Main Menu.  
## Graph Menu
This menu shows the statistics of the last match played.  
There are 2 buttons on the button left.  

**MENU:** Clicking on this button opens the Main Menu.

In case of winning:  
**NEXT:** Opens the match on the next level.  
In case of losing:  
**AGAIN:** Opens the match on the current level  
