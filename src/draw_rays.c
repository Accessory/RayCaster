#include "draw_rays.h"
#include "globals.h"
#include "utils.h"
#include <float.h>
#include <raylib.h>
#include <raymath.h>

bool outOfMapBounds(const int x, const int y, const int *map) {
  return x < 0 || x >= MAP_X || y < 0 || y >= MAP_Y;
}

bool isLookUp(const float angle) {
  if (angle > PI && angle < 2 * PI)
    return true;
  return false;
}

bool isLookRight(const float angle) {
  if (angle > PI / 2 && angle < 3 * PI / 2)
    return false;
  return true;
}

float fixFishEye(const float distance, const float angle,
                 const float playerAngle) {
  const float diff = angle - playerAngle;
  return distance * cosf(diff);
}

void draw_rays(const float x, const float y, const float orientation,
               const int ray_count, const int deeps_of_fields, const int *map) {
  // Sky
  DrawRectangle(HALF_WIDTH + 20, 0 + 20, HALF_WIDTH - 40, HALF_HEIGHT - 40,
                SKYBLUE);
  // Ground
  DrawRectangle(HALF_WIDTH + 20, HALF_HEIGHT + 20, HALF_WIDTH - 40,
                HALF_HEIGHT - 40, DARKGRAY);

  // ra = orientation;
  float ra = orientation - ((float)ray_count / 2.0f) * DEG2RAD;
  // float ra = orientation;
  fix_angle(&ra);

  // for (int r = 0; r < 1; ++r) {
  for (int r = 0; r < ray_count; ++r) {

    const float cTan = tan(ra);
    // Vertical

    float nextX, nextY;
    float distanceVertical = FLT_MAX;
    if (ra != PI / 2.0f && ra != PI + PI / 2.0f) {
      const bool right = isLookRight(ra);

      const float firstX =
          right ? floorf(x / MAP_S) * MAP_S + MAP_S : floorf(x / MAP_S) * MAP_S;

      const float firstY = y + (firstX - x) * cTan;

      const float xA = right ? (float)MAP_S : (float)-MAP_S;
      const float yA = xA * cTan;

      bool wall = false;
      nextX = firstX;
      nextY = firstY;

      while (!wall) {
        const int cellX =
            right ? (int)floorf(nextX / MAP_S) : (int)floorf(nextX / MAP_S) - 1;
        const int cellY = (int)floorf(nextY / MAP_S);

        if (outOfMapBounds(cellX, cellY, map)) {
          break;
        }

        wall = map[cellY * MAP_X + cellX] > 0;
        if (!wall) {
          nextX += xA;
          nextY += yA;
        }
      }

      distanceVertical =
          Vector2Distance((Vector2){x, y}, (Vector2){nextX, nextY});
    }

    //  Horizontal
    float distanceHorizontal = FLT_MAX;
    float nextX_H, nextY_H;
    if (ra != 0 && ra != PI) {
      const bool up = isLookUp(ra);

      const float firstY_H =
          up ? floorf(y / MAP_S) * MAP_S : floorf(y / MAP_S) * MAP_S + MAP_S;
      const float firstX_H = x + (firstY_H - y) / cTan;

      const float yA_H = up ? -MAP_S : MAP_S;
      const float xA_H = yA_H / cTan;

      bool wall_H = false;
      nextX_H = firstX_H;
      nextY_H = firstY_H;
      while (!wall_H) {
        const int cellX = (int)(nextX_H / MAP_S);
        const int cellY =
            up ? (int)(nextY_H / MAP_S) - 1 : (int)(nextY_H / MAP_S);

        if (outOfMapBounds(cellX, cellY, map)) {
          break;
        }

        wall_H = map[cellY * MAP_X + cellX] > 0;
        if (!wall_H) {
          nextX_H += xA_H;
          nextY_H += yA_H;
        }
      }
      distanceHorizontal =
          Vector2Distance((Vector2){x, y}, (Vector2){nextX_H, nextY_H});
    }

    float distance;
    Color color;
    if (distanceHorizontal < distanceVertical) {
      DrawLine(x, y, nextX_H, nextY_H, BLUE);
      distance = fixFishEye(distanceHorizontal, ra, orientation);
      color = DARKGREEN;
    } else {
      DrawLine(x, y, nextX, nextY, RED);
      distance = fixFishEye(distanceVertical, ra, orientation);
      color = GREEN;
    }

    int line = MAP_S * HALF_HEIGHT * 1.5 / distance;
    int lineOff = HALF_HEIGHT - (line >> 1);

    DrawLineEx(
        (Vector2){r * LINE_WIDTH + HALF_WIDTH + 20 + LINE_WIDTH / 2, lineOff},
        (Vector2){r * LINE_WIDTH + HALF_WIDTH + 20 + LINE_WIDTH / 2,
                  lineOff + line},
        (float)LINE_WIDTH, color);

    ra += 1.0f * DEG2RAD;
    fix_angle(&ra); // go to next ray
  }
}