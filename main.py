# main file to play reversi vs AI
import pygame
import time

from revpy import Reversi, AI, Tiles, Side, SCREEN_SIZE, WHITE, BLACK

DATA_FILE = "data/data1.txt"

def main():
    pygame.init()
    screen = pygame.display.set_mode(SCREEN_SIZE)
    pygame.display.set_caption("vs REVERSI AI")

    reversi = Reversi()
    ai = AI(DATA_FILE)
    tiles = Tiles()
    side = Side()

    ai.set_white()
    working = True

    while working:
        tiles.draw(screen, reversi)
        side.draw(screen, reversi)
        pygame.display.update()

        if reversi.turn == WHITE:
            ai.put_stone(reversi)
            time.sleep(1)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                working = False
            if event.type == pygame.MOUSEBUTTONDOWN:
                if event.pos in tiles:
                    if reversi.is_puttable(tiles.n):
                        reversi.put_stone(tiles.n)

    pygame.quit()


if __name__ == "__main__":
    main()
