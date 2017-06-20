#include <iostream>
#include <iomanip>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include<time.h>
#include "ai.h"
#include "chessman.h"
#include <list>
#include <vector>
#include <math.h>
#include "function.h"
#include <iomanip>
typedef int8_t int8;

//Function		:ai
//Description	:Constructor, initialize all game info.
ai::ai(){
  //Board init
  init_all(chessBoard, chessMan, available, typeStart, rotateLimit);

  openingPattern = -1;
  openingComplete = false;
  skipStar = false;
  totalIteration = 5000;
}

void ai::ai_greeting(){
  std::cout << "Hi there!" << std::endl;
}

//Function		:judge
//Description	:Judge a match and return result.
matchResult ai::judge(int8 (&chessBoard)[19][19]){
 int checkBoard[13][13];
  for(int i=0; i<13; i++){
    for(int j=0; j<13; j++){
	  checkBoard[i][j] = 0;
	}
  }

  //增加邊界
  for(int i=2; i<17; i++){
    chessBoard[2][i] = 4;
	chessBoard[i][2] = 4;
	chessBoard[16][i] = 4;
	chessBoard[i][16] = 4;
  }

  //檢查死子
  for(int i=1; i<=2; i++){
    for(int j=0; j<13; j++){
	  for(int k=0; k<13; k++){
	    //迴避重複檢查
	    if(checkBoard[j][k] == 1) continue;
		if(chessBoard[j+3][k+3] == i){
		  //開始定位整個段落
		  //Section: 0=> empty; 1=> part of this section
		  int section[13][13];
		  for(int l=0; l<13; l++){
		    for(int m=0; m<13; m++){
			  section[l][m] = 0;
			}
		  }
          std::list<coordinate> path;
		  coordinate curCoor;
		  curCoor.row = j+3;
		  curCoor.col = k+3;
		  path.push_back(curCoor);

		  while(!(path.empty())){
		    curCoor = path.front();
		    path.pop_front();

			if(checkBoard[curCoor.row-3][curCoor.col-3] == 0){
			  //標記現在的位置
			  section[curCoor.row-3][curCoor.col-3] = 1;
		      checkBoard[curCoor.row-3][curCoor.col-3] = 1;
			  //像八個方向拓展
			  coordinate nextCoor;
			  //左上
			  if(chessBoard[curCoor.row-1][curCoor.col-1] == i){
			    nextCoor.row = curCoor.row - 1;
				nextCoor.col = curCoor.col - 1;
				path.push_back(nextCoor);
		      }
			  //上
			  if(chessBoard[curCoor.row-1][curCoor.col] == i){
			    nextCoor.row = curCoor.row - 1;
				nextCoor.col = curCoor.col;
				path.push_back(nextCoor);
		      }
			  //右上
			  if(chessBoard[curCoor.row-1][curCoor.col+1] == i){
			    nextCoor.row = curCoor.row - 1;
				nextCoor.col = curCoor.col + 1;
				path.push_back(nextCoor);
		      }
			  //右
			  if(chessBoard[curCoor.row][curCoor.col+1] == i){
			    nextCoor.row = curCoor.row;
				nextCoor.col = curCoor.col + 1;
				path.push_back(nextCoor);
		      }
			  //右下
			  if(chessBoard[curCoor.row+1][curCoor.col+1] == i){
			    nextCoor.row = curCoor.row + 1;
				nextCoor.col = curCoor.col + 1;
				path.push_back(nextCoor);
		      }
			  //下
			  if(chessBoard[curCoor.row+1][curCoor.col] == i){
			    nextCoor.row = curCoor.row + 1;
				nextCoor.col = curCoor.col;
				path.push_back(nextCoor);
		      }
			  //左下
			  if(chessBoard[curCoor.row+1][curCoor.col-1] == i){
			    nextCoor.row = curCoor.row + 1;
				nextCoor.col = curCoor.col - 1;
				path.push_back(nextCoor);
		      }
			  //左
			  if(chessBoard[curCoor.row][curCoor.col-1] == i){
			    nextCoor.row = curCoor.row;
				nextCoor.col = curCoor.col - 1;
				path.push_back(nextCoor);
		      }
            }
		  }

		  //開始檢查死活
		  bool alive = false;
		  int border = 0;
		  bool continueBorder = false;
		  //遊走邊界檢查
		  for(int l=0; l<13; l++){
		    if(section[0][l] == 1){
			  if(!continueBorder){
			    border++;
				continueBorder = true;
			  }
			}
		    else continueBorder = false;
		  }
		  for(int l=1; l<13; l++){
		    if(section[l][12] == 1){
			  if(!continueBorder){
			    border++;
				continueBorder = true;
			  }
			}
			else continueBorder = false;
		  }

		  for(int l=11; l>=0; l--){
		    if(section[12][l] == 1){
		      if(!continueBorder){
			      border++;
			   	  continueBorder = true;
			  }
			}
			else continueBorder = false;
		  }
		  for(int l=11; l>=0; l--){
		    if(section[l][0] == 1){
		      if(!continueBorder){
			      border++;
			   	  continueBorder = true;
			  }
			}
			else continueBorder = false;
		  }
		  //邊界遊走完成
		  if(border >= 2){
		    alive = true;
		  }
          else{
		    //掃描
			//水平掃描
            for(int l=0; l<13; l++){
			  for(int m=0; m<13; m++){
			    if(section[l][m] != 1){
				  section[l][m] = 2;
				}
				else break;
			  }
			  for(int m=12; m>=0; m--){
			    if(section[l][m] != 1){
				  section[l][m] = 2;
				}
			    else break;
			  }
			}
            //垂直掃描
            for(int l=0; l<13; l++){
			  for(int m=0; m<13; m++){
			    if(section[m][l] != 1){
				  section[m][l] = 2;
				}
				else break;
			  }
			  for(int m=12; m>=0; m--){
			    if(section[m][l] != 1){
				  section[m][l] = 2;
				}
			    else break;
			  }
			}
			//檢查是否還有空地存在
            for(int l=0; l<13; l++){
			  for(int m=0; m<13; m++){
			    if(section[l][m] == 0){
				  alive = true;
				  break;
				}
			  }
			  if(alive)break;
			}
		  }
		  if(alive){
		    for(int l=0; l<13; l++){
			  for(int m=0; m<13; m++){
			    if(section[l][m] == 1){
				  chessBoard[l+3][m+3] = i+4;
				}
			  }
			}
		  }
		}
	  }
    }
  }
  //領土結算
  int firstArea = 0;
  int secondArea = 0;
  for(int i=0; i<13; i++){
    for(int j=0; j<13; j++){
	  //由空地開始擴散
	  if(chessBoard[i+3][j+3] < 3){
	    int firstDead = 0;
		int secondDead = 0;
		int counter = 0;
		bool firstBorder = false;
		bool secondBorder = false;
		coordinate curCoor;
		curCoor.row = i;
		curCoor.col = j;
		std::list<coordinate> path;
		path.push_back(curCoor);
		while(!(path.empty())){
		  curCoor = path.front();
		  path.pop_front();
		  //碰到邊界則停止
          if(chessBoard[curCoor.row+3][curCoor.col+3] == 4) continue;
		  //碰到先手方
		  if(chessBoard[curCoor.row+3][curCoor.col+3] == 5){
		    firstBorder = true;
			continue;
		  }
		  //碰到後手方
		  if(chessBoard[curCoor.row+3][curCoor.col+3] == 6){
		    secondBorder = true;
			continue;
		  }
		  //碰到已經結算過得
		  if(chessBoard[curCoor.row+3][curCoor.col+3] == 7) continue;
		  //其他情況
		  switch(chessBoard[curCoor.row+3][curCoor.col+3]){
		    //空地
		    case 0:
			  counter++;
			  break;
			//先手方死子
			case 1:
			  firstDead++;
              break;
			//後手方死子
			case 2:
			  secondDead++;
			  break;
			//星位
			case 3:
			  counter++;
			  break;
			default:
			  break;
		  }
		  //標記
		  chessBoard[curCoor.row+3][curCoor.col+3] = 7;
          coordinate nextCoor;
		  //右
		  nextCoor.row = curCoor.row;
		  nextCoor.col = curCoor.col+1;
		  path.push_back(nextCoor);
		  //下
		  nextCoor.row = curCoor.row+1;
		  nextCoor.col = curCoor.col;
		  path.push_back(nextCoor);
		  //左
		  nextCoor.row = curCoor.row;
		  nextCoor.col = curCoor.col-1;
		  path.push_back(nextCoor);
		  //上
		  nextCoor.row = curCoor.row-1;
		  nextCoor.col = curCoor.col;
		  path.push_back(nextCoor);

		}
		//領地判別完成
		if(firstBorder && !secondBorder){
		  firstArea += (counter + secondDead*2);
		}
		else if(!firstBorder && secondBorder){
		  secondArea += (counter + firstDead*2);
		}

	  }
	}
  }
  matchResult result;
  if(firstArea > secondArea){
    result.winner = 1;
	result.score = firstArea;
    return result;
  }
  else if(secondArea > firstArea){
    result.winner = 2;
	result.score = secondArea;
    return result;
  }

  else{
    result.winner = 0;
	result.score = 0;
    return result;
  }
}

