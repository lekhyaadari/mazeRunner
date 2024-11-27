# Maze Runner

### What is finished so far
1. all the art is finished
2. sprite setup and implementation is finished (player, grievers, hearts, spear, and letters  numbers for time left)
3. state machine is completely setup
4. all the three levels have been implemented with varying levels of difficulty (less time, more grievers, harder maze, less powerups, etc.)
5. sounds have been added (1 sound plays in the BG as the game progresses and the other is a sound effect tha tplays when the player launches their spear)
6. parallax background has been seup (in the pause state)
7. palette modification is complete (player sprite's colors are modified when they collide with a heart in level 3 when they activate the anti venom).
8. tile modification is done during the cut scenes between the two levels. It simply continues the storyline and acts as a transistion between levels.
9. timers for the levels as well as view map have been set up. Map can only be viewed for 2 seconds.

### what still needs to be finished
1. I want to implemented chasing with the grievers. right now they just rnadomly bouncing off walls, I want their movements to be more impactful and actually create tension within the game.
2. I want to fix the positioning of the hearts, they are fine right now, however they use rand() to determine their initial position, but I think hard coding their locations would be better.
3. in levle 3, the right shoulder button can be pressed multiple times but I want it to only be effective once so I may change this code logic.
4. other than cleaning up this game logic to have the game run more smoothly, and cleaning up the code architechure there is not much left to do for my game.

### Known Bugs
- Not really sure that there are any major ones at the moment.

### How to Play / Navigate:
> Start:
- start button: starts level one
- select button: goes to instructions state
> Instructions:
- start button: starts level one
> Pause:
- start button: go back to start state
- select button: go back to the game
> Game One, Two, and Three:
- select button: pauses the game
- up, down, left, right buttons: moves the player
- b button: goes to view map one state -> able to view maze map
- a button: launches spear
- right shoulder button: after colliding with atleast one heart -> makes grievers disappear
- *(level three only!!)* left shoulder button: activates venom to protect against single collision iwth a griever
> Cutscene One:
- start button: starts level 2
- select button: goes back to start state
- rshoulder button: goes to win state (just had this for testing, will not be part of final submission)
> Cutscene Two:
- start button: starts level 3
- select button: goes back to start state
- rshoulder button: goes to win state (just had this for testing, will not be part of final submission)
> Win and Lose:
- start button: goes back to start state