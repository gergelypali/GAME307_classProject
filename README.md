# Basic Game AI Demo
This repository is the class project for Humber College's GAME307 - Artifical Intelligence.<br />
For this project we had to implement working solutions for three Game AI topics:

+ Steering
+ Pathginding
+ Decision Making

A sample codebase was provided to us and I used it for my solution.
My idea was to implement as many different algorithms as possible during this semester, so the game itself is just a shell to showcase the functionalities. It is not a complete game from start to end.<br />
_Used literacy: Artificial Intelligence for Games by Ian Millington_

### Steering
See Scene1 for demo.<br />
There are quite a few functions for steering from the kinematic or dynamic side.<br /> Just a few example:
+ Seek - kinematic / dynamic
+ Arrive - kinematic / dynamic
+ Align - dynamic
+ Wander - kinematic
+ LookWhereYouGoing - dynamic
+ Separation - dynamic
+ ObstacleAvoidance - dynamic

To demonstrate I created one kinematic NPC that chases the player and three dynamic NPCs that are using three types of steering behaviour:
+ steering based on the Player's state <- seek
+ steering based on the obstacles on the map <- obstacle avoidance
+ steering based on other NPCs <- separation

### Pathfinding
See Scene2 for demo.<br />
Three pathfindig algorithms implemented:
+ Breadth first search
+ Greedy search
+ A Star algorithm

To visualize the functionality I created a grid representation of the game screen. Added controls for setting start, end and wall grids so you can build a maze that the pathfinding has to find the one shortest way out.

### Decision Making
See Scene3 for demo.<br />
I implemented a state machine and a decision tree solution. Both of them are classes that should be used to create our own decision making algorithm for the given NPC.<br />
Demonstration contains two NPCs, one with a state machine and one with a decision tree. The used steering functions are similar for these two to showcase that both implementation's result can be the same.
