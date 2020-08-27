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

#include<Node.h>

Node::Node(string _name){
  if(_name == ""){
    name += to_string(node_count);
    node_count++;
  }
  else{
    name = _name;
  }
}

void Node::ResetChildIndex(int start_index){
  for(int i = start_index; i < child.size(); i++){
    child.at(i)->index_on_parent = i;
  }
}

void Node::_SetParent(Node *node){parent = node;}
Transform_node Node::_GetTransform(){return transform;}
void Node::_SetTransformDirection(float up, float right){transform.up = up; transform.right = right;}

void Node::_Rotate(float angle, Vector2 pivot){
  float x = 0.0f;
  float y = 0.0f;
  float px = pivot.x;
  float py = pivot.y;
  float tx = transform.position.x;
  float ty = transform.position.y;

  x =
    (tx * cos(Deg2Rad(angle)) ) -
    (ty * sin(Deg2Rad(angle)) ) -
    (px * cos(Deg2Rad(angle)) ) +
    (py * sin(Deg2Rad(angle)) ) +
    px; 

  y =
    (tx * sin(Deg2Rad(angle)) ) +
    (ty * cos(Deg2Rad(angle)) ) -
    (px * sin(Deg2Rad(angle)) ) -
    (py * cos(Deg2Rad(angle)) ) +
    py; 

  SetPosition(Vector2{x, y}); 

}

void Node::SetParent(Node *node){
  if(parent != node){
    node->AddChild(this);
  }
}

void Node::AddChild(Node *node){
  if(node->GetParent() != this){

    if(node->GetParent() != NULL){
      node->GetParent()->RemoveChild(node->index_on_parent);

    } // != NULL

    node->index_on_parent = child.size();
    node->_SetParent(this);
    child.push_back(node);

  } // != this

}

void Node::RemoveChild(int index){
  child.erase(child.begin() + index);
  ResetChildIndex(index);
}

void Node::SetPosition(Vector2 position){
  float dx = position.x - GetPosition().x;
  float dy = position.y - GetPosition().y;

  transform.position = position;

  if(child.size() > 0){
    for(int i = 0; i < child.size(); i++){
      GetChild(i)->SetPosition(Vector2{GetChild(i)->GetPosition().x + dx,
	    GetChild(i)->GetPosition().y + dy});

    } // for
  } // if

}

void Node::SetRotation(float angle){
  float da = angle - transform.rotation;
  transform.rotation = angle;

  // set direction
  transform.up += da;
  transform.right += da;

  if(child.size() > 0){
    for(int i = 0; i < child.size(); i++){


      GetChild(i)->SetRotation(transform.rotation);

      // set direction
      GetChild(i)->
	_SetTransformDirection(GetChild(i)->_GetTransform().up + da,
			       GetChild(i)->_GetTransform().right + da);

      // child transformation rotation
      if(!GetChild(i)->is_fixed_transform_rotation){
	GetChild(i)->_Rotate(da, transform.position);
      }

    } // for
  } // if

}

void Node::SetRotation(float angle, Vector2 pivot){
  float _da = angle - transform.rotation;
  _Rotate(_da, pivot);
  SetRotation(angle);
}

void Node::ClearParent(){parent = NULL;}
void Node::SetTransform(Transform_node _transform){transform = _transform;}
float Node::GetUpDirection(){return transform.up;}
float Node::GetRightDirection(){return transform.right;}
Vector2 Node::GetPosition(){return transform.position;}
void Node::SetScale(Vector2 _scale){transform.scale = _scale;}
Vector2 Node::GetScale(){return transform.scale;}
float Node::GetRotation(){return transform.rotation;}
Node* Node::GetParent(){return parent;}
vector<Node*> Node::GetChild(){return child;}
Node* Node::GetChild(int index){return child.at(index);}
