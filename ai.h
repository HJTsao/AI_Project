#ifndef AI_H
#define AI_H
#include<iostream>
#include<list>
struct coordinate{
  int row;
  int col;
};

struct tableElement;

struct node{
  int redWin;
  int greenWin;
  int total;
  int round;
  int board[19][19];
  int available[2][8];
  
  //From what action
  int type;
  int rotate;
  int row;
  int col;

  node* parent;
  tableElement* element; 
  std::list<node*> children;
};

struct tableElement{
  int redWin;
  int greenWin;
  int total;
  node* link;
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
	void ai_play(int (&curBoard)[19][19],
	             int (&curAvailable)[2][8],
				 int round,
				 int term,
				 int (&aiResult)[3]);

	//UCT select
	node* uct(std::list<tableElement> &nodeTable,
	          int term,
			  int iteration);

	//Expand all possible move.
	void feasible_way(node* root,
					  int term,
					  std::list<tableElement> &nodeTable);

	//Simulate
	void simulate_node(node* start);

	//Update board with a legal move.
	void update_board(int (&curBoard)[19][19],
	                  int (&newBoard)[19][19],
	                  int chessIndex,
					  int row,
					  int col,
					  int term);

	//Initialize new feasible move.
	inline void initialize_node(node* feasMove,
	                            node* parent,
								std::list<tableElement>& nodeTable,
	                            int (&curBoard)[19][19],
								int (&curAvailable)[2][8],
	                            int round,
								int type,
								int rotate,
								int row,
								int col);

    //Initialize or update a state with a exist node.
    /*inline void initialize_element(tableElement* curElement,
	                               node* curNode);*/

	//Check legal move.
	bool check_chessman(int (&curBoard)[19][19],
	                    int chessIndex,
						int row,
						int col,
						int term); 

	//Judge game result.
    int judge(int (&chessBoard)[19][19]);	

  private:
	int chessBoard[19][19];
	int chessMan[20][4][4];
	int typeStart[8];
	int rotateLimit[8];
	int available[2][8];
	
};
#endif
