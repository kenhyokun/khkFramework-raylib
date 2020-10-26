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
#include<TextureAtlas.h>

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
    - AtlasAnimator
    - Tilemap
    - TMXMap
  */

  enum DrawableType{
    NONE,
    SPRITE_RENDERER,
    ANIMATOR,
    ATLAS_ANIMATOR,
    TILEMAP,
    TMXMAP
  };

  struct BaseComponent{
    bool is_enable = true;

    void Attach();
    void SetNode(Node *_node);
    Node* GetNode();
  protected:
    Node *node = nullptr; // component owner

    virtual void _OnAttach();
  };

  struct DrawableBaseComponent{
    int sorting_order = 0;
    bool is_visible = true;

  protected:
    Texture2D *texture = nullptr;
    v2 pivot;
    Rectangle src_rect;
    Rectangle dst_rect;
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
    int max_width = 0;
    int max_height = 0;

    int _GetIndex(int column, int row);
    v2 _GetTransformRotation(int column, int row); // tile transformation rotation
  };


  /*
    SpriteRenderer Component
  */
  typedef struct SpriteRenderer : BaseComponent, DrawableBaseComponent{
    SpriteRenderer(Texture2D *_texture);
    void Draw(); // draw texture with center pivot point
  } *sprite_renderer;


  /*
    Animator Component
  */
  typedef struct Animator : BaseComponent, DrawableBaseComponent, GridBaseComponent{
    Animator(Texture2D *_texture, int _frame_width, int _frame_height);
    void PlayAnim(vector<int> anim_frame, int fps);
    void Draw();

    int GetFrameWidth();
    int GetFrameHeight();

  protected:
    int frame_index = 0;
    int frame_counter = 0;
    int frame_width = 0;
    int frame_height = 0;
  } *animator;


  /*
    AtlasAnimator Component
  */
  typedef struct AtlasAnimator : BaseComponent, DrawableBaseComponent{
    AtlasAnimator(TextureAtlas *_texture_atlas);
    void PlayAnim(string _anim_name, int fps);
    void DebugDraw();
    void Draw();

  protected:

    map<string, vector<Texture2D>> anim_frame;
    int map_index = 0;
    string last_posible_anim_name = "nan";
    vector<Texture2D> frame_list;

    bool _IsPosibleAnimName(string region_map_name, string *posible_anim_name, int *index);
    void _CreateAnimFrame();
  
    TextureAtlas *texture_atlas = nullptr;
    int frame_counter = 0;
    int frame_index = 1;
    string anim_name;
    Texture2D curr_texture;
    v2 pivot {0.0f, 0.0f};
  } *atlas_animator;


  /*
    Tilemap Component
  */
  typedef struct Tilemap : BaseTilemap, DrawableBaseComponent{
    Tilemap(Texture2D *_texture, Grid *_grid, int* _tile_map);
    void Draw();

    bool IsTiled(int column, int row);

  protected:
    int *tile_map;
  } *tilemap;


  /*
    TMXMap Component
  */
  typedef struct TMXMap : BaseTilemap, DrawableBaseComponent{
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

}; // component namespace

#endif
