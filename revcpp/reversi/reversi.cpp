#include <iostream>

#include "reversi.h"

#define b(y, x) board[y][x]
#define by(y) b(y,0)+b(y,1)+b(y,2)+b(y,3)+b(y,4)+b(y,5)

using std::array;
using std::cout;
using std::endl;

Reversi::Reversi() {
	constexpr int NORTHWEST = REVERSI_SIZE/2-1;
	constexpr int SOUTHEAST = REVERSI_SIZE/2;
	board[NORTHWEST][NORTHWEST] = WHITE;
	board[NORTHWEST][SOUTHEAST] = BLACK;
	board[SOUTHEAST][NORTHWEST] = BLACK;
	board[SOUTHEAST][SOUTHEAST] = WHITE;
	turn = BLACK;
	oppTurn = WHITE;
}

array<float, PARAMETERS> Reversi::get_inputs() {
	array<float, PARAMETERS> rtn = {};
	array<int, 6> arr = {};

	// 中心2x2
	arr[0] = b(2,2)+b(2,3)+b(3,2)+b(3,3);
	// 4x4の角
	arr[1] = b(1,1)+b(1,4)+b(4,1)+b(4,4);
	// 角
	arr[2] = b(0,0)+b(0,5)+b(5,0)+b(5,5);
	// 角横
	arr[3] = b(0,1)+b(0,4)+b(1,0)+b(1,5)+b(4,0)+b(4,5)+b(5,1)+b(5,4);
	// 角横の横
	arr[4] = b(0,2)+b(0,3)+b(2,0)+b(2,5)+b(3,0)+b(3,5)+b(5,2)+b(5,3);
	// 全部
	arr[5] = by(0)+by(1)+by(2)+by(3)+by(4)+by(5);
	
	// arr[n]%WHITE は黒の数, arr[n]/WHITEは白の数
	rtn[0] = arr[0]%WHITE - arr[0]/WHITE;

	rtn[1] = arr[1]%WHITE;
	rtn[2] = arr[1]/WHITE;
	rtn[3] = arr[1]%WHITE - arr[1]/WHITE;

	rtn[4] = arr[2]%WHITE;
	rtn[5] = arr[2]/WHITE;
	rtn[6] = arr[2]%WHITE - arr[2]/WHITE;

	rtn[7] = arr[3]%WHITE;
	rtn[8] = arr[3]/WHITE;
	rtn[9] = arr[3]%WHITE - arr[3]/WHITE;

	rtn[10] = arr[4]%WHITE;
	rtn[11] = arr[4]/WHITE;
	rtn[12] = arr[4]%WHITE - arr[4]/WHITE;

	rtn[13] = arr[5]%WHITE;
	rtn[14] = arr[5]/WHITE;
	rtn[15] = arr[5]%WHITE - arr[5]/WHITE;
	rtn[16] = arr[5]%WHITE + arr[5]/WHITE;

	return rtn;
}

bool Reversi::is_puttable(int n) {
	int y = n / REVERSI_SIZE;
	int x = n % REVERSI_SIZE;

	if (board[y][x] != EMPTY) return false;

	int dx, dy, sx, sy, reverseCount;
	auto tmpboard = board;

	tmpboard[y][x] = turn;
	for ( dx=-1; dx<2; dx++ ) {
		for ( dy=-1; dy<2; dy++ ) {
			sx = x; sy = y; reverseCount = 0;
			while(true) {
				sx += dx; sy += dy;
				if ( sx < 0 or REVERSI_SIZE <= sx ) break;
				if ( sy < 0 or REVERSI_SIZE <= sy ) break;
				if (tmpboard[sy][sx] == EMPTY) break;
				if (tmpboard[sy][sx] == oppTurn) { reverseCount++; continue; }
				if (tmpboard[sy][sx] == turn and reverseCount > 0) return true;
				break;
			}
		}
	}
	return false;
}

void Reversi::put_stone(int n) {
	int y = n / REVERSI_SIZE;
	int x = n % REVERSI_SIZE;
	int dx, dy, sx, sy, i, reverseCount;
	board[y][x] = turn;
	for ( dx=-1; dx<2; dx++ ) {
		for ( dy=-1; dy<2; dy++ ) {
			sx = x; sy = y; reverseCount = 0;
			while(true) {
				sx += dx; sy += dy;
				if ( sx < 0 or REVERSI_SIZE <= sx ) break;
				if ( sy < 0 or REVERSI_SIZE <= sy ) break;
				if (board[sy][sx] == EMPTY) break;
				if (board[sy][sx] == oppTurn) { ++reverseCount; continue; }
				if (board[sy][sx] == turn) {
					if (reverseCount == 0) break;
					for ( i=0; i<reverseCount; i++ ) {
						sx -= dx; sy -= dy;
						board[sy][sx] = turn;
					}
					break;
				}
			}
		}
	}
	update();
}

void Reversi::update() {
	turn = oppTurn; oppTurn = WHITE / turn;
	if (is_nextPlayer_puttable()) return;

	// next player can't put
	turn = oppTurn; oppTurn = WHITE / turn;
	if (is_nextPlayer_puttable()) return;

	// the game has end when the program comes here
	turn = 0; oppTurn = 0; return;
}

bool Reversi::is_nextPlayer_puttable() {
	for ( int n=0; n<REVERSI_MAX; n++ ) {
		if ( is_puttable(n) ) return true;
	}
	return false;
}

int Reversi::get_score() {
	int s = 0;
	for ( auto& boa : board ) {
		for ( auto& b : boa ) s += b;
	}
	int whites = s / WHITE;
	int blacks = s % WHITE;
	int empties = REVERSI_MAX - (whites + blacks);
	
	if (blacks == whites) return 0;
	if (blacks > whites) return (blacks-whites+empties);
	return (blacks-whites-empties);
}

Reversi Reversi::clone() {
	Reversi r;
	r.board = board;
	r.turn = turn;
	r.oppTurn = oppTurn;
	return r;
}

void Reversi::print() {
	for ( auto& boa : board ) {
		for ( auto& b : boa ) {
			printf(" %3d,", b);
		}
		cout << endl;
	}
	cout << "Turn : " << turn << endl;
	cout << "======================" << endl;
}
