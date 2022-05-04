#pragma once

#include <iostream>
#include <ctime>
#include <stdlib.h>

namespace myrand {

	inline void rand_init() {
		srand(time(NULL));
	}

	// return -1 <= x < 1
	inline float rand_f() {
		return ((float)rand()/(RAND_MAX/2)-1);
	}

	inline bool roulette(float rate) {
		return ( ((float)rand() / RAND_MAX) < rate);
	}

}
