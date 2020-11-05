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

#ifndef CMATH_H
#define CMATH_H
// my custom math library 

#include<m_raylib.h>
#include<cmath>

#define pi 3.14159

inline float Rad2Deg(float rad){
  return (180.0 / pi) * rad;
}
  
inline float Deg2Rad(float deg){
  return (deg * pi) / 180;
}

inline v2 TransformRotation(float rad_angle, v2 position, v2 pivot){
  float x = 0.0f;
  float y = 0.0f;
  float px = pivot.x;
  float py = pivot.y;
  float tx = position.x;
  float ty = position.y;

  x =
    (tx * cos(rad_angle)) -
    (ty * sin(rad_angle)) -
    (px * cos(rad_angle)) +
    (py * sin(rad_angle)) +
    px; 

  y =
    (tx * sin(rad_angle) ) +
    (ty * cos(rad_angle) ) -
    (px * sin(rad_angle) ) -
    (py * cos(rad_angle) ) +
    py; 

  return v2{x, y}; 

}

#endif
