#pragma once

#include "ai/dna.h"
#include "reversi.h"

class AI : public DNA {
private:
	int play_color;
public:
	float evaluation(Reversi& r, int deep=1);
	void put_stone(Reversi& r);
	AI birth(const AI& father);
	void set_black() { play_color = BLACK; };
	void set_white() { play_color = WHITE; };
};
