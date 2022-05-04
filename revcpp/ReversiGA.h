#pragma once

#include <string>
#include <array>
#include <fstream>

#include "ai.h"

class ReversiGA {
private:
	std::array<AI, POPULATION> ais;
public:
	ReversiGA();
	void play_reversi(AI& ai1, AI& ai2);
	void one_generation(const int gen);
	void read(std::ifstream& read_file);
	void write(std::ofstream& write_file);
};
