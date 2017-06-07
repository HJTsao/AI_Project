#ifndef AI_H
#define AI_H
#include <iostream>
#include <list>
#include <stdint.h>
typedef int8_t int8;
struct coordinate{
  int8 row;
  int8 col;
};


struct matchResult{
  int8 winner;
  int8 score;
};

struct node{
  int redWin;
  int greenWin;
  int total;
  int8 round;
  int8 board[19][19];
  int8 available[2][8];
  double redScore;
  double greenScore;


  //From what action
  int8 type;
  int8 rotate;
  int8 row;
  int8 col;

  node* parent;
  std::list<node*> children;
};

class ai{
  public:
    //Constructor: Initialize game information.
    ai();

	//Update available chessman information.
	void ai_available(int8 (&curAvailable)[2][8]);
	//void ai_available(int &(curAvailable)[2][8]);

	//AI connection check.
	void ai_greeting();

	//AI MCTS
	void ai_play(int8 (&curBoard)[19][19],
	             int8 (&curAvailable)[2][8],
				 int8 round,
				 int8 term,
				 int (&aiResult)[3],
                 bool debug = false);
    node* select(node* root,
	             int8 term,
				 int iteration);
	double uct_value(node* curNode,
	                 int iteration);
	//UCT select
	/*node* uct(std::list<tableElement> &nodeTable,
	          int term,
			  int iteration);*/

	//Expand all possible move.
	void feasible_way(node* root, bool debug = false);

	//Simulate
	void simulate_node(node* start);

	//Update board with a legal move.
	void update_board(int8 (&curBoard)[19][19],
	                  int8 (&newBoard)[19][19],
	                  int8 chessIndex,
					  int8 row,
					  int8 col,
					  int8 term);

	//Initialize new feasible move.
	inline void initialize_node(node* feasMove,
	                            node* parent,
	                            int8 (&curBoard)[19][19],
								int8 (&curAvailable)[2][8],
	                            int8 round,
								int8 type,
								int8 rotate,
								int8 row,
								int8 col);
    void debug_board(int8 (&chessBoard)[19][19]);
    //Initialize or update a state with a exist node.
    /*inline void initialize_element(tableElement* curElement,
	                               node* curNode);*/

	//Check legal move.
	bool check_chessman(int8 (&curBoard)[19][19],
	                    int8 chessIndex,
						int8 row,
						int8 col,
						int8 term);

	//Judge game result.
    matchResult judge(int8 (&chessBoard)[19][19]);

	//Delete all node
	void ai_clean(node* root);

	//Analyze current board
	void ai_analyze(node* root, int8 term);
  private:
	int8 chessBoard[19][19];
	int8 chessMan[20][4][4];
	int8 typeStart[8];
	int8 rotateLimit[8];
	int8 available[2][8];
	int8 openingPattern; // 0->top two; 1->bottom two; 2->left two; 3->right two 4->/; 5->\ //
	bool openingComplete;



};
#endif
