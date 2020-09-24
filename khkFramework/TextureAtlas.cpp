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

#include<TextureAtlas.h>

TextureAtlas::TextureAtlas(string file_src, string img_src){

  // load image
  if(img_src != "nan"){
    buffer_image = LoadImage(img_src.c_str());
  }
  
  // load atlas file
  ifstream file(file_src);
  string line;
  if(file.is_open()){
    while(getline(file, line)){
      line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end()); // trim line
      line_list.push_back(line);
    }
    file.close();
    line_list.push_back("[EOF]");
  }
  else{
    cout<<"Unable to open "<<file_src<<" file!"<<endl;
  }

  _ReadSequence();

  line_list.clear();
}

void TextureAtlas::UnloadBufferImage(){UnloadImage(buffer_image);}

Texture2D TextureAtlas::CreateTexture(string name){
  AtlasRegion atlas_region = GetRegion(name);
  Image temp_image {0};

  temp_image = ImageFromImage(buffer_image,
			      Rectangle{(float)atlas_region.xy.x,
				  (float)atlas_region.xy.y,
				  (float)atlas_region.size.x,
				  (float)atlas_region.size.y
				  });
  
  if(atlas_region.is_rotate){
    ImageRotateCW(&temp_image);
  }

  return LoadTextureFromImage(temp_image);
}

void TextureAtlas::_CreateValuePair(string line, string *attribute, string *value){
  size_t colon_index = line.find(":");
  *attribute = line.substr(0, colon_index);
  *value = line.substr(colon_index + 1, line.length());
}

void TextureAtlas::_GetNumOfValue(string value, string *num_of_value, int last_index){
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

bool TextureAtlas::_IsHas(string line, string sub_str){
  size_t found = line.find(sub_str);
  if(found != string::npos){
    return true;
  }
  return false;
}

bool TextureAtlas::_IsSection(string line){
  if(!_IsHas(line, ":") &&
     !_IsHas(line, ",") &&
     !_IsHas(line, ".png")){
    return true;
  }
  return false;
}

bool TextureAtlas::_IsEOF(string line){
  if(_IsHas(line, "[EOF]")){
    return true;
  }
  return false;
}

void TextureAtlas::_InsertRegion(string name, AtlasRegion atlas_region){
  region_map.insert(pair<string, AtlasRegion>(name, atlas_region));
}

void TextureAtlas::_InsertAttribute(string name, string *value){
  attribute_map.insert(pair<string, string*>(name, value));
}

void TextureAtlas::_ReadSequence(){
	
  switch(status){
  case GET_STARTED:

    while(!_IsSection(line_list.at(line_index))){

      if(_IsHas(line_list.at(line_index), ".png")){
	_InsertAttribute("texture file", &line_list.at(line_index));
      }
      else{
	string attribute;
	string value;
	string *num_of_value = new string[2];
	_CreateValuePair(line_list.at(line_index), &attribute, &value);
	_GetNumOfValue(value, num_of_value);
	_InsertAttribute(attribute, num_of_value);
      }

      line_index++;
    }

    status = GET_SECTION;
    _ReadSequence();

    break;

  case GET_SECTION:
    section = line_list.at(line_index);
    region_attribute_index = line_index + 1;

    while(!_IsSection(line_list.at(region_attribute_index)) &&
	  !_IsEOF(line_list.at(region_attribute_index))){

      string attribute;
      string value;
      string *num_of_value = new string[2];
      _CreateValuePair(line_list.at(region_attribute_index), &attribute, &value);
      _GetNumOfValue(value, num_of_value);

      if(attribute == "rotate"){

	istringstream(value) >>
	  std::boolalpha >>
	  atlas_region.is_rotate;

      }
      else if(attribute == "xy"){
	atlas_region.xy = v2i{stoi(num_of_value[0]),
			      stoi(num_of_value[1])};
      }
      else if(attribute == "size"){
	if(!atlas_region.is_rotate){
	  atlas_region.size = v2i{stoi(num_of_value[0]),
				  stoi(num_of_value[1])};
	}
	else{
	  atlas_region.size = v2i{stoi(num_of_value[1]),
				  stoi(num_of_value[0])};
	}
      }
      else if(attribute == "orig"){
	atlas_region.orig = v2i{stoi(num_of_value[0]),
				stoi(num_of_value[1])};
      }
      else if(attribute == "offset"){
	atlas_region.offset = v2i{stoi(num_of_value[0]),
				  stoi(num_of_value[1])};
      }
      else if(attribute == "index"){
	atlas_region.index = stoi(value);

	if(stoi(value) > -1){
	  section.append("_" + value);
	}

      }
	
      region_attribute_index++;
    }

    _InsertRegion(section, atlas_region);
    line_index = region_attribute_index;

    if(line_index < line_list.size() - 1){
      // brrrr....
    }
    else{
      status = GET_EOF;
    } 

    _ReadSequence();

    break;

  case GET_EOF:
    break;

  }
}

v2i TextureAtlas::GetImageSize(){return v2i{stoi(GetValue("size")[0]), stoi(GetValue("size")[1])};}
AtlasRegion TextureAtlas::GetRegion(string name){return region_map.at(name);}
string* TextureAtlas::GetValue(string attribute_name){return attribute_map.at(attribute_name);}
map<string, AtlasRegion>* TextureAtlas::GetRegionMap(){return &region_map;}
