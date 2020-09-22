/*
  Kevin Haryo Kuncoro
  kevinhyokun91@gmail.com
*/

#include<iostream>
#include<string>
#include<BaseApp.h>
#include<Node.h>
#include<Component.h>
#include<B2D.h>
#include<File.h>
#include<TextureAtlas.h>

using namespace std;
using namespace Component;

/*
  Game loop:
  - OnInit
  - OnUpdate
  - OnDraw
*/

/*
TODO [kevin]:
 - add more function on rigid body
 - contact listener test
 - platfomer test (what is this ghost vertice thingy...)
 - resource manager maybe...
*/


struct App : BaseApp, ContactListener{

  Node *player;
  Node *dynamic_box;
  Node *static_box;
  Node *dynamic_circle;
  Node *dynamic_capsule;
  Node *dynamic_polygon;
  Node *edge_ground;

  int dir_state = 0;

  //component
  Texture2D dia_red, tile, lilwitch;
  SpriteRenderer *sprite_renderer;
  Animator *animator;
  Tilemap *tilemap;
  TMXMap *tmxmap;

  App(int _window_width, int _window_height, string _title) :
    BaseApp(_window_width, _window_height, _title){}

  ~App(){
    delete world;
  }

  void OnInit() override {

    B2D::Init(v2{0, 1000});
    B2D::SetContactListener(this);

    JSONFile tes;
    tes.LoadFile("tes.json");
    float _pi = tes.json["pi"];
    cout<<_pi<<endl;

    TextureAtlas texture_atlas("test2.atlas");
    cout<<texture_atlas.GetRegion("card_back").xy.x<<endl;
    cout<<texture_atlas.GetRegion("card_back").xy.y<<endl;
    cout<<texture_atlas.GetRegion("card_back").size.x<<endl;
    cout<<texture_atlas.GetRegion("card_back").size.y<<endl;
    cout<<texture_atlas.GetRegion("card_back").is_rotate<<endl;

    player = new Node("player"); // lilwitch test
    dynamic_box = new Node("dynamic box"); // box dynamic rigid body test
    static_box = new Node("static box"); // box static rigid body test
    dynamic_circle = new Node("dynamic circle"); // circle dynamic rigid body test
    dynamic_capsule = new Node("dynamic capsule"); // capsule dynamic rigid body test
    dynamic_polygon = new Node("dynamic polygon"); // polygon dynamic rigid body test
    edge_ground = new Node("edge ground"); // edge rigid body test

    dia_red = LoadTexture("./resources/images/dia_red.png");
    lilwitch = LoadTexture("./resources/images/lilwitch.png");
    tile = LoadTexture("./resources/images/tile.png");
    sprite_renderer = new SpriteRenderer(&dia_red);
    animator = new Animator(&lilwitch, 78, 87);

    player->SetPosition(v2{50.0f, 50.0f});
    dynamic_box->SetPosition(v2{30.0f, 50.0f});
    static_box->SetPosition(v2{-50.0f, 180.0f});
    dynamic_circle->SetPosition(v2{-120.0f, -20.0f});
    dynamic_capsule->SetPosition(v2{-120.0f, -90.0f});
    dynamic_polygon->SetPosition(v2{static_box->GetPosition().x, 0});
    edge_ground->SetPosition(v2{-450, 450});

    camera->AttachTo(player);

    player->AddComponent<Component::animator>(animator);
    player->AddComponent<Component::capsule_collider>(new CapsuleCollider(20, 30));
    player->AddComponent<Component::rigid_body>(new RigidBody);

    // kinematic test
    // player->GetComponent<Component::rigid_body>()->SetBodyType(RigidBody::KINEMATIC);

    dynamic_box->AddComponent<Component::box_collider>(new BoxCollider(100, 100));
    dynamic_box->AddComponent<Component::rigid_body>(new RigidBody());

    static_box->AddComponent<Component::box_collider>(new BoxCollider(100, 100));
    static_box->AddComponent<Component::rigid_body>(new RigidBody());
    static_box->GetComponent<Component::rigid_body>()->SetBodyType(RigidBody::STATIC);
    // static_box->GetComponent<Component::rigid_body>()->SetBodyType(RigidBody::KINEMATIC);
    // static_box->GetComponent<Component::rigid_body>()->SetAlwaysAwake();

    dynamic_circle->AddComponent<Component::circle_collider>(new CircleCollider(50));
    dynamic_circle->AddComponent<Component::rigid_body>(new RigidBody());

    dynamic_capsule->AddComponent<Component::capsule_collider>(new CapsuleCollider(50, 50));
    dynamic_capsule->AddComponent<Component::rigid_body>(new RigidBody());

    vector<v2> polygon_vertice{
      v2{dynamic_polygon->GetPosition().x , dynamic_polygon->GetPosition().y},
      v2{dynamic_polygon->GetPosition().x - 100 , dynamic_polygon->GetPosition().y},
      v2{dynamic_polygon->GetPosition().x , dynamic_polygon->GetPosition().y - 100},
    };
    dynamic_polygon->AddComponent<Component::polygon_collider>(new PolygonCollider(polygon_vertice));
    dynamic_polygon->AddComponent<Component::rigid_body>(new RigidBody());

    //  using 4 vertice to create edge collider with box2d chain shape
    vector<v2> edge_vertice{
      v2{edge_ground->GetPosition().x , edge_ground->GetPosition().y},
    	v2{edge_ground->GetPosition().x + 250, edge_ground->GetPosition().y},
    	  v2{edge_ground->GetPosition().x + 500, edge_ground->GetPosition().y - 100},
	    v2{edge_ground->GetPosition().x + 750, edge_ground->GetPosition().y - 100},
	      v2{edge_ground->GetPosition().x + 1000, edge_ground->GetPosition().y}
    };

    edge_ground->AddComponent<Component::edge_collider>(new EdgeCollider(edge_vertice));

    v2 vertice = {edge_ground->GetPosition().x + 1000, edge_ground->GetPosition().y};
    // edge_ground->AddComponent<Component::edge_collider>(new EdgeCollider(vertice));
    edge_ground->AddComponent<Component::rigid_body>(new RigidBody());
    edge_ground->GetComponent<Component::rigid_body>()->SetBodyType(RigidBody::STATIC);

    float density = 0.1f;
    dynamic_box->GetComponent<Component::rigid_body>()->SetDensity(density);
    dynamic_polygon->GetComponent<Component::rigid_body>()->SetDensity(density);
    dynamic_circle->GetComponent<Component::rigid_body>()->SetDensity(density);
    dynamic_capsule->GetComponent<Component::rigid_body>()->SetDensity(density);

    float restitution = 0.5f;
    dynamic_box->GetComponent<Component::rigid_body>()->SetRestitution(restitution);
    dynamic_polygon->GetComponent<Component::rigid_body>()->SetRestitution(restitution);
    dynamic_circle->GetComponent<Component::rigid_body>()->SetRestitution(restitution);
    dynamic_capsule->GetComponent<Component::rigid_body>()->SetRestitution(restitution);
    
    float mass = 10.0f;
    dynamic_box->GetComponent<Component::rigid_body>()->SetMass(mass);
    dynamic_polygon->GetComponent<Component::rigid_body>()->SetMass(mass);
    dynamic_circle->GetComponent<Component::rigid_body>()->SetMass(mass);
    dynamic_capsule->GetComponent<Component::rigid_body>()->SetMass(mass);

    player->GetComponent<Component::rigid_body>()->SetDensity(10.0f);
    player->GetComponent<Component::rigid_body>()->SetMass(10.0f);
    player->GetComponent<Component::rigid_body>()->SetFixedRotation();
    // player->GetComponent<Component::rigid_body>()->SetAngularDamping(100.0f); 
    // player->GetComponent<Component::rigid_body>()->SetAlwaysAwake();

  }

