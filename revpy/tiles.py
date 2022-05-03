import pygame
from .button import Button
from .settings import *

class Tile(Button):
    def __init__(self, n):
        bx = (n % REVERSI_SIZE) * (TILE_WIDTH + TILE_MARGIN * 2) + TILE_MARGIN
        by = (n // REVERSI_SIZE) * (TILE_WIDTH + TILE_MARGIN * 2) + TILE_MARGIN
        super().__init__(bx, by, TILE_WIDTH, TILE_HEIGHT, TILE_COLOR)

    def draw(self, screen, state):
        super().draw(screen)
        if state == BLACK: pygame.draw.circle(screen, BLACK_COLOR, self.get_center(), STONE_RADIUS)
        if state == WHITE: pygame.draw.circle(screen, WHITE_COLOR, self.get_center(), STONE_RADIUS)

class Tiles:
    def __init__(self):
        self.tiles = [ Tile(n) for n in range(REVERSI_MAX)]
        self.n = 0

    def draw(self, screen, r):
        screen.fill(EDGE_COLOR)

        for n, tile in enumerate(self.tiles):
            y = n // REVERSI_SIZE
            x = n % REVERSI_SIZE
            tile.draw(screen, r.board[y][x])

    def __contains__(self, pos):
        for n, tile in enumerate(self.tiles):
            if pos in tile:
                self.n = n
                return True
        return False
