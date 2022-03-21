#include "init_game.h"

void init_game(int screenWidth, int screenHeight) {
  InitWindow(screenWidth, screenHeight, "RayCaster - Example");
  SetTargetFPS(60);
}