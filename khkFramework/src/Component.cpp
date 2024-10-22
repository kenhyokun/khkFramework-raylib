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

#include<Component.h>

void Component::BaseComponent::Attach(){_OnAttach();}
void Component::BaseComponent::_OnAttach(){}
void Component::BaseComponent::SetNode(Node *_node){if(_node != nullptr && node == nullptr) node = _node;}
Node* Component::BaseComponent::GetNode(){return node;}

void Component::DrawableBaseComponent::Draw(int layer_index){
  if(is_enable && is_visible){
    if(texture != nullptr){
      _OnDraw(layer_index);
    }
  }
}

void Component::DrawableBaseComponent::_OnDraw(int layer_index){}

Rectangle Component::GridBaseComponent::_GetSrcRect(int tile){
  int texture_column = texture->width / grid->width;
  int texture_row = texture->height / grid->height;
  int begin_column = 1;
  int range_column = texture_column - begin_column;
  int temp_row = (tile + range_column) / texture_column;
  int end_column_in_row = temp_row * texture_column;
  int temp_column = texture_column - (end_column_in_row - tile);
  
  int src_x = temp_column - 1;
  int src_y = temp_row - 1;

  return Rectangle{
    (float)src_x * (float)grid->width,
      (float)src_y * (float)grid->height,
      (float) grid->width,
      (float) grid->height
      };
}

Grid* Component::GridBaseComponent::GetGrid(){return grid;}

v2 Component::BaseTilemap::GetGridPosition(int column, int row){
  float x0 = node->GetPosition().x - (max_width / 2);
  float y0 = node->GetPosition().y - (max_height / 2);
  float _x = (grid->width * column) + (grid->width / 2);
  float _y = (grid->height * row) + (grid->height / 2);
  float tx = x0 + _x;
  float ty = y0 + _y;

  if(node->GetRotation() > 0){
    return TransformRotation(Deg2Rad(node->GetRotation()), v2{tx, ty}, node->GetPosition());
  }
  return v2{tx, ty};
}

int Component::BaseTilemap::GetMaxWidth(){return max_width;}
int Component::BaseTilemap::GetMaxHeight(){return max_height;}
int Component::BaseTilemap::_GetIndex(int column, int row){return (row * grid->column + column);}


/*
  SpriteRenderer Component
*/
Component::SpriteRenderer::SpriteRenderer(Texture2D *_texture){
  texture = _texture;
  src_rect = {0.0f, 0.0f, (float)texture->width, (float)texture->height};
}

void Component::SpriteRenderer::_OnDraw(int layer_index){
  pivot = {((float)texture->width * node->GetScale().x) / 2.0f,
	   ((float)texture->height * node->GetScale().y) / 2.0f};

  src_rect = {0.0f, 0.0f, (float)texture->width, (float)texture->height};
    
  dst_rect = {node->GetPosition().x,
	      node->GetPosition().y,
	      (float)texture->width,
	      (float)texture->height};

  dst_rect.width *= node->GetScale().x;
  dst_rect.height *= node->GetScale().y;

  DrawTexturePro(*texture,
		 src_rect,
		 dst_rect,
		 pivot,
		 node->GetRotation(),
		 WHITE);
}


/*
  Animator Component
*/
Component::Animator::Animator(int frame_width,
			      int frame_height,
			      Texture2D *_texture){

  texture = _texture; 

  grid = new Grid();
  grid->width = frame_width;
  grid->height = frame_height;

  src_rect = {0.0f, 0.0f, (float)frame_width, (float)frame_height};
}

void Component::Animator::PlayAnim(vector<int> anim_frame, int fps){
  if(texture != nullptr){
    frame_counter++;

    if(frame_counter >= (60 / fps)){
      frame_counter = 0;
      frame_index++;
    }

    if(frame_index > anim_frame.size() - 1){
      frame_index = 0;
    }

    src_rect = _GetSrcRect(anim_frame.at(frame_index));
  }
}

void Component::Animator::_OnDraw(int layer_index){
  pivot = {((float)grid->width * node->GetScale().x) / 2.0f,
	   ((float)grid->height * node->GetScale().y) / 2.0f};

  dst_rect = {node->GetPosition().x,
	      node->GetPosition().y,
	      (float)grid->width,
	      (float)grid->height
  };

  dst_rect.width *= node->GetScale().x;
  dst_rect.height *= node->GetScale().y;

  DrawTexturePro(*texture,
		 src_rect,
		 dst_rect,
		 pivot,
		 node->GetRotation(),
		 WHITE);

}


/* 
   AtlasAnimator Component
*/
Component::AtlasAnimator::AtlasAnimator(TextureAtlas *_texture_atlas){
  texture_atlas = _texture_atlas;
  _CreateAnimFrame();
  frame_list.clear();
}

