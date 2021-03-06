#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED
#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
typedef int8_t int8;

class timer{
  public:
    //Constructor
    timer();

    //Set timer start
    void timer_start();

    //Return time elapsed from last start
    int timer_gettime();

  private:
    struct timeval start, end;
};
void display_time(bool CR = false);
void delete_last_line(std::fstream &gameLog);
void to_last_line(std::fstream &gameLog);
void init_all(int8 (&chessBoard)[19][19],
               int8 (&chessMan)[20][4][4],
			   int8 (&available)[2][8],
			   int8 (&typeStart)[8],
			   int8 (&rotateLimit)[8]);




#endif // FUNCTION_H_INCLUDED
