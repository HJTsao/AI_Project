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

    int maxPerimeter = 0;
    int checkBoard2[19][19];
    for(int i=0; i<19; i++)for(int j=0; j<19; j++)checkBoard2[i][j] = 0;

    //Calculate perimeter for all sessions
    for(int i=3; i<16; i++){
        for(int j=3; j<16; j++){
            //Check next position if current position is not the session we are finding.
            if(checkBoard2[i][j] != 0 || checkBoard[i][j] == 0) continue;

            //Expand the whole session.
            //Check up, down, left, right connected to same session or not, if not, perimeter increase.
            //Otherwise, push that connected same session part into list.
            int curPerimeter = 0;
            int curSession = checkBoard[i][j];
            std::list<coordinate> findingPath;
            coordinate curCor;
            curCor.row = i; curCor.col = j;
            findingPath.push_back(curCor);
            while(!findingPath.empty()){
                curCor = *(findingPath.begin());
                findingPath.pop_front();

                //Skip if already visited.
                if(checkBoard2[curCor.row][curCor.col] == 1)continue;
                
                //Mark visited position.
                checkBoard2[curCor.row][curCor.col] = 1;
                
                //Increase perimeter if next to an empty or enemy chess.
                if(checkBoard[curCor.row-1][curCor.col] != curSession && (curCor.row - 1) > 2)curPerimeter++;
                if(checkBoard[curCor.row][curCor.col-1] != curSession && (curCor.col - 1) > 2)curPerimeter++;
                if(checkBoard[curCor.row+1][curCor.col] != curSession && (curCor.row + 1) < 16) curPerimeter++;
                if(checkBoard[curCor.row][curCor.col+1] != curSession && (curCor.col + 1) < 16)curPerimeter++;

                //Push connected same session part into list.
                coordinate tempCor;
                if(checkBoard[curCor.row-1][curCor.col] == curSession && checkBoard2[curCor.row-1][curCor.col] == 0){
                    tempCor.row = curCor.row-1;
                    tempCor.col = curCor.col;
                    findingPath.push_back(tempCor);
                }
                if(checkBoard[curCor.row-1][curCor.col+1] == curSession && checkBoard2[curCor.row-1][curCor.col+1] == 0){
                    tempCor.row = curCor.row-1;
                    tempCor.col = curCor.col+1;
                    findingPath.push_back(tempCor);
                }
                if(checkBoard[curCor.row][curCor.col+1] == curSession && checkBoard2[curCor.row][curCor.col+1] == 0){
                    tempCor.row = curCor.row;
                    tempCor.col = curCor.col+1;
                    findingPath.push_back(tempCor);
                }
                if(checkBoard[curCor.row+1][curCor.col+1] == curSession && checkBoard2[curCor.row+1][curCor.col+1] == 0){
                    tempCor.row = curCor.row+1;
                    tempCor.col = curCor.col+1;
                    findingPath.push_back(tempCor);
                }
                if(checkBoard[curCor.row+1][curCor.col] == curSession && checkBoard2[curCor.row+1][curCor.col] == 0){
                    tempCor.row = curCor.row+1;
                    tempCor.col = curCor.col;
                    findingPath.push_back(tempCor);
                }
                if(checkBoard[curCor.row+1][curCor.col-1] == curSession && checkBoard2[curCor.row+1][curCor.col-1] == 0){
                    tempCor.row = curCor.row+1;
                    tempCor.col = curCor.col-1;
                    findingPath.push_back(tempCor);
                }
                if(checkBoard[curCor.row][curCor.col-1] == curSession && checkBoard2[curCor.row][curCor.col-1] == 0){
                    tempCor.row = curCor.row;
                    tempCor.col = curCor.col-1;
                    findingPath.push_back(tempCor);
                }
                if(checkBoard[curCor.row-1][curCor.col-1] == curSession && checkBoard2[curCor.row-1][curCor.col-1] == 0){
                    tempCor.row = curCor.row-1;
                    tempCor.col = curCor.col-1;
                    findingPath.push_back(tempCor);
                }
                
                

            }
            std::cout << "Current session: " << curSession << ", Perimeter: " << curPerimeter << std::endl;

        }
    }
    
  std::cout << "Find " << sessionCounter << " session(s).\n";
}