//Function		:debug_board
//Description	:Display board with color.
void ai::debug_board(int8 (&chessBoard)[19][19]){
  //行座標
  std::cout << "    ";
  for(int i=0; i<13; i++){
    std::cout << std::setw(2) << i << " ";
  }
  std::cout  << std::endl;
  std::cout << "    ";
  for(int i=0; i<13; i++){
    std::cout << std::setw(2) << "___";
  }
  std::cout << std::endl;

  for(int i=3; i<16; i++){
    //列座標
    std::cout << std::setw(2) << i-3 << " |";

	//內容
    for(int j=3; j<16; j++){
	  std::string display;
	  switch(chessBoard[i][j]){
	    case 0:
		  display = " o";
		  break;
		case 1:
          display = "\033[1;41m 1\033[0m";
		  break;
		case 2:
		  display = "\033[1;42m 2\033[0m";
		  break;
		case 3:
		  display = "\033[1;33m *\033[0m";
		  break;
		default:
		  display = (int)(chessBoard[i][j]);
	  }

	  std::cout << display << " ";
	}
	std::cout << std::endl;
  }
}

//Function		:check_chessman
//Description	:Check if a move is legal or not.
bool ai::check_chessman(int8 (&curBoard)[19][19],
                        int8 chessIndex,
						int8 row,
						int8 col,
						int8 term){
 //先檢查是否有空間
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
	  if((chessMan[chessIndex][i][j] == 1 )&&( (curBoard[row+i][col+j] != 0 && curBoard[row+i][col+j] != 3))){
	    return false;
	  }
	}
  }

  //檢查相連
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
	  if(chessMan[chessIndex][i][j] == 1){
	    //先確認相連
	    //Up
	    if((((row+i) - 1) > 2) && (curBoard[row+i-1][col+j] == term)){
		  return true;
		}
		//Down
	    else if((((row+i) + 1) < 16) && (curBoard[row+i+1][col+j] == term)){
		  return true;
		}
		//Left
		else if((((col+j) - 1) > 2) && (curBoard[row+i][col+j-1] == term)){
		  return true;
		}
		//Right
		else if((((col+j) + 1) < 16) && (curBoard[row+i][col+j+1] == term)){
		  return true;
		}

		//確認星位
		else if(curBoard[row+i][col+j] == 3){
		  return true;
		}
      }
	}
  }
  return false;

}

