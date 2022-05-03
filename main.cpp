// main file to improve AI
#include <iostream>

#include "revcpp/ReversiGA.h"

#define GEN_MAX 800
#define READ_FILE "data/data1.txt"
#define WRITE_FILE "data/data1.txt"

int main() {
	ReversiGA rga;

	//rga.read(READ_FILE);

	rga.start(GEN_MAX);

	//rga.write(WRITE_FILE);
}
