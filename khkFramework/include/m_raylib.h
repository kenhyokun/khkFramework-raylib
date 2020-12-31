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

#ifndef M_RAYLIB
#define M_RAYLIB

#include<iostream>
#include<raylib.h>
#include<cmath>

using namespace std;

/* #define v2_0 Vector2{0.0f, 0.0f} */
/* #define v2_half Vector2{0.5f, 0.5f} // I don't know why this feels like necessary */
/* #define v2_1 Vector2{1.0f, 1.0f} */
/* typedef Vector2 v2; */

struct v2{
  float x, y;

  inline v2 operator+ (const v2& _v2){
    v2 result;
    result.x = x + _v2.x;
    result.y = y + _v2.y;
    return result;
  }

  inline v2 operator- (const v2& _v2){
    v2 result;
    result.x = x - _v2.x;
    result.y = y - _v2.y;
    return result;
  }

  inline float Magnitude(v2 origin = v2{0.0f, 0.0f}){
    float magnitude = 0.0f;
    float rx = x - origin.x;
    float ry = y - origin.y;
    magnitude = sqrt( pow(rx, 2) + pow(ry, 2) );
    return magnitude;
  }

  inline v2 Normalize(v2 origin = v2{0.0f, 0.0f}){
    v2 norm;
    float rx = x - origin.x;
    float ry = y - origin.y;
    float magnitude = Magnitude(origin);
    norm.x = rx / magnitude;
    norm.y = ry / magnitude;
    return norm;
  }

  inline float Distance(v2 _v2){
    float dist = 0.0f;
    sqrt( pow( _v2.x - x, 2 ) + pow( _v2.y - y, 2 ) );
    return dist;
  }

};

#define v2_0 v2{0.0f, 0.0f}
#define v2_half v2{0.5f, 0.5f} // I don't know why this feels like necessary
#define v2_1 v2{1.0f, 1.0f}

struct v2i{
  int x,y;
};

#define v2i_0 v2i{0, 0}

struct Rectanglei{
  int x, y, width, height;
};

inline void log(string log_str){
  cout<<log_str<<endl;
}

inline void rlDrawCircle(float x, float y, float r, Color color){
  DrawCircle(x, y, r, color);
}

inline void DrawRectangle(float x, float y, int width, int height, Color color, float rotation = 0.0f){
  DrawRectanglePro(Rectangle{x, y, (float)width, (float)height},
		   Vector2{width * 0.5f, height * 0.5f},
		   rotation,
		   color);
}

#endif
