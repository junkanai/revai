import copy

from .settings import *

class Reversi:
    def __init__(self):
        self.turn = BLACK
        self.oppTurn = WHITE
        self.board = [[0, 0,  0,  0, 0, 0],
                      [0, 0,  0,  0, 0, 0],
                      [0, 0,128,  1, 0, 0],
                      [0, 0,  1,128, 0, 0],
                      [0, 0,  0,  0, 0, 0],
                      [0, 0,  0,  0, 0, 0]]
        self.blacks = 2
        self.whites = 2

    def is_puttable(self, n):
        y = n // REVERSI_SIZE
        x = n % REVERSI_SIZE
        if self.board[y][x] != EMPTY: return False

        tmpboard = copy.deepcopy(self.board)
        for (dx, dy) in [(-1,-1), (-1,0), (-1,1), (0,-1), (0,1), (1,-1), (1,0), (1,1)]:
            sx = x; sy = y; reverseCount = 0
            while True:
                sx += dx; sy += dy
                if sx < 0 or REVERSI_SIZE <= sx: break
                if sy < 0 or REVERSI_SIZE <= sy: break
                if tmpboard[sy][sx] == EMPTY: break
                if tmpboard[sy][sx] == self.oppTurn:
                    reverseCount += 1; continue
                if tmpboard[sy][sx] == self.turn and reverseCount > 0: return True
                break

        return False

    def put_stone(self, n):
        y = n // REVERSI_SIZE
        x = n % REVERSI_SIZE
        self.board[y][x] = self.turn
        for (dx, dy) in [(-1,-1), (-1,0), (-1,1), (0,-1), (0,1), (1,-1), (1,0), (1,1)]:
            sx = x; sy = y; reverseCount = 0
            while True:
                sx += dx; sy += dy
                if sx < 0 or REVERSI_SIZE <= sx: break
                if sy < 0 or REVERSI_SIZE <= sy: break
                if self.board[sy][sx] == EMPTY: break
                if self.board[sy][sx] == self.oppTurn:
                    reverseCount += 1; continue
                if self.board[sy][sx] == self.turn:
                    if reverseCount == 0: break
                    for i in range(reverseCount):
                        sx -= dx; sy -= dy
                        self.board[sy][sx] = self.turn
                    break
        self._update()

    def _update(self):
        self.whites = sum(map(sum, self.board)) // WHITE
        self.blacks = sum(map(sum, self.board)) % WHITE

        self.turn = self.oppTurn
        self.oppTurn = WHITE // self.turn
        if self.is_nextPlayer_puttable(): return

        self.turn = self.oppTurn
        self.oppTurn = WHITE // self.turn
        if self.is_nextPlayer_puttable(): return

        # the game has finished
        self.turn = EMPTY

    def is_nextPlayer_puttable(self):
        for n in range(REVERSI_MAX):
            if self.is_puttable(n):
                return True
        return False
