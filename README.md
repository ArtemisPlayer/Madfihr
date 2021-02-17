# MADFIHR - A 3D engine
## Concept
The objective is tu visualize simple 3D forms (made in triangles) with a full hand-written 3D engine (exept for the SDL library used to create the window).
## What has been done so far ?
The program is able to show multiples 3D triangles in Orthographic projection (so not using perspective yet) and moving around in a 3D space.
## What's next ?
The engine will support perspective view.
Code will be restructured (Indeed, not using .h files is not a good idea).
The trianles will support color.
The triangles will be able to be displayed one above others.
## Damn ! I want to try out this very promising 3D engine !
You can ! First you should install the SDL library, then clone this repo and compile it.
(I'm using *gcc main.c -lm $(sdl2-config --cflags --libs) -Wall*)
You also can download *a.out* which is an executable compiled on Ubuntu 20.04, but I haven't tried so far...
