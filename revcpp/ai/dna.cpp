#include <iostream>

#include "dna.h"

using std::array;

DNA::DNA() {
	for ( auto& arr : i_to_m ) {
		for ( auto& a : arr ) a = 0.9;
	}
	for ( auto& a : m_to_o ) a = 0.9;
	reward = 0; gen = 0;
}

float DNA::evaluate(array<float, PARAMETERS> inputs) {
	return 3.14;
}

void DNA::mutate() {
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
