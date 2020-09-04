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

#include<B2D_DebugDraw.h>

B2D_DebugDraw::B2D_DebugDraw(){
  m_drawFlags = e_shapeBit;
  // m_drawFlags = e_jointBit;
  // m_drawFlags = e_aabbBit;
  // m_drawFlags = e_pairBit;
  // m_drawFlags = e_centerOfMassBit;
}

void B2D_DebugDraw::DrawPolygon(const b2v2 *vertices, int32 vertexCount, const b2Color &color){cout<<"hello world"<<endl;}
void B2D_DebugDraw::DrawSolidPolygon(const b2v2 *vertices, int32 vertexCount, const b2Color &color){cout<<"hello world"<<endl;}
void B2D_DebugDraw::DrawCircle(const b2v2 &center, float radius, const b2Color &color){cout<<"hello world"<<endl;}
void B2D_DebugDraw::DrawSolidCircle(const b2v2 &center, float radius, const b2v2 &axis, const b2Color& color){cout<<"hello world"<<endl;}
void B2D_DebugDraw::DrawSegment(const b2v2 &p1, const b2v2 &p2, const b2Color &color){cout<<"hello world"<<endl;}
void B2D_DebugDraw::DrawTransform(const b2Transform &xf){cout<<"hello world"<<endl;}
void B2D_DebugDraw::DrawPoint(const b2v2 &p, float size, const b2Color &color){cout<<"hello world"<<endl;}
