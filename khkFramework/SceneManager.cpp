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

  _CreateSortingDataList(scene);
  _BubbleSort();

  BaseComponent *component = new BaseComponent();
  component->user_data = &sort_data_list;
  scene->AddComponent<base_component>(component);

  scene_list->AddChild(scene);
}

void SceneManager::Draw(){

  vector<SortingData> *vec = static_cast<vector<SortingData>*>(scene_list->GetChild(0)->GetComponent<Component::base_component>()->user_data);
  
  // for(int i = 0; i < vec->size(); i++){
  //   int draw_index = vec->at(i).index;
  //   scene_list->GetChild(0)->GetChild(draw_index)->GetComponent<Component::sprite_renderer>()->Draw();
  // }

  for(int i = 0; i < vec->size(); i++){
    vec->at(i).node->GetComponent<Component::sprite_renderer>()->Draw();
  }

  vec = nullptr;

}

void SceneManager::_GetNodeOnTree(Node *node, SortingData *data){
  cout<<node->name<<" have "<<node->GetChild()->size()<<" childs"<<endl;

  if(node->IsHasDrawableComponent()){
    data->node = node;
    // data->index = i;

    data->sorting_order =
      node->GetComponent<Component::sprite_renderer>()->sorting_order;

    sort_data_list.push_back(*data);
  }

  if(node->GetChild()->size() > 0){
    for(int i = 0; i < node->GetChild()->size(); i++){
      _GetNodeOnTree(node->GetChild(i), data);
    }
  }
}

void SceneManager::_CreateSortingDataList(Scene *scene){
  SortingData data;

  _GetNodeOnTree(scene, &data); // call recursive function to get all node on tree.

  // for(int i = 0; i < scene->GetChild()->size(); i++){
  //   if(scene->GetChild(i)->IsHasDrawableComponent()){
  //     data.index = i;
      
  //     data.sorting_order =
  // 	scene->GetChild(i)->
  // 	GetComponent<Component::sprite_renderer>()->sorting_order;

  //     sort_data_list.push_back(data);
  //   }
  // }

}

void SceneManager::_BubbleSort(){
  for(int i = 0; i < sort_data_list.size(); i++){
    int sort_index = i;
    int sorting_order = sort_data_list.at(i).sorting_order;

    for(int j = i + 1; j < sort_data_list.size(); j++){
      if(sort_data_list.at(j).sorting_order < sorting_order){
	sort_index = j;
	sorting_order = sort_data_list.at(j).sorting_order;
      }
    }
    std::swap(sort_data_list[sort_index], sort_data_list[i]);
  }

}

Scene* SceneManager::GetScene(string name){return scene_list->GetChild(name);}
