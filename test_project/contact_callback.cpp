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

struct Player : Node, CollisionListener{

  Player(string name) : Node(name), CollisionListener(this){}

  void OnCollisionEnter(Node *collision_node) override{    
    // if(collision_node->name == "static box")
      cout<<name<<" collide with "<<collision_node->name<<endl;
  }
  
  void OnCollisionExit(Node *collision_node) override{    
    cout<<name<<" not touching "<<collision_node->name<<" any more..."<<endl;
  }
  
};

struct App : BaseApp, ContactListener{

  Player *player;
  Node *dia_red_node;
  Node *dynamic_box;
  Node *static_box;
  Node *dynamic_circle;
  Node *dynamic_capsule;
  Node *dynamic_polygon;
  Node *edge_ground;
  Node *atlas_animator_node;

  int dir_state = 0;

  //component
  Texture2D dia_red, tile, lilwitch;
  SpriteRenderer *sprite_renderer;
  Animator *animator;
  Tilemap *tilemap;
  TMXMap *tmxmap;

  Image buffer_image;
  Texture2D buffer_texture;

  AtlasAnimator *atlas_animator;
  TextureAtlas *texture_atlas;


  App(int _window_width, int _window_height, string _title, bool _is_resizable) :
    BaseApp(_window_width, _window_height, _title, _is_resizable){}

  ~App(){
    delete world;
  }

  void OnInit() override {

    camera->SetOffsetToCenter();

    B2D::Init(v2{0, 1000});
    B2D::SetContactListener(this);

    JSONFile tes;
    tes.LoadFile("./resources/tes.json");
    float _pi = tes.json["pi"];
    cout<<_pi<<endl;

    atlas_animator_node = new Node("atlas animator");

    texture_atlas = new TextureAtlas("./resources/texture_packer.atlas",
				     "./resources/images/texture_packer.png");

    cout<<texture_atlas->GetRegion("run_left_1").xy.x<<endl;
    cout<<texture_atlas->GetRegion("run_left_1").xy.y<<endl;
    cout<<texture_atlas->GetRegion("run_left_1").size.x<<endl;
    cout<<texture_atlas->GetRegion("run_left_1").size.y<<endl;
    cout<<texture_atlas->GetRegion("run_left_1").is_rotate<<endl;
    cout<<texture_atlas->GetRegion("card_back1").xy.x<<endl;
    cout<<texture_atlas->GetRegion("card_back1").xy.y<<endl;
    cout<<texture_atlas->GetRegion("card_back1").size.x<<endl;
    cout<<texture_atlas->GetRegion("card_back1").size.y<<endl;
    cout<<texture_atlas->GetRegion("card_back1").is_rotate<<endl;

    buffer_texture = texture_atlas->CreateTexture("card_back1");
    // buffer_texture = texture_atlas.CreateTexture("dia_red");
    // buffer_texture = texture_atlas.CreateTexture("run_1");

    atlas_animator = new AtlasAnimator(texture_atlas);

    texture_atlas->UnloadBufferImage(); // memory management thingy...

    atlas_animator_node->AddComponent(atlas_animator);

    player = new Player("player"); // lilwitch test
    dia_red_node = new Node("dia_red");
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
    animator = new Animator(78, 87, &lilwitch);

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
    player->AddComponent<Component::rigidbody>(new RigidBody);
    player->GetComponent<Component::rigidbody>()->SetFixedRotation();

    /*
      NOTE[kevin]:
      collision_listener_list on ContactListener must be clear 
      when game scene changed or when we dont need it any more.
    */
    AddContactListener(player);

    if(player->IsHasRigidBodyComponent()) cout<<player->name<<" has rigid body component..."<<endl;
    if(player->IsHasDrawableComponent()) cout<<player->name<<" has drawble component..."<<endl;
    if(Node::IsHas<Component::animator>(player)) cout<<player->name<<" has animator component..."<<endl;

    // kinematic test
    // player->GetComponent<Component::rigidbody>()->SetBodyType(RigidBody::KINEMATIC);

    dynamic_box->AddComponent<Component::box_collider>(new BoxCollider(100, 100));
    dynamic_box->AddComponent<Component::rigidbody>(new RigidBody());

    static_box->AddComponent<Component::box_collider>(new BoxCollider(100, 100));
    static_box->AddComponent<Component::rigidbody>(new RigidBody());
    static_box->GetComponent<Component::rigidbody>()->SetBodyType(RigidBody::STATIC);
    // static_box->GetComponent<Component::rigidbody>()->SetBodyType(RigidBody::KINEMATIC);
    // static_box->GetComponent<Component::rigidbody>()->SetAlwaysAwake();

    dynamic_circle->AddComponent<Component::circle_collider>(new CircleCollider(50));
    dynamic_circle->AddComponent<Component::rigidbody>(new RigidBody());

    dynamic_capsule->AddComponent<Component::capsule_collider>(new CapsuleCollider(50, 50));
    dynamic_capsule->AddComponent<Component::rigidbody>(new RigidBody());

    vector<v2> polygon_vertice{
      v2{dynamic_polygon->GetPosition().x , dynamic_polygon->GetPosition().y},
      v2{dynamic_polygon->GetPosition().x - 100 , dynamic_polygon->GetPosition().y},
      v2{dynamic_polygon->GetPosition().x , dynamic_polygon->GetPosition().y - 100},
    };
    dynamic_polygon->AddComponent<Component::polygon_collider>(new PolygonCollider(polygon_vertice));
    dynamic_polygon->AddComponent<Component::rigidbody>(new RigidBody());

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
    edge_ground->AddComponent<Component::rigidbody>(new RigidBody());
    edge_ground->GetComponent<Component::rigidbody>()->SetBodyType(RigidBody::STATIC);

    // player->GetComponent<Component::rigidbody>()->SetDensity(10.0f);
    // player->GetComponent<Component::rigidbody>()->SetMass(10.0f);


    // float density = 0.1f;
    // dynamic_box->GetComponent<Component::rigidbody>()->SetDensity(density);
    // dynamic_polygon->GetComponent<Component::rigidbody>()->SetDensity(density);
    // dynamic_circle->GetComponent<Component::rigidbody>()->SetDensity(density);
    // dynamic_capsule->GetComponent<Component::rigidbody>()->SetDensity(density);

    // float restitution = 0.5f;
    // dynamic_box->GetComponent<Component::rigidbody>()->SetRestitution(restitution);
    // dynamic_polygon->GetComponent<Component::rigidbody>()->SetRestitution(restitution);
    // dynamic_circle->GetComponent<Component::rigidbody>()->SetRestitution(restitution);
    // dynamic_capsule->GetComponent<Component::rigidbody>()->SetRestitution(restitution);
    
    // float mass = 10.0f;
    // dynamic_box->GetComponent<Component::rigidbody>()->SetMass(mass);
    // dynamic_polygon->GetComponent<Component::rigidbody>()->SetMass(mass);
    // dynamic_circle->GetComponent<Component::rigidbody>()->SetMass(mass);
    // dynamic_capsule->GetComponent<Component::rigidbody>()->SetMass(mass);

    dia_red_node->AddComponent<Component::sprite_renderer>(new SpriteRenderer(&dia_red));
  }

