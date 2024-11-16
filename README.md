# Maze Runner

### What is finished so far
1. state machine is completely set up in main.c
2. complex movement for the player has been established
3. collision map for the player and the grievers is set up. needs to be redone.
4. sprite animation is set up but the art is not done.
5. when the player reaches the end of the maze, the game enters the first "cutscene" / transition between the first and second level.
6. The heart sprites for the cheat have been implemented. The player changes color using palette modification after colliding with a heart sprite. and after pressing the Right Shoulder button all the grievers disappear as well. The timer for this needs to still be set up.
7. I used tilemap modification to animate the text in the first cutscene state. I haven't decided the dialogue yet.
8. I set up my state machine to include two more levels (originally there was only 1).
9. During the first level you can view the overall map of that level by pressing the B button. There is no timer for this yet, you just have to press the Select Button to go back to the game.
10. attacks for the grievers has been implemented, if you press the A button, you launch a spear and if the spear collides with a griever it kills it. You can use this attack any number of times. If the spear collides with a bush it goes back to the player.
11. THe grievers are kind of moving but they are also having issues with the collision map, this may be the same issue that is causing the player sprite to move through the bushes. Their movements are not as smooth as I would like them to be.

### what still needs to be finished
1. timers have not been set up for anything. 
2. art is obviously not complete.
3. background maps for levels 2 and 3 still need to be completed.
4. To make levels 2 and 3 harder, I want to reduce the amount of time the player has to finish the level (for ex. if level 1 the player has 5 minutes than in level 2 the player will only have 3 minutes), try to make a more complicated maze with each level increase, and add more grievers. I also want to include a new power up in the third level, an anti venom serum that the player can pick up and it saves them from one collision with a griever, I did something similar for HW5 so it should not be too hard to implement.
5. I am still not sure what to do about the lighting, I may not implement this depending on how much time I have left.
6. cutscenes have to be completed.
7. parallax movement has yet to be implemented anywhere.
8. win and lose state bg is still the same as instructions bg

### Known Bugs
- The player and grievers can kind of move through the bushes when they are not supposed to. I still have to figure out a solution for this weird edge case.

### How to Play / Navigate:
> Start:
- start button: starts level one
- select button: goes to instructions state
> Instructions:
- start button: starts level one
> Pause:
- start button: go back to start state
- select button: go back to the game
> Game One:
- select button: pauses the game
- up, down, left, right buttons: moves the player
- b button: goes to view map one state -> able to view maze map
- a button: launches spear
- right shoulder button: after colliding with atleast one heart -> makes grievers disappear
> Cutscene One:
- start button: starts level 2 (nothing happens because level 2 has been initialized)
- select button: goes back to start state
- rshoulder button: goes to win state (just had this for testing, will not be part of final submission)
> Win and Lose:
- start button: goes back to start state