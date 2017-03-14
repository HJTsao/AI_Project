#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"ai.h"
#include"chessman.h"
#include<list>
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

int ai::judge(int (&chessBoard)[19][19]){
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
  //std::cout << "先手領土 : " << firstArea << std::endl;
  //std::cout << "後手領土 : " << secondArea << std::endl;
  if(firstArea > secondArea)return 1;
  else if(secondArea > firstArea)return 2;
  else return 0;
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

void ai::feasible_way(node* root, int term){
  //For all available chessman
  for(int i=0; i<8; i++){
    if((root->available)[term-1][i] > 0){
	  //For all direction
	  for(int j=0; j<rotateLimit[i]; j++){
	    int chessIndex = typeStart[i] + j;
		//For all position
		for(int k=3; k<16; k++){
		  for(int l=3; l<16; l++){
		    if((check_chessman((root->board), chessIndex, k, l, term)) == true){
			  //Possible move
			  //Board after possible move
			  int newBoard[19][19];
			  update_board((root->board), newBoard, chessIndex, k, l, term);

			  //Available chessman after possible move
              int newAvailable[2][8];
			  memcpy(&newAvailable, &(root->available), sizeof(newAvailable));
			  newAvailable[term-1][i]--;

			  //Create new node
			  node* feasMove = new node;
			  initialize_node(feasMove, root, newBoard, newAvailable, (root->round)+1, i, j, k, l);
			  //memcpy(&(feasMove->board), &newBoard, sizeof(feasMove->board));
			  //(feasMove->parent) = &root;

			  //Append to root
			  (root->children).push_back(feasMove);
			  //std::cout << "Type[" << i << "] can be place on (" << k << ", " << l << ") with rotation " << j << std::endl;
			}
		  }
		}
	  }
	}
  }
}

void ai::simulate_node(node* start){
  
  while(start->round != 18){
    //std::cout << "Simulate start." << std::endl;
    //Determine term
    int term = start->round % 2;

    int type, rotate, row, col;
	bool legalMove = false;
	//Choose type
	while(!legalMove){
	  type = rand() % 8;
      while(available[term][type] == 0)type = rand() % 8;
	  rotate = rand() % rotateLimit[type];
	  row = rand() % 13;
	  col = rand() % 13;
	  legalMove =  check_chessman(start->board, typeStart[type]+rotate, row+3, col+3, term+1);
	}
    update_board(start->board, start->board, typeStart[type]+rotate, row+3, col+3, term+1);
	(start->round)++;
  }
  //std::cout << "Simulation complete." << std::endl;

}
inline void ai::initialize_node(node* feasMove, node* parent, int (&curBoard)[19][19], int (&curAvailable)[2][8], int round, int type, int rotate, int row, int col){
  (feasMove->redWin) = 0;
  (feasMove->greenWin) = 0;
  (feasMove->total) = 0;
  (feasMove->round) = round;
  (feasMove->parent) = parent;
  (feasMove->type) = type;
  (feasMove->rotate) = rotate;
  (feasMove->row) = row;
  (feasMove->col) = col;
  memcpy(&(feasMove->board), &curBoard, sizeof(feasMove->board));
  memcpy(&(feasMove->available), &curAvailable, sizeof(feasMove->available));
}

inline void ai::initialize_element(tableElement* curElement, node* curNode){
  curElement->redWin = curNode->redWin;
  curElement->greenWin = curNode->greenWin;
  curElement->total = curNode->total;
  curElement->link = curNode;
}

void ai::update_board(int (&curBoard)[19][19],
                      int (&newBoard)[19][19],
					  int chessIndex,
					  int row,
					  int col,
					  int term){
  memcpy(&newBoard, &curBoard, sizeof(newBoard));
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
	  if(chessMan[chessIndex][i][j]){
	    newBoard[row+i][col+j] = term;
	  }
	}
  }
}
/*
node* ai::uct(node* root){
  */

void ai::ai_play(int (&curBoard)[19][19], int (&curAvailable)[2][8],int round, int term, int (&aiResult)[3]){
  srand(time(NULL));
  
  //Fixed round
  int curRound = round-1;
  
  //Create empty node table
  std::list<tableElement> nodeTable; 
  
  //建立MCTS root
  node root;
  initialize_node(&root, NULL, curBoard, curAvailable, curRound, 0, 0, 0, 0);
  /*memcpy(&(root.board), &curBoard, sizeof(root.board));
  root.parent = NULL;*/
  tableElement element;
  nodeTable.push_back(element);
  initialize_element(&(nodeTable.back()), &root);

  //feasible_way(curBoard, curAvailable, root, round, term);
    
  //開始MCTS
  int iteration = 0;
  while(iteration < 10000){
    //std::cout << "Current root child :" << root.children.size() << std::endl;
    //Select
	node* mctsStart = &root;
    //node* start = uct(&root, term);
    //Expand
	//If start is leaf node but not ended state
	node* simStart;
	
	if(mctsStart->round != 18){
	  if((mctsStart->children).size() == 0){
	    feasible_way(mctsStart, term);
        std::cout << "Found " << (mctsStart->children).size() << " way(s)." << std::endl;
      }
	  //Then randomly pick a possible move
      int index = rand() % ((mctsStart->children).size());
	  std::list<node*>::iterator it = (mctsStart->children).begin();
	  for(int i=0; i<index; i++)it++;
	  simStart = *it;
	  //std::cout << "Randomly pike Type[" << simulate->type << "]_rotate[" << simulate->rotate << "] at (" << simulate->row << ", " << simulate->col << ")" << std::endl;
	}
	else simStart = mctsStart;
    node simCopy = (*simStart);
	//std::cout << "Test :(" << simStart->row << ", " << simStart->col << ")" << std::endl;
	//Simulate : simulate with a copy version!!
	simulate_node(&simCopy);
	//To do: simulate function
    int winner = judge(simCopy.board);

	//Update
	node* temp = simStart;
	switch(winner){
	  case 1:
	    while(temp != NULL){
	      temp->total++;
		  temp->redWin++;
		  temp = temp->parent;
		}
		break;
	  case 2:
	    while(temp != NULL){
		  temp->total++;
		  temp->greenWin++;
		  temp = temp->parent;
		}
		break;
    }
    iteration++;
  }
  node* result;
  double maxRate = -1.0;
  double curRate = 0.0; 
  std::list<node*>::iterator it = root.children.begin();
  while(it != root.children.end()){
    if(term == 1){
	  curRate = (double)((*it)->redWin) / (double)((*it)->total);
	  if(curRate > maxRate){
	    maxRate = curRate;
		result = *it;
	  }
	}
	else{
      curRate = (double)((*it)->greenWin) / (double)((*it)->total);
	  if(curRate > maxRate){
	    maxRate = curRate;
		result = *it;
	  }
	}
	it++;
  }
  std::cout << "Max win rate is :" << maxRate << std::endl;
  std::cout << "Win :" << result->greenWin << std::endl;
  std::cout << "Total :" << result->total << std::endl;
  std::cout << "AI choose type[" << result->type << "], rotate[" << result->rotate << "], at (" << (result->row)-3 << ", " << (result->col)-3 << ")." << std::endl;
}

