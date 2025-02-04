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

#ifndef CONTACT_LISTENER_H
#define CONTACT_LISTENER_H

#include<iostream>
#include<vector>
#include<Node.h>
#include<m_box2d.h>
#include<CollisionListener.h>

using namespace std;

struct ContactListener : b2ContactListener{
  vector<CollisionListener*> collision_listener_list;

  void AddContactListener(CollisionListener *collision_listener);
  void BeginContact(b2Contact *contact) override ;
  void EndContact(b2Contact *contact) override ;
  virtual void OnBeginContact(b2Contact *contact);
  virtual void OnBeginContact(b2Contact *contact, Node *node_a, Node *node_b);
  virtual void OnEndContact(b2Contact *contact);
  virtual void OnEndContact(b2Contact *contact, Node *node_a, Node *node_b);
};

#endif
