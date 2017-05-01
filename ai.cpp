#include<iostream>
#include<iomanip>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"ai.h"
#include"chessman.h"
#include<list>
#include<vector>
#include<math.h>
ai::ai(){
  //Board init
  for(int i=0; i<19; i++){
    for(int j=0; j<19; j++){
	  chessBoard[i][j] = 0;
	}
  }
  //星位
  chessBoard[6][6] = 3;
  chessBoard[6][12] = 3;
  chessBoard[12][6] = 3;
  chessBoard[12][12] = 3;

  //可用棋子
  for(int i=1; i<8; i++){
    available[0][i] = 1;
	available[1][i] = 1;
  }
  available[0][0] = 2;
  available[1][0] = 2;

  //起始位置
  typeStart[0] = 0;
  typeStart[1] = 1;
  typeStart[2] = 5;
  typeStart[3] = 9;
  typeStart[4] = 11;
  typeStart[5] = 13;
  typeStart[6] = 17;
  typeStart[7] = 19;

  //旋轉限制
  rotateLimit[0] = 1;
  rotateLimit[1] = 4;
  rotateLimit[2] = 4;
  rotateLimit[3] = 2;
  rotateLimit[4] = 2;
  rotateLimit[5] = 4;
  rotateLimit[6] = 2;
  rotateLimit[7] = 1;

  //Chessman init
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
	  chessMan[0][i][j] = chess_type_0[i][j];
	}
  }
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
	  chessMan[1][i][j] = chess_type_1[i][j];
	}
  }
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
	  chessMan[2][i][j] = chess_type_2[i][j];
	}
  }
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
	  chessMan[3][i][j] = chess_type_3[i][j];
	}
  }
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
	  chessMan[4][i][j] = chess_type_4[i][j];
	}
  }
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
	  chessMan[5][i][j] = chess_type_5[i][j];
	}
  }
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
	  chessMan[6][i][j] = chess_type_6[i][j];
	}
  }
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
	  chessMan[7][i][j] = chess_type_7[i][j];
	}
  }
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
	  chessMan[8][i][j] = chess_type_8[i][j];
	}
  }
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
	  chessMan[9][i][j] = chess_type_9[i][j];
	}
  }
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
	  chessMan[10][i][j] = chess_type_10[i][j];
	}
  }
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
	  chessMan[11][i][j] = chess_type_11[i][j];
	}
  }
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
	  chessMan[12][i][j] = chess_type_12[i][j];
	}
  }
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
	  chessMan[13][i][j] = chess_type_13[i][j];
	}
  }
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
	  chessMan[14][i][j] = chess_type_14[i][j];
	}
  }
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
	  chessMan[15][i][j] = chess_type_15[i][j];
	}
  }
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
	  chessMan[16][i][j] = chess_type_16[i][j];
	}
  }
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
	  chessMan[17][i][j] = chess_type_17[i][j];
	}
  }
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
	  chessMan[18][i][j] = chess_type_18[i][j];
	}
  }
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
	  chessMan[19][i][j] = chess_type_19[i][j];
	}
  }
}

void ai::ai_greeting(){
  std::cout << "Hi there!" << std::endl;
}

matchResult ai::judge(int (&chessBoard)[19][19]){
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
				//std::cout << section[l][m] << " ";
			  }
			  //std::cout << std::endl;
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
  //std::cout << "先手領土 : " << firstArea << std::endl;
  //std::cout << "後手領土 : " << secondArea << std::endl;
  //std::cout << std::endl;
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

void ai::debug_board(int (&chessBoard)[19][19]){
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
		  display = chessBoard[i][j];
	  }

	  std::cout << display << " ";
	}
	std::cout << std::endl;
  }
}

