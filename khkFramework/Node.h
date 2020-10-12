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

#ifndef NODE_H
#define NODE_H

#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<m_raylib.h>
#include<CMath.h>

using namespace std;

struct CTransform{
  v2 position = v2_0;
  v2 scale = v2_1;
  float rotation = 0.0f;
  float up = 0.0f;
  float right = 90.0f;
};

static int node_count = 1; // for auto node naming

class Node{
  CTransform transform;
  Node *parent = nullptr;
  vector<Node*> *child = new vector<Node*>();

  template<typename T>
    static map<Node*, T> component_map;


protected:
  bool is_has_rigid_body_component = false;
  static string comp_name;

  void _SetParent(Node *node);
  CTransform _GetTransform();
  void _SetTransformDirection(float up, float right);
  void _Rotate(float angle, v2 pivot); // transformation rotation
  void _RemoveChild(vector<Node*>::iterator it);
  static Node* _IsSearchedChild(Node *child_node);

public:
  const string unamed_node_name = "Unamed Node"; // give this name to node name if node name not set
  const string untagged_node_tag = "Untagged Node"; // give this tag to node tag if node tag not set
  string name = unamed_node_name;
  string tag = untagged_node_tag;
  bool is_fixed_transform_rotation = false;

  template<typename T>
    static typename map<Node*, T>::iterator component_map_it;

  Node(string _name = "");
  void AddChild(Node *node);
  void RemoveChild(int index); // remove child by index

  template<typename T>
  inline T AddComponent(T component){
    component->node = this;
    component->Attach();
    component_map<T>.insert(pair<Node*, T>(this, component));
    return component_map<T>.at(this);
  }

  template<typename T>
  inline T GetComponent(){
    return component_map<T>.at(this);
  }

  void SetTransform(CTransform _transform);
  float GetUpDirection();
  float GetRightDirection();
  void SetPosition(v2 position);
  v2 GetPosition();
  void SetScale(v2 scale);
  v2 GetScale();
  void SetRotation(float angle);
  void SetRotation(float angle, v2 pivot);
  float GetRotation();
  void SetParent(Node *node);
  Node* GetParent();
  void ClearParent();
  vector<Node*>* GetChild(); // get child vector
  Node* GetChild(int index); // get child by index
  Node* GetChild(string name); // get child by name
  void HasRigidBodyComponent();
  bool IsHasRigidBodyComponent();
  void PrintAllChildName();
};

template<typename T>
map<Node*, T> Node::component_map;

template<typename T>
typename map<Node*, T>::iterator Node::component_map_it;

#endif
