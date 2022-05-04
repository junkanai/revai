#pragma once

#include <fstream>
#include <array>

#include "../defines.h"
#include "../reversi.h"

class DNA {
private:
	float ReLU(float x) { return ((x > 0) ? x : 0); }
protected:
	std::array<std::array<float, PARAMETERS>, PARAMETERS> i_to_m;
	std::array<float, PARAMETERS> m_to_o;
public:
	int reward;
	int gen;
	DNA();
	float evaluate(const std::array<float, PARAMETERS> inputs);
	void mutate();
	void print();
	void read(std::ifstream& read_file);
	void write(std::ofstream& write_file);
};
