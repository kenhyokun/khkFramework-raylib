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

#ifndef M_RAYLIB
#define M_RAYLIB
#include<iostream>
#include<raylib.h>

using namespace std;

#define v2_0  Vector2{0, 0}
#define v2_half  Vector2{0.5f, 0.5f} // I don't know why this feels like necessary
#define v2_1  Vector2{1.0f, 1.0f}
typedef Vector2 v2;

inline void log(string log_str){
  cout<<log_str<<endl;
}

inline void DrawRectangle(float x, float y, int width, int height, Color color, float rotation = 0.0f){
  DrawRectanglePro(Rectangle{x, y, (float)width, (float)height},
		   v2{width * 0.5f, height * 0.5f},
		   rotation,
		   color);
}

#endif
