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

#include<BaseApp.h>

BaseApp::BaseApp(int _window_width, int _window_height, string _title){
  window_width = _window_width;
  window_height = _window_height;
  game_screen_width = window_width;
  game_screen_height = window_height;
  title = _title;
}

Vector2 BaseApp::ClampValue(Vector2 value, Vector2 min, Vector2 max){
  Vector2 result = value;
  result.x = (result.x > max.x) ? max.x : result.x;
  result.x = (result.x < max.x) ? min.x : result.x;
  result.y = (result.y > max.y) ? max.y : result.y;
  result.y = (result.y < max.y) ? min.y : result.y;
  return result;
}

void BaseApp::SetGameScreen(int _game_screen_width, int _game_screen_height){
  game_screen_width = _game_screen_width;
  game_screen_height = _game_screen_height;
}

void BaseApp::Init(){
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  InitWindow(window_width, window_height, title.c_str());
  SetWindowMinSize(min_window_width, min_window_height);

  target = LoadRenderTexture(game_screen_width,
			     game_screen_height);

  SetTextureFilter(target.texture, FILTER_BILINEAR);
  SetTargetFPS(target_fps);

  OnInit();
}

void BaseApp::Update(){
  // update mouse
  mouse = GetMousePosition();
  virtual_mouse = { 0 };
  virtual_mouse.x = (mouse.x - (GetScreenWidth() - (game_screen_width * scale) ) * 0.5f) / scale;
  virtual_mouse.y = (mouse.y - (GetScreenHeight() - (game_screen_height * scale) ) * 0.5f) / scale;

  virtual_mouse = ClampValue(virtual_mouse,
			     (Vector2){0, 0},
			     (Vector2){(float)game_screen_width, (float)game_screen_height});
  // update mouse

  // update window/screen scale
  scale = min((float)GetScreenWidth() / game_screen_width,
	      (float)GetScreenHeight() / game_screen_height);

  OnUpdate();
}

void BaseApp::Draw(){
  BeginDrawing(); //// draw to window

  ClearBackground(BLACK); // black letterbox color

  BeginTextureMode(target); // --- draw to target texture

  ClearBackground(RAYWHITE);
  OnDraw(); 

  EndTextureMode(); // ---

  // draw target texture to window
  DrawTexturePro(target.texture,
		 (Rectangle){0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height},
		 (Rectangle){
		   (GetScreenWidth() - ((float)game_screen_width * scale)) * 0.5f,
		     (GetScreenHeight() - ((float)game_screen_height * scale)) * 0.5f,
		     (float)game_screen_width * scale,
		     (float)game_screen_height * scale
		     },
		 (Vector2){0, 0},
		 0.0f,
		 WHITE
		 );

  EndDrawing(); ////
}

void BaseApp::Run(){
  while(!WindowShouldClose()){
    Update();
    Draw();
  }

  UnloadRenderTexture(target);
  CloseWindow();
}

void BaseApp::OnInit(){}
void BaseApp::OnUpdate(){}
void BaseApp::OnDraw(){}
