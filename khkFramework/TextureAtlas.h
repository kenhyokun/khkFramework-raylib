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
#include<sstream>
#include<cstdlib>
#include<string>
#include<cctype>
#include<vector>
#include<map>

using namespace std;

struct AtlasRegion{
  bool is_rotate;
  v2i xy;
  v2i size; // size after texture packing
  v2i orig; // original size
  v2i offset;
  int index;
};

struct TextureAtlas{

  TextureAtlas(string file_src, string img_src = "nan");
  Image CreateImage(string name);
  Texture2D CreateTexture(string name);
  void UnloadBufferImage();
  void PrintGetRegion();

  v2i GetImageSize();
  AtlasRegion GetRegion(string name);
  AtlasRegion* GetRegionPtr(string name);
  string* GetValue(string attribute_name);
  map<string, AtlasRegion>* GetRegionMap();

protected:

  enum Status{
    GET_STARTED,
    GET_SECTION,
    GET_EOF
  };

  Image buffer_image;
  Status status = GET_STARTED;
  vector<string> line_list;
  map<string, string*> attribute_map; // texture atlas attribute value pair
  map<string, AtlasRegion> region_map;
  map<string, AtlasRegion*> ptr_region_map;
  int line_index = 0;
  int region_attribute_index;
  string section;
  AtlasRegion atlas_region;

  void _CreateValuePair(string line, string *attribute, string *value);
  void _GetNumOfValue(string value, string *num_of_value, int last_index = 0);
  bool _IsHas(string line, string sub_str);
  bool _IsSection(string line);
  bool _IsEOF(string line);
  void _ReadSequence();
  void _InsertRegion(string name, AtlasRegion atlas_region);
  void _InsertAttribute(string name, string *value);

};

#endif
