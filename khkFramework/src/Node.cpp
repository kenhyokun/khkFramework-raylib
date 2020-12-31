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

#include<Node.h>

Node::Node(string _name){
  if(_name == UNAMED_NODE){
    name += to_string(node_count);
    node_count++;
  }
  else{
    name = _name;
  }
}

void Node::_SetParent(Node *node){parent = node;}
void Node::_SetTransformDirection(float up, float right){transform.up = up; transform.right = right;}

void Node::_Rotate(float angle, v2 pivot){
  SetPosition(TransformRotation(Deg2Rad(angle), GetPosition(), pivot));
}

void Node::SetParent(Node *node){
  if(node == nullptr){

    if(parent != nullptr){
      vector<Node*>::iterator it;
      it = std::find(parent->GetChild()->begin(), parent->GetChild()->end(), this);

      parent->_RemoveChild(it);
    }

    parent = nullptr;

  }
  else{

    if(parent != node){
      node->AddChild(this);
    }

  }

}

void Node::AddChild(Node *node){
  if(node->GetParent() != this){

    if(node->GetParent() != nullptr){
      vector<Node*>::iterator it;
      it = std::find(node->GetParent()->GetChild()->begin(), node->GetParent()->GetChild()->end(), node);

      node->GetParent()->_RemoveChild(it);

    } // != nullptr

    node->_SetParent(this);
    child->push_back(node);

  } // != this

}

void Node::_RemoveChild(vector<Node*>::iterator it){
  static_cast<Node*>(*it)->parent = nullptr;
  child->erase(it);
}

void Node::RemoveChild(int index){
  child->at(index)->parent = nullptr;
  child->erase(child->begin() + index);
}

void Node::RemoveChild(string name){
  searched_name = name;
  vector<Node*>::iterator it;
  it = std::find_if(child->begin(), child->end(), _IsSearchedChild);
  _RemoveChild(it);
}

void Node::SetPosition(v2 position){
  float dx = position.x - GetPosition().x;
  float dy = position.y - GetPosition().y;

  transform.position = position;

  if(child->size() > 0){
    for(int i = 0; i < child->size(); ++i){
      if(!GetChild(i)->IsHasRigidBodyComponent()){ // parent node can't move child node if child node have rigid body component
  	GetChild(i)->SetPosition(v2{GetChild(i)->GetPosition().x + dx,
  	      GetChild(i)->GetPosition().y + dy});
      } // !IsHasRigidBodyComponent
    } // for
  } // if

}

void Node::SetRotation(float angle){
  float da = angle - transform.rotation;
  transform.rotation = angle;

  // set direction
  transform.up += da;
  transform.right += da;

  if(child->size() > 0){
    for(int i = 0; i < child->size(); ++i){

      GetChild(i)->SetRotation(transform.rotation);

      // set direction
      GetChild(i)->
  	_SetTransformDirection(GetChild(i)->GetTransform().up + da,
  			       GetChild(i)->GetTransform().right + da);

      // child transformation rotation
      if(!GetChild(i)->is_fixed_transform_rotation){
  	GetChild(i)->_Rotate(da, transform.position);
      }

    } // for
  } // if

}

void Node::PrintAllChildName(){
  if(child->size() > 0){
    for(int i = 0; i < child->size(); ++i){
      cout<<GetChild(i)->name<<endl;
    }
  }
}

void Node::SetRotation(float angle, v2 pivot){
  float _da = angle - transform.rotation;
  _Rotate(_da, pivot);
  SetRotation(angle);
}

string Node::searched_name = "";
Node* Node::_IsSearchedChild(Node *child_node){
  if(child_node->name == searched_name){
    return child_node;
  }
}

Node* Node::GetChild(string name){
  searched_name = name;
  vector<Node*>::iterator it;
  it = std::find_if(child->begin(), child->end(), _IsSearchedChild);
  return *it;
}

void Node::ClearChild(){
  for(int i = 0; i < GetChild()->size(); ++i){
    GetChild(i)->ClearParent();
  }
  child->clear();
}

void Node::ClearParent(){parent = nullptr;}
void Node::SetTransform(CTransform _transform){transform = _transform;}
CTransform Node::GetTransform(){return transform;}
float Node::GetUpDirection(){return transform.up;}
float Node::GetRightDirection(){return transform.right;}
v2 Node::GetPosition(){return transform.position;}
void Node::SetScale(v2 _scale){transform.scale = _scale;}
v2 Node::GetScale(){return transform.scale;}
float Node::GetRotation(){return transform.rotation;}
Node* Node::GetParent(){return parent;}
vector<Node*>* Node::GetChild(){return child;}
Node* Node::GetChild(int index){return child->at(index);}
bool Node::IsHasRigidBodyComponent(){return component_entity.is_has_rigidbody_component;}
bool Node::IsHasDrawableComponent(){return component_entity.is_has_drawable_component;}
