#include <iostream>
#include <vector>

#include "../defines.h"
#include "../ai.h"
#include "random.h"

#define MOTHER_PRIORITY 0.6

using myrand::roulette;

float AI::evaluation(Reversi& r, int deep) {
	if ( deep == 1 ) {
		return evaluate(r.get_inputs());
	} else {
		float value;
	}
	return 3.14;
}

void AI::put_stone(Reversi& r) {
	if ( !r.is_turn(play_color) ) return;
	int px = 0; int py = 0;
	float best = 0;
	float value;

	if (play_color == BLACK) best = -1000000.0;
	if (play_color == WHITE) best = 1000000.0;

	for ( int y=0; y<REVERSI_SIZE; y++ ) {
		for ( int x=0; x<REVERSI_SIZE; x++ ) {
			if ( !r.is_puttable(x, y) ) continue;
			Reversi rc = r.clone();
			rc.put_stone(x, y);
			value = evaluation(rc, DEEP);
			if ( play_color == BLACK ) {
				if ( value < best ) continue;
				best = value; px = x; py = y;
			} else if ( play_color ==  WHITE ) {
				if ( value > best ) continue;
				best = value; px = x; py = y;
			} else {
				std::cout << "AI's turn is not set." << std::endl;
				return;
			}
		}
	}

	r.put_stone(px, py);
}

AI AI::birth(const AI& father) {
	AI child;
	for ( int i=0; i<PARAMETERS; i++ ) {
		for ( int j=0; j<PARAMETERS; j++ ) {
			if ( roulette(MOTHER_PRIORITY) ) {
				child.i_to_m[i][j] = i_to_m[i][j];
			} else {
				child.i_to_m[i][j] = father.i_to_m[i][j];
			}
		}
		if ( roulette(MOTHER_PRIORITY) ) {
			child.m_to_o[i] = m_to_o[i];
		} else {
			child.m_to_o[i] = father.m_to_o[i];
		}
	}
	return child;
}
