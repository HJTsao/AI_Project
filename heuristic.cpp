#include <iostream>
#include <list>
#include "heuristic.h"
typedef int8_t int8;
scoring::scoring(){
  std::cout << "Scoring heuristic created.\n";
}

int scoring::perimeter(node* curNode,
                  int8 term){
  //Find session(s)
  int sessionCounter = 0;
  int checkBoard[19][19];
  for(int i=0; i<19; i++)for(int j=0; j<19; j++)checkBoard[i][j] = 0;
  for(int i=3; i<16; i++){
    for(int j=3; j<16; j++){
        if(checkBoard[i][j] != 0)continue;
        if((curNode->board)[i][j] == (term+1)){
            //New session found!
            sessionCounter++;
            checkBoard[i][j] = sessionCounter;
            std::list<coordinate> findingPath;
            coordinate curCor;
            curCor.row = i;
            curCor.col = j;
            findingPath.push_back(curCor);
            while(!findingPath.empty()){
                curCor = findingPath.pop_back();
                if((curNode->board)[i-1][j] == (term+1)){
                    curCor.row = i-1;
                    curCor.col = j;
                    findingPath.push_back(curCor);
                }
                if((curNode->board)[i-1][j+1] == (term+1)){
                    
                }
                if((curNode->board)[i][j+1] == (term+1)){
                    
                }
                if((curNode->board)[i+1][j+1] == (term+1)){
                    
                }
                if((curNode->board)[i+1][j] == (term+1)){
                    
                }
                if((curNode->board)[i+1][j-1] == (term+1)){
                    
                }
                if((curNode->board)[i][j-1] == (term+1)){
                    
                }
                if((curNode->board)[i-1][j-1] == (term+1)){
                    
                }
            }
        }
    }
  }
}
