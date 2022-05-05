#pragma once

#include <array>

#include "defines.h"

#define REVERSI_SIZE 6
#define REVERSI_MAX 36
#define EMPTY 0
#define BLACK 1
#define WHITE 128

class Reversi {
private:
	std::array<std::array<int, REVERSI_SIZE>, REVERSI_SIZE> board = {};
	int turn, oppTurn;

	void update_turn();
	bool is_nextPlayer_puttable() const;
public:
	Reversi();
	std::array<int, PARAMETERS> get_inputs() const;
	bool is_puttable(int x, int y) const;
	void put_stone(int x, int y);
	int get_score() const;
	Reversi clone() const;
	bool is_turn_white() const { return ( turn == WHITE ); };
	bool is_turn_black() const { return ( turn == BLACK ); };
	bool is_turn(int color) const { return ( turn == color ); };
	bool can_continue() const { return ( turn != EMPTY ); };
	bool is_end() const { return ( turn == EMPTY ); };
	void print() const;
};
