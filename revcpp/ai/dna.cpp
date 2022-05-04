#include <iostream>

#include "dna.h"
#include "random.h"

using std::array;
using myrand::rand_f;
using myrand::roulette;

DNA::DNA() {
	for ( auto& arr : i_to_m ) {
		for ( auto& a : arr ) a = rand_f();
	}
	for ( auto& a : m_to_o ) a = rand_f();
	reward = 0; gen = 0;
}

float DNA::evaluate(const array<float, PARAMETERS> inputs) {
	float result = 0.0;
	float tmp;

	for ( int i=0; i<PARAMETERS; i++ ) {
		tmp = 0.0;
		for ( int j=0; j<PARAMETERS; j++ ) {
			tmp += i_to_m[i][j] * inputs[j];
		}
		result += ReLU(tmp) * m_to_o[i];
	}
	return result;
}

void DNA::mutate() {
	for ( auto& arr : i_to_m ) {
		for ( auto& a : arr ) {
			if (roulette(MUTATION_RATE)) a = rand_f();
		}
	}
	for ( auto& a : m_to_o ) {
		if (roulette(MUTATION_RATE)) a = rand_f();
	}
}

void DNA::print() {
	std::cout << "i_to_m:" << std::endl;
	for ( auto& arr : i_to_m ) {
		for ( auto& a : arr ) std::cout << " " << a;
		std::cout << std::endl;
	}

	std::cout << "m_to_o:" << std::endl;
	for ( auto& a : m_to_o ) std::cout << " " << a;
	std::cout << std::endl;

	std::cout << "reward: " << reward << std::endl;
}

void DNA::read(std::ifstream& read_file) {
	for ( auto& arr : i_to_m ) {
		for ( auto& a : arr ) read_file >> a;
	}
	for ( auto& ar : m_to_o ) read_file >> ar;
}

void DNA::write(std::ofstream& write_file) {
	for ( auto& arr : i_to_m ) {
		for ( auto& a : arr ) write_file << a << " ";
		write_file << std::endl;
	}
	for ( auto& a : m_to_o ) write_file << a << " ";
	write_file << std::endl;
}
