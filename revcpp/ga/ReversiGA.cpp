#include <iostream>
#include <algorithm>

#include "../ReversiGA.h"
#include "../reversi.h"
#include "../ai/random.h"

using std::array;
using std::string;
using std::cout;
using std::endl;

bool cmp(const AI& ai1, const AI& ai2) { return ai1.reward > ai2.reward; }

ReversiGA::ReversiGA() {
	myrand::rand_init();
}

void ReversiGA::play_reversi(AI& ai1, AI& ai2) {
	Reversi r;
	int score;
	ai1.set_black();
	ai2.set_white();

	while ( r.is_game_continue() ) {
		ai1.put_stone(r);
		ai2.put_stone(r);
	}

	score = r.get_score();
	ai1.reward += score;
	ai2.reward -= score;
}

void ReversiGA::one_generation(const int gen) {
	// Quarlifying Round
	for ( auto& ai : ais ) ai.reward = 0;
	for ( int a=0; a<POPULATION; a++ ) {
		for ( int b=0; b<POPULATION; b++ ) {
			if ( a == b ) continue;
			play_reversi(ais[a], ais[b]);
		}
	}
	std::sort(ais.begin(), ais.end(), cmp);

	// Final Round
	for ( int i=0; i<FINALISTS; i++ ) ais[i].reward = FINALISTS-i;
	for ( int a=0; a<FINALISTS; a++ ) {
		for ( int b=0; b<FINALISTS; b++ ) {
			if ( a == b ) continue;
			play_reversi(ais[a], ais[b]);
		}
	}
	std::sort(ais.begin(), ais.begin()+FINALISTS, cmp);

	// output
	for ( auto& ai : ais ) cout << " " << ai.reward;
	cout << endl << "No.1's Gen : " << ais[0].gen << endl;

	// selection
	int child = ELITE;
	AI selected_ais[6] = {ais[12], ais[16], ais[20], ais[24], ais[28], ais[32]};

	// crossover SUPER_ELITE x ELITE
	for ( int mother=0; mother<SUPER_ELITE; mother++ ) {
		for ( int father=mother+1; father<ELITE; father++ ) {
			ais[child++] = ais[mother].birth(ais[father]);
			if ( child == POPULATION ) { cout << "Unexpected Crossover 1 " << endl; return; }
		}
	}
	// crossover ELITE x selected_ais
	for ( int mother=0; mother<ELITE; mother++ ) {
		for ( auto& father : selected_ais ) ais[child++] = ais[mother].birth(father);
		if ( child == POPULATION ) { cout << "Unexpected Crossover 2 " << endl; return; }
	}

	// add 3 random players
	AI random_ais[3];
	for ( int i=0; i<3; i++ ) { ais[POPULATION-3+i] = random_ais[i]; }

	// mutation
	for ( int i=ELITE; i<POPULATION; i++ ) { ais[i].mutate(); }

	// update gen
	for ( auto& ai : ais ) { if ( ai.gen == 0 ) ai.gen = gen+1; }
}


void ReversiGA::read(std::ifstream& read_file) {
	for ( auto& ai : ais ) ai.read(read_file);
}

void ReversiGA::write(std::ofstream& write_file) {
	for ( auto& ai : ais ) ai.write(write_file);
}