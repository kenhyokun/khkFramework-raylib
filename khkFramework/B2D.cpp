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

/*
  BoxCollider Component
*/
Component::BoxCollider::BoxCollider(float width, float height){
  box_collision_shape = new b2PolygonShape();
  box_collision_shape->SetAsBox(width * 0.5f, height * 0.5f);
}


/*
  CircleCollider Component
*/
Component::CircleCollider::CircleCollider(float radius){
  circle_collision_shape = new b2CircleShape();
  circle_collision_shape->m_radius = radius;
}


/*
  RigidBody Component
*/
void Component::RigidBody::OnAttach(){
  b2BodyDef body_def;
  body_def.type = DYNAMIC; 
  body_def.position.Set(node->GetPosition().x, node->GetPosition().y);
  body = world.CreateBody(&body_def);

  if(!_SetCollider()){
    cout<<"you must add Collider component first"<<endl;
  }

}

bool Component::RigidBody::_SetCollider(int state){

  switch(state){

  case 0: // box collider

    Node::component_map_it<box_collider> =
      Node::component_map<box_collider>.find(node);

    if(Node::component_map_it<box_collider> !=
       Node::component_map<box_collider>.end()){

      fixture_def.shape = node->GetComponent<box_collider>()->box_collision_shape;
      fixture_def.density = 1.0f;
      fixture_def.friction = 0.3f;
      fixture = body->CreateFixture(&fixture_def);

      B2D::Attach(node);

      return true;
    }
    else{
      _SetCollider(1);
    }

    break;

  case 1: // circle collider

    Node::component_map_it<circle_collider> =
      Node::component_map<circle_collider>.find(node);

    if(Node::component_map_it<circle_collider> !=
       Node::component_map<circle_collider>.end()){

      fixture_def.shape = node->GetComponent<circle_collider>()->circle_collision_shape;
      fixture_def.density = 1.0f;
      fixture_def.friction = 0.3f;
      fixture = body->CreateFixture(&fixture_def);

      B2D::Attach(node);

      return true;

    }
    else{
      // _SetCollider(2);
      return false;
    }

    break;

    return false;

  } // switch

}

void Component::RigidBody::Step(){
  node->SetPosition(Vector2{body->GetPosition().x, body->GetPosition().y});
  node->SetRotation(Rad2Deg(body->GetAngle()));
}

void Component::RigidBody::SetBodyType(b2BodyType type){body->SetType(type);}
void Component::RigidBody::SetFixedRotation(bool is_fixed){body->SetFixedRotation(is_fixed);}
b2Body* Component::RigidBody::GetBody(){return body;}



void B2D::Attach(Node *node){
  node_list.push_back(node);
}

void B2D::SetContactListener(b2ContactListener *contact_listener){
  world.SetContactListener(contact_listener);
}

void B2D::Step(){
  world.Step(time_step, velocity_iterations, position_iterations);

  for(int i = 0; i < node_list.size(); i++){
    node_list.at(i)->GetComponent<Component::rigid_body>()->Step();
  } 

  for(b2Contact* c = world.GetContactList(); c; c = c->GetNext()){
    // cout<<"duh... contact..."<<endl;
    // cout<<c->GetFixtureB()->GetType()<<endl;
    // cout<<c->GetFixtureB()->GetShape()->m_radius<<endl;
  }


}
