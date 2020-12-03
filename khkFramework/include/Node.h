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
#include<n_component_derived_check.h>

using namespace std;

#define UNAMED_NODE  "Unamed node"
#define UNTAGGED_NODE "Untagged node"

struct CTransform{
  v2 position = v2_0;
  v2 scale = v2_1;
  float rotation = 0.0f;
  float up = 0.0f;
  float right = 90.0f;
};

static int node_count = 1; // for node auto naming

struct Node{
private:

  struct ComponentEntity{
    bool is_has_rigidbody_component = false;
    bool is_has_drawable_component = false;
    Component::DrawableType drawable_type = Component::NONE;
    int *draw_sort_index = nullptr; // drawable component index on scene manager sort component
  };

  CTransform transform;
  Node *parent = nullptr;
  vector<Node*> *child = new vector<Node*>();

protected:
  static string searched_name;

  void _SetParent(Node *node);
  void _SetTransformDirection(float up, float right);
  void _Rotate(float angle, v2 pivot); // transformation rotation
  void _RemoveChild(vector<Node*>::iterator it);
  static Node* _IsSearchedChild(Node *child_node);

public:
  ComponentEntity component_entity;
  string name = UNAMED_NODE;
  string tag = UNTAGGED_NODE;
  bool is_fixed_transform_rotation = false;

  template<typename T>
    static map<Node*, T> component_map;

  template<typename T>
    static typename map<Node*, T>::iterator component_map_it;

  Node(string _name = UNAMED_NODE);
  void AddChild(Node *node);
  void RemoveChild(int index); // remove child by index
  void RemoveChild(string name); // remove child by name

  template<typename T>
  inline T AddComponent(T component){

    if(Component::IsDerivedDrawable(*component)){
      if(Component::IsDerivedSpriteRenderer(*component)){
	component_entity.drawable_type = Component::SPRITE_RENDERER;
	component_entity.draw_sort_index = new int[1]();
      }
      if(Component::IsDerivedAnimator(*component)){
	component_entity.drawable_type = Component::ANIMATOR;
	component_entity.draw_sort_index = new int[1]();
      }
      if(Component::IsDerivedAtlasAnimator(*component)){
	component_entity.drawable_type = Component::ATLAS_ANIMATOR;
	component_entity.draw_sort_index = new int[1]();
      }
      if(Component::IsDerivedTilemap(*component)){
	component_entity.drawable_type = Component::TILEMAP;
	component_entity.draw_sort_index = new int[1]();
      }
      if(Component::IsDerivedTMXMap(*component)){
	component_entity.drawable_type = Component::TMXMAP;
	// initilize draw_sort_index on _OnAttach function.
      }

      component_entity.is_has_drawable_component = true;
    }

    if(Component::IsDerivedRigidBody(*component)){
      component_entity.is_has_rigidbody_component = true;
    }

    component->SetNode(this);
    component->Attach();
    component_map<T>.insert(pair<Node*, T>(this, component));
    return component_map<T>.at(this);
  }

  template<typename T>
  inline T GetComponent(){
    return component_map<T>.at(this);
  }

  template<typename T>
  static bool IsHas(Node* node){

    component_map_it<T> =
      component_map<T>.find(node);

    if(component_map_it<T> != component_map<T>.end()){
      return true;
    }

    return false;
  }

  template<typename T>
  inline void RemoveComponent(){
    if(IsHas<T>(this)){
      component_map<T>.erase(this);
      T component;
      if(Component::IsDerivedDrawable(*component)) component_entity.is_has_drawable_component = false;
      if(Component::IsDerivedRigidBody(*component)) component_entity.is_has_rigidbody_component = false;
    }
  }

  void SetTransform(CTransform _transform);
  CTransform GetTransform();
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
  void ClearChild();
  vector<Node*>* GetChild(); // get child vector
  Node* GetChild(int index); // get child by index
  Node* GetChild(string name); // get child by name
  bool IsHasRigidBodyComponent();
  bool IsHasDrawableComponent();
  void PrintAllChildName();
};

template<typename T>
map<Node*, T> Node::component_map;

template<typename T>
typename map<Node*, T>::iterator Node::component_map_it;

#endif
