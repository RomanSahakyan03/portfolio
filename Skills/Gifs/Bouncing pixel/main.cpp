
// This program generates a GIF animation of a bouncing point.
// It uses the "gif.hpp" library to create a writer object with the filename "output.gif",
// the width and height of the frames set to 128x128 pixels and the number of repetitions set to 2.
// In the main function, the program sets the seed for the random number generator with the current
// time and generates a random starting position for the bouncing point along with its x and y speeds.
// The program then writes 1000 frames of the animation by updating the position of the bouncing point each time,
// using the speeds and checking if it hits the edges of the frame. If the point reaches the edge,
// its speed in the corresponding direction is reversed. The color of the point is set to a constant white.
// The frames are then written to the file specified by the filename using the write_frame method of the writer object.


#include <cmath>
#include <ctime>
#include "gif.hpp"

const int width = 128;
const int height = 128;

gif::Pixel get_random_color() {
  return gif::Pixel{
      static_cast<uint8_t>(rand() % 128 + 128),
      static_cast<uint8_t>(rand() % 128 + 128),
      static_cast<uint8_t>(rand() % 128 + 128),
  };
}

int main() {
  
  const std::string filename{"./output.gif"};

  gif::GifWriter writer{filename, width, height, 2};

  srand(time(0));
  gif::Pixel color = {255,255,255};

  float x_speed= -1 + 2*((rand()) / static_cast <float> (RAND_MAX))
  
, y_speed = -1 + 2*((rand()) / static_cast <float> (RAND_MAX));
  int i=rand()%129,j=rand()%129;
  float x =i, y =j;

  for (int frame_number = 0; frame_number < 1000; ++frame_number) {

    x += 5*x_speed;
    y += 5*y_speed;
    gif::Frame frame{width, height};
    

    
    if(x >= height-1){
      x_speed = -x_speed;
    }
    if(x <= 1){
      x_speed = -x_speed;
    }
    if(y >= width-1){
      y_speed = -y_speed;
    }
    if(y <= 1){
      y_speed = -y_speed;
    }
    
    i = std::trunc(x);
    j = std::trunc(y);
    frame[{i, j}] = color;
    
    writer.write_frame(frame);
  }
  return 0;
}
