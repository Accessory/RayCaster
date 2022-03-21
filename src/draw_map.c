#include "draw_map.h"
#include <raylib.h>
#include <stdio.h>

void draw_map(const int *map, const int mapX, const int mapY, const int mapS) {
  const int OFFSET = 2;

  for (int y = 0; y < mapY; ++y) {
    for (int x = 0; x < mapX; ++x) {
      int xo = x * mapS;
      int yo = y * mapS;
      if (map[y * mapX + x] == 0) {
        DrawRectangle(xo + OFFSET, yo + OFFSET, mapS - OFFSET, mapS - OFFSET,
                      GRAY);
      } else {
        DrawRectangle(xo + OFFSET, yo + OFFSET, mapS - OFFSET, mapS - OFFSET,
                      BLACK);
      }
    }
  }
};