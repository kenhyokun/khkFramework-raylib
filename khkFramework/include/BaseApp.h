/*
  license under zlib license
  Copyright (C) 2020-2021 Kevin Haryo Kuncoro

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
#include<CCamera.h>
#include<File.h>
#include<KeyButton.h>

using namespace std;

struct BaseApp{
  BaseApp(int _window_width = 800,
	  int _window_height = 450,
	  string _title = "My Game",
	  bool _is_resizable = true);

  v2 ClampValue(v2 value, v2 min, v2 max);
  void SetGameScreen(int _game_screen_width, int _game_screen_height);
  static void AddKeyButton(string action_name, int key_code);
  static Key* GetKeyButton(string action_name);
  static int SettingCallback(IniDispatch *dispatch, void *v_null);
  void Init(int texture_filter_mode = FILTER_POINT);
  void Update();
  void Draw();
  void Run();

protected:
  int target_fps = 60;
  int window_width = 800;
  int window_height = 450;
  string title = "My Game";
  bool is_resizable = true;
  int game_screen_width = window_width;
  int game_screen_height = window_height;
  int min_window_width = 0;
  int min_window_height = 0;
  v2 mouse;
  v2 virtual_mouse;
  v2 clamp_virtual_mouse;
  float scale = 0.0f;
  RenderTexture2D blank_renderer;
  CCamera *camera;
  static map<string, Key*> key_map;

  virtual void OnInit();
  virtual void OnUpdate();
  virtual void OnDraw();
  virtual void OnDrawGUI();
  virtual void OnClear();
};

#endif
