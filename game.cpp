#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<vector>
#include<list>
#include "chessman.h"
#include "ai.h"
struct coordinate {
 int row;
 int col;
};

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

void game_init(int (&chessBoard)[19][19],
               int (&chessMan)[20][4][4],
			   int (&available)[2][8],
			   int (&typeStart)[8],
			   int (&rotateLimit)[8]){
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

int game_judge(int (&chessBoard)[19][19]){
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
		  //取得完整的段落資料
		  /*for(int l=0; l<13; l++){
		    for(int m=0; m<13; m++){
			  std::cout << section[l][m] << " ";
			}
			std::cout << std::endl;
		  }
		  std::cout << std::endl;*/

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
  std::cout << "先手領土 : " << firstArea << std::endl;
  std::cout << "後手領土 : " << secondArea << std::endl;
  if(firstArea > secondArea)return 1;
  else if(secondArea > firstArea)return 2;
  else return 0;
}

void debug_display_board(int (&chessBoard)[19][19]){
  for(int i=2; i<17; i++){
    for(int j=2; j<17; j++){
	  std::cout << chessBoard[i][j] << " ";
	}
	std::cout << std::endl;
  }
}

void display_board(int (&chessBoard)[19][19]){
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

void display_chessman(int (&chessMan)[20][4][4]){
  for(int i=0; i<20; i++){
    std::cout << "Type: " << i << std::endl;
    for(int j=0; j<4; j++){
	  for(int k=0; k<4; k++){
	    std::cout << chessMan[i][j][k] << " ";
	  }
	  std::cout << std::endl;
    }
    std::cout<< std::endl;
  }
}

bool check_chessman(int (&chessBoard)[19][19],
                    int (&chessMan)[20][4][4],
					int (&typeStart)[8],
					int (&rotateLimit)[8],
					int type,
					int rotate,
					int row,
					int col,
					int term){
  //先檢查是否有空間
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
	  if(chessMan[(typeStart[type] + (rotate % rotateLimit[type]))][i][j] == 1 && (chessBoard[row+i][col+j] != 0 && chessBoard[row+i][col+j] != 3)){
        std::cout << "所選位置重疊到其他棋子" << std::endl;
	    return false;
	  }
	}
  }

  //檢查相連
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
	  if(chessMan[(typeStart[type] + (rotate % rotateLimit[type]))][i][j] == 1){
	    //std::cout << (typeStart[type] + (rotate % rotateLimit[type])) << std::endl;
	    //std::cout << "check (" << row+i << " ," << col+j << ")" << std::endl;
	    //先確認相連
	    //Up
	    if((((row+i) - 1) > 2) && (chessBoard[row+i-1][col+j] == term)){
		  return true;
		}
		//Down
	    else if((((row+i) + 1) < 16) && (chessBoard[row+i+1][col+j] == term)){
		  return true;
		}
		//Left
		else if((((col+j) - 1) > 2) && (chessBoard[row+i][col+j-1] == term)){
		  return true;
		}
		//Right
		else if((((col+j) + 1) < 16) && (chessBoard[row+i][col+j+1] == term)){
		  return true;
		}

		//確認星位
		else if(chessBoard[row+i][col+j] == 3){
		  return true;
		}
      }
	}
  }
  std::cout << "沒有相連或不在星位上" << std::endl;
  return false;
}