//Function      :ai_analyze
//Description   :Analyze current board and update member.
void ai::ai_analyze(node* root, int8 term, bool debug){
    int8 LTop, LBot, RTop, RBot;
    LTop = (root->board)[6][6];
    LBot = (root->board)[12][6];
    RTop = (root->board)[6][12];
    RBot = (root->board)[12][12];
    openingComplete = true;

    //Check star point.
    if( ((int)LTop == 3) || ((int)LBot == 3) || ((int)RTop == 3) || ((int)RBot == 3) ){
        openingComplete = false;
        openingPattern = -1;
    }
    else if( (LTop == 1) && (RTop == 1) ){
        if(term == 1){
            openingPattern = 0;
        }
        else{
            openingPattern = 1;
        }
    }
    else if( (LBot == 1) && (RBot == 1) ){
        if(term == 1){
            openingPattern = 1;
        }
        else{
            openingPattern = 0;
        }
    }
    else if( (LTop == 1) && (LBot == 1) ){
        if(term == 1){
            openingPattern = 2;
        }
        else{
            openingPattern = 3;
        }
    }
    else if( (RTop == 1) && (RBot == 1) ){
        if(term == 1){
            openingPattern = 3;
        }
        else{
            openingPattern = 2;
        }
    }
    else if( (LTop == 1) && (RBot == 1) ){
        if(term == 1){
            openingPattern = 5;
        }
        else{
            openingPattern = 4;
        }
    }
    else if( (RTop == 1) && (LBot == 1) ){
        if(term == 1){
            openingPattern = 4;
        }
        else{
            openingPattern = 5;
        }
    }

    if(debug){
        display_time(false);
        std::cout << "Analyze completed." << std::endl;
        if(openingComplete){
            std::cout << "           " << "All star points is occupied. My pattern is " << (int)openingPattern << "." << std::endl;
        }
        else{
            std::cout << "           " <<  "Star points are not yet all occupied." << std::endl;
    }
  }

}

