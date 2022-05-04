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
        if deep == 1:
            return self.evaluate(r.get_inputs())
        else:
            pass

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
