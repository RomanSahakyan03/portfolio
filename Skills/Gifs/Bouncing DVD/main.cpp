
// This program generates a GIF animation of a bouncing DVD.
// It uses the "gif.hpp" library to create a writer object with the filename "output.gif",
// the width and height of the frames set to 128x128 pixels and the number of repetitions set to 2.
// In the main function, the program sets the seed for the random number generator with the current
// time and generates a random starting position for the bouncing DVD along with its x and y speeds.
// The program then writes 1000 frames of the animation by updating the position of the bouncing DVD each time,
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
  
  //извиняюсь, но лень было сделать идеальный расчёт граней
  int i=rand()%100+10,j=rand()%100+10;
  
  float x =i, y =j;

  for (int frame_number = 0; frame_number < 1000; ++frame_number) {

    x += 1*x_speed;
    y += 1*y_speed;
    gif::Frame frame{width, height};
    

    
    if(x >= height-5){
      x_speed = -x_speed;
      color = get_random_color();
    }
    if(x <= 5){
      x_speed = -x_speed;
      color = get_random_color();
    }
    if(y >= width-5){
      y_speed = -y_speed;
      color = get_random_color();
    }
    if(y <= 6){
      y_speed = -y_speed;
      color = get_random_color();
    }
    
    i = std::trunc(x);
    j = std::trunc(y);
    //V
    frame[{i  , j}] = color; //main pixel
    frame[{i-1, j-1}] = color;
    frame[{i-2, j-1}] = color;
    frame[{i-3, j-1}] = color;
    frame[{i-4, j-1}] = color;
    frame[{i-1, j+1}] = color;
    frame[{i-2, j+1}] = color;
    frame[{i-3, j+1}] = color;
    frame[{i-4, j+1}] = color;
    //V
    //D(left)
    frame[{i  , j-4}] = color;
    frame[{i  , j-5}] = color;
    frame[{i-1, j-5}] = color;
    frame[{i-2, j-5}] = color;
    frame[{i-3, j-5}] = color;
    frame[{i-4, j-5}] = color;
    frame[{i-4, j-4}] = color;
    frame[{i-3, j-3}] = color;
    frame[{i-2, j-3}] = color;
    frame[{i-1, j-3}] = color;
    //D(left)
    //D(right)
    frame[{i  , j+4}] = color;
    frame[{i  , j+3}] = color;
    frame[{i-1, j+3}] = color;
    frame[{i-2, j+3}] = color;
    frame[{i-3, j+3}] = color;
    frame[{i-4, j+3}] = color;
    frame[{i-4, j+4}] = color;
    frame[{i-3, j+5}] = color;
    frame[{i-2, j+5}] = color;
    frame[{i-1, j+5}] = color;
    //D(right)
    //oo
    frame[{i+2  , j}] = color;
    frame[{i+3  , j}] = color;
    frame[{i+2  , j-1}] = color;
    frame[{i+2  , j-2}] = color;
    frame[{i+2  , j-3}] = color;
    frame[{i+3  , j-4}] = color;
    frame[{i+4  , j-3}] = color;
    frame[{i+4  , j-2}] = color;
    frame[{i+4  , j-1}] = color;
    frame[{i+4  , j}] = color;
    frame[{i+4  , j+1}] = color;
    frame[{i+4  , j+2}] = color;
    frame[{i+4  , j+3}] = color;
    frame[{i+3  , j+4}] = color;
    frame[{i+2  , j+3}] = color;
    frame[{i+2  , j+2}] = color;
    frame[{i+2  , j+1}] = color;
    //oo
    
    writer.write_frame(frame);
  }
  return 0;
}