//Function      :ai_star
//Description   :Analyze if current board still have star point.
bool ai::ai_star(node* root){
  if(skipStar) return false;
  int8 LTop, LBot, RTop, RBot, star;
  LTop = (root->board)[6][6];
  LBot = (root->board)[12][6];
  RTop = (root->board)[6][12];
  RBot = (root->board)[12][12];
  star = 3;
  if( ((int)LTop == 3) || ((int)LBot == 3) || ((int)RTop == 3) || ((int)RBot == 3) )return true;
  else return false;
}

//Function		:ai_available
//Description	:Update AI's available variable.
//**Currently no use**
void ai::ai_available(int8 (&curAvailable)[2][8]){
  for(int i=0; i<8; i++){
    available[0][i] = curAvailable[0][i];
	available[1][i] = curAvailable[1][i];
  }
}

//Function		:feasible_way
//Description	:Find all feasible move at a state.
void ai::feasible_way(node* root, bool debug){
  int8 term = ((root->round) % 2)+1;
  bool star = ai_star(root);

  //For all available chessman
  for(int i=0; i<8; i++){
    if((root->available)[term-1][i] > 0){

	  //For all rotation
	  for(int8 j=0; j<rotateLimit[i]; j++){
	    int8 chessIndex = typeStart[i] + j;

		//For all position
		for(int8 k=3; k<16; k++){
		  for(int8 l=3; l<16; l++){

            //Check if star point all taken.
            if(star)if((root->board)[k][l] != 3)continue;
		    if((check_chessman((root->board), chessIndex, k, l, term)) == true){
			  //Possible move founded.
			  //Board after possible move.
			  int8 newBoard[19][19];
			  update_board((root->board), newBoard, chessIndex, k, l, term);

			  //Available chessman after possible move
              int8 newAvailable[2][8];
			  memcpy(&newAvailable, &(root->available), sizeof(newAvailable));
			  newAvailable[term-1][i]--;

			  //Create new node
			  node* feasMove = new node;
			  initialize_node(feasMove, root, newBoard, newAvailable, (root->round)+1, i, j, k, l);

			  //Append to root
			  (root->children).push_back(feasMove);
			}
		  }
		}
	  }
	}
  }
}

//Function		:simulate_node
//Description	:Do the simulation part in MCTS.
//TODO: new simulate heuristic
void ai::simulate_node(node* start){
  //Check if not reach end.
  while(start->round != 18){

    //Determine term
    int8 term = (((start->round) % 2));
    int8 type, rotate, row, col;
	bool legalMove = false;
	//Make a move.
	int failCount = 0;
	int range = 2;
	while(!legalMove){
	  failCount++;
	  if(failCount > 1000){
	    failCount = 0;
		range = range*2;
		if(range > 16){
		  range = 16;
		}
      }

	  //Determine type.
	  type = rand() % 8;
      while((start->available)[term][type] == 0)type = rand() % 8;
	  //Determine rotation.
	  rotate = rand() % rotateLimit[type];

	  //Determine position.
	  row = rand() % 13;
	  col = rand() % 13;
	  /*col = 6+((rand() % range)-(range/2));
	  if(col < 0) col = 0;
	  else if(col > 12) col = 12;
      */
	  //Check legal move.
	  legalMove =  check_chessman(start->board, typeStart[type]+rotate, row+3, col+3, term+1);
	}

	//Update current available.
    (start->available)[term][type] -= 1;

	//Update board.
    update_board(start->board, start->board, typeStart[type]+rotate, row+3, col+3, term+1);
	(start->round)++;
  }
}

inline void ai::initialize_node(node* feasMove, node* parent, int8 (&curBoard)[19][19], int8 (&curAvailable)[2][8], int8 round, int8 type, int8 rotate, int8 row, int8 col){
  //Initial state(node) parameter.
  (feasMove->redWin) = 0;
  (feasMove->greenWin) = 0;
  (feasMove->total) = 0;
  (feasMove->round) = round;
  (feasMove->parent) = parent;
  (feasMove->type) = type;
  (feasMove->rotate) = rotate;
  (feasMove->row) = row;
  (feasMove->col) = col;
  (feasMove->redScore) = 0;
  (feasMove->greenScore) = 0;
  memcpy(&(feasMove->board), &curBoard, sizeof(feasMove->board));
  memcpy(&(feasMove->available), &curAvailable, sizeof(feasMove->available));
}

