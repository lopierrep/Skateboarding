# Skateboarding

Hello,

Since I have never used a skateboard, the first thing I did was look for a video on YouTube about skateboarding to be sure that the image I had in my head was correct. 

## Skate (less than 1h)
First, I converted the skateboard model from max to fbx so I could import it into unreal. Then I use the Merge Actors tools to merge all the different parts of the skate in one and change to de Modeling Mode to fix the pivot of the merged skate.

## Skate Movement Component (3h)
For lateral movement I modify the player's rotation based on his speed. For the forward/backward movement I use "AddMovementInput" with the forward vector and make and interpolation of the forward input value to make it smoother.

## Player Animation Blueprint and animations (4h)
I retargeted the animations from mixamo to the UE5 skeleton with an IK Rig that I have from another project. I used the animation blueprint to combine the animations and make the movement as fluid as possible

## Obstacles (1h)
I made a base class in C++ with a mesh and a box component for the collision. Then I made the ObstacleLogicComponent to easily identify an actor as an obstacle by having this component and also to add any possible logic for the obstacle in the future, but for now it is empty.

## Score Component and widget (1h)
Binds to the Jump from the Skate Movement Component and every time the player jumps checks if the player jumps over an obstacle and is it was a valid point and update the score widget.

## Map



Finally, my personal assessment of my performance is an 8 out of 10, I think that the movement and score systems are pretty good, but I am not I'm not sure if you'll like the map. And perhaps with more and better animations the prototype would have looked better.
Christian Lopierre

