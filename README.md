<img align="center" src="https://github.com/kenhyokun/khkFramework-raylib/blob/master/github_resources/logo/khkFramework-raylib-logo.png" width=512>

Experimental C/C++ 2D game framework with **[raylib][1]** inspired by popular game engine like **[Ogre3D][2]**, **[libGDX][3]** and Unity3D.
</br>
**Note: Build and tested on Ubuntu 18.04. No cross platform makefile for now.**

Current progress:
</br>
<img align="center" src="https://github.com/kenhyokun/khkFramework-raylib/blob/master/github_resources/curr_progress.gif" width=712>

# Features:
  - Load exported **.tmx** file from **[Tiled map editor](https://www.mapeditor.org/)** for tile mapping. (only orthogonal view for now)
  - Load exported **.atlas** file from **[gdx texture packer](https://github.com/crashinvaders/gdx-texture-packer-gui)**. (only load image for now, animation on proggress)
  - box2d physics engine. (only box, circle, capsule, polygon, and edge collision for now)

# Third party library:
  - Core / graphics engine:
    - raylib v3.0.0 (https://github.com/raysan5/raylib)
  - Physics engine:
    - box2d v2.4.0 (https://github.com/erincatto/box2d)
  - File parser:
    - tinyxml2 (https://github.com/leethomason/tinyxml2) 
    - libconfini v1.14.1 (https://github.com/madmurphy/libconfini/)
    - json (https://github.com/nlohmann/json)

# Todo for version 1.0.0 release:
  - Add sample project.
  - Add basic collision shape detection (rectangle, circle, point).
  - Add capsule collider, edge collider and contact callback function with box2d.
  - Node need to optimised, especially when removing child node.
  - Beta testing

#
<p>
Kevin Haryo Kuncoro </br>
kevinhyokun91@gmail.com </br>
2020 
</p>

[1]: https://github.com/raysan5/raylib
[2]: https://github.com/OGRECave/ogre
[3]: https://github.com/libgdx/libgdx