  void OnBeginContact(b2Contact *contact) override{
    // cout<<"hello from OnBeginContact..."<<endl;
  }

  void OnBeginContact(b2Contact *contact, Node *node_a, Node *node_b) override{
    // cout<<"hello from OnBeginContact..."<<endl;
    // cout<<node_b->name<<" => "<<node_a->name<<endl;
  }
  
  void Controller(){
    float move_speed = 100.0f;
    float h_force = 10000;
    float v_force = 195555;
    if(GetKeyButton("up")->IsDown()){
      player->GetComponent<Component::rigidbody>()->SetLinearVelocity(v2{player->GetComponent<rigidbody>()->GetLinearVelocity().x, -move_speed});
    }

    if(GetKeyButton("down")->IsDown()){
      player->GetComponent<Component::rigidbody>()->SetLinearVelocity(v2{player->GetComponent<rigidbody>()->GetLinearVelocity().x, move_speed});
    }

    if(!GetKeyButton("up")->IsDown() && !GetKeyButton("down")->IsDown()){
      player->GetComponent<Component::rigidbody>()->SetLinearVelocity(v2{player->GetComponent<rigidbody>()->GetLinearVelocity().x, 0});
    }

    if(GetKeyButton("right")->IsDown()){
      dir_state = 0;

      // apply force to dynamic rigid body
      // player->GetComponent<Component::rigidbody>()->ApplyForce(v2{h_force, 0}, true);

      // set linear velocity to dynamic or kinematic body
      player->GetComponent<Component::rigidbody>()->SetLinearVelocity(v2{move_speed, player->GetComponent<rigidbody>()->GetLinearVelocity().y});
    }

    if(GetKeyButton("left")->IsDown()){
      dir_state = 1;

      // apply force to dynamic rigid body
      // player->GetComponent<Component::rigidbody>()->ApplyForce(v2{-h_force, 0}, true);

      // set linear velocity to dynamic or kinematic body
      player->GetComponent<Component::rigidbody>()->SetLinearVelocity(v2{-move_speed, player->GetComponent<rigidbody>()->GetLinearVelocity().y});
    }

    if(!GetKeyButton("right")->IsDown() && !GetKeyButton("left")->IsDown()){
      // player->GetComponent<Component::rigidbody>()->SetLinearVelocity(v2{0, player->GetComponent<rigidbody>()->GetLinearVelocity().y});

      if(player->GetComponent<rigidbody>()->GetLinearVelocity().x > 0){
	player->GetComponent<Component::rigidbody>()->SetLinearVelocity(v2{player->GetComponent<rigidbody>()->GetLinearVelocity().x - 3, player->GetComponent<rigidbody>()->GetLinearVelocity().y});
      }
      else if(player->GetComponent<rigidbody>()->GetLinearVelocity().x < 0){
	player->GetComponent<Component::rigidbody>()->SetLinearVelocity(v2{player->GetComponent<rigidbody>()->GetLinearVelocity().x + 3, player->GetComponent<rigidbody>()->GetLinearVelocity().y});
      }

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
    // static_box->GetComponent<Component::rigidbody>()->SetPosition(v2{static_box->GetPosition().x + 0.2f, static_box->GetPosition().y});
    static_box->GetComponent<Component::rigidbody>()->SetLinearVelocity(v2{10, static_box->GetComponent<rigidbody>()->GetLinearVelocity().y});

    atlas_animator_node->GetComponent<Component::atlas_animator>()->PlayAnim("run_right", 5);

    B2D::Step(); // run box2d step simulation
  }


  void OnDraw() override {
    DrawText("my first raylib window", 190, 200, 20, LIGHTGRAY);
    DrawTexture(buffer_texture, 0, 0, WHITE);
    player->GetComponent<Component::animator>()->Draw();

    atlas_animator_node->GetComponent<Component::atlas_animator>()->Draw();

    // dia_red_node->GetComponent<Component::sprite_renderer>()->Draw();

    B2D::DebugDraw();
  }

};

int main(){
  App app(800, 450, "My Game", true);
  app.Init();
  app.Run();

  return 0;
}
