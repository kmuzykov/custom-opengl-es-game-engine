custom-opengl-es-game-engine
============================

This repository contains my results of learning and experimenting with OpenGL ES 2.0
  
##Contents:
### /Blender
Blender models, UV unwraps and .OBJ files of Bowling ball, Pins and Bowling lane used in Bowling project. All models done by me, and I have like 10 days experience, so take this into account.

### /Bowling
iOS Bowling game created using custom game engine. 
Some notes:
* The iOS part consists of only small amount of the Objective-C code required to switch to C++, the rest is written in C++.
* Currently there is only one test scene where the bowling ball is thrown and hits some pins, so it is hard to call it a game right now :)

### /Engine
Custom game engine I've created while learning OpenGL ES. You defenitelly shouldn't think of using it **anywhere**, but it might be helpful if you're learning OpenGL ES and stuck at something.

Notes:
* I was very much inspired by cocos2d, so there are nodes, scenes and etc.
* RenderableNodes use component system. You create a shader or use one of created by me (remember I'm still learning) and then you add components to your renderable node (texture module, lightning and etc.). The only thing that modules currently do are passing attributes and uniforms to shader.
* There are still a lot to be done to call it a game engine. There is currently no user input handling, no labels and etc., but at least it can render .OBJ models, position them in scene, do a basic lightening (per-vertex) and very-very basic physics engine integration.

### /bullet-2.82-r2704
Bullet Physics engine used in bowling game. Please see LICENSE, AUTORS and other documents inside the folder. You can find more at http://bulletphysics.org/


## Reason

I didn't want to upload it in this state, but it looks I won't be able to work on this anywhere soon since I have a lot of projects to work on. So I thought it might be useful to someone. 

I'll try to update it as soon as I'll have some free time.

###I hope it will be useful to someone!