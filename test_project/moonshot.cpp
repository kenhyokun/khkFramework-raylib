/*
  License under zlib license 
  Copyright (C) 2020 Kevin Haryo Kuncoro

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
  claim that you wrote the original software. If you use this software
  in a product, an acknowledgment in the product documentation would be
  appreciated but is not required.

  2. Altered source versions must be plainly marked as such, and must not be
  misrepresented as being the original software.

  3. This notice may not be removed or altered from any source distribution.

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

  Texture2D tile, octocat;
  Node *tilemap, *hero;

  App(int _window_width, int _window_height, string _title) :
    BaseApp(_window_width, _window_height, _title){}

  ~App(){
  }

  void OnInit() override {
    tile = LoadTexture("./resources/images/tile.png");
    octocat = LoadTexture("./resources/images/octocat.png");

    tilemap = new Node("tilemap");
    hero = new Node("hero octocat");
    hero->AddComponent<Component::animator>(new Animator(75, 119, &octocat));
    hero->SetPosition(v2{150, 150});
  }

  void OnUpdate() override {
    hero->GetComponent<Component::animator>()->PlayAnim(vector<int>{1,2,3,4}, 5);
  }

  void OnDraw() override {
    hero->GetComponent<Component::animator>()->Draw();
  }

};

int main(){
  App app(800, 450, "My Game");
  app.Init();
  app.Run();

  return 0;
}
