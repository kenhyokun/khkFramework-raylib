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

  App(int _window_width, int _window_height, string _title, bool _is_resizable) :
    BaseApp(_window_width, _window_height, _title, _is_resizable){}

  ~App(){
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

  }

  void OnUpdate() override {
  }

  void OnDraw() override {
    // obj1->GetComponent<Component::sprite_renderer>()->Draw();
    // obj2->GetComponent<Component::sprite_renderer>()->Draw();
    // obj3->GetComponent<Component::sprite_renderer>()->Draw();

    scene_manager->Draw();
  }

};

int main(){
  App app(800, 450, "My Game", true);
  app.Init();
  app.Run();

  return 0;
}
