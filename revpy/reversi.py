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

    def get_inputs(self):
        arr = [0, 0, 0, 0, 0, 0]
        rtn = [0 for _ in range(PARAMETERS)]

        arr[0] = self.board[2][2] + self.board[2][3] + self.board[3][2] + self.board[3][3]
        arr[1] = self.board[1][1] + self.board[1][4] + self.board[4][1] + self.board[4][4]
        arr[2] = self.board[0][0] + self.board[0][5] + self.board[5][0] + self.board[5][5]
        arr[3] = self.board[0][1] + self.board[0][4] + self.board[1][0] + self.board[1][5] + \
                self.board[4][0] + self.board[4][5] + self.board[5][1] + self.board[5][4]
        arr[4] = self.board[0][2] + self.board[0][3] + self.board[2][0] + self.board[2][5] + \
                self.board[3][0] + self.board[3][5] + self.board[5][2] + self.board[5][3]
        arr[5] = sum(map(sum,self.board))

        rtn[0] = arr[0]%WHITE - arr[0]//WHITE

        rtn[1] = arr[1]%WHITE
        rtn[2] = arr[1]//WHITE
        rtn[3] = rtn[1] - rtn[2]

        rtn[4] = arr[2]%WHITE
        rtn[5] = arr[2]//WHITE
        rtn[6] = rtn[4] - rtn[5]

        rtn[7] = arr[3]%WHITE
        rtn[8] = arr[3]//WHITE
        rtn[9] = rtn[7] - rtn[8]

        rtn[10] = arr[4]%WHITE
        rtn[11] = arr[4]//WHITE
        rtn[12] = rtn[10] - rtn[11]

        rtn[13] = arr[5]%WHITE
        rtn[14] = arr[5]//WHITE
        rtn[15] = rtn[13] - rtn[14]
        rtn[16] = rtn[13] - rtn[14]

        return rtn

    def clone(self):
        r = Reversi()
        r.board = copy.deepcopy(self.board)
        r.turn = self.turn
        r.oppTurn = self.oppTurn
        r.blacks = self.blacks
        r.whites = self.whites
        return r
