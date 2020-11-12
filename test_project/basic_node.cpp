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

// just leave this here. not sure if I need instantiate function or not.
static Node* Instantiate(Node* node, string name = "", v2 position = {0.0f, 0.0f}){
  Node *inst_node = nullptr; 
  Texture2D *texture = nullptr;
  int sorting_order = 0;

  if(name != ""){
    inst_node = new Node(name);
  }
  else{
    inst_node = new Node();
  }

  inst_node->SetPosition(position);

  switch(node->component_entity.drawable_type){

  case Component::SPRITE_RENDERER:
    texture = node->GetComponent<Component::sprite_renderer>()->texture; // need more test for texture instantiate... I mean... pointer...
    sorting_order = node->GetComponent<Component::sprite_renderer>()->sorting_order;
    inst_node->AddComponent<Component::sprite_renderer>(new Component::SpriteRenderer(texture));
    break;

  case Component::ANIMATOR:
    int frame_width;
    int frame_height;
    frame_width = node->GetComponent<Component::animator>()->GetGrid()->width;
    frame_height = node->GetComponent<Component::animator>()->GetGrid()->height;
    texture = node->GetComponent<Component::animator>()->texture;
    sorting_order = node->GetComponent<Component::animator>()->sorting_order;
    inst_node->AddComponent<Component::animator>(new Component::Animator(frame_width, frame_height, texture));
    break;

  case Component::ATLAS_ANIMATOR:
    break;

  case Component::TILEMAP:
    break;

  case Component::TMXMAP:
    break;

  }

  return inst_node;
}

static Node* Instantiate(Node* node, string name, CTransform transform){}

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
    B2D::Init(v2{0, 1000});
    B2D::SetContactListener(this);

    lilwitch = LoadTexture("./resources/images/circle.png");
    tile = LoadTexture("./resources/images/tile.png");

    node1 = new Node("node 1");
    node1->AddComponent<Component::sprite_renderer>(new SpriteRenderer(&lilwitch));

    Grid *tilemap_grid = new Grid{48, 48, 5, 5};
    int *tile_map = new int[25]{1,1,0,1,1,
				1,1,1,1,1,
				0,0,0,0,0,
				3,3,0,4,4,
				3,3,0,4,4
    };

    node2 = new Node("node 2");
    node2->AddComponent<Component::tilemap>(new Tilemap(tilemap_grid, tile_map, &tile));
    node2->SetPosition(v2{300, 300});

    // node2->SetRotation(45);

    node1->SetPosition(node2->GetComponent<Component::tilemap>()->
		       GetGridPosition(1, 4));

    node3 = Instantiate(node1);
    node3->SetPosition(v2{0,0});

  }

  void OnBeginContact(b2Contact *contact) override{
  }

  void OnUpdate() override {
    B2D::Step();
  }

  void OnDraw() override {
    DrawText("my first raylib window", 190, 200, 20, LIGHTGRAY);
    node2->GetComponent<Component::tilemap>()->Draw();
    node1->GetComponent<Component::sprite_renderer>()->Draw();
    node3->GetComponent<Component::sprite_renderer>()->Draw();

    B2D::DebugDraw();
  }

};

int main(){
  App app(800, 450, "My Game");
  app.Init();
  app.Run();

  return 0;
}
