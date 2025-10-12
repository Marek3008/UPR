#include <stdio.h>
#include "drawing.h"


void line_dotted(int length){
  
  set_blue_color();
  
  for(int i = 1; i <= length; i++){
    draw_pixel();
    move_right();
    move_right();
  }
}

void steps(int number){
  
  set_white_color();
  
  for(int i = 1; i <= number; i++){
    for(int i = 1; i <= 5; i++){
      draw_pixel();
      move_right();
    }

    for(int i = 1; i <= 5; i++){
      draw_pixel();
      move_down();
    }
  }
}

void steps_animated(int number){
  
  set_white_color();

  for(int i = 1; i <= number; i++){
    for(int i = 1; i <= 5; i++){
      draw_pixel();
      animate_ms(100);
      move_right();
    }

    for(int i = 1; i <= 5; i++){
      draw_pixel();
      animate_ms(100);
      move_down();
    }
  }
}

void flower(int x, int y){

  int outer_line = x / 3;
  int midpoint = (x / 2) + 1;
  int stem_height = y - x;

  set_yellow_color();

  for(int i = 1; i <= x; i++){
    for(int j = 1; j <= x; j++){
      if(i > outer_line && i < x - outer_line + 1 && j > outer_line && j < x - outer_line + 1){
        set_black_color();
      }
      else{
        set_yellow_color();
      }
      draw_pixel();
      move_right();
    }
    move_down();
    for(int i = 1; i <= x; i++){
      move_left();
    }
  }
  set_green_color();
  for(int i = 1; i < midpoint; i++){
    move_right();
  }

  for(int i = 1; i <= stem_height; i++){
    draw_pixel();
    move_down();
  }

  for(int i = 1; i <= y; i++){
    move_up();
  }

  for(int i = 1; i <= midpoint; i++){
    move_right();
  }
}

void meadow(int rows, int cols){

  int x = 5;
  int y = 7;
  int get_to_start = (y + 2) * cols;
  int move_by_y = y + 2;

  for(int i = 1; i <= rows; i++){
    for(int j = 1; j <= cols; j++){
      flower(x, y);

      if(j != cols){
        move_right();
        move_right();
      }
    }

    for(int j = 1; j <= get_to_start; j++){
      move_left();
    }

    for(int j = 1; j <= move_by_y; j++){
      move_down();
    }
  }
}

int main() {

  int image;
  scanf("%d", &image);

  clear_screen();

  switch(image)
  {
    case 0:
      line_dotted(20);
      break;
    
    case 1: 
      steps(3);
      break;
    
    case 2:
      flower(5, 10);
      break;
    
    case 3:
      meadow(2, 7);
      break;

    case 4:
      steps_animated(5);
      break;

    default:
      printf("Neznamy input");
  }
  
  end_drawing();

  return 0;
}
