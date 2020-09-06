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

using namespace std;
using namespace Component;

/*
  Game loop:
  - OnInit
  - OnUpdate
  - OnDraw
*/

struct App : BaseApp, ContactListener{

  Node *player, *dynamic_box, *static_box,
    *dynamic_circle, *dynamic_capsule, *dynamic_polygon,
    *node13;

  Camera2D camera;

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

    B2D::Init(this);

    player = new Node(); // lilwitch test
    dynamic_box = new Node(); // box dynamic rigid body test
    static_box = new Node(); // box static rigid body test
    dynamic_circle = new Node(); // circle dynamic rigid body test
    dynamic_capsule = new Node(); // capsule dynamic rigid body test
    dynamic_polygon = new Node(); // polygon dynamic rigid body test
    node13 = new Node(); // edge rigid body test

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
    // dynamic_polygon->SetPosition(v2{-120.0f, -90.0f});
    dynamic_polygon->SetPosition(static_box->GetPosition());
    node13->SetPosition(v2{50, -250});

    player->AddComponent<Component::animator>(animator);

    dynamic_box->AddComponent<Component::box_collider>(new BoxCollider(100, 100));
    dynamic_box->AddComponent<Component::rigid_body>(new RigidBody());
    // dynamic_box->GetComponent<Component::rigid_body>()->SetBodyType(RigidBody::STATIC);

    static_box->AddComponent<Component::box_collider>(new BoxCollider(100, 100));
    static_box->AddComponent<Component::rigid_body>(new RigidBody());
    static_box->GetComponent<Component::rigid_body>()->SetBodyType(RigidBody::STATIC);

    dynamic_circle->AddComponent<Component::circle_collider>(new CircleCollider(50));
    dynamic_circle->AddComponent<Component::rigid_body>(new RigidBody());
    // dynamic_circle->GetComponent<Component::rigid_body>()->SetBodyType(RigidBody::STATIC);

    dynamic_capsule->AddComponent<Component::capsule_collider>(new CapsuleCollider(50, 50));
    dynamic_capsule->AddComponent<Component::rigid_body>(new RigidBody());
    // dynamic_capsule->GetComponent<Component::rigid_body>()->SetBodyType(RigidBody::STATIC);

    vector<v2> polygon_vertice{
      v2{static_box->GetPosition().x , static_box->GetPosition().y},
    	v2{100, 100},
    	v2{50, 100},
	
    };
    dynamic_polygon->AddComponent<Component::polygon_collider>(new PolygonCollider(polygon_vertice));
    dynamic_polygon->AddComponent<Component::rigid_body>(new RigidBody());
    // dynamic_polygon->GetComponent<Component::rigid_body>()->SetBodyType(RigidBody::STATIC);

    //  using 4 vertice to create edge collider with box2d chain shape
    vector<v2> edge_vertice{
      v2{node13->GetPosition().x , node13->GetPosition().y},
    	v2{node13->GetPosition().x + 20, node13->GetPosition().y + 20},
    	  v2{node13->GetPosition().x - 20, node13->GetPosition().y + 20},
    	    v2{node13->GetPosition().x + 20, node13->GetPosition().y + 50}
	
    };

    //  using 2 vertice to create edge collider with box2d edge shape
    // vector<v2> edge_vertice{
    //   v2{node13->GetPosition().x , node13->GetPosition().y},
    // 	v2{node13->GetPosition().x + 20, node13->GetPosition().y + 20}
    // };

    // node13->AddComponent<Component::edge_collider>(new EdgeCollider(edge_vertice));
    
    node13->AddComponent<Component::edge_collider>(new EdgeCollider(v2{node13->GetPosition().x + 20, node13->GetPosition().y + 20}));
    node13->AddComponent<Component::rigid_body>(new RigidBody());
    // node13->GetComponent<Component::rigid_body>()->SetBodyType(RigidBody::STATIC);

    camera = {0};
    camera.target = player->GetPosition();
    camera.offset = v2{(float)game_screen_width / 2,
		       (float)game_screen_height / 2};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

  }

  void BeginContact(b2Contact* contact) override {
    // cout<<"begin contact"<<endl;
    void *user_data = 
      contact->GetFixtureB()->GetBody()->GetUserData();
    // cout<< static_cast<Node*>(user_data)->name<<endl;

  }

  void Controller(){
    float move_speed = 2.0f;
    if(IsKeyDown(KEY_W)){
      player->SetPosition(v2{player->GetPosition().x,
	    player->GetPosition().y - move_speed});
    }

    if(IsKeyDown(KEY_S)){
      player->SetPosition(v2{player->GetPosition().x,
	    player->GetPosition().y + move_speed});
    }

    if(IsKeyDown(KEY_D)){
      dir_state = 0;
      player->SetPosition(v2{player->GetPosition().x + move_speed,
	    player->GetPosition().y});
    }

    if(IsKeyDown(KEY_A)){
      dir_state = 1;
      player->SetPosition(v2{player->GetPosition().x - move_speed,
	    player->GetPosition().y});
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

    camera.target = player->GetPosition();

    B2D::Step(); // run box2d step simulation
  }


  void OnDraw() override {
    BeginMode2D(camera);

    DrawText("my first raylib window", 190, 200, 20, LIGHTGRAY);

    player->GetComponent<Component::animator>()->Draw();

    B2D::DebugDraw();

    EndMode2D();

  }

};

int main(){
  App app(800, 450, "My Game");
  app.Init();
  app.Run();

  return 0;
}