void game_main(){
  int chessBoard[19][19];
  int chessMan[20][4][4];
  int typeStart[8];
  int rotateLimit[8];
  int term = 1;
  int available[2][8];
  int round = 1;
  std::string input;
  int type = 0;
  int rotate = 0;
  int row = 0;
  int col = 0;

  game_init(chessBoard, chessMan, available, typeStart, rotateLimit);
  std::string logName = "cur_game.txt";
  std::fstream gameLog;
  gameLog.open(logName.c_str(), std::fstream::in | std::fstream::out | std::fstream::trunc);

  //AI init
  ai AI;
  AI.ai_greeting();

  //Load or New game
  char ans;
  std::cout << "是否讀取棋盤(y/n)？ ";
  std::cin >> ans;
  if(ans == 'y'){
    //Open saved file
    std::string load_file;
	std::cout << "請輸入存檔名稱： ";
	std::cin >> load_file;
	std::fstream loadFs;
	loadFs.open(load_file.c_str(), std::fstream::in);
	while(!loadFs){
	  std::cout << "不正確的名稱" << std::endl;
	  std::cout << "請輸入存檔名稱： ";
	  std::cin >> load_file;
	  loadFs.open(load_file.c_str(), std::fstream::in);
	}

	//Get information
	//Round
	loadFs >> round;
	//Term
	term = (round % 2)? 1 : 2;
	//Available
	for(int i=0; i<2; i++){
	  for(int j=0; j<8; j++){
	    loadFs >> available[i][j];
	  }
	}
	//Board
	for(int i=0; i<19; i++){
	  for(int j=0; j<19; j++){
	    loadFs >> chessBoard[i][j];
	  }
	}

	//Load log
    std::string log_string;
    getline(loadFs, log_string);while(loadFs && log_string == "")getline(loadFs, log_string);
	while(loadFs){
      gameLog << log_string << std::endl;
      getline(loadFs, log_string);while(loadFs && log_string == "")getline(loadFs, log_string);
    }
	loadFs.close();
  }

  while(round != 19){
    //棋局資訊
    std::cout << "第" << round << "手, ";
	if(term == 1) std::cout << "先手方下棋" << std::endl;
	else std::cout << "後手方下棋" << std::endl;
	
	std::cout << "  剩餘棋子：(\"[]\" = Type )" << std::endl;
	for(int i=0; i<8; i++){
	  std::cout << "[" << i << "]: " << available[term-1][i] << "   ";
	}

    std::cout << std::endl << std::endl << "Current chessboard:" << std::endl;
    display_board(chessBoard);
    //display_chessman(chessMan);

	//指令判別
	std::cout << "請輸入指令或是棋子型別：(輸入help來查詢指令)";
	while(std::cin >> input){

	  //幫助
	  if(input == "help"){
	    std::cout << "s : 存檔" << std::endl << "b ：回上一手" << std::endl << "ai : Call AI for next move." << std::endl;
	  }
      else if(input == "ai"){
		int aiResult[3];
		AI.ai_play(chessBoard, available, round, term, aiResult);
	    break;
	  }
      //存檔
	  else if(input == "s"){
	    std::cout << "should ask file name and copy log" << std::endl;
		//Get save name
		std::string save_file;
		std::cout << "請輸入存檔名稱： ";
		std::cin >> save_file;
		std::fstream saveFs;
		saveFs.open(save_file.c_str(), std::fstream::out | std::fstream::trunc);
		//Save information
		//Round
        saveFs << round;
		//Available
		for(int i=0; i<2; i++){
		  for(int j=0; j<8; j++){
		    saveFs << " " << available[i][j];
		  }
		}
		//Board
		for(int i=0; i<19; i++){
		  for(int j=0; j<19; j++){
		    saveFs << " " << chessBoard[i][j];
		  }
		}
		saveFs << std::endl;
		
		
		//Log
		gameLog.seekg(0);
		std::string log;
		getline(gameLog, log);while(gameLog && log == "")getline(gameLog, log);
		while(gameLog){
		  saveFs << log << std::endl;
  		  getline(gameLog, log);while(gameLog && log == "")getline(gameLog, log);
		}

	    gameLog.seekg(gameLog.beg);
		gameLog.seekp(0, gameLog.beg);

		std::cout << "Save complete." << std::endl;
		break;
	  }

	  //回上一手
      else if(input == "b"){
	    //Adjust stream pointer
		gameLog.seekg(gameLog.beg);

	    std::cout << "should generate new log(remove last line) and recover board" << std::endl;
        if(round == 1){
		  std::cout << "無上一手" << std::endl;
		  std::cout << "-------[ 指令無效 ]-------" << std::endl << std::endl;
		}
		else{
		  //Get last round information
		  std::string lastLine;
		  to_last_line(gameLog);
		  getline(gameLog, lastLine);

		  //Translate information
		  std::stringstream ss;
		  ss.str(lastLine);
		  int last_term, last_type, last_rotate, last_row, last_col;
		  ss >> last_term >> last_type >> last_rotate >> last_row >> last_col;
          std::cout << last_term << last_type << last_rotate << last_row << last_col << std::endl;
		  //Recover board
		  for(int i=0; i<4; i++){
		    for(int j=0; j<4; j++){
			  if(chessMan[(typeStart[last_type] + (last_rotate % rotateLimit[last_type]))][i][j] == 1){
			    if(((last_row+i) == 6) && ((last_col+j) == 6)){
				  chessBoard[last_row+i][last_col+j] = 3;
				}
			    else if(((last_row+i) == 6) && ((last_col+j) == 12)){
				  chessBoard[last_row+i][last_col+j] = 3;
				}
			    else if(((last_row+i) == 12) && ((last_col+j) == 6)){
				  chessBoard[last_row+i][last_col+j] = 3;
				}
			    else if(((last_row+i) == 12) && ((last_col+j) == 12)){
				  chessBoard[last_row+i][last_col+j] = 3;
				}
				else{
				  chessBoard[last_row+i][last_col+j] = 0;
				}
			  }
			}
		  }

          //Recover term
		  term = last_term;
 
          //Recover round
		  round -= 1;

		  //Recover available
		  available[last_term-1][last_type] += 1;

		  //Recover log
		  delete_last_line(gameLog);
		  gameLog.seekp(0, gameLog.end);
	      std::cout << "-------[ 回復上一手 ]-------" << std::endl << std::endl;
		}
		break;
	  }

	  //落子
	  else{
	    bool legalType = false;
        std::stringstream ss;
		ss.str(input);
		ss >> type;
		if(available[term-1][type] != 0) legalType = true;
		while(!legalType){
		  std::cout << "請輸入正確可用的棋子型別：";
		  std::cin >> type;
		  if(available[term-1][type] != 0) legalType = true;
		}
		std::cout << "已選擇型別" << type << std::endl << "請輸入右轉次數：";
		std::cin >> rotate;
		while(rotate > 3 || rotate < 0){
		  std::cout << "請輸入0-3的右轉次數：";
		  std::cin >> rotate;
		}
		std::cout << "已選擇型別" << type << ", 右轉次數" << rotate << std::endl;
		std::cout << "請輸入row：";
		std::cin >> row;
		std::cout << "請輸入col：";
		std::cin >> col;
	    //Adjust position.
		row += 3; col += 3;
		//檢查合法位置
		bool legalPos = false;
		legalPos = check_chessman(chessBoard, chessMan, typeStart, rotateLimit, type, rotate, row, col, term);
		
		while(!legalPos){
		  std::cout << "無法在該位置下子,請輸入row：";
		  std::cin >> row;
		  std::cout << "請輸入col：";
		  std::cin >> col;
		  //Adjust position.
		  row += 3; col += 3;
		  //檢查合法位置
  		  legalPos = check_chessman(chessBoard, chessMan, typeStart, rotateLimit, type, rotate, row, col, term);
		}
		std::cout << "合法位置" << std::endl;
		//更新board
		for(int i=0; i<4; i++){
		  for(int j=0; j<4; j++){
		    if(chessMan[(typeStart[type] + (rotate % rotateLimit[type]))][i][j] == 1){
			  chessBoard[row+i][col+j] = term;
			}
		  }
		}
		//更新available
		available[term-1][type]--;
		//更新log
        gameLog << term << " " << type << " " << rotate << " " << row << " " << col << std::endl;
	    std::cout << "----------[ 回合結束 ]----------" << std::endl << std::endl;
		if(term == 1) term = 2;
		else term = 1;
	    round++;
		break;
	  }

	}
  }
  int result;
  display_board(chessBoard);
  result = game_judge(chessBoard);
  switch(result){
    case 0:
	  std::cout << "平手" << std::endl;
	  break;
    case 1:
	  std::cout << "先手方勝利" << std::endl;
	  break;
	case 2:
	  std::cout << "後手方勝利" << std::endl;
	  break;
  }
  std::cout << "遊戲結束" << std::endl; 
  gameLog.close();
}

int main(){
  game_main();
  //std::cout << "Welcome." << std::endl;
}

 

