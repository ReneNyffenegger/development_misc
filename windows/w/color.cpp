/* 
   Color.cpp

   Copyright (C) René Nyffenegger

   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:

   1. The origin of this source code must not be misrepresented; you must not
      claim that you wrote the original source code. If you use this source code
      in a product, an acknowledgment in the product documentation would be
      appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
      misrepresented as being the original source code.

   3. This notice may not be removed or altered from any source distribution.

   René Nyffenegger rene.nyffenegger@adp-gmbh.ch
*/

#include "Color.h"

Color::Color(unsigned char red, unsigned char green, unsigned char blue) : 
  color_ (RGB(red, green, blue)) {
}

Color::Color(COLORREF cr) : color_(cr) {

}

Color::Color(const std::string& colorName) {
  if (colorName == "Aquamarine") {
    color_=RGB( 0x70, 0xDB, 0x93);
  }
  if (colorName == "Baker's Chocolate") {
    color_=RGB( 0x5C, 0x33, 0x17);
  }
  if (colorName == "Black") {
    color_=RGB( 0x00, 0x00, 0x00);
  }
  if (colorName == "Blue") {
    color_=RGB( 0x00, 0x00, 0xFF);
  }
  if (colorName == "Blue Violet") {
    color_=RGB( 0x9F, 0x5F, 0x9F);
  }
  if (colorName == "Brass") {
    color_=RGB( 0xB5, 0xA6, 0x42);
  }
  if (colorName == "Bright Gold") {
    color_=RGB( 0xD9, 0xD9, 0x19);
  }
  if (colorName == "Brown") {
    color_=RGB( 0xA6, 0x2A, 0x2A);
  }
  if (colorName == "Bronze") {
    color_=RGB( 0x8C, 0x78, 0x53);
  }
  if (colorName == "Bronze II") {
    color_=RGB( 0xA6, 0x7D, 0x3D);
  }
  if (colorName == "Cadet Blue") {
    color_=RGB( 0x5F, 0x9F, 0x9F);
  }
  if (colorName == "Cool Copper") {
    color_=RGB( 0xD9, 0x87, 0x19);
  }
  if (colorName == "Copper") {
    color_=RGB( 0xB8, 0x73, 0x33);
  }
  if (colorName == "Coral") {
    color_=RGB( 0xFF, 0x7F, 0x00);
  }
  if (colorName == "Corn Flower Blue") {
    color_=RGB( 0x42, 0x42, 0x6F);
  }
  if (colorName == "Cyan") {
    color_=RGB( 0x00, 0xFF, 0xFF);
  }
  if (colorName == "Dark Brown") {
    color_=RGB( 0x5C, 0x40, 0x33);
  }
  if (colorName == "Dark Green") {
    color_=RGB( 0x2F, 0x4F, 0x2F);
  }
  if (colorName == "Dark Green Copper") {
    color_=RGB( 0x4A, 0x76, 0x6E);
  }
  if (colorName == "Dark Olive Green") {
    color_=RGB( 0x4F, 0x4F, 0x2F);
  }
  if (colorName == "Dark Orchid") {
    color_=RGB( 0x99, 0x32, 0xCD);
  }
  if (colorName == "Dark Purple") {
    color_=RGB( 0x87, 0x1F, 0x78);
  }
  if (colorName == "Dark Slate Blue") {
    color_=RGB( 0x6B, 0x23, 0x8E);
  }
  if (colorName == "Dark Slate Grey") {
    color_=RGB( 0x2F, 0x4F, 0x4F);
  }
  if (colorName == "Dark Tan") {
    color_=RGB( 0x97, 0x69, 0x4F);
  }
  if (colorName == "Dark Turquoise") {
    color_=RGB( 0x70, 0x93, 0xDB);
  }
  if (colorName == "Dark Wood") {
    color_=RGB( 0x85, 0x5E, 0x42);
  }
  if (colorName == "Dim Grey") {
    color_=RGB( 0x54, 0x54, 0x54);
  }
  if (colorName == "Dusty Rose") {
    color_=RGB( 0x85, 0x63, 0x63);
  }
  if (colorName == "Feldspar") {
    color_=RGB( 0xD1, 0x92, 0x75);
  }
  if (colorName == "Firebrick") {
    color_=RGB( 0x8E, 0x23, 0x23);
  }
  if (colorName == "Forest Green") {
    color_=RGB( 0x23, 0x8E, 0x23);
  }
  if (colorName == "Gold") {
    color_=RGB( 0xCD, 0x7F, 0x32);
  }
  if (colorName == "Goldenrod") {
    color_=RGB( 0xDB, 0xDB, 0x70);
  }
  if (colorName == "Grey") {
    color_=RGB( 0xC0, 0xC0, 0xC0);
  }
  if (colorName == "Green") {
    color_=RGB( 0x00, 0xFF, 0x00);
  }
  if (colorName == "Green Copper") {
    color_=RGB( 0x52, 0x7F, 0x76);
  }
  if (colorName == "Green Yellow") {
    color_=RGB( 0x93, 0xDB, 0x70);
  }
  if (colorName == "Hunter Green") {
    color_=RGB( 0x21, 0x5E, 0x21);
  }
  if (colorName == "Indian Red") {
    color_=RGB( 0x4E, 0x2F, 0x2F);
  }
  if (colorName == "Khaki") {
    color_=RGB( 0x9F, 0x9F, 0x5F);
  }
  if (colorName == "Light Blue") {
    color_=RGB( 0xC0, 0xD9, 0xD9);
  }
  if (colorName == "Light Grey") {
    color_=RGB( 0xA8, 0xA8, 0xA8);
  }
  if (colorName == "Light Steel Blue") {
    color_=RGB( 0x8F, 0x8F, 0xBD);
  }
  if (colorName == "Light Wood") {
    color_=RGB( 0xE9, 0xC2, 0xA6);
  }
  if (colorName == "Lime Green") {
    color_=RGB( 0x32, 0xCD, 0x32);
  }
  if (colorName == "Magenta") {
    color_=RGB( 0xFF, 0x00, 0xFF);
  }
  if (colorName == "Mandarian Orange") {
    color_=RGB( 0xE4, 0x78, 0x33);
  }
  if (colorName == "Maroon") {
    color_=RGB( 0x8E, 0x23, 0x6B);
  }
  if (colorName == "Medium Aquamarine") {
    color_=RGB( 0x32, 0xCD, 0x99);
  }
  if (colorName == "Medium Blue") {
    color_=RGB( 0x32, 0x32, 0xCD);
  }
  if (colorName == "Medium Forest Green") {
    color_=RGB( 0x6B, 0x8E, 0x23);
  }
  if (colorName == "Medium Goldenrod") {
    color_=RGB( 0xEA, 0xEA, 0xAE);
  }
  if (colorName == "Medium Orchid") {
    color_=RGB( 0x93, 0x70, 0xDB);
  }
  if (colorName == "Medium Sea Green") {
    color_=RGB( 0x42, 0x6F, 0x42);
  }
  if (colorName == "Medium Slate Blue") {
    color_=RGB( 0x7F, 0x00, 0xFF);
  }
  if (colorName == "Medium Spring Green") {
    color_=RGB( 0x7F, 0xFF, 0x00);
  }
  if (colorName == "Medium Turquoise") {
    color_=RGB( 0x70, 0xDB, 0xDB);
  }
  if (colorName == "Medium Violet Red") {
    color_=RGB( 0xDB, 0x70, 0x93);
  }
  if (colorName == "Medium Wood") {
    color_=RGB( 0xA6, 0x80, 0x64);
  }
  if (colorName == "Midnight Blue") {
    color_=RGB( 0x2F, 0x2F, 0x4F);
  }
  if (colorName == "Navy Blue") {
    color_=RGB( 0x23, 0x23, 0x8E);
  }
  if (colorName == "Neon Blue") {
    color_=RGB( 0x4D, 0x4D, 0xFF);
  }
  if (colorName == "Neon Pink") {
    color_=RGB( 0xFF, 0x6E, 0xC7);
  }
  if (colorName == "New Midnight Blue") {
    color_=RGB( 0x00, 0x00, 0x9C);
  }
  if (colorName == "New Tan") {
    color_=RGB( 0xEB, 0xC7, 0x9E);
  }
  if (colorName == "Old Gold") {
    color_=RGB( 0xCF, 0xB5, 0x3B);
  }
  if (colorName == "Orange") {
    color_=RGB( 0xFF, 0x7F, 0x00);
  }
  if (colorName == "Orange Red") {
    color_=RGB( 0xFF, 0x24, 0x00);
  }
  if (colorName == "Orchid") {
    color_=RGB( 0xDB, 0x70, 0xDB);
  }
  if (colorName == "Pale Green") {
    color_=RGB( 0x8F, 0xBC, 0x8F);
  }
  if (colorName == "Pink") {
    color_=RGB( 0xBC, 0x8F, 0x8F);
  }
  if (colorName == "Plum") {
    color_=RGB( 0xEA, 0xAD, 0xEA);
  }
  if (colorName == "Quartz") {
    color_=RGB( 0xD9, 0xD9, 0xF3);
  }
  if (colorName == "Red") {
    color_=RGB( 0xFF, 0x00, 0x00);
  }
  if (colorName == "Rich Blue") {
    color_=RGB( 0x59, 0x59, 0xAB);
  }
  if (colorName == "Salmon") {
    color_=RGB( 0x6F, 0x42, 0x42);
  }
  if (colorName == "Scarlet") {
    color_=RGB( 0x8C, 0x17, 0x17);
  }
  if (colorName == "Sea Green") {
    color_=RGB( 0x23, 0x8E, 0x68);
  }
  if (colorName == "Semi-Sweet Chocolate") {
    color_=RGB( 0x6B, 0x42, 0x26);
  }
  if (colorName == "Sienna") {
    color_=RGB( 0x8E, 0x6B, 0x23);
  }
  if (colorName == "Silver") {
    color_=RGB( 0xE6, 0xE8, 0xFA);
  }
  if (colorName == "Sky Blue") {
    color_=RGB( 0x32, 0x99, 0xCC);
  }
  if (colorName == "Slate Blue") {
    color_=RGB( 0x00, 0x7F, 0xFF);
  }
  if (colorName == "Spicy Pink") {
    color_=RGB( 0xFF, 0x1C, 0xAE);
  }
  if (colorName == "Spring Green") {
    color_=RGB( 0x00, 0xFF, 0x7F);
  }
  if (colorName == "Steel Blue") {
    color_=RGB( 0x23, 0x6B, 0x8E);
  }
  if (colorName == "Summer Sky") {
    color_=RGB( 0x38, 0xB0, 0xDE);
  }
  if (colorName == "Tan") {
    color_=RGB( 0xDB, 0x93, 0x70);
  }
  if (colorName == "Thistle") {
    color_=RGB( 0xD8, 0xBF, 0xD8);
  }
  if (colorName == "Turquoise") {
    color_=RGB( 0xAD, 0xEA, 0xEA);
  }
  if (colorName == "Very Dark Brown") {
    color_=RGB( 0x5C, 0x40, 0x33);
  }
  if (colorName == "Very Light Grey") {
    color_=RGB( 0xCD, 0xCD, 0xCD);
  }
  if (colorName == "Violet") {
    color_=RGB( 0x4F, 0x2F, 0x4F);
  }
  if (colorName == "Violet Red") {
    color_=RGB( 0xCC, 0x32, 0x99);
  }
  if (colorName == "Wheat") {
    color_=RGB( 0xD8, 0xD8, 0xBF);
  }
  if (colorName == "White") {
    color_=RGB( 0xFF, 0xFF, 0xFF);
  }
  if (colorName == "Yellow") {
    color_=RGB( 0xFF, 0xFF, 0x00);
  }
  if (colorName == "Yellow Green") {
    color_=RGB( 0x99, 0xCC, 0x32);
  }
  if (colorName == "Dark Yellow") {
    color_=RGB( 0x99, 0xCC, 0x32);
  }
}

