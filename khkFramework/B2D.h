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

#define vec2_zero b2Vec2{0, 0}

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

enum ColliderShape{
  BOX,
  CIRCLE,
  CAPSULE,
  POLYGON
};

namespace Component{

  /*
    Available component:
    - BoxCollider
    - CircleCollider
    - CapsuleCollider
    - PolygonCollider
    - RigidBody
  */

  struct FixtureData{
    b2Vec2 rel_position = {0, 0};
    int32 vertice_count = 0;
    b2Vec2 *vertice = NULL;
  };

  struct Box2DBaseComponent : BaseComponent{

    Vector2 GetSize();
    float GetWidth();
    float GetHeight();
    float GetRadius();
    ColliderShape GetColliderShape();
  protected:
    ColliderShape collider_shape;
    float width = 0.0f;
    float height = 0.0f;
    float radius = 0.0f;
  };


  /*
    BoxCollider Component
  */
  typedef struct BoxCollider : Box2DBaseComponent{
    b2PolygonShape *box_collision_shape;
    BoxCollider(float _width, float _height);
  } *box_collider;


  /*
    CircleCollider Component
  */
  typedef struct CircleCollider : Box2DBaseComponent{
    b2CircleShape *circle_collision_shape;
    CircleCollider(float _radius);
  } *circle_collider;


  /*
    CapsuleCollider Component
  */
  typedef struct CapsuleCollider : Box2DBaseComponent{
    b2CircleShape *circle_collision_shape;
    b2PolygonShape *box_collision_shape;
    CapsuleCollider(float height, float radius);
  } *capsule_collider;


  /*
    PolygonCollider Component
  */
  typedef struct PolygonCollider : Box2DBaseComponent{
    b2PolygonShape *polygon_collision_shape;
    vector<Vector2> point_list;
    PolygonCollider(vector<Vector2> _point_list);

  protected:
    void _OnAttach() override;
  } *polygon_collider;


  /*
    RigidBody Component
  */
  typedef struct RigidBody : Box2DBaseComponent{
    static const b2BodyType STATIC = b2_staticBody;
    static const b2BodyType DYNAMIC = b2_dynamicBody;
    static const b2BodyType KINEMATIC = b2_kinematicBody;

    void Step();

    b2Vec2 GetBodyPosition();
    float GetBodyRadian(); // body angle rotation (in radian)
    void SetBodyType(b2BodyType type);
    void SetFixedRotation(bool is_fixed = true);
    b2Body* GetBody();

  protected:
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
  void DebugDraw(float opacity = 0.666f, Color color1 = GREEN, Color color2 = RED);

}; // B2D namespace

#endif
