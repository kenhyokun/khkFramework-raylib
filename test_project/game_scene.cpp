/*
  Kevin Haryo Kuncoro
  kevinhyokun91@gmail.com
*/

#include<iostream>
#include<string>
#include<BaseApp.h>
#include<Node.h>
#include<Component.h>
#include<SceneManager.h>

using namespace std;
using namespace Component;

/*
  Game loop:
  - OnInit
  - OnUpdate
  - OnDraw
*/

struct App : BaseApp{
  SceneManager *scene_manager;
  Scene *scene1;
  Scene *scene2;
  Node *obj1;
  Node *obj2;
  Node *obj3;
  TextureAtlas *texture_atlas;
  Texture2D card_texture, dia_texture, tile_texture; // just realize that we must declare this variable here to avoid crash

  Node *a, *b, *c, *d, *e, *f, *g, *h, *i, *j;

  App(int _window_width, int _window_height, string _title, bool _is_resizable) :
    BaseApp(_window_width, _window_height, _title, _is_resizable){}

  ~App(){
  }

  int node_tree_count = 0;
  void GetNodeOnTree(Node *node){
    cout<<node->name<<" have "<<node->GetChild()->size()<<" childs"<<endl;
    node_tree_count++;
    
    if(node->GetChild()->size() > 0){
      for(int i = 0; i < node->GetChild()->size(); i++){
	GetNodeOnTree(node->GetChild(i));
      }
    }
  }

  void OnInit() override {
    texture_atlas = new TextureAtlas("./resources/texture_packer.atlas",
				     "./resources/images/texture_packer.png");

    dia_texture = texture_atlas->CreateTexture("dia_red");
    tile_texture = texture_atlas->CreateTexture("tile");
    card_texture = texture_atlas->CreateTexture("card_back1");
    
    texture_atlas->UnloadBufferImage();

    obj1 = new Node("obj1");
    obj1->SetPosition(v2{150, 150});
    obj1->AddComponent<Component::sprite_renderer>(new SpriteRenderer(&dia_texture));
    
    obj2 = new Node("obj2");
    obj2->SetPosition(v2{150, 150});
    obj2->AddComponent<Component::sprite_renderer>(new SpriteRenderer(&tile_texture));

    obj3 = new Node("obj3");
    obj3->SetPosition(v2{150, 150});
    obj3->AddComponent<Component::sprite_renderer>(new SpriteRenderer(&card_texture));

    scene1 = new Scene("scene 1");
    scene2 = new Scene("scene 2");

    obj1->GetComponent<Component::sprite_renderer>()->sorting_order = 3;
    obj2->GetComponent<Component::sprite_renderer>()->sorting_order = 2;
    obj3->GetComponent<Component::sprite_renderer>()->sorting_order = 1;

    scene1->AddChild(obj1);
    scene1->AddChild(obj2);
    scene1->AddChild(obj3);

    scene_manager = new SceneManager();
    scene_manager->AddScene(scene1);

    a = new Node("a");
    b = new Node("b");
    c = new Node("c");
    d = new Node("d");
    e = new Node("e");
    f = new Node("f");
    g = new Node("g");
    h = new Node("h");
    i = new Node("i");
    j = new Node("j");

    a->AddChild(b);
    a->AddChild(c);

    b->AddChild(d);
    b->AddChild(e);

    c->AddChild(f);
    c->AddChild(g);

    d->AddChild(h);
    d->AddChild(i);

    GetNodeOnTree(a);

    cout<<node_tree_count<<endl;

  }

  void OnUpdate() override {
  }

  void OnDraw() override {
    scene_manager->Draw();
  }

};

int main(){
  App app(800, 450, "My Game", true);
  app.Init();
  app.Run();

  return 0;
}
