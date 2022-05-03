#include <fstream>

#include "ReversiGA.h"

using std::array;
using std::string;

ReversiGA::ReversiGA() {
	//std::array<AI, POPULATION> ais;
}

void ReversiGA::start(int gen_max) {
}

void ReversiGA::read(string read_file_name) {
	return;
	std::ifstream read_file;
	read_file.open(read_file_name, std::ios::in);
	for ( auto& ai : ais ) ai.read(read_file);
	read_file.close();
}

void ReversiGA::write(string write_file_name) {
	return;
	std::ofstream write_file;
	write_file.open(write_file_name, std::ios::out);
	for ( auto& ai : ais ) ai.write(write_file);
	write_file.close();
}
