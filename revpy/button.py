import pygame

class Button:
    def __init__(self, bx=0, by=0, bw=200, bh=50, color=(255, 255, 255)):
        self._is_active = True
        self._is_visible = True
        self._is_bg_visible = True
        self._bx, self._by, self._bw, self._bh = bx, by, bw, bh
        self._color = color
        self._margin = 10
        self._hasText = False
        self._tx, self._ty = 0, 0

        self._update()

    def get_center(self):
        return (self._bx+self._bw//2, self._by+self._bh//2)

    def __contains__(self, pos):
        if not self._is_active: return False
        if not (self._bx < pos[0] <= self._bx + self._bw): return False
        if not (self._by < pos[1] <= self._by + self._bh): return False
        return True

    def set_position(self, bx, by):
        self._bx, self._by = bx, by
        self._update()

    def set_size(self, bw, bh):
        self._bw, self._bh = bw, bh
        self._update()

    def set_color(self, c):
        self._color = c

    def set_active(self, b=True):
        self._is_active = b

    def set_visible(self, b=True):
        self._is_visible = b

    def set_bg_visible(self, b=True):
        self._is_bg_visible = b

    def set_margin(self, margin):
        self._margin = margin
        self._update()

    def set_text(self, text, color=(0, 0, 0), size=40, font=None, bold=False):
        self._text = text
        self._textColor = color
        self._textSize = size
        self._font = font
        self._isBold = bold
        self._hasText = True
        self._update()

    def change_text(self, text):
        self._text = text
        self._update()

    def set_textColor(self, color):
        self._textColor = color
        self._update()

    def set_textSize(self, size):
        self._textSize = size
        self._update()

    def set_font(self, font):
        self._font = font
        self._update()

    def set_bold(self, bold=True):
        self._isBold = bold
        self._update()

    def _update(self):
        self._preparation()
        text_offset = [0, 0]

        if self._hasText:
            text_offset = self._pyText.get_rect(center=(self._bw//2, self._bh//2))

        self._ty = text_offset[1] + self._by
        self._tx = text_offset[0] + self._bx

        self._preparation()

    def _preparation(self):
        self._pyBox = pygame.Rect(self._bx, self._by, self._bw, self._bh)
        if self._hasText:
            pyfont = pygame.font.SysFont(self._font, self._textSize, bold=self._isBold)
            self._pyText = pyfont.render(self._text, True, self._textColor)

    def draw(self, screen):
        if not self._is_visible: return
        if self._is_bg_visible: pygame.draw.rect(screen, self._color, self._pyBox)
        if self._hasText: screen.blit(self._pyText, (self._tx, self._ty))
