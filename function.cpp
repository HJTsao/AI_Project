#include <iostream>
#include <ctime>
#include <iomanip>
#include <stdio.h>
#include "function.h"
void display_time(bool CR){
    time_t t = time(0);
    struct tm* now = localtime(&t);
    printf("[%02d:%02d:%02d] ", now->tm_hour, now->tm_min, now->tm_sec);
    if(CR) std::cout << std::endl;
}
