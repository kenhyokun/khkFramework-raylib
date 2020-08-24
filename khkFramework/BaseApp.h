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
#include<raylib.h>

using namespace std;

struct BaseApp{
  int target_fps = 60;
  int window_width = 800;
  int window_height = 450;
  string title = "My Game";
  int game_screen_width = window_width;
  int game_screen_height = window_height;
  int min_window_width = 320;
  int min_window_height = 240;
  Vector2 mouse, virtual_mouse;
  float scale = 0.0f;
  RenderTexture2D target;

  BaseApp(int _window_width = 800, int _window_height = 450, string _title = "My Game");
  Vector2 ClampValue(Vector2 value, Vector2 min, Vector2 max);
  void SetGameScreen(int _game_screen_width, int _game_screen_height);
  void Update();
  void Draw();
  void Run();

  virtual void OnInit();
  virtual void OnUpdate();
  virtual void OnDraw();

};

#endif
