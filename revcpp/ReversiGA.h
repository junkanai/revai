#pragma once

#include <array>
#include <string>

#include "defines.h"
#include "ai/ai.h"

class ReversiGA {
private:
	std::array<AI, POPULATION> ais;
public:
	ReversiGA();
	void read(std::string read_file);
	void start(int gen_max);
	void write(std::string write_file);
};