//Function		:update_board
//Description	:Update a board variable with specified chess type and position, term.
void ai::update_board(int8 (&curBoard)[19][19],
                      int8 (&newBoard)[19][19],
					  int8 chessIndex,
					  int8 row,
					  int8 col,
					  int8 term){
  //First copy old board to new board.
  memcpy(&newBoard, &curBoard, sizeof(newBoard));

  //Then add a move to board.
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
	  if(chessMan[chessIndex][i][j]){
	    newBoard[row+i][col+j] = term;
	  }
	}
  }
}

//Function		:select
//Description	:Select until reach leaf node with largest uct value at each depth.
node* ai::select(node* root, int8 term, int iteration){
  node* curNode = root;
  while((!(curNode->children).empty())&&((curNode->total)>4)){
    double maxUCT = -10.0;
	double curUCT = -10.0;
	node* nextNode;
	std::list<node*>::iterator it = (curNode->children).begin();
	while((it != (curNode->children).end())){
	  curUCT = uct_value(*it, iteration);
	  if(curUCT > maxUCT){
	    maxUCT = curUCT;
		nextNode = *it;
	  }
      it++;
	}
	curNode = nextNode;
  }
  return curNode;
}

//Function		:uct_value
//Description	:Calculate the uct value of a node.
double ai::uct_value(node* curNode, int iteration){
  double result = 0.0;
  double winRate = 0.0;
  if((curNode->round % 2) == 1){
    //First(Red)
	if(curNode->total == 0){
	  result = 0.6;
	}
	else{
      winRate = (double)(curNode->redWin)/(double)(curNode->total);
      result = winRate + 0.1 * sqrt(log10(iteration)/(double)(curNode->total));
	}

  }
  else{
    //Second(Green)
	if(curNode->total == 0){
	  result = 0.6;
	}
	else{
      winRate = (double)(curNode->greenWin)/(double)(curNode->total);
      result = winRate + 0.1 * sqrt(log10(iteration)/(double)(curNode->total));
	}
  }
  return result;
}


