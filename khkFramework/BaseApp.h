/*
  license under zlib license
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

#ifndef BASEAPP_H
#define BASEAPP_H

#include<iostream>
#include<m_raylib.h>
#include<Node.h>
#include<KeyButton.h>

using namespace std;

struct CCamera{
  Camera2D camera;
  Node *target =  nullptr;

  inline void Init(int offset_x, int offset_y){
    camera = {0};
    camera.offset = v2{(float)offset_x, (float)offset_y};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
  }

  inline void AttachTo(Node *node){target = node;}

  inline void Follow(){
    if(target != nullptr){
      camera.target = target->GetPosition();
    }
  }

};

struct BaseApp{
  int target_fps = 60;
  int window_width = 800;
  int window_height = 450;
  string title = "My Game";
  int game_screen_width = window_width;
  int game_screen_height = window_height;
  int min_window_width = 320;
  int min_window_height = 240;
  v2 mouse, virtual_mouse;
  float scale = 0.0f;
  RenderTexture2D target;

  CCamera *camera;
  static map<string, Key*> key_map;

  BaseApp(int _window_width = 800,
	  int _window_height = 450,
	  string _title = "My Game");

  v2 ClampValue(v2 value, v2 min, v2 max);
  void SetGameScreen(int _game_screen_width, int _game_screen_height);
  static void AddKeyButton(string action_name, int key_code);
  static Key* GetKeyButton(string action_name);
  void Init(int texture_filter_mode = 0);
  void Update();
  void Draw();
  void Run();

  virtual void OnInit();
  virtual void OnUpdate();
  virtual void OnDraw();
  virtual void OnDrawGUI();

};

#endif
