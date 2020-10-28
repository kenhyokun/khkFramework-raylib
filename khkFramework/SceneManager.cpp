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
  scene_list = new Node("SceneManager scene list");
}

void SceneManager::AddScene(Scene *scene){
  SortingDataComponent *sorting_component = new SortingDataComponent();

  _CreateSortingDataList(scene, sorting_component);
  _BubbleSort(sorting_component);

  scene->AddComponent<SortingDataComponent*>(sorting_component);
  scene_list->AddChild(scene);

  if(selected_scene == nullptr){
    selected_scene = scene;

    selected_scene_sort_component = 
      scene->AddComponent<SortingDataComponent*>(sorting_component);
  }

}

void SceneManager::Draw(){
  if(scene_list->GetChild()->size() > 0 &&
     selected_scene->GetChild()->size() > 0){

    for(int i = 0; i < selected_scene_sort_component->sort_data_list.size(); i++){

      switch(selected_scene_sort_component->
	     sort_data_list.at(i).node->
	     component_entity.drawable_type){

      case SPRITE_RENDERER:
	selected_scene_sort_component->
	  sort_data_list.at(i).node->
	  GetComponent<Component::sprite_renderer>()->
	  Draw();
	break;

      case ANIMATOR:
	selected_scene_sort_component->
	  sort_data_list.at(i).node->
	  GetComponent<Component::animator>()->
	  Draw();
	break;

      case ATLAS_ANIMATOR:
	selected_scene_sort_component->
	  sort_data_list.at(i).node->
	  GetComponent<Component::atlas_animator>()->
	  Draw();
	break;

      case TILEMAP:
	selected_scene_sort_component->
	  sort_data_list.at(i).node->
	  GetComponent<Component::tilemap>()->
	  Draw();
	break;

      case TMXMAP:
	selected_scene_sort_component->
	  sort_data_list.at(i).node->
	  GetComponent<Component::tmxmap>()->
	  Draw(selected_scene_sort_component->sort_data_list.at(i).layer_index);
	break;

      } // switch
    } // for
  } // if size > 0
}

void SceneManager::_GetNodeOnTree(Node *node, SortingDataComponent * sorting_component){
  bool should_push = true;
  
  if(node->IsHasDrawableComponent()){
    SortingData data;
    data.node = node;

    if(node->component_entity.drawable_type == SPRITE_RENDERER){
      data.sorting_order =
	node->GetComponent<Component::sprite_renderer>()->sorting_order;
    }
    else if(node->component_entity.drawable_type == ANIMATOR){
      data.sorting_order =
	node->GetComponent<Component::animator>()->sorting_order;
    }
    else if(node->component_entity.drawable_type == ATLAS_ANIMATOR){
      data.sorting_order =
	node->GetComponent<Component::atlas_animator>()->sorting_order;
    }
    else if(node->component_entity.drawable_type == TILEMAP){
      data.sorting_order =
	node->GetComponent<Component::tilemap>()->sorting_order;
    }
    else if(node->component_entity.drawable_type == TMXMAP){
      should_push = false;

      data.layer_sorting_order =
	node->GetComponent<Component::tmxmap>()->layer_sorting_order;

      data.layer_count=
	node->GetComponent<Component::tmxmap>()->GetLayerCount();

      for(int i = 0; i < data.layer_count; i++){
	data.layer_index = i;

	data.sorting_order =
	  node->GetComponent<Component::tmxmap>()->layer_sorting_order[i];

	sorting_component->sort_data_list.push_back(data);
      }

    }

    if(should_push){
      sorting_component->sort_data_list.push_back(data);
    }

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

void SceneManager::SetSortingOrder(Node *node, int sorting_order){

  // set node sorting order
  switch(node->component_entity.drawable_type){

  case SPRITE_RENDERER:
    node->GetComponent<Component::sprite_renderer>()->sorting_order =
      sorting_order;
    break;

  case ANIMATOR:
    node->GetComponent<Component::animator>()->sorting_order =
      sorting_order;
    break;

  case ATLAS_ANIMATOR:
    node->GetComponent<Component::atlas_animator>()->sorting_order =
      sorting_order;
    break;

  case TILEMAP:
    node->GetComponent<Component::tilemap>()->sorting_order =
      sorting_order;
    break;

  case TMXMAP:
    break;

  }

  // set selected sort component list at index(n) sorting order
  selected_scene_sort_component->
    sort_data_list.at(selected_scene_sort_component->GetIndexAt(node)).sorting_order = sorting_order;

  _BubbleSort(selected_scene_sort_component);
}

void SceneManager::SetSortingOrder(Node *node,
				   int layer_index,
				   int sorting_order){

  node->GetComponent<Component::tmxmap>()->layer_sorting_order[layer_index] =
    sorting_order;

  selected_scene_sort_component->
    sort_data_list.at(selected_scene_sort_component->GetIndexAt(node, layer_index)).sorting_order = sorting_order;

  selected_scene_sort_component->
    sort_data_list.at(selected_scene_sort_component->GetIndexAt(node, layer_index)).layer_index = layer_index;

  _BubbleSort(selected_scene_sort_component);
}

Scene* SceneManager::GetScene(int scene_index){return scene_list->GetChild(scene_index);}
Scene* SceneManager::GetScene(string scene_name){return scene_list->GetChild(scene_name);}
Scene* SceneManager::GetSelectedScene(){return selected_scene;}