//Function		:ai_play
//Description	:main flow control of MCTS
void ai::ai_play(int8 (&curBoard)[19][19], int8 (&curAvailable)[2][8],int8 round, int8 term, int8 (&aiResult)[4], bool debug){
  srand(time(NULL));

  //Debug mode information
  if(debug){
    display_time(false);
    std::cout << "AI called with debug mode." << std::endl;
  }

  //std::cout << "AI received round: " << (int)round << std::endl;
  //Fixed round(框架內的round是未落子的round, 但ai要的round是當下state所在的)
  int8 curRound = round;
  //std::cout << "Term :" << (int)term << std::endl;

  //建立MCTS root
  node root;
  initialize_node(&root, NULL, curBoard, curAvailable, curRound-1, 0, 0, 0, 0);

  //Analyze board
  ai_analyze(&root, term, debug);
  //開始MCTS
  int iteration = 0;
  long long int expandCount = 0;
  int noWinner = 0;
  if(debug){display_time(false);std::cout << "MCTS Start." << std::endl;}

  while(iteration < totalIteration){
    if(debug){
        if((iteration % 1000) == 0){
            display_time(false);
            std::cout << "           Current iteration: " << iteration << std::endl;
        }
    }

    //Select
    node* mctsStart = select(&root, term, iteration);
    //Expand
	node* simStart;

	//Check if start is ended state or not.
	if(mctsStart->round != 18){
      //std::cout << "Select rount :" << mctsStart->round << std::endl;
	  //Check if start is leaf node.
	  if((mctsStart->children).size() == 0){
	    //Expand all possible move.
		feasible_way(mctsStart);
		expandCount++;
      }

	  //Then randomly pick a possible move
      int index = rand() % ((mctsStart->children).size());
	  std::list<node*>::iterator it = (mctsStart->children).begin();
	  for(int i=0; i<index; i++)it++;
	  simStart = *it;
	}
	else simStart = mctsStart;
	node simCopy = (*simStart);

	//Simulate: simulate with a copy version.
	simulate_node(&simCopy);

	//Judge result(should add area).
    matchResult matchOut = judge(simCopy.board);

	int winner = matchOut.winner;

	//Update
	node* temp = simStart;
	switch(winner){
	  case 1:
	    while(temp != NULL){
	      //Update node.
		  temp->total++;
		  temp->redWin++;
		  temp->redScore = (((temp->redScore*((double)temp->redWin-(double)1))+(double)matchOut.score)/(double)temp->redWin);

		  temp = temp->parent;
		}
		break;
	  case 2:
	    while(temp != NULL){
		  //Update node.
		  temp->total++;
		  temp->greenWin++;
		  temp->greenScore = (((temp->greenScore*((double)temp->greenWin-(double)1))+(double)matchOut.score)/(double)temp->greenWin);

		  temp = temp->parent;
		}
		break;
	  case 0:
	    noWinner++;
        while(temp != NULL){
		  //Update node.
		  temp->total++;
		  temp = temp->parent;
		}
		break;
    }
    iteration++;
  }
  if(debug){display_time(false);std::cout << "MCTS Completed." << std::endl;}

  node* result;
  double maxRate = -1.0;
  double curRate = 0.0;
  double maxScore = -1.0;
  std::list<node*>::iterator it = root.children.begin();
  while(it != root.children.end()){
    //std::cout << "Total check :" << (*it)->total << std::endl;
    if(term == 1){
	  curRate = (double)((*it)->redWin) / (double)((*it)->total);
	  if(curRate > maxRate){
	    maxRate = curRate;
		maxScore = (*it)->redScore;
		result = *it;
	  }
	  else if((curRate == maxRate) && ((*it)->redScore > maxScore)){
	    maxScore = (*it)->redScore;
		result = *it;
	  }
	}
	else{
      curRate = (double)((*it)->greenWin) / (double)((*it)->total);
	  if(curRate > maxRate){
	    maxRate = curRate;
		maxScore = (*it)->greenScore;
		result = *it;
	  }
	  else if((curRate == maxRate) && ((*it)->greenScore > maxScore)){
	    maxScore = (*it)->greenScore;
		result = *it;
	  }
	}
	it++;
  }
  //std::cout << "No winner :" << noWinner << std::endl;
  //std::cout << "Term :" << (int)term << std::endl;
  aiResult[0] = result->type;
  aiResult[1] = result->rotate;
  aiResult[2] = result->row;
  aiResult[3] = result->col;
  std::cout << "AI choose type[" << (int)(result->type) << "], rotate[" << (int)(result->rotate) << "], at (" << int((result->row)-3) << ", " << (int)((result->col)-3) << ")." << std::endl;
  std::cout << "Max win rate is :" << maxRate << std::endl;
  if(term == 1)std::cout << "Win :" << result->redWin << std::endl;
  else std::cout << "Win :" << result->greenWin << std::endl;
  std::cout << "Total :" << result->total << std::endl;
  if(debug){
    display_time(false);std::cout << "Basic information" << std::endl;
    std::cout << "           Choice :" << root.children.size() << std::endl;
    std::cout << "           Expand times :" << expandCount << std::endl;
    std::cout << "           Root total :" << root.total << std::endl;
    display_time(false);std::cout << "Choice of root and win rate" << std::endl;
    it = root.children.begin();
    while(it != root.children.end()){
      if( ((*it)->total) > 9 ){
        double win;
        if(term == 1) win = (*it)->redWin;
        else  win = (*it)->greenWin;
        double rate = win/(double)((int)(*it)->total);
        std::cout << "           Type[" << (int)(*it)->type << "] Rotate[" << (int)(*it)->rotate;
        std::cout << "] at(" << std::setw(2) << (int)((*it)->row - 3) << "," << std::setw(2) << (int)((*it)->col - 3) << ") | total=" << (*it)->total;
        std::cout << " win rate = " << rate << std::endl;
      }
      it++;
    }
  }

  ai_clean(&root);
}

//Function		:ai_clean
//Description	:Clean up heap memory.
void ai::ai_clean(node* root){
  int maxRound = -1;
  std::list<node*> toDelete;
  std::list<node*>::iterator it = (root->children).begin();
  while(it != (root->children).end()){
    toDelete.push_back(*(it++));
  }
  while(!toDelete.empty()){
    node* curNode = toDelete.front();
	if((curNode->round) > maxRound)maxRound = (curNode->round);
	toDelete.pop_front();
	it = (curNode->children).begin();
	while(it != (curNode->children).end()){
	  toDelete.push_back(*(it++));
	}
	delete curNode;
  }
  std::cout << "Leaf node round :" << maxRound << std::endl;
  return;
}

void ai::ai_option(bool s, int i){
  skipStar = s;
  totalIteration = i;
}
