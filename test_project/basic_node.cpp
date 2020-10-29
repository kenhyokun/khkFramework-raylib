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
    *node4, *node5, *node6;

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
  }

  void OnInit() override {
    lilwitch = LoadTexture("./resources/images/circle.png");
    tile = LoadTexture("./resources/images/tile.png");

    node1 = new Node("node 1");
    node1->AddComponent<Component::sprite_renderer>(new SpriteRenderer(&lilwitch));

    int *tile_map = new int[9]{1,2,3,
			       4,1,4,
			       3,2,1};

    node2 = new Node("node 2");
    node2->AddComponent<Component::tilemap>(new Tilemap(&tile, new Grid{48, 48, 3, 3}, tile_map));
    node2->SetPosition(v2{300, 300});

    node2->SetRotation(45);

    node1->SetPosition(node2->GetComponent<Component::tilemap>()->
		       GetGridPosition(1, 0));

  }

  void OnUpdate() override {
  }

  void OnDraw() override {
    DrawText("my first raylib window", 190, 200, 20, LIGHTGRAY);
    node2->GetComponent<Component::tilemap>()->Draw();
    node1->GetComponent<Component::sprite_renderer>()->Draw();
  }

};

int main(){
  App app(800, 450, "My Game");
  app.Init();
  app.Run();

  return 0;
}