void Component::AtlasAnimator::PlayAnim(string _anim_name, int fps){
  if(texture != nullptr){
    frame_counter++;
    anim_name = _anim_name;

    if(frame_counter >= (60 / fps)){
      frame_counter = 0;
      frame_index++;

      if(frame_index > anim_frame.at(anim_name).size()){
	frame_index = 1;
      }
    }

    AtlasRegion atlas_region = 
      texture_atlas->GetRegion(anim_name + "_" + to_string(frame_index));

    v2i size = atlas_region.size;
    v2i origin_size = atlas_region.orig;
    v2i offset = atlas_region.offset;

    // draw position
    v2 position = {node->GetPosition().x + offset.x,
		   node->GetPosition().y + offset.y};

    pivot = {((float)origin_size.x * node->GetScale().x) / 2.0f,
	     ((float)origin_size.y * node->GetScale().y) / 2.0f};
  
    src_rect = {0, 0,
		(float)size.x,
		(float)size.y};

    dst_rect = {position.x,
		position.y,
		(float)size.x,
		(float)size.y};
  }
}

void Component::AtlasAnimator::DebugDraw(){
  if(is_enable && is_visible){
    for(int i = 0; i < anim_frame.at(anim_name).size(); ++i){
      Rectangle _dst_rect = {dst_rect.x + (dst_rect.width * i),
			     dst_rect.y - dst_rect.height,
			     dst_rect.width,
			     dst_rect.height};

      DrawTexturePro(anim_frame.at(anim_name).at(i),
		     src_rect,
		     _dst_rect,
		     pivot,
		     node->GetRotation(),
		     WHITE);
    }
  }
}

void Component::AtlasAnimator::_OnDraw(int layer_index){
  texture = &anim_frame.at(anim_name).at(frame_index - 1);
  DrawTexturePro(*texture,
		 src_rect,
		 dst_rect,
		 pivot,
		 node->GetRotation(),
		 WHITE);
}

bool Component::AtlasAnimator::_IsPosibleAnimName(string region_map_name, string *posible_anim_name, int *index){
  if(isdigit(region_map_name[region_map_name.length() - 1]) &&
     region_map_name[region_map_name.length() - 2] == '_'){
    *posible_anim_name = region_map_name.substr(0, region_map_name.length() - 2);
    *index = stoi(&region_map_name[region_map_name.length()-1]);
    return true;
  }
  return false;
}

void Component::AtlasAnimator::_CreateAnimFrame(){
    string posible_anim_name;
    int index;  
    
    map<string, AtlasRegion>::iterator it;
    it = texture_atlas->GetRegionMap()->begin();
    const auto &next = std::next(it, map_index);
    
    if(_IsPosibleAnimName(next->first, &posible_anim_name, &index)){ 
      if(last_posible_anim_name == "nan"){
	frame_list.push_back(texture_atlas->CreateTexture(posible_anim_name +"_"+ to_string(index)));
	last_posible_anim_name = posible_anim_name;

	if(texture == nullptr) texture = &frame_list.at(0);
      }
      else{
	if(posible_anim_name == last_posible_anim_name){
	  frame_list.push_back(texture_atlas->CreateTexture(last_posible_anim_name + "_" + to_string(index)));
	}
	else{
	  anim_frame.insert(pair<string, vector<Texture2D>>(last_posible_anim_name, frame_list));
	  frame_list.clear();
	  last_posible_anim_name = posible_anim_name;
	  
	  frame_list.push_back(texture_atlas->CreateTexture(last_posible_anim_name + "_" + to_string(index)));
	}
      }
    }
    
    map_index++;

    if(map_index < texture_atlas->GetRegionMap()->size()){
      _CreateAnimFrame();
    }
    else{
      anim_frame.insert(pair<string, vector<Texture2D>>(last_posible_anim_name, frame_list));
      frame_list.clear();
    }

}


/*
  Tilemap Component
*/
Component::Tilemap::Tilemap(Grid *_grid,
			    int* _tile_map,
			    Texture2D *_texture){
  texture = _texture;
  grid = _grid;
  tile_map = _tile_map;
  max_width = grid->width * grid->column;
  max_height = grid->height * grid->row;
}

void Component::Tilemap::_OnDraw(int layer_index){
  for(int i = 0; i < grid->row; ++i){
    for(int j = 0; j < grid->column; ++j){

      int tile = tile_map[_GetIndex(j, i)];

      if(IsTiled(j, i)){
	src_rect = _GetSrcRect(tile);
	v2 transform_rotation = GetGridPosition(j, i);

	dst_rect = {transform_rotation.x,
		    transform_rotation.y,
		    (float)grid->width,
		    (float)grid->height};

	DrawTexturePro(*texture,
		       src_rect,
		       dst_rect,
		       Vector2{(float)grid->width * 0.5f, (float)grid->height * 0.5f},
		       node->GetRotation(),
		       WHITE);

      } // is tiled 
    } // j
  } // i
}

