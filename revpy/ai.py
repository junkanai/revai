from .settings import *

def ReLU(x):
    return x if x > 0 else 0

class AI:
    def __init__(self, datafile):
        self.dna = []
        self.play_color = EMPTY
        with open(datafile, "r") as f:
            for i in range(PARAMETERS+1):
                s = f.readlines(1)
                sl = s[0].split(" ")
                sarray = []
                for j in range(PARAMETERS):
                    sarray.append(float(sl[j]))
                self.dna.append(sarray)

    def put_stone(self, r):
        if r.turn != self.play_color: return
        pn = 0
        best = 0; value = 0

        if self.play_color == BLACK: best = -100000
        if self.play_color == WHITE: best = 100000

        for n in range(REVERSI_MAX):
            if not r.is_puttable(n): continue
            rc = r.clone()
            rc.put_stone(n)
            value = self.evaluation(rc, DEEP)
            if self.play_color == BLACK:
                if value < best: continue
                best = value; pn = n
            elif self.play_color == WHITE:
                if value > best: continue
                best = value; pn = n
            else:
                print("AI's turn is not set")
                return

        r.put_stone(pn)


    def evaluation(self, r, deep):
        best1 = 0
        best2 = 0
        if self.play_color == BLACK: best1 = 100000
        elif self.play_color == WHITE: best1 = -100000
        else:
            print("AI's turn is not set")
            return

        if not r.is_game_continue():
            if r.blacks > r.whites: return 100000
            if r.blacks < r.whites: return -100000
            return 0

        if deep == 1: return self.evaluate(r.get_inputs())

        for n1 in range(REVERSI_MAX):
            if not r.is_puttable(n1): continue
            rc = r.clone()
            rc.put_stone(n1)

            if not rc.is_game_continue():
                if rc.blacks > rc.whites: best2 = 100000
                if rc.blacks < rc.whites: best2 = -100000
                if rc.blacks == rc.whites: best2 = 0
            else:
                if self.play_color == BLACK: best2 = -100000
                else: best2 = 100000
                for n2 in range(REVERSI_MAX):
                    if not rc.is_puttable(n2): continue
                    rcc = rc.clone()
                    rcc.put_stone(n2)

                    value = self.evaluation(rcc, deep-1)
                    if self.play_color == BLACK:
                        if value < best2: continue
                        best2 = value
                    else:
                        if value > best2: continue
                        best2 = value

            if self.play_color == BLACK:
                if best2 > best1: continue
                best1 = best2
            else:
                if best2 < best1: continue
                best1 = best2

        return best1

    def evaluate(self, inputs):
        result = 0
        for i in range(PARAMETERS):
            tmp = 0
            for j in range(PARAMETERS):
                tmp += self.dna[i][j] * inputs[j]
            result += ReLU(tmp) * self.dna[PARAMETERS][i]
        return result

    def set_white(self):
        self.play_color = WHITE

    def set_black(self):
        self.play_color = BLACK
