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

Component::BoxCollider::BoxCollider(float width, float height){
  box_collision_shape = new b2PolygonShape();
  box_collision_shape->SetAsBox(width * 0.5f, height * 0.5f);
}

void Component::RigidBody::OnAttach(){
  b2BodyDef body_def;
  body_def.type = DYNAMIC; 
  body_def.position.Set(node->GetPosition().x, node->GetPosition().y);
  body = world.CreateBody(&body_def);

  if(Node::component_map<box_collider>.size() > 0){
    if(node->GetComponent<box_collider>() == NULL){
      cout<<"you must add Collider component first"<<endl;
    }
    else{
      cout<<"Collider component found..."<<endl;
      b2FixtureDef fixture_def;
      fixture_def.shape = node->GetComponent<box_collider>()->box_collision_shape;
      fixture_def.density = 1.0f;
      fixture_def.friction = 0.3f;
      fixture = body->CreateFixture(&fixture_def);
    }
  }
  else{
    cout<<"you must add Collider component first"<<endl;
  }

}

void Component::RigidBody::Step(){
  node->SetPosition(Vector2{body->GetPosition().x, body->GetPosition().y});
  node->SetRotation(Rad2Deg(body->GetAngle()));
}

void Component::RigidBody::SetBodyType(b2BodyType type){body->SetType(type);}
b2Body* Component::RigidBody::GetBody(){return body;}

void B2D::Attach(Node *node){
  node_list.push_back(node);
}

void B2D::Step(){
  world.Step(time_step, velocity_iterations, position_iterations);

  for(int i = 0; i < node_list.size(); i++){
    node_list.at(i)->GetComponent<Component::rigid_body>()->Step();
  } 
}
