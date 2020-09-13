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

#ifndef COMPONENT_H
#define COMPONENT_H

#include<Node.h>
#include<File.h>

struct Grid{
  int width = 0;
  int height = 0;
  int column = 0;
  int row = 0;
};

namespace Component{

  /*
    Available component:
    - SpriteRenderer
    - Animator
    - Tilemap
    - TMXMap
  */

  struct BaseComponent{
    Node* node = nullptr; // component owner
    bool is_enable = true;

    inline void Attach(){
      _OnAttach();
    }

  protected:
    virtual void _OnAttach(){}
  };

  struct DrawableBaseComponent{
    int sorting_order;
  };

  struct GridBaseComponent{
    Grid* GetGrid();

  protected:
    Grid *grid = nullptr;
    int texture_column = 0;
    int texture_row = 0;

    Rectangle _GetSrcRect(int tile);
  };

  struct BaseTilemap : BaseComponent, GridBaseComponent{
    int GetMaxWidth();
    int GetMaxHeight();

  protected:
    Texture2D *texture;
    int max_width = 0;
    int max_height = 0;

    int _GetIndex(int column, int row);
    v2 _GetTransformRotation(int column, int row); // tile transformation rotation
  };
  

  /*
    SpriteRenderer Component
  */
  typedef struct SpriteRenderer : BaseComponent{
    Texture2D *texture = nullptr;

    SpriteRenderer(Texture2D *_texture);
    void Draw(int state = 0); // draw texture with center pivot point

  protected:
    v2 pivot;
    Rectangle src_rect;
    Rectangle dst_rect;
  } *sprite_renderer;


  /*
    Animator Component
  */
  typedef struct Animator : SpriteRenderer, GridBaseComponent{
    int frame_index;
    int frame_counter;

    Animator(Texture2D *_texture, int _frame_width, int _frame_height);
    void PlayAnim(vector<int> anim_frame, int fps);
    void Draw();

    int GetFrameWidth();
    int GetFrameHeight();

  protected:
    int frame_width;
    int frame_height;

  } *animator;


  /*
    Tilemap Component
  */
  typedef struct Tilemap : BaseTilemap{
    Tilemap(Texture2D *_texture, Grid *_grid, int* _tile_map);
    void Draw();

    bool IsTiled(int column, int row);

  protected:
    int *tile_map;

  } *tilemap;


  /*
    TMXMap Component
  */
  typedef struct TMXMap : BaseTilemap{
    TMXMap(Texture2D *_texture, string tmx_file_src);
    void Draw(int layer_index);
    void Draw();
    void PrintMapAttribute();

    bool IsTiled(int layer_index, int column, int row);

  protected:
    int layer_count;
    string map_orientation = "";
    vector<string> map_layer_name_list;
    vector<string> map_layer_str_list;
    vector<int*> map_layer_list;

  } *tmxmap;

  typedef struct SceneComponent : BaseComponent{
    map<string, Node*> attached_node;
    void AttachNode(Node *node);
  } *scene_component;

}; // component namespace

#endif
