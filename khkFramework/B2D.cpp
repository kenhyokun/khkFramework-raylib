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

#include<B2D.h>

ColliderShape Component::ColliderBaseComponent::GetColliderShape(){return collider_shape;}
v2 Component::ShapeColliderBaseComponent::GetSize(){return v2{width, height};}
float Component::ShapeColliderBaseComponent::GetRadius(){return radius;}
float Component::ShapeColliderBaseComponent::GetWidth(){return GetSize().x;}
float Component::ShapeColliderBaseComponent::GetHeight(){return GetSize().y;}
int32 Component::VerticeColliderBaseComponent::GetVerticeCount(){return v_count;}

void Component::VerticeColliderBaseComponent::_OnAttach(){
  vertice = new b2v2[vertice_list.size()];
  for(int i = 0; i < vertice_list.size(); i++){

    v2 rel_position = v2{vertice_list.at(i).x - node->GetPosition().x,
			 vertice_list.at(i).y - node->GetPosition().y };

    vertice[i].Set(rel_position.x, rel_position.y);
    vertice_list.at(i) = rel_position;
  }
}


/*
  BoxCollider Component
*/
Component::BoxCollider::BoxCollider(float _width, float _height){
  collider_shape = ColliderShape::BOX;
  width = _width;
  height = _height;
  box_shape = new b2PolygonShape();
  box_shape->SetAsBox(width * 0.5f, height * 0.5f);
}


/*
  CircleCollider Component
*/
Component::CircleCollider::CircleCollider(float _radius){
  collider_shape = ColliderShape::CIRCLE;
  radius = _radius;
  circle_shape = new b2CircleShape();
  circle_shape->m_radius = radius;
}


/*
  CapsuleCollider Component
*/
Component::CapsuleCollider::CapsuleCollider(float _height, float _radius){
  collider_shape = ColliderShape::CAPSULE;
  width = _radius * 2; // debug draw width
  height = _height; if(height <= 0) height = 1;
  radius = _radius;
  circle_shape = new b2CircleShape();
  circle_shape->m_radius = radius;
  box_shape = new b2PolygonShape();
  box_shape->SetAsBox(radius, height * 0.5f); // use radius as width for box fixture width
}


/*
  PolygonCollider Component
*/
Component::PolygonCollider::PolygonCollider(vector<v2> _vertice_list){
  collider_shape = ColliderShape::POLYGON;
  vertice_list = _vertice_list;
  v_count = vertice_list.size();
  polygon_shape = new b2PolygonShape();
}

void Component::PolygonCollider::_OnAttach(){
  Component::VerticeColliderBaseComponent::_OnAttach();
  polygon_shape->Set(vertice, v_count);
  vertice_list.clear();
}


/*
  EdgeCollider Component
*/
Component::EdgeCollider::EdgeCollider(vector<v2> _vertice_list){
  collider_shape = ColliderShape::EDGE; 
  vertice_list = _vertice_list;
  v_count = _vertice_list.size();
  chain_shape = new b2ChainShape();
}

Component::EdgeCollider::EdgeCollider(v2 _vertice){
  collider_shape = ColliderShape::EDGE; 
  vertice_list.push_back(_vertice);
  v_count = vertice_list.size();
}

void Component::EdgeCollider::_OnAttach(){
  Component::VerticeColliderBaseComponent::_OnAttach();

  if(v_count > 2){ // create chain shape
    chain_shape->CreateChain(vertice, v_count, vertice[0], vertice[v_count - 1]);
  }
  else{ // create edge shape
    edge_shape = new b2EdgeShape();

    if(v_count < 2){
      vertice[1] = b2v2_0;
      v_count++;
    }

    edge_shape->SetTwoSided(vertice[0], vertice[1]);
  } // else
  vertice_list.clear();
}


/*
  RigidBody Component
*/
void Component::RigidBody::_OnAttach(){
  b2BodyDef body_def;
  body_def.type = DYNAMIC; 
  body_def.position.Set(node->GetPosition().x, node->GetPosition().y);
  body = world->CreateBody(&body_def);

  if(_IsGetCollider()){
    body->SetUserData(node);
  }
  else{
    cout<<"you must add collider component at "<<node->name<<" first!"<<endl;
  }
}

