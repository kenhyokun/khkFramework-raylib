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

#ifndef TEXTURE_ATLAS_H
#define TEXTURE_ATLAS_H

#include<m_raylib.h>
#include<algorithm>
#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
#include<map>

using namespace std;

struct AtlasRegion{
  bool is_rotate;
  v2 offset;
  v2 original_size;
  Rectangle rect;
  int index;
};

struct TextureAtlas{

  string texture_file_name;

  inline TextureAtlas(string file_src){
    ifstream file(file_src);
    string line;
    if(file.is_open()){
      while(getline(file, line)){

	line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end()); // trim line

	if(!_IsHas(line, ":") &&
	   !_IsHas(line, ",") &&
	   !_IsHas(line, ".png")){

	  cout<<line<<endl;

	}
	else{
	  if(_IsHas(line, ".png")){
	    texture_file_name = line;
	  }
	  else{

	    _CreateValuePair(line);

	  }
	}

      }
      file.close();
    }
    else{
      cout<<"unable to open file!"<<endl;
    }
  }

  Rectangle FindRegion(string name);
  Texture2D CreateTexture(string name);

protected:
  map<string, string*> value_pair_map; // texture atlas attribute value pair
  map<string, AtlasRegion> region_map;

  inline void _CreateValuePair(string line){
    size_t colon_index = line.find(":");
    string attribute = line.substr(0, colon_index);
    string value = line.substr(colon_index + 1, line.length());

    cout<<attribute<<", "<<value<<endl;
  }

  inline bool _IsHas(string line, string sub_str){
    size_t found = line.find(sub_str);
    if(found != string::npos){
      return true;
    }
    return false;
  }

  inline void _Insert(string name, AtlasRegion atlas_region){
    region_map.insert(pair<string, AtlasRegion>(name, atlas_region));
  }

};

#endif