  void BeginContact(b2Contact* contact) override {
    // cout<<"begin contact"<<endl;
    Fixture *fixture_a = contact->GetFixtureA();
    Fixture *fixture_b = contact->GetFixtureB();

    void *user_data_a = fixture_a->GetBody()->GetUserData();
    void *user_data_b = fixture_b->GetBody()->GetUserData();

    // cout<< static_cast<Node*>(user_data_b)->name<<" => "<<static_cast<Node*>(user_data_a)->name<<endl;
  }

  void Controller(){
    float move_speed = 100.0f;
    float h_force = 10000;
    float v_force = 195555;
    if(GetKeyButton("up")->IsDown()){
      player->GetComponent<Component::rigid_body>()->SetLinearVelocity(v2{player->GetComponent<rigid_body>()->GetLinearVelocity().x, -move_speed});
    }

    if(GetKeyButton("down")->IsDown()){
      player->GetComponent<Component::rigid_body>()->SetLinearVelocity(v2{player->GetComponent<rigid_body>()->GetLinearVelocity().x, move_speed});
    }

    if(!GetKeyButton("up")->IsDown() && !GetKeyButton("down")->IsDown()){
      player->GetComponent<Component::rigid_body>()->SetLinearVelocity(v2{player->GetComponent<rigid_body>()->GetLinearVelocity().x, 0});
    }

    if(GetKeyButton("right")->IsDown()){
      dir_state = 0;

      // apply force to dynamic rigid body
      // player->GetComponent<Component::rigid_body>()->ApplyForce(v2{h_force, 0}, true);

      // set linear velocity to dynamic or kinematic body
      player->GetComponent<Component::rigid_body>()->SetLinearVelocity(v2{move_speed, player->GetComponent<rigid_body>()->GetLinearVelocity().y});
    }

    if(GetKeyButton("left")->IsDown()){
      dir_state = 1;

      // apply force to dynamic rigid body
      // player->GetComponent<Component::rigid_body>()->ApplyForce(v2{-h_force, 0}, true);

      // set linear velocity to dynamic or kinematic body
      player->GetComponent<Component::rigid_body>()->SetLinearVelocity(v2{-move_speed, player->GetComponent<rigid_body>()->GetLinearVelocity().y});
    }

    if(!GetKeyButton("right")->IsDown() && !GetKeyButton("left")->IsDown()){
      player->GetComponent<Component::rigid_body>()->SetLinearVelocity(v2{0, player->GetComponent<rigid_body>()->GetLinearVelocity().y});
    }

    if(IsKeyDown(KEY_SPACE)){
    }

  }

  void OnUpdate() override {
    Controller();

    switch(dir_state){
    case 0:
      player->GetComponent<Component::animator>()->PlayAnim(vector<int>{1, 2, 3, 4}, 5);
      break;
    case 1:
      player->GetComponent<Component::animator>()->PlayAnim(vector<int>{5, 6, 7, 8}, 5);
      break;
    }

    // moving static box
    static_box->GetComponent<Component::rigid_body>()->SetPosition(v2{static_box->GetPosition().x + 0.2f, static_box->GetPosition().y});

    B2D::Step(); // run box2d step simulation
  }


  void OnDraw() override {
    DrawText("my first raylib window", 190, 200, 20, LIGHTGRAY);
    player->GetComponent<Component::animator>()->Draw();
    B2D::DebugDraw();
  }

};

int main(){
  App app(800, 450, "My Game");
  app.Init();
  app.Run();

  return 0;
}
