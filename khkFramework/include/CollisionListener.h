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

#ifndef COLLISION_LISTENER_H
#define COLLISION_LISTENER_H

#include<Node.h>
#include<m_box2d.h>

struct CollisionListener{
  // bool is_exit = false;
  
  CollisionListener(Node *_node = nullptr){node = _node;}
  inline void AddCollisionListener(Node *_node){node = _node;}
  virtual void OnCollisionEnter(Node *collision_node) = 0;
  virtual void OnCollisionExit(Node *collision_node) = 0;

  inline Node* GetNode(){return node;}
  
protected:
  Node *node = nullptr;
};

#endif
