/*
  license under zlib license
  Copyright (C) 2020 Kevin Haryo Kuncoro

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

#include<CCamera.h>

CCamera::CCamera (int _width, int _height){
  camera = {0};
  camera.offset = v2{0, 0};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;
  width = _width;
  height = _height;
}

void CCamera::SetOffset(int offset_x, int offset_y){
  camera.offset = v2{(float)offset_x, (float)offset_y};
}

void CCamera::SetOffsetToCenter(){
  SetOffset(width / 2, height / 2);
}

void CCamera::Rotate(float angle){camera.rotation = angle;}
void CCamera::Zoom(int _zoom){camera.zoom = _zoom;}
void CCamera::AttachTo(Node *node){target = node;}
void CCamera::Detach(){target = nullptr;}
void CCamera::Follow(){
  if(target != nullptr){
    camera.target = target->GetPosition();
  }
}
