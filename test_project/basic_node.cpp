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
    lilwitch = LoadTexture("./resources/images/lilwitch.png");
    node1 = new Node("node 1");
    node1->AddComponent<Component::sprite_renderer>(new SpriteRenderer(&lilwitch));

    cout<<Node::component_map<Component::sprite_renderer>.size()<<endl;
    
    node1->RemoveComponent<Component::sprite_renderer>();

    cout<<Node::component_map<Component::sprite_renderer>.size()<<endl;
  }

  void OnUpdate() override {
  }

  void OnDraw() override {
    DrawText("my first raylib window", 190, 200, 20, LIGHTGRAY);
    // node1->GetComponent<Component::sprite_renderer>()->Draw();
  }

};

int main(){
  App app(800, 450, "My Game");
  app.Init();
  app.Run();

  return 0;
}
