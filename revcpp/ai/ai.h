#pragma once

#include "dna.h"
#include "reversi.h"

class AI : public DNA {
private:
	int play_color;
public:
	float evaluation(Reversi& r, int deep=1);
	void put_stone(Reversi& r);
	AI birth(const AI& father);
	float gameEndEvaluate(int score) const {
		if ( score > 0 ) return score*10000.0;
		if ( score < 0 ) return -score*10000.0;
		return 0.0;
	};
	void set_black() { play_color = BLACK; };
	void set_white() { play_color = WHITE; };
};
