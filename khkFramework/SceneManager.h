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
#include<algorithm>

using namespace Component;

typedef Node Scene;

/*
TODO[Kevin]:
- update scene sorting data list when scene child get 
  changed (removed or added new child) / drawable component
  sorting order changed.
*/

struct SceneManager{

  struct SortingData{
    Node *node = nullptr;
    int sorting_order = 0;
    DrawableType drawable_type = NONE;

    // multiple layer drawable component
    int layer_count = 0;
    int *layer_sorting_order = nullptr;
    int layer_index = 0;
  };

  struct SortingDataComponent : BaseComponent{
    vector<SortingData> sort_data_list;

    inline int GetIndexAt(Node *node){
      for(int i = 0; i < sort_data_list.size(); i++){
	if(sort_data_list[i].node == node){
	  return i;
	}
      }
      return -1;
    }

    inline int GetIndexAt(Node *node, int layer_index){
      for(int i = 0; i < sort_data_list.size(); i++){
	if(sort_data_list[i].node == node &&
	   sort_data_list[i].layer_index == layer_index){
	  return i;
	}
      }
      return -1;
    }

  };

  SceneManager();

  void AddScene(Scene *scene);
  void LoadScene(int scene_index);
  void LoadScene(string scene_name);
  void Draw();

  void SetSortingOrder(Node *node, int sorting_order);
  void SetSortingOrder(Node *node, int layer_index, int sorting_order);
  Scene* GetScene(int scene_index);
  Scene* GetScene(string scene_name);

protected:
  Scene *scene_list = nullptr;
  Scene *selected_scene = nullptr;
  SortingDataComponent *selected_scene_sort_component= nullptr;

  void _SetDrawableType(Node* node);
  void _GetNodeOnTree(Node *node, SortingDataComponent * sorting_component);
  void _CreateSortingDataList(Scene *scene, SortingDataComponent * sorting_component);
  void _BubbleSort(SortingDataComponent *sorting_component); // sort scene draw by drawable component sorting order

};

#endif
