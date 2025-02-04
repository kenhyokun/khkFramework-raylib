/*
  license under zlib license
  Copyright (C) 2020-2021 Kevin Haryo Kuncoro

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.
  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
  claim that you wrote the original software. If you use this software
  in a product, an acknowledgment in the product documentation would be
  appreciated but is not required.

  2. Altered source versions must be plainly marked as such, and must not be
  misrepresented as being the original software.

  3. This notice may not be removed or altered from any source distribution.

  Kevin Haryo Kuncoro
  kevinhyokun91@gmail.com
*/

#ifndef CCAMERA_H
#define CCAMERA_H

#include<iostream>
#include<m_raylib.h>
#include<Node.h>

using namespace std;

struct CCamera{
  Camera2D camera;
  int width = 0;
  int height = 0;
  Node *target =  nullptr;

  CCamera (int _width, int _height);

  void SetOffset(int offset_x, int offset_y);
  void SetOffsetToCenter();
  void Rotate(float angle);
  void Zoom(int _zoom);
  void AttachTo(Node *node);
  void Detach();
  void Follow();
};

#endif
