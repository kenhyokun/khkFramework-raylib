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

#define max(a, b) ((a)>(b)? (a) : (b))
#define min(a, b) ((a)<(b)? (a) : (b))

map<string, Key*> BaseApp::key_map;

BaseApp::BaseApp(int _window_width, int _window_height, string _title){
  window_width = _window_width;
  window_height = _window_height;
  game_screen_width = window_width;
  game_screen_height = window_height;
  min_window_width = _window_width;
  min_window_height = _window_height;
  title = _title;
}

v2 BaseApp::ClampValue(v2 value, v2 min, v2 max){
  v2 result = value;
  result.x = (result.x > max.x) ? max.x : result.x;
  result.x = (result.x < max.x) ? min.x : result.x;
  result.y = (result.y > max.y) ? max.y : result.y;
  result.y = (result.y < max.y) ? min.y : result.y;
  return result;
}

void BaseApp::SetGameScreen(int _game_screen_width, int _game_screen_height){
  if(_game_screen_width < window_width &&
     _game_screen_height < window_height){
    
    game_screen_width = _game_screen_width;
    game_screen_height = _game_screen_height;
  }
}

void BaseApp::AddKeyButton(string action_name, int key_code){
  key_map.insert(pair<string, Key*>(action_name, new Key{key_code}));
}

int BaseApp::SettingCallback(IniDispatch *dispatch, void *v_null){
#define is_section(SECTION) (ini_array_match(SECTION, dispatch->append_to, '.', dispatch->format)) 

  if(dispatch->type == INI_KEY){
    if(is_section("keyboard_controller")){

      string str = dispatch->value;
      int key_code = 0;

      if(str.length() > 1){
	key_code = Key::GetFunctionKeyCode(str); 
      } 
      else{
	key_code = (int)dispatch->value[0];
      }

      AddKeyButton(dispatch->data, key_code);

    }
  }

  return 0;

#undef is_section

}

void BaseApp::Init(int texture_filter_mode){
  // init app
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  InitWindow(window_width, window_height, title.c_str());
  SetWindowMinSize(min_window_width, min_window_height);

  blank_renderer = LoadRenderTexture(game_screen_width,
				     game_screen_height);

  SetTextureFilter(blank_renderer.texture, texture_filter_mode);
  SetTargetFPS(target_fps);

  // init camera
  camera = new CCamera(game_screen_width, game_screen_height);

  ConfigFile setting_conf_file;
  if(setting_conf_file.LoadFile("./resources/settings.cfg", SettingCallback) == 0){
    log("Found settings.cfg file");
  }
  else{
    log("settings.cfg file not found");
  }

  // overiding init 
  OnInit();
}

void BaseApp::Update(){
  // update window/screen scale
  scale = min((float)GetScreenWidth() / game_screen_width,
	      (float)GetScreenHeight() / game_screen_height);

  // update mouse
  mouse = GetMousePosition();
  virtual_mouse = { 0 };
  virtual_mouse.x = (mouse.x - (GetScreenWidth() - (game_screen_width * scale) ) * 0.5f) / scale;
  virtual_mouse.y = (mouse.y - (GetScreenHeight() - (game_screen_height * scale) ) * 0.5f) / scale;

  clamp_virtual_mouse = ClampValue(virtual_mouse,
				   (v2){0, 0},
				   (v2){(float)game_screen_width, (float)game_screen_height});

  // update camera
  camera->Follow();

  // overiding update
  OnUpdate();
}

void BaseApp::Draw(){
  BeginDrawing(); //// draw to window

  ClearBackground(BLACK); // black letterbox color

  BeginTextureMode(blank_renderer); // --- draw to blank_renderer texture

  ClearBackground(RAYWHITE);

  BeginMode2D(camera->camera);
  OnDraw(); 
  EndMode2D();

  OnDrawGUI();

  EndTextureMode(); // ---


  // draw blank_renderer texture to window
  DrawTexturePro(blank_renderer.texture,
		 (Rectangle){0.0f, 0.0f, (float)blank_renderer.texture.width, (float)-blank_renderer.texture.height},
		 (Rectangle){
		   (GetScreenWidth() - ((float)game_screen_width * scale)) * 0.5f,
		     (GetScreenHeight() - ((float)game_screen_height * scale)) * 0.5f,
		     (float)game_screen_width * scale,
		     (float)game_screen_height * scale
		     },
		 (v2){0, 0},
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

  UnloadRenderTexture(blank_renderer);
  CloseWindow();
}

Key* BaseApp::GetKeyButton(string action_name){return key_map.at(action_name);}

void BaseApp::OnInit(){}
void BaseApp::OnUpdate(){}
void BaseApp::OnDraw(){}
void BaseApp::OnDrawGUI(){}