bool Component::Tilemap::IsTiled(int column, int row){
  if(tile_map[_GetIndex(column, row)] != 0){
    return true;
  }
  return false;
}

int* Component::Tilemap::GetTileMap(){return tile_map;}


/*
  TMXMap Component
*/
Component::TMXMap::TMXMap(string tmx_file_src, Texture2D *_texture){
  texture = _texture;
  grid = new Grid();
  XMLFile xml_file;
   
  if(xml_file.LoadFile(tmx_file_src.c_str()) == XML_SUCCESS){

    XMLNode *root = xml_file.FirstChild();
    XMLElement *map = root->NextSibling()->ToElement();
  
    // map attribute //
    const XMLAttribute *map_orientation_attr = map->FindAttribute("orientation");  
    const XMLAttribute *map_width_attr = map->FindAttribute("width");  
    const XMLAttribute *map_height_attr = map->FindAttribute("height");  
    const XMLAttribute *map_tile_width_attr = map->FindAttribute("tilewidth");  
    const XMLAttribute *map_tile_height_attr = map->FindAttribute("tileheight");
    
    if(map){	
      
      map_orientation = map_orientation_attr->Value();
      grid->column = stoi(map_width_attr->Value());
      grid->row = stoi(map_height_attr->Value());
      grid->width = stoi(map_tile_width_attr->Value()); 
      grid->height = stoi(map_tile_height_attr->Value());

      max_width = grid->column * grid->width;
      max_height = grid->row * grid->height;
      
      // get map child with loop to get all layer data
      for(XMLElement *e = map->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
	if(e->FindAttribute("name")){
	  map_layer_name_list.push_back(e->FindAttribute("name")->Value());
	  XMLElement *e_child = e->FirstChildElement();

	  int index = 0; // tile index on map
	  string temp_str = e_child->ToElement()->GetText();

	  // remove '\n' on first line
	  temp_str.erase(temp_str.begin());
	    
	  map_layer_str_list.push_back(temp_str);		    
	  int *map = new int[grid->column * grid->row];

	  for(int i = 0; i < temp_str.length(); ++i){	    
	    string get_char = "";
	    get_char.push_back(temp_str[i]);
	  	    
	    if(isdigit(get_char[0])){	      
	      int get_int = stoi(get_char);	      
	      map[index] = get_int;
	      index++;	      
	    } // if is digit
	  } // get char loop 

	  map_layer_list.push_back(map);
	    
	}
      } // xml element loop 
	         
    }
    else{
      cout<<"Not get map element..."<<endl;
    }

    layer_count = map_layer_list.size();
    layer_sorting_order = new int[layer_count]();
    
  }
  else{
    xml_file.PrintError();
  }
}

void Component::TMXMap::_OnDraw(int layer_index){
  if(layer_index >= 0){
    _DrawLayer(layer_index);
  }
  else{
    _DrawAllLayer();
  }
}

void Component::TMXMap::_DrawLayer(int layer_index){
  for(int i = 0; i < grid->row; ++i){
    for(int j = 0; j < grid->column; j++){

      int tile = map_layer_list.at(layer_index)[_GetIndex(j, i)];
      
      if(tile != 0){

	src_rect = _GetSrcRect(tile);
	v2 transform_rotation = GetGridPosition(j, i);

	dst_rect = {transform_rotation.x,
		    transform_rotation.y,
		    (float)grid->width,
		    (float)grid->height};

	DrawTexturePro(*texture,
		       src_rect,
		       dst_rect,
		       Vector2{(float)grid->width * 0.5f, (float)grid->height * 0.5f},
		       node->GetRotation(),
		       WHITE);

      }// if tile != 0 
    } // i
  }// j 
}

void Component::TMXMap::_DrawAllLayer(){
  for(int i = 0; i < map_layer_list.size(); ++i){
    Draw(i);
  }
}

void Component::TMXMap::_OnAttach(){
  node->component_entity.draw_sort_index = new int[layer_count]();
}

void Component::TMXMap::PrintMapAttribute(){
  cout<<"map orientation:"<<map_orientation<<endl; 
  cout<<"map width:"<<grid->column<<endl;
  cout<<"map height:"<<grid->row<<endl; 
  cout<<"tile width:"<<grid->width<<endl; 
  cout<<"tile height:"<<grid->height<<endl;
}

bool Component::TMXMap::IsTiled(int layer_index, int column, int row){
  if(map_layer_list.at(layer_index)[_GetIndex(column, row)] != 0){
    return true;
  }
  return false;
}

int Component::TMXMap::GetLayerCount(){return layer_count;}
