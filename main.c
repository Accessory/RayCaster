#include "src/globals.h"
#include "src/draw_map.h"
#include "src/draw_player.h"
#include "src/init_game.h"
#include "src/map.h"
#include "src/utils.h"
#include "src/draw_rays.h"
#include <raylib.h>
#include <raymath.h>

int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------
  init_game(SCREEN_WIDTH, SCREEN_HEIGHT);

  Vector2 playerPosition = {(float)SCREEN_WIDTH / 4, (float)SCREEN_HEIGHT / 4};
  float orientation = 0.0f;

  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------

    const float xe = PLAYER_SPEED * cosf(orientation);
    const float ye = PLAYER_SPEED * sinf(orientation);
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
      orientation += PLAYER_TURNSPEED;
      fix_angle(&orientation);
    }
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
      orientation -= PLAYER_TURNSPEED;
      fix_angle(&orientation);
    }
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
      playerPosition.x += xe;
      playerPosition.y += ye;
    }
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
      playerPosition.x -= xe;
      playerPosition.y -= ye;
    }
    if (IsKeyDown(KEY_Q)) {
      orientation -= PLAYER_TURNSPEED;
      fix_angle(&orientation);
    }
    if (IsKeyDown(KEY_E)) {
      orientation += PLAYER_TURNSPEED;
      fix_angle(&orientation);
    }

    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
    ClearBackground(RAYWHITE);
    draw_map(map, MAP_X, MAP_Y, MAP_S);
    draw_player(playerPosition.x, playerPosition.y, orientation);
    draw_rays(playerPosition.x, playerPosition.y, orientation, RAY_COUNT, DEPS_OF_FIELD, map);
    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}