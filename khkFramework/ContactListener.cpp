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

#include<ContactListener.h>

void ContactListener::AddCollisionListener(CollisionListener *collision_listener){
  collision_listener_list.push_back(collision_listener);
}

void ContactListener::BeginContact(b2Contact *contact){
  Node *node_a = static_cast<Node*>
    (contact->GetFixtureA()->GetBody()->GetUserData());

  Node *node_b = static_cast<Node*>
    (contact->GetFixtureB()->GetBody()->GetUserData());

  /*
    FIXME [Kevin]: there is no circle collision contact...
  */

  for(int i = 0; i < collision_listener_list.size(); i++){

    if(collision_listener_list.at(i)->GetNode() != nullptr){
      
      if(node_b == collision_listener_list.at(i)->GetNode()){
	collision_listener_list.at(i)->is_exit = false;
	collision_listener_list.at(i)->contact = contact;
	collision_listener_list.at(i)->OnCollisionEnter(node_a);

	cout<<contact->GetManifold()->type<<endl;
      }

      if(collision_listener_list.at(i)->contact != nullptr && 
	 !collision_listener_list.at(i)->contact->IsTouching()
	 ){

	if(!collision_listener_list.at(i)->is_exit){
	  cout<<"not touching any more..."<<endl;
	  collision_listener_list.at(i)->is_exit = true;
	}

      }

    } // node != nullptr
  } // for


  OnBeginContact(contact);
}

void ContactListener::OnBeginContact(b2Contact *contact){}