bool Component::RigidBody::_IsGetCollider(int state){
  switch(state){

  case 0: // box collider

    Node::component_map_it<box_collider> =
      Node::component_map<box_collider>.find(node);

    if(Node::component_map_it<box_collider> !=
       Node::component_map<box_collider>.end()){

      box_collider collider = Node::component_map_it<box_collider>->second;
      fixture = body->CreateFixture(collider->box_shape, 1.0f);

      // fixture_data _fixture_data = new FixtureData();
      // _fixture_data->v_count = collider->box_shape->m_count;
      // _fixture_data->size = collider->GetSize();
      // fixture->SetUserData(_fixture_data);

      delete collider;
      return true;
    }
    else{
      _IsGetCollider(1);
    }

    break;

  case 1: // circle collider

    Node::component_map_it<circle_collider> =
      Node::component_map<circle_collider>.find(node);

    if(Node::component_map_it<circle_collider> !=
       Node::component_map<circle_collider>.end()){

      circle_collider collider = Node::component_map_it<circle_collider>->second;
      fixture = body->CreateFixture(collider->circle_shape, 1.0f);
      // fixture->SetUserData(new FixtureData());

      delete collider;
      return true;
    }
    else{
      _IsGetCollider(2);
    }

    break;

  case 2: // capsule collider

    Node::component_map_it<capsule_collider> =
      Node::component_map<capsule_collider>.find(node);

    if(Node::component_map_it<capsule_collider> !=
       Node::component_map<capsule_collider>.end()){

      capsule_collider collider =
	Node::component_map_it<capsule_collider>->second;

      // upper circle
      collider->circle_shape->m_p = b2v2{0, -collider->GetHeight() / 2};
      fixture = body->CreateFixture(collider->circle_shape, 1.0f);
      // fixture->SetUserData(new FixtureData{b2v2{0, -collider->GetHeight() / 2}});

      // mid box
      fixture = body->CreateFixture(collider->box_shape, 1.0f);
      // fixture_data _fixture_data = new FixtureData();
      // _fixture_data->v_count = collider->box_shape->m_count;
      // _fixture_data->size = collider->GetSize();
      // fixture->SetUserData(_fixture_data);

      // bottom circle
      collider->circle_shape->m_p = b2v2{0, collider->GetHeight() / 2};
      fixture = body->CreateFixture(collider->circle_shape, 1.0f);
      // fixture->SetUserData(new FixtureData{b2v2{0, collider->GetHeight() / 2}});

      delete collider;
      return true;
    }
    else{
      _IsGetCollider(3);
    }

    break;

  case 3: // polygon collider

    Node::component_map_it<polygon_collider> =
      Node::component_map<polygon_collider>.find(node);

    if(Node::component_map_it<polygon_collider> !=
       Node::component_map<polygon_collider>.end()){

      polygon_collider collider = Node::component_map_it<polygon_collider>->second;
      fixture = body->CreateFixture(collider->polygon_shape, 1.0f);

      // fixture_data _fixture_data = new FixtureData();
      // _fixture_data->v_count = collider->polygon_shape->m_count;
      // _fixture_data->vertice = collider->vertice;
      // fixture->SetUserData(_fixture_data);

      delete collider;
      return true;
    }
    else{
      _IsGetCollider(4);
    }
    break;

  case 4: // edge collider

    Node::component_map_it<edge_collider> =
      Node::component_map<edge_collider>.find(node);

    if(Node::component_map_it<edge_collider> !=
       Node::component_map<edge_collider>.end()){

      edge_collider collider = Node::component_map_it<edge_collider>->second;

      // fixture_data _fixture_data = new FixtureData();
      if(collider->GetVerticeCount() > 2){
      fixture = body->CreateFixture(collider->chain_shape, 1.0f);
      // _fixture_data->v_count = collider->chain_shape->m_count;
      }
      else{
      fixture = body->CreateFixture(collider->edge_shape, 1.0f);
      // _fixture_data->v_count = collider->GetVerticeCount();
      }
      // _fixture_data->vertice = collider->vertice;
      // fixture->SetUserData(_fixture_data);

      delete collider;
      return true;
    }
    else{
      return false;
    }
    break;

    return false;

  } // switch

}

void Component::RigidBody::Step(){
  node->SetPosition(v2{body->GetPosition().x, body->GetPosition().y});
  node->SetRotation(Rad2Deg(body->GetAngle()));
}

b2v2 Component::RigidBody::GetBodyPosition(){return body->GetPosition();}
float Component::RigidBody::GetBodyRadian(){return body->GetAngle();}
void Component::RigidBody::SetBodyType(b2BodyType type){body->SetType(type);}
void Component::RigidBody::SetFixedRotation(bool is_fixed){body->SetFixedRotation(is_fixed);}
b2Body* Component::RigidBody::GetBody(){return body;}



void B2D::Init(ContactListener *contact_listener){
  if(contact_listener != nullptr){
    world->SetContactListener(contact_listener);
  }

  world->SetDebugDraw(&debug_draw);
}

void B2D::Step(){
  world->Step(time_step, velocity_iterations, position_iterations); 

  for(b2Body *body = world->GetBodyList(); body; body = body->GetNext()){
    static_cast<Node*>(body->GetUserData())->GetComponent<Component::rigid_body>()->Step();
  }

}

void B2D::DebugDraw(float opacity , Color color1, Color color2){
  debug_draw.SetFlags(b2Draw::e_shapeBit);
  world->DebugDraw();
}
