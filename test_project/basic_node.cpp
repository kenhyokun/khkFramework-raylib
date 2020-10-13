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
    node1 = new Node("first node");
    node2 = new Node("node2");
    node3 = new Node("3rd node");
    node4 = new Node("4th node");
    node5 = new Node("node #5");
    node6 = new Node("node number six");

    node1->AddChild(node2);
    node1->AddChild(node3);
    node1->AddChild(node4);
    node2->AddChild(node5);
    node2->AddChild(node6);

    node1->PrintAllChildName();
    cout<<"--------"<<endl;

    cout<<node1->GetChild("node2")->name<<endl;
    cout<<node1->GetChild(0)->name<<endl;
    cout<<node1->GetChild(0)->tag<<endl;
    cout<<node1->GetChild("3rd node")->name<<endl;
    cout<<node1->GetChild(1)->name<<endl;
    cout<<node1->GetChild(1)->tag<<endl;
    cout<<node2->GetChild("node #5")->name<<endl;
    cout<<node2->GetChild(0)->name<<endl;
    cout<<node2->GetChild(0)->tag<<endl;

  }

  void OnUpdate() override {
  }

  void OnDraw() override {
    DrawText("my first raylib window", 190, 200, 20, LIGHTGRAY);
  }

};

int main(){
  App app(800, 450, "My Game");
  app.Init();
  app.Run();

  return 0;
}
