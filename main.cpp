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

  Node *node1, *node2, *node3,
    *node4, *node5, *node6,
    *node7, *node8, *node9,
    *node10;

  Camera2D camera;

  int dir_state = 0;

  //component
  Texture2D dia_red, tile, lilwitch;
  SpriteRenderer *sprite_renderer;
  Animator *animator;
  Tilemap *tilemap;
  TMXMap *tmxmap;


  App(int _window_width, int _window_height, string _title) : BaseApp(_window_width, _window_height, _title){
  }

  void OnInit() override {

    B2D::SetContactListener(this);

    node1 = new Node();
    node2 = new Node();
    node3 = new Node();
    node4 = new Node();
    node5 = new Node();
    node6 = new Node();
    node7 = new Node(); // lilwitch test
    node8 = new Node(); // box dynamic rigid body test
    node9 = new Node(); // box static rigid body test
    node10 = new Node(); // circle dynamic rigid body test

    dia_red = LoadTexture("./resources/images/dia_red.png");
    lilwitch = LoadTexture("./resources/images/lilwitch.png");
    tile = LoadTexture("./resources/images/tile.png");
    sprite_renderer = new SpriteRenderer(&dia_red);
    animator = new Animator(&lilwitch, 78, 87);

    int *tile_map = new int[9]{1,2,3,
			       4,4,4,
			       3,2,1};

    tilemap = new Tilemap(&tile, new Grid{48, 48, 3, 3}, tile_map);
    tmxmap = new TMXMap(&tile, "./resources/tmx/map1.tmx");
    tmxmap->PrintMapAttribute();

    node1->AddComponent<Component::sprite_renderer>(sprite_renderer);
    node5->AddComponent<Component::tilemap>(tilemap);
    node6->AddComponent<Component::tmxmap>(tmxmap);
    node7->AddComponent<Component::animator>(animator);

    node1->SetScale(Vector2{2.0f, 2.0f});

    node1->SetPosition(Vector2{300.0f, 55.0f});
    node2->SetPosition(Vector2{450.0f, 55.0f});
    node3->SetPosition(Vector2{450.0f, 250.0f});
    node4->SetPosition(Vector2{450.0f, 70.0f});
    node7->SetPosition(Vector2{50.0f, 50.0f});
    node8->SetPosition(Vector2{30.0f, 50.0f});
    node9->SetPosition(Vector2{-50.0f, 180.0f});
    node10->SetPosition(Vector2{-120.0f, -20.0f});

    node8->AddComponent<Component::box_collider>(new BoxCollider(100, 100));
    node8->AddComponent<Component::rigid_body>(new RigidBody());
    // node8->GetComponent<Component::rigid_body>()->SetBodyType(RigidBody::STATIC);

    node9->AddComponent<Component::box_collider>(new BoxCollider(100, 100));
    node9->AddComponent<Component::rigid_body>(new RigidBody());
    node9->GetComponent<Component::rigid_body>()->SetBodyType(RigidBody::STATIC);

    node10->AddComponent<Component::circle_collider>(new CircleCollider(50));
    node10->AddComponent<Component::rigid_body>(new RigidBody());
    // node10->GetComponent<Component::rigid_body>()->SetBodyType(RigidBody::STATIC);

    node5->SetPosition(Vector2{
	(float)game_screen_width * 0.5f + 250,
	(float)game_screen_height * 0.5f});

    node6->SetPosition(Vector2{
	(float)game_screen_width * 0.5f + 200,
	(float)game_screen_height * 0.5f});

    node1->SetParent(node2);
    node2->SetParent(node3);
    node3->AddChild(node1);

    camera = {0};
    camera.target = node7->GetPosition();
    camera.offset = Vector2{(float)game_screen_width / 2,
			    (float)game_screen_height / 2};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // cout<<"node1 child size:"<<node1->GetChild()->size()<<endl;
    cout<<"node2 child size:"<<node2->GetChild()->size()<<endl;
    cout<<"node3 child size:"<<node3->GetChild()->size()<<endl;

  }

  void BeginContact(b2Contact* contact) override {
    cout<<"begin contact"<<endl;

    void *user_data = 
      contact->GetFixtureB()->GetBody()->GetUserData();

    cout<< static_cast<Node*>(user_data)->name<<endl;

  }

  void Controller(){
    float move_speed = 2.0f;
    if(IsKeyDown(KEY_W)){
      node7->SetPosition(Vector2{node7->GetPosition().x,
	    node7->GetPosition().y - move_speed});
    }

    if(IsKeyDown(KEY_S)){
      node7->SetPosition(Vector2{node7->GetPosition().x,
	    node7->GetPosition().y + move_speed});
    }

    if(IsKeyDown(KEY_D)){
      dir_state = 0;
      node7->SetPosition(Vector2{node7->GetPosition().x + move_speed,
	    node7->GetPosition().y});
    }

    if(IsKeyDown(KEY_A)){
      dir_state = 1;
      node7->SetPosition(Vector2{node7->GetPosition().x - move_speed,
	    node7->GetPosition().y});
    }

  }

  void OnUpdate() override {
    Controller();

    node3->SetPosition(Vector2{node3->GetPosition().x, node3->GetPosition().y + 0.3f});
    node5->SetPosition(Vector2{node5->GetPosition().x, node5->GetPosition().y + 0.3f});

    switch(dir_state){
    case 0:
      node7->GetComponent<Component::animator>()->PlayAnim(vector<int>{1, 2, 3, 4}, 5);
      break;
    case 1:
      node7->GetComponent<Component::animator>()->PlayAnim(vector<int>{5, 6, 7, 8}, 5);
      break;
    }

    // b2Vec2 position = node8->GetComponent<rigid_body>()->GetBody()->GetPosition();
    // cout<<position.x<<", "<<position.y<<endl;

    camera.target = node7->GetPosition();

    B2D::Step(); // run box2d step simulation
  }



  float angle = 0.0f;
  float angle2 = 0.0f;

  void OnDraw() override {
    BeginMode2D(camera);

    angle += 0.7f;
    DrawText("my first raylib window", 190, 200, 20, LIGHTGRAY);

    DrawRectangle(node1->GetPosition().x, node1->GetPosition().y,
		  100.0f, 100.0f,
		  RED,
		  node2->GetRotation());

    DrawRectangle(node2->GetPosition().x, node2->GetPosition().y,
		  100.0f, 100.0f,
		  GREEN,
		  node2->GetRotation());

    DrawRectangle(node3->GetPosition().x, node3->GetPosition().y,
		  100.0f, 100.0f,
		  BLUE,
		  node3->GetRotation());

    DrawRectangle(node4->GetPosition().x, node4->GetPosition().y,
		  100.0f, 100.0f,
		  BLUE,
		  node4->GetRotation());


    node3->SetRotation(angle);
    node4->SetRotation(angle, node3->GetPosition());
    node5->SetRotation(angle);

    if(angle2 < 95) angle2 ++;
    node6->SetRotation(angle2);

    if(angle > 360) angle = 0;

    node1->GetComponent<Component::sprite_renderer>()->Draw();
    node5->GetComponent<Component::tilemap>()->Draw();
    // node6->GetComponent<Component::tmxmap>()->Draw(0); // layer index 0
    // node6->GetComponent<Component::tmxmap>()->Draw(1); // layer index 1
    node6->GetComponent<Component::tmxmap>()->Draw(); // draw all layer
    node7->GetComponent<Component::animator>()->Draw();

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
