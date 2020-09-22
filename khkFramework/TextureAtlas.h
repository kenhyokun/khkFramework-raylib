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
#include<vector>
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

  inline TextureAtlas(string file_src){

    // load atlas file
    ifstream file(file_src);
    string line;
    if(file.is_open()){
      while(getline(file, line)){
	line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end()); // trim line
	line_list.push_back(line);
      }
      file.close();
    }
    else{
      cout<<"Unable to open "<<file_src<<" file!"<<endl;
    }

    _ReadSequence();

    line_list.clear();
  }

  Rectangle FindRegion(string name);
  Texture2D CreateTexture(string name);

  inline string* GetValue(string attribute_name){return attribute_map.at(attribute_name);}

protected:

  enum Status{
    GET_STARTED,
    GET_SECTION,
    GET_EOF
  };

  Status status = GET_STARTED;
  
  vector<string> line_list;
  map<string, string*> attribute_map; // texture atlas attribute value pair
  map<string, AtlasRegion> region_map;

  inline void _CreateValuePair(string line, string *attribute, string *value){
    size_t colon_index = line.find(":");
    *attribute = line.substr(0, colon_index);
    *value = line.substr(colon_index + 1, line.length());
  }

  inline void _GetNumOfValue(string value, string *num_of_value, int last_index = 0){
    size_t comma_index = value.find(",");
    if(comma_index != string::npos){
      num_of_value[last_index] = value.substr(0, comma_index);
      value.erase(0, comma_index + 1);

      _GetNumOfValue(value, num_of_value, last_index + 1);

    }
    else{
      num_of_value[last_index] = value;
    }
  }

  inline bool _IsHas(string line, string sub_str){
    size_t found = line.find(sub_str);
    if(found != string::npos){
      return true;
    }
    return false;
  }

  inline bool _IsSection(string line){
    if(!_IsHas(line, ":") &&
       !_IsHas(line, ",") &&
       !_IsHas(line, ".png")){
      return true;
    }
    return false;
  }

  inline void _ReadSequence(){
	
    switch(status){
    case GET_STARTED:
      for(int i = 0; i < line_list.size(); i++){
	if(_IsHas(line_list.at(i), ".png")){
	  _InsertAttribute("texture file", &line_list.at(i));
	}
	else{
	  string attribute;
	  string value;
	  string *num_of_value = new string[2];
	  _CreateValuePair(line_list.at(i), &attribute, &value);
	  _GetNumOfValue(value, num_of_value);
	  _InsertAttribute(attribute, num_of_value);
	}
      }
      break;

    case GET_SECTION:
      break;
    }
  }

  inline void _InsertRegion(string name, AtlasRegion atlas_region){
    region_map.insert(pair<string, AtlasRegion>(name, atlas_region));
  }

  inline void _InsertAttribute(string name, string *value){
    attribute_map.insert(pair<string, string*>(name, value));
  }

};

#endif
