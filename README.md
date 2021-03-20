# MADFIHR - A 3D engine
## Concept
The objective is tu visualize simple 3D forms (made in triangles) with a full hand-written 3D engine (exept for the SDL library used to create the window).
## What has been done so far ?
The program is able to show multiples 3D triangles in perspective and moving around in a 3D space. You can move with ZQSD (position), CTRL/SHIFT (height) and AE (rotation).
## Damn ! I want to try out this very promising 3D engine !
You can ! First you should install the SDL library, then clone this repo and compile it.
(I'm using *gcc main.c -lm $(sdl2-config --cflags --libs) -Wall -g3*)
You also can download *a.out* which is an executable compiled on Ubuntu 20.04, but I haven't tried so far...
## About the code
I'm french so most of the comments are in french. The main.c file contains the whole code. WORLD contains a representation on the world.

4C50D74F92127CD8F941AE4EF484FF91