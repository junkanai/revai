#include "ai.h"

AI AI::birth(AI& father) {
	AI child;
	for ( int i=0; i<PARAMETERS; i++ ) {
		for ( int j=0; j<PARAMETERS; j++ ) {
			//if ( roulette(0.6) ) child.i_to_m[i][j] = i_to_m[i][j];
			//else child.i_to_m[i][j] = father.i_to_m[i][j];
		}
		//if ( roulette(0.6) ) child.m_to_o[i] = m_to_o[i];
		//else child.m_to_o[i] = father.m_to_o[i];
	}
	return child;
}