bool ai::check_chessman(int (&curBoard)[19][19],
                        int chessIndex,
						int row,
						int col,
						int term){
 //先檢查是否有空間
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
	  if(chessMan[chessIndex][i][j] == 1 && (curBoard[row+i][col+j] != 0 && curBoard[row+i][col+j] != 3)){
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



void ai::ai_available(int (&curAvailable)[2][8]){
  for(int i=0; i<8; i++){
    available[0][i] = curAvailable[0][i];
	available[1][i] = curAvailable[1][i];
  }
}

void ai::feasible_way(node* root){
  int term = ((root->round) % 2)+1;
  //For all available chessman
  for(int i=0; i<8; i++){
    if((root->available)[term-1][i] > 0){

	  //For all rotation
	  for(int j=0; j<rotateLimit[i]; j++){
	    int chessIndex = typeStart[i] + j;

		//For all position
		for(int k=3; k<16; k++){
		  for(int l=3; l<16; l++){
		    if((check_chessman((root->board), chessIndex, k, l, term)) == true){

			  //Possible move founded.
			  //Board after possible move.
			  int newBoard[19][19];
			  update_board((root->board), newBoard, chessIndex, k, l, term);

			  //Available chessman after possible move
              int newAvailable[2][8];
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

void ai::simulate_node(node* start){
  //Check if not reach end.
  while(start->round != 18){

    //Determine term
    int term = (((start->round) % 2));
    int type, rotate, row, col;
	bool legalMove = false;
	//Make a move.
	while(!legalMove){
	  //Determine type.
	  type = rand() % 8;
      while((start->available)[term][type] == 0)type = rand() % 8;
	  //Determine rotation.
	  rotate = rand() % rotateLimit[type];

	  //Determine position.
	  row = rand() % 13;
	  col = rand() % 13;

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

inline void ai::initialize_node(node* feasMove, node* parent, int (&curBoard)[19][19], int (&curAvailable)[2][8], int round, int type, int rotate, int row, int col){
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

void ai::update_board(int (&curBoard)[19][19],
                      int (&newBoard)[19][19],
					  int chessIndex,
					  int row,
					  int col,
					  int term){
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

node* ai::select(node* root, int term, int iteration){
  node* curNode = root;
  while(!(curNode->children).empty()){
    double maxUCT = -10.0;
	double curUCT = -10.0;
	node* nextNode;
	std::list<node*>::iterator it = (curNode->children).begin();
	while(it != (curNode->children).end()){
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

double ai::uct_value(node* curNode, int iteration){
  double result = 0.0;
  double winRate = 0.0;
  if((curNode->round % 2) == 1){
    //First(Red)
	if(curNode->total == 0){
	  result = 1.05;
	}
	else{
      winRate = (double)(curNode->redWin)/(double)(curNode->total);
      result = winRate + 0.1 * sqrt(log10(iteration)/(double)(curNode->total));
	}

  }
  else{
    //Second(Green)
	if(curNode->total == 0){
	  result = 1.05;
	}
	else{
      winRate = (double)(curNode->greenWin)/(double)(curNode->total);
      result = winRate + 0.1 * sqrt(log10(iteration)/(double)(curNode->total));
	}
  }
  return result;
}

void ai::ai_play(int (&curBoard)[19][19], int (&curAvailable)[2][8],int round, int term, int (&aiResult)[3]){
  srand(time(NULL));
  std::cout << "AI received round: " << round << std::endl; 
  //Fixed round(框架內的round是未落子的round, 但ai要的round是當下state所在的)
  int curRound = round;
  std::cout << "Term :" << term << std::endl;

  //建立MCTS root
  node root;
  initialize_node(&root, NULL, curBoard, curAvailable, curRound-1, 0, 0, 0, 0);
    
  //開始MCTS
  int iteration = 0;
  while(iteration < 10000){
    //std::cout << "Iteration " << iteration << std::endl;
    //Select
	//std::cout << "Select start.\n";
    node* mctsStart = select(&root, term, iteration);
    //Expand
	//std::cout << "Expand start.\n";
	node* simStart;
	
	//Check if start is ended state or not.
	if(mctsStart->round != 18){

	  //Check if start is leaf node.
	  if((mctsStart->children).size() == 0){
	    //std::cout << "Current round: " << mctsStart->round << std::endl;
	    //Expand all possible move.
		feasible_way(mctsStart);

		//Log on console how many feasible move.
        //std::cout << "Found " << (mctsStart->children).size() << " move(s)." << std::endl;
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
	//std::cout << "Simulation start." << std::endl;
	simulate_node(&simCopy);

	//Judge result(should add area).
	//std::cout << "Judge start.\n";
	//debug_board(simCopy.board);
    matchResult matchOut = judge(simCopy.board);

	int winner = matchOut.winner;
    //std::cout << "Winner: " << winner << std::endl;

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
    }
    iteration++;
  }
  node* result;
  double maxRate = -1.0;
  double curRate = 0.0; 
  double maxScore = -1.0;
  std::list<node*>::iterator it = root.children.begin();
  while(it != root.children.end()){
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
  std::cout << "Term :" << term << std::endl; 
  std::cout << "Max win rate is :" << maxRate << std::endl;
  if(term == 1)std::cout << "Win :" << result->redWin << std::endl;
  else std::cout << "Win :" << result->greenWin << std::endl;
  std::cout << "Total :" << result->total << std::endl;
  std::cout << "AI choose type[" << result->type << "], rotate[" << result->rotate << "], at (" << (result->row)-3 << ", " << (result->col)-3 << ")." << std::endl;
  ai_clean(&root);
}

void ai::ai_clean(node* root){
  std::list<node*> toDelete;
  std::list<node*>::iterator it = (root->children).begin();
  while(it != (root->children).end()){
    toDelete.push_back(*(it++));
  }
  while(!toDelete.empty()){
    //std::cout << "Del..\n";
    node* curNode = toDelete.front();
	toDelete.pop_front();
	it = (curNode->children).begin();
	while(it != (curNode->children).end()){
	  toDelete.push_back(*(it++));
	}
	delete curNode;
  }
  return;
}
