#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/time.h>
#include "function.h"
#include "chessman.h"
typedef int8_t int8;
//To do
/*
    Simulation check.
    Heuristic: total boarder length or taken row & col
    Expand: advance move check
*/


//Function      :timer
//Description   :Constructor of timer
timer::timer(){
  //Do nothing.
}

//Function      :timer_start
//Description   :Update start time of timer
void timer::timer_start(){
  gettimeofday(&start, 0);
}

//Function      :timer_gettime
//Description   :Get time elapsed from last start
int timer::timer_gettime(){
  gettimeofday(&end,0);
  int sec;
  sec = end.tv_sec - start.tv_sec;
  return sec;
}

void display_time(bool CR){
    time_t t = time(0);
    struct tm* now = localtime(&t);
    printf("[%02d:%02d:%02d] ", now->tm_hour, now->tm_min, now->tm_sec);
    if(CR) std::cout << std::endl;
}

void to_last_line(std::fstream &gameLog){
  gameLog.seekg(-2, gameLog.end);
  bool keepLoop = true;
  while(keepLoop){
    char cur_char;
	gameLog.get(cur_char);
	//只有一行
	if((int)gameLog.tellg() <= 1){
	  gameLog.seekg(0);
	  keepLoop = false;
	}
    //若讀到倒數第二個換行代表完成
	else if(cur_char == '\n'){
	  keepLoop = false;
	}
    //若未讀到換行則繼續往前跳
	else{
	  gameLog.seekg(-2, gameLog.cur);
	}
  }
}

void delete_last_line(std::fstream &gameLog){
  //Get last line
  std::string lastLine, logContent;
  to_last_line(gameLog);
  getline(gameLog, lastLine);

  //Get all log
  gameLog.seekg(0);
  std::stringstream ss;
  ss << gameLog.rdbuf();
  logContent = ss.str();
  logContent.replace(logContent.find(lastLine), lastLine.length()+1, "");

  //Write back
  gameLog.close();
  gameLog.open("cur_game.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
  gameLog << logContent;
}

void init_all(int8 (&chessBoard)[19][19],
               int8 (&chessMan)[20][4][4],
			   int8 (&available)[2][8],
			   int8 (&typeStart)[8],
			   int8 (&rotateLimit)[8]){
  //Board init
  for(int i=0; i<19; i++){
    for(int j=0; j<19; j++){
	  chessBoard[i][j] = 4;
	}
  }
  for(int i=3; i<16; i++){
    for(int j=3; j<16; j++){
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
