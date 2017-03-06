#ifndef AI_H
#define AI_H
#include<iostream>
#include<list>
struct node{
	int redWin;
	int greenWin;
	int total;
	int board[19][19];
	node* parent;
	std::list<node*> children;
};
class ai{
  public:
    //Constructor: Initialize game information.
    ai();

	//Update available chessman information.
	void ai_available(int (&curAvailable)[2][8]);
	//void ai_available(int &(curAvailable)[2][8]);

	//AI connection check.
	void ai_greeting();

	//AI MCTS
	//void ai_play(int &(curBoard)[19][19], int &(aiResult)[3]);

	//UCT select
	//node* uct();

	//Expand all possible move.
	void feasible_way(int (&curBoard)[19][19],
	                  int (&curAvailable)[2][8],
					  node &root,
					  int term);

	//Update board with a legal move.
	void update_board(int (&curBoard)[19][19],
	                  int (&newBoard)[19][19],
	                  int chessIndex,
					  int row,
					  int col,
					  int term);

	//Initialize new feasible move.
	void initialize_node(node* feasMove);

	//Check legal move.
	bool check_chessman(int (&curBoard)[19][19],
	                    int chessIndex,
						int row,
						int col,
						int term); 

  private:
	int chessBoard[19][19];
	int chessMan[20][4][4];
	int typeStart[8];
	int rotateLimit[8];
	int available[2][8];
	
};
#endif
