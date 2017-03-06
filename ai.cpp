#include<iostream>
#include<string.h>
#include"ai.h"
#include"chessman.h"
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

bool ai::check_chessman(int (&curBoard)[19][19],
                        int chessIndex,
						int row,
						int col,
						int term){
 //先檢查是否有空間
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
	  if(chessMan[chessIndex][i][j] == 1 && (curBoard[row+i][col+j] != 0 && curBoard[row+i][col+j] != 3)){
        std::cout << "所選位置重疊到其他棋子" << std::endl;
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
  std::cout << "沒有相連或不在星位上" << std::endl;
  return false;
  
}


void ai::ai_available(int (&curAvailable)[2][8]){
  for(int i=0; i<8; i++){
    available[0][i] = curAvailable[0][i];
	available[1][i] = curAvailable[1][i];
  }
}

void ai::feasible_way(int (&curBoard)[19][19],
                  int (&curAvailable)[2][8],
				  node &root,
				  int term){
  //For all available chessman
  for(int i=0; i<8; i++){
    if(curAvailable[term][i] > 0){
	  //For all direction
	  for(int j=0; j<rotateLimit[i]; j++){
	    int chessIndex = typeStart[i] + j;
		//For all position
		for(int k=3; k<16; k++){
		  for(int l=3; l<16; l++){
		    if((check_chessman(curBoard, chessIndex, k, l, term)) == true){
			  //Possible move
			  //Board after possible move
			  int newBoard[19][19];
			  update_board(curBoard, newBoard, chessIndex, k, l, term);

			  //Create new node
			  node* feasMove = new node;
			  initialize_node(feasMove);
			  memcpy(&(feasMove->board), &newBoard, sizeof(feasMove->board));
			  (feasMove->parent) = &root;

			  //Append to root
			  (root.children).push_back(feasMove);
			}
		  }
		}
	  }
	}
  }
}

void ai::initialize_node(node* feasMove){
  (feasMove->redWin) = 0;
  (feasMove->greenWin) = 0;
  (feasMove->total) = 0;
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
void ai::ai_play(int &(curBoard)[19][19], int &(aiResult)[3]){
  //建立MCTS root
  node root;
  root.redWin = 0;
  root.greenWin = 0;
  root.total = 0;
  root.board = curBoard;
  root.parent = NULL;
  
  //開始MCTS
  int iteration = 0;
  while(iteration < 100){
    iteration++;
  }
}
*/
