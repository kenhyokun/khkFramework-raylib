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

#include<DebugDraw.h>

DebugDraw::DebugDraw(){
  log("debug draw was created...");
}
void DebugDraw::Create(){log("1");}
void DebugDraw::Destroy(){log("2");}
void DebugDraw::DrawPolygon(const b2v2* vertices, int32 vertexCount, const b2Color& color){
  log("there is a polygon shape");
}
void DebugDraw::DrawSolidPolygon(const b2v2* vertices, int32 vertexCount, const b2Color& color){
  log("there is a polygon shape");
}
void DebugDraw::DrawCircle(const b2v2& center, float radius, const b2Color& color){
  log("there is a circle shape");
}
void DebugDraw::DrawSolidCircle(const b2v2& center, float radius, const b2v2& axis, const b2Color& color){
  log("there is a circle shape");
}
void DebugDraw::DrawSegment(const b2v2& p1, const b2v2& p2, const b2Color& color){}
void DebugDraw::DrawTransform(const b2Transform& xf){}
void DebugDraw::DrawPoint(const b2v2& p, float size, const b2Color& color){} 
void DebugDraw::Flush(){}
DebugDraw::~DebugDraw(){}
