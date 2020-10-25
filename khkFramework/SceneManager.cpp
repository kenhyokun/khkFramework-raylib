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

#include<SceneManager.h>

SceneManager::SceneManager(){
  scene_list = new Node("scene manager node");
}

void SceneManager::AddScene(Scene *scene){
  SortingDataComponent *sorting_component = new SortingDataComponent();

  _CreateSortingDataList(scene, sorting_component);
  _BubbleSort(sorting_component);

  scene->AddComponent<SortingDataComponent*>(sorting_component);
  scene_list->AddChild(scene);
}

void SceneManager::Draw(){
  for(int i = 0; i < scene_list->GetChild(0)->GetComponent<SortingDataComponent*>()->sort_data_list.size(); i++){

    scene_list->GetChild(0)->GetComponent<SortingDataComponent*>()->
      sort_data_list.at(i).node->GetComponent<Component::sprite_renderer>()->
      Draw();
  }
}

void SceneManager::_GetNodeOnTree(Node *node, SortingDataComponent * sorting_component){
  if(node->IsHasDrawableComponent()){
    SortingData data;
    data.node = node;
    data.sorting_order =
      node->GetComponent<Component::sprite_renderer>()->sorting_order;

    sorting_component->sort_data_list.push_back(data);
  }

  if(node->GetChild()->size() > 0){
    for(int i = 0; i < node->GetChild()->size(); i++){
      _GetNodeOnTree(node->GetChild(i), sorting_component);
    }
  }

}

void SceneManager::_CreateSortingDataList(Scene *scene, SortingDataComponent *sorting_component){
  _GetNodeOnTree(scene, sorting_component); // call recursive function to get all node on tree.
}

void SceneManager::_BubbleSort(SortingDataComponent *sorting_component){
  for(int i = 0; i < sorting_component->sort_data_list.size(); i++){
    int sort_index = i;
    int sorting_order = sorting_component->sort_data_list.at(i).sorting_order;

    for(int j = i + 1; j < sorting_component->sort_data_list.size(); j++){
      if(sorting_component->sort_data_list.at(j).sorting_order < sorting_order){
	sort_index = j;
	sorting_order = sorting_component->sort_data_list.at(j).sorting_order;
      }
    }

    std::swap(sorting_component->sort_data_list[sort_index],
	      sorting_component->sort_data_list[i]);
  }
}

Scene* SceneManager::GetScene(string name){return scene_list->GetChild(name);}
