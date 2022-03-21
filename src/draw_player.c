#include "draw_player.h"
#include <raylib.h>
#include <math.h>


void draw_player(const float x, const float y, const float orientation) {

  DrawCircle(x, y, 10, GOLD);
  const int xe = x + 20.0f * cosf(orientation);
  const int ye = y + 20.0f * sinf(orientation);
  DrawLineEx((Vector2) {x, y}, (Vector2) {xe, ye}, 4, BLUE);
}