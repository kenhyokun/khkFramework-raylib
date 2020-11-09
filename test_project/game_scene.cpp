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
  Node *obj1; // sprite renderer
  Node *obj2; // sprite renderer
  Node *obj3; // sprite renderer
  Node *obj4; // animator
  Node *obj5; // tilemap
  Node *obj6; // atlas animator 
  Node *obj7; // tmxmap 
  TextureAtlas *texture_atlas;
  Texture2D card_texture, dia_texture, tile_texture, lilwitch; // just realize that we must declare this variable here to avoid crash
  AtlasAnimator *atlas_animator;

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

    atlas_animator = new AtlasAnimator(texture_atlas);
    
    texture_atlas->UnloadBufferImage();

    lilwitch = LoadTexture("./resources/images/lilwitch.png");

    obj1 = new Node("obj1 sprite renderer");
    obj1->SetPosition(v2{150, 150});
    obj1->AddComponent<Component::sprite_renderer>(new SpriteRenderer(&dia_texture));


    obj2 = new Node("obj2 sprite renderer");
    obj2->SetPosition(v2{150, 150});
    obj2->AddComponent<Component::sprite_renderer>(new SpriteRenderer(&tile_texture));

    obj3 = new Node("obj3 sprite renderer");
    obj3->SetPosition(v2{150, 150});
    obj3->AddComponent<Component::sprite_renderer>(new SpriteRenderer(&card_texture));

    obj4 = new Node("obj4 animator");
    obj4->SetPosition(v2{230, 150});
    obj4->AddComponent<Component::animator>(new Animator(78, 87, &lilwitch));

    obj5 = new Node("obj5 tilemap");
    obj5->SetPosition(v2{330, 150});

    int *tile_map = new int[9]{1,2,3,
			       4,4,4,
			       3,2,1};

    obj5->AddComponent<Component::tilemap>(new Tilemap(new Grid{48, 48, 3, 3}, tile_map, &tile_texture));

    obj6 = new Node("obj6 atlas animator");
    obj6->SetPosition(v2{230, 200});
    obj6->AddComponent<Component::atlas_animator>(atlas_animator);

    obj7 = new Node("obj7 tmxmap");
    obj7->SetPosition(v2{555, 200});
    obj7->AddComponent<Component::tmxmap>(new TMXMap("./resources/tmx/map1.tmx", &tile_texture));

    scene1 = new Scene("scene 1");
    scene2 = new Scene("scene 2");

    obj1->GetComponent<Component::sprite_renderer>()->sorting_order = 3;
    obj2->GetComponent<Component::sprite_renderer>()->sorting_order = 2;
    obj3->GetComponent<Component::sprite_renderer>()->sorting_order = 1;

    obj4->GetComponent<Component::animator>()->sorting_order = 0;
    // obj4->GetComponent<Component::animator>()->sorting_order = 4;

    // obj5->GetComponent<Component::tilemap>()->sorting_order = 0;
    obj5->GetComponent<Component::tilemap>()->sorting_order = 6;

    obj7->GetComponent<Component::tmxmap>()->layer_sorting_order[0] = 5;
    obj7->GetComponent<Component::tmxmap>()->layer_sorting_order[1] = 2;

    // obj1->RemoveComponent<Component::sprite_renderer>();

    // obj1->GetComponent<Component::sprite_renderer>()->is_visible = false;
    // obj2->GetComponent<Component::sprite_renderer>()->is_visible = false;
    // obj3->GetComponent<Component::sprite_renderer>()->is_visible = false;
    // obj4->GetComponent<Component::animator>()->is_visible = false;
    // obj5->GetComponent<Component::tilemap>()->is_visible = false;
    // obj6->GetComponent<Component::atlas_animator>()->is_visible = false;
    // obj7->GetComponent<Component::tmxmap>()->is_enable = false;
    // obj7->GetComponent<Component::tmxmap>()->is_visible = false;

    scene1->AddChild(obj1);
    scene1->AddChild(obj2);
    scene1->AddChild(obj3);
    scene1->AddChild(obj4);
    scene1->AddChild(obj5);
    scene1->AddChild(obj6);
    scene1->AddChild(obj7);

    scene_manager = new SceneManager();
    scene_manager->AddScene(scene1);

    scene_manager->SetSortingOrder(obj4, 7);
    scene_manager->SetSortingOrder(obj7, 1, 7);
  }

  void OnUpdate() override {
    obj4->GetComponent<Component::animator>()->PlayAnim(vector<int>{1, 2, 3, 4}, 5);
    obj6->GetComponent<Component::atlas_animator>()->PlayAnim("run_right", 5);
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
