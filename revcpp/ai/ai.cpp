#include <iostream>
#include <vector>

#include "../defines.h"
#include "../ai.h"
#include "random.h"

#define MOTHER_PRIORITY 0.6

using myrand::roulette;

float AI::evaluation(Reversi& r, int deep) {
	float value, best1, best2;

	if (play_color == BLACK) {
		best1 = 100000.0;
	} else if (play_color == WHITE) {
		best1 = -100000.0;
	} else {
		std::cout << "AI's turn is not set." << std::endl;
		return 0;
	}

	if ( !r.is_game_continue() ) {
		int score = r.get_score();
		if ( score > 0 ) return 100000.0;
		if ( score < 0 ) return -100000.0;
		return 0.0;
	}

	if ( deep == 1 ) return evaluate(r.get_inputs());

	for ( int y1=0; y1<REVERSI_SIZE; y1++ ) {
		for ( int x1=0; x1<REVERSI_SIZE; x1++ ) {
			if ( !r.is_puttable(x1, y1) ) continue;
			Reversi rc = r.clone();
			rc.put_stone(x1, y1);

			if ( !rc.is_game_continue() ) {
				int score = rc.get_score();
				if ( score > 0 ) best2 = 100000.0;
				if ( score < 0 ) best2 = -100000.0;
				if ( score == 0 ) best2 = 0;
			} else {
				if (play_color == BLACK) best2 = -100000.0;
				else best2 = 100000.0;
				for ( int y2=0; y2<REVERSI_SIZE; y2++ ) {
					for ( int x2=0; x2<REVERSI_SIZE; x2++ ) {
						if ( !rc.is_puttable(x2, y2) ) continue;
						Reversi rcc = rc.clone();
						rcc.put_stone(x2, y2);

						value = evaluation(rcc, deep-2);
						if ( play_color == BLACK ) {
							if ( value < best2 ) continue;
							best2 = value;
						} else if ( play_color == WHITE ) {
							if ( value > best2 ) continue;
							best2 = value;
						}
					}
				}
			}

			if ( play_color == BLACK ) {
				if ( best2 > best1 ) continue;
				best1 = best2;
			} else if ( play_color == WHITE ) {
				if ( best2 < best1 ) continue;
				best1 = best2;
			}
		}
	}

	return best1;
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
