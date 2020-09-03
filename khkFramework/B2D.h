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

#define b2v2_0 b2v2{0, 0}

typedef b2ContactListener ContactListener;
typedef b2Vec2 b2v2;

static b2v2 gravity(0.0f, 10.0f);
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
  POLYGON,
  EDGE
};

namespace Component{

  /*
    Available component:
    - BoxCollider
    - CircleCollider
    - CapsuleCollider
    - PolygonCollider
    - EdgeCollider
    - RigidBody
  */

  typedef struct FixtureData{
    b2v2 rel_position = b2v2_0;
    v2 size = v2_0;
    b2v2 *vertice = nullptr;
    int32 v_count = 0; // vertice count
  } *fixture_data;

  struct ColliderBaseComponent : BaseComponent{
    ColliderShape GetColliderShape();
  protected:
    ColliderShape collider_shape;
  };

  struct ShapeColliderBaseComponent : ColliderBaseComponent{
    v2 GetSize();
    float GetWidth();
    float GetHeight();
    float GetRadius();
  protected:
    float width = 0.0f;
    float height = 0.0f;
    float radius = 0.0f;
  };

  struct VerticeColliderBaseComponent : ColliderBaseComponent{
    int GetVerticeCount();
    vector<v2> vertice_list;
    b2v2 *vertice;
  protected:
    int32 v_count; // vertice count
    void _OnAttach() override;
  };


  /*
    BoxCollider Component
  */
  typedef struct BoxCollider : ShapeColliderBaseComponent{
    b2PolygonShape *box_shape = nullptr;
    BoxCollider(float _width, float _height);
  } *box_collider;


  /*
    CircleCollider Component
  */
  typedef struct CircleCollider : ShapeColliderBaseComponent{
    b2CircleShape *circle_shape = nullptr;
    CircleCollider(float _radius);
  } *circle_collider;


  /*
    CapsuleCollider Component
  */
  typedef struct CapsuleCollider : ShapeColliderBaseComponent{
    b2CircleShape *circle_shape = nullptr;
    b2PolygonShape *box_shape = nullptr;
    CapsuleCollider(float height, float radius);
  } *capsule_collider;


  /*
    PolygonCollider Component
  */
  typedef struct PolygonCollider : VerticeColliderBaseComponent{
    b2PolygonShape *polygon_shape = nullptr;
    PolygonCollider(vector<v2> _vertice_list);
  protected:
    void _OnAttach() override;
  } *polygon_collider;


  /*
    EdgeCollider Component
  */
  typedef struct EdgeCollider : VerticeColliderBaseComponent{
    b2ChainShape *chain_shape = nullptr;
    b2EdgeShape *edge_shape = nullptr;
    EdgeCollider(v2 _vertice);
    EdgeCollider(vector<v2> _vertice_list);
  protected:
    void _OnAttach() override;
  } *edge_collider;


  /*
    RigidBody Component
  */
  typedef struct RigidBody : BaseComponent{
    static const b2BodyType STATIC = b2_staticBody;
    static const b2BodyType DYNAMIC = b2_dynamicBody;
    static const b2BodyType KINEMATIC = b2_kinematicBody;

    void Step();

    b2v2 GetBodyPosition();
    float GetBodyRadian(); // body angle rotation (in radian)
    void SetBodyType(b2BodyType type);
    void SetFixedRotation(bool is_fixed = true);
    b2Body* GetBody();

  protected:
    b2Body *body = nullptr;
    b2Fixture *fixture = nullptr;

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
