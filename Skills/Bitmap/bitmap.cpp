// This code is written in C++ and uses a library called BitmapPlusPlus.
// The purpose of the code is to create a bitmap image of size 512x512 and fill it with three different colors.
// The first third of the image is filled with red (R = 250, G = 0, B = 0),
// the second third is filled with blue (R = 0, G = 0, B = 250),
// and the last third is filled with orange (R = 255, G = 100, B = 0).
// The final result is saved as a bitmap image named "flag.bmp".

#include <iostream>
#include "BitmapPlusPlus.hpp"

int main() {
  bmp::Bitmap nkar(512, 512);
  for (std::int32_t y = 0; y < nkar.Height()/3; ++y){
    for (std::int32_t x = 0; x < nkar.Width(); ++x){
      bmp::Pixel colour_1{
        static_cast<std::uint8_t>(250),
        static_cast<std::uint8_t>(0),
        static_cast<std::uint8_t>(0)
      };
      nkar.Set(x, y, colour_1);
      
    }
  }
  for (std::int32_t y = nkar.Height()/3; y < 2 * nkar.Height()/3; ++y){
    for (std::int32_t x = 0; x < nkar.Width(); ++x){
      bmp::Pixel colour_1{
        static_cast<std::uint8_t>(0),
        static_cast<std::uint8_t>(0),
        static_cast<std::uint8_t>(250)
      };
      nkar.Set(x, y, colour_1);
      
    }
  }
  for (std::int32_t y = 2*nkar.Height()/3 ; y < nkar.Height(); ++y){
    for (std::int32_t x = 0; x < nkar.Width(); ++x){
      bmp::Pixel colour_1{
        static_cast<std::uint8_t>(255),
        static_cast<std::uint8_t>(100),
        static_cast<std::uint8_t>(0)
      };
      nkar.Set(x, y, colour_1);
      
    }
  }
  nkar.Save("flag.bmp");
}
