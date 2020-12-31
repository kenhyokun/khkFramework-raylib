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

#ifndef KEY_BUTTON_H
#define KEY_BUTTON_H

#include<m_raylib.h>

struct Key{
  int key_code;

  static int GetFunctionKeyCode(string key_sym){
    if(key_sym == "SPACE") return KEY_SPACE;
    if(key_sym == "ESCAPE") return KEY_ESCAPE;
    if(key_sym == "ENTER") return KEY_ENTER;
    if(key_sym == "TAB") return KEY_TAB;
    if(key_sym == "BACKSPACE") return KEY_BACKSPACE;
    if(key_sym == "INSERT") return KEY_INSERT;
    if(key_sym == "DELETE") return KEY_DELETE;
    if(key_sym == "RIGHT") return KEY_RIGHT;
    if(key_sym == "LEFT") return KEY_LEFT;
    if(key_sym == "DOWN") return KEY_DOWN;
    if(key_sym == "UP") return KEY_UP;
    if(key_sym == "PAGE_UP") return KEY_PAGE_UP;
    if(key_sym == "PAGE_DOWN") return KEY_PAGE_DOWN;
    if(key_sym == "HOME") return KEY_HOME;
    if(key_sym == "END") return KEY_END;
    if(key_sym == "CAPS_LOCK") return KEY_CAPS_LOCK;
    if(key_sym == "SCROLL_LOCK") return KEY_SCROLL_LOCK;
    if(key_sym == "NUM_LOCK") return KEY_NUM_LOCK;
    if(key_sym == "PRINT_SCREEN") return KEY_PRINT_SCREEN;
    if(key_sym == "PAUSE") return KEY_PAUSE;
    if(key_sym == "F1") return KEY_F1;
    if(key_sym == "F2") return KEY_F2;
    if(key_sym == "F3") return KEY_F3;
    if(key_sym == "F4") return KEY_F4;
    if(key_sym == "F5") return KEY_F5;
    if(key_sym == "F6") return KEY_F6;
    if(key_sym == "F7") return KEY_F7;
    if(key_sym == "F8") return KEY_F8;
    if(key_sym == "F9") return KEY_F9;
    if(key_sym == "F10") return KEY_F10;
    if(key_sym == "F11") return KEY_F11;
    if(key_sym == "F12") return KEY_F12;
    if(key_sym == "LEFT_SHIFT") return KEY_LEFT_SHIFT;
    if(key_sym == "LEFT_CONTROL") return KEY_LEFT_CONTROL;
    if(key_sym == "LEFT_ALT") return KEY_LEFT_ALT;
    if(key_sym == "LEFT_SUPER") return KEY_LEFT_SUPER;
    if(key_sym == "RIGHT_SHIFT") return KEY_RIGHT_SHIFT;
    if(key_sym == "RIGHT_CONTROL") return KEY_RIGHT_CONTROL;
    if(key_sym == "RIGHT_ALT") return KEY_RIGHT_ALT;
    if(key_sym == "RIGHT_SUPER") return KEY_RIGHT_SUPER;
    if(key_sym == "KB_MENU") return KEY_KB_MENU;
    if(key_sym == "BACKSLASH") return KEY_BACKSLASH;
    if(key_sym == "GRAVE") return KEY_GRAVE; 

    // if(key_sym == "RIGHT_BRACKET") return KEY_RIGHT_BRACKET;
    // if(key_sym == "LEFT_BRACKET") return KEY_LEFT_BRACKET;

    return 0;
  }

  inline bool IsDown(){
    return IsKeyDown(key_code);
  }
  inline bool IsPressed(){
    return IsKeyPressed(key_code);
  }
  inline bool IsReleased(){
    return IsKeyReleased(key_code);
  }

};

#endif
