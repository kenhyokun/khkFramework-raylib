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

#include<File.h>

map<string, string> ConfigFile::value_map;

int ConfigFile::LoadFile(string file_src){
  return load_ini_path(file_src.c_str(),
		       INI_DEFAULT_FORMAT,
		       NULL,
		       _DefCallback,
		       NULL);
}

int ConfigFile::LoadFile(string file_src, const IniDispHandler callback){
  return load_ini_path(file_src.c_str(),
		       INI_DEFAULT_FORMAT,
		       NULL,
		       callback,
		       NULL);
}

string ConfigFile::GetValue(string data){
  return value_map.at(data);
}

int ConfigFile::_DefCallback(IniDispatch *dispatch, void *v_null){
  if(dispatch->type == INI_KEY){
    value_map.insert(pair<string, string>(dispatch->data, dispatch->value));
  }
  return 0;
}

