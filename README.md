# Phelsuma

This project is meant to be a set of utilities & maybe some kind of "engine" for computer games. It is my ongoing effort with discovering many things, mostly:

* OpenGL and computer graphics theory in general. I had some experience with computer vision & computational photography before, which can be helpful here.
* Modern C++ tooling & the language itself. I have very shallow experience with C++, mostly using it as 'C with STL'.
* Some occasions to do optimising work - I really enjoy reading about low-level optimalisation like time/spatial locality and such. Game engine is propably an ideal project for such optimalisations.
* Implement some SIGGRAPH papers maybe? Never had occasion to work with lighting and stuff.
* Implement simple games with it - some 2D games like Arkanoid / Space Invaders and maybe something in 3D then.
* Discover some algorithms which I heard about but never had occasion to implement - including quad trees, 'generic' AI algorithms and much more.
* Create some simple tooling around typical computer game - or include support for some known ones. Like loading maps from Hammer (Steam) for example would be a huge deal for me.
* Audio and algorithms around it - like altering sound based on its position and so on.
* Hands-on experience with creating games! :)

## Installation:

This project uses CMake to build itself. In order to compile the code you need to set these, required, variables:

* `PHELSUMA_GLAD_SRC_PATH` - path to `glad.c` file which can be generated for your target OGL version [here](http://glad.dav1d.de/).
* `PHELSUMA_GLAD_INCLUDE_PATH` - path to include files which are from the GLAD package.
* `PHELSUMA_SCE_VECTORMATH_PATH` - path to Sony Computer Entertainment vector math library - it can be taken from [here](https://github.com/erwincoumans/sce_vectormath).

## Examples:

Since testing the game engine without a dynamic application is pointless, I'll try to include some examples in the codebase. They can be disabled from building using `PHELSUMA_BUILD_EXAMPLES` option.

## License:

MIT. See LICENSE file.