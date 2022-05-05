// main file to improve AI
#include <iostream>
#include <fstream>

#include "revcpp/revcpp.h"

#define GEN_MAX 10
#define READ_FILE "data/data5.txt"
#define WRITE_FILE "data/data5.txt"

#define NC "\e[0m"
#define MAG "\e[0;35m"

int main() {
	ReversiGA rga;

	std::ifstream read_file;
	read_file.open(READ_FILE, std::ios::in);
	rga.read(read_file);
	read_file.close();

	{
		StopWatch stopwatch;

		for ( int gen=1; gen<=GEN_MAX; gen++ ) {
			std::cout << MAG "Gen : " << gen << NC << std::endl;
			rga.one_generation(gen);
			stopwatch.lap();
		}
	}

	std::ofstream write_file;
	write_file.open(WRITE_FILE, std::ios::out);
	rga.write(write_file);
	write_file.close();
}
