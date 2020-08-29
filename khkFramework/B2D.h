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

#ifndef B2D_H
#define B2D_H

#include<box2d/box2d.h>
#include<Component.h>

typedef b2ContactListener ContactListener;

static b2Vec2 gravity(0.0f, 10.0f);
static b2World world(gravity);
static float time_step = 1.0f / 60.0f;
static int32 velocity_iterations = 6;
static int32 position_iterations = 2;

/*
  Available namespace:
  - Component
  - B2D
*/

namespace Component{

  /*
    Available component:
    - BoxCollider
    - CircleCollider
    - RigidBody
  */


  /*
    BoxCollider Component
  */
  typedef struct BoxCollider : BaseComponent{
    b2PolygonShape *box_collision_shape;
    BoxCollider(float width, float height);
  } *box_collider;


  /*
    CircleCollider Component
  */
  typedef struct CircleCollider : BaseComponent{
    b2CircleShape *circle_collision_shape;
    CircleCollider(float radius);
    float GetRadius();
  } *circle_collider;


  /*
    CapsuleCollider Component
  */
  typedef struct CapsuleCollider : BoxCollider, CircleCollider{
    CapsuleCollider(float height, float radius);
  protected:
  } *capsule_collider;


  /*
    RigidBody Component
  */
  typedef struct RigidBody : BaseComponent{
    static const b2BodyType STATIC = b2_staticBody;
    static const b2BodyType DYNAMIC = b2_dynamicBody;
    static const b2BodyType KINEMATIC = b2_kinematicBody;

    void Step();

    b2Vec2 GetBodyPosition();
    float GetBodyRadian();
    void SetBodyType(b2BodyType type);
    void SetFixedRotation(bool is_fixed = true);
    // void SetFixture(b2FixtureDef fixture_def);
    b2Body* GetBody();

  protected:
    b2FixtureDef fixture_def;
    b2Body *body;
    b2Fixture *fixture;

    void _OnAttach() override;
    bool _SetCollider(int state = 0); // search and set collider shape

  } *rigid_body; 

}; // Component namespace


namespace B2D{
  typedef b2Body Body;
  typedef b2World World;
  
  void SetContactListener(b2ContactListener *contact_listener);
  void Step();

}; // B2D namespace

#endif
