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

#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include<Component.h>

typedef Node Scene;

struct SceneManager{
  Scene *scene_manager_node;

  SceneManager(){
    scene_manager_node = new Node("scene manager node");
  }

  inline void AddScene(Scene *scene);
  inline void LoadScene(string scene_name);
  inline void Draw();

  inline Scene* GetScene(string scene_name);

protected:
  inline void _Sort(Scene *scene); // sort scene child node that have drawable component by sorting order
};

void SceneManager::AddScene(Scene *scene){
  scene_manager_node->AddChild(scene);
  _Sort(scene);
}

void SceneManager::Draw(){
  for(int i = 0; i < scene_manager_node->GetChild(0)->GetChild()->size(); i++){
    if(scene_manager_node->GetChild(0)->GetChild(i)->IsHasDrawableComponent()){
      scene_manager_node->GetChild(0)->GetChild(i)->GetComponent<Component::sprite_renderer>()->Draw();
    }
  }
}

void SceneManager::_Sort(Scene *scene){}

Scene* SceneManager::GetScene(string name){return scene_manager_node->GetChild(name);}

#endif
