#include <iostream>
#include <list>
#include "heuristic.h"
typedef int8_t int8;
scoring::scoring(){
  std::cout << "Scoring heuristic created.\n";
}

int scoring::perimeter(node* curNode,
                  int8 term){
    //Debug
    /*for(int i=0;i<19;i++){
        for(int j=0;j<19;j++){
            std::cout << (curNode->board)[i][j] << " ";
        }
        std::cout <<  std::endl;
    }*/
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
                coordinate tempCor;
                tempCor = *(findingPath.begin());
                std::cout << (int)(tempCor.row) << " " << (int)(tempCor.col) << std::endl;
                findingPath.pop_front();
                checkBoard[tempCor.row][tempCor.col] = sessionCounter;
                if((curNode->board)[tempCor.row-1][tempCor.col] == (term+1) && checkBoard[tempCor.row-1][tempCor.col] == 0){
                    curCor.row = tempCor.row-1;
                    curCor.col = tempCor.col;
                    findingPath.push_back(curCor);
                }
                if((curNode->board)[tempCor.row-1][tempCor.col+1] == (term+1) && checkBoard[tempCor.row-1][tempCor.col+1] == 0){
                    curCor.row = tempCor.row-1;
                    curCor.col = tempCor.col+1;
                    findingPath.push_back(curCor);
                }
                if((curNode->board)[tempCor.row][tempCor.col+1] == (term+1) && checkBoard[tempCor.row][tempCor.col+1] == 0){
                    curCor.row = tempCor.row;
                    curCor.col = tempCor.col+1;
                    findingPath.push_back(curCor);
                }
                if((curNode->board)[tempCor.row+1][tempCor.col+1] == (term+1) && checkBoard[tempCor.row+1][tempCor.col+1] == 0){
                    curCor.row = tempCor.row+1;
                    curCor.col = tempCor.col+1;
                    findingPath.push_back(curCor);
                }
                if((curNode->board)[tempCor.row+1][tempCor.col] == (term+1) && checkBoard[tempCor.row+1][tempCor.col] == 0){
                    curCor.row = tempCor.row+1;
                    curCor.col = tempCor.col;
                    findingPath.push_back(curCor);
                }
                if((curNode->board)[tempCor.row+1][tempCor.col-1] == (term+1) && checkBoard[tempCor.row+1][tempCor.col-1] == 0){
                    curCor.row = tempCor.row+1;
                    curCor.col = tempCor.col-1;
                    findingPath.push_back(curCor);
                }
                if((curNode->board)[tempCor.row][tempCor.col-1] == (term+1) && checkBoard[tempCor.row][tempCor.col-1] == 0){
                    curCor.row = tempCor.row;
                    curCor.col = tempCor.col-1;
                    findingPath.push_back(curCor);
                }
                if((curNode->board)[tempCor.row-1][tempCor.col-1] == (term+1) && checkBoard[tempCor.row-1][tempCor.col  -1] == 0){
                    curCor.row = tempCor.row-1;
                    curCor.col = tempCor.col-1;
                    findingPath.push_back(curCor);
                }
            }
        }
    }
  }
  std::cout << "Find " << sessionCounter << " session(s).\n";
}
