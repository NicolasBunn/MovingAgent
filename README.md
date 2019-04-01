Hello

This is the Autonomously Moving Actor from my blog : https://nicolasbun.blogspot.com/2019/04/c-opengl-autonomously-moving-actor.html

To launch the application you need to create an "/ExternalRessources/" for Assimp, GLEW , GLFW and Freetype which are 3rd party are necessary
for this project

So on the root of the project "MovingAgent-master" create a repository "ExternalRessources" where you unzip GLEW Assimp GLEW et Freetype.
Launch visual studio and build the project should run 

On the scene, the red triangle is the player, the green triangle is the ia actor, the blue square is a wall and the the white dots are waypoint

Here is the command to move the player actor 

Z : Move Forward
S : Move Backward
Q : Rotate Left 
D : Rotate Right

The command to command the IA Actor

W : Idle
X : Wander
C : Go to the player position
V : Pursuit
B : Follow Path : the ia actor will follow white waypoint from the most left to the most right


