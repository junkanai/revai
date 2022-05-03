#pragma once

#include <array>

#include "../defines.h"

#define REVERSI_SIZE 6
#define REVERSI_MAX 36
#define EMPTY 0
#define BLACK 1
#define WHITE 128

class Reversi {
private:
	std::array<std::array<int, REVERSI_SIZE>, REVERSI_SIZE> board = {};
	int turn, oppTurn;

	void update();
	bool is_nextPlayer_puttable();
public:
	Reversi();
	std::array<float, PARAMETERS> get_inputs();
	bool is_puttable(int n);
	void put_stone(int n);
	int get_score();
	Reversi clone();
	bool is_turn_white() { return ( turn == WHITE ); };
	bool is_turn_black() { return ( turn == BLACK ); };
	bool is_game_continue() { return ( turn != EMPTY ); };
	void print();
};
