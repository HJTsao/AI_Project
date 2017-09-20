#ifndef HEURISTIC_H
#define HEURISTIC_H
#include <iostream>
#include <stdint.h>
#include "ai.h"
class scoring{
  public:

    //Constructor
    scoring();

    //Perimeter calculator(can't handle illegal move)
    int perimeter(node* curNode,
                  int8 term);



};




#endif
