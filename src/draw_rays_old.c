#include "draw_rays.h"
#include "globals.h"
#include "utils.h"
#include <float.h>
#include <raylib.h>
#include <raymath.h>

void draw_rays(const float x, const float y, const float orientation,
               const int ray_count, const int deeps_of_fields, const int *map) {
  // Sky
  DrawRectangle(HALF_WIDTH, 0, HALF_WIDTH, HALF_HEIGHT, SKYBLUE);
  // Ground
  DrawRectangle(HALF_WIDTH, HALF_HEIGHT, HALF_WIDTH, HALF_HEIGHT, GREEN);

  int mx, my, mp, dof, side;
  float vx, vy, rx, ry, ra, xo, yo, disV, disH;
  // ra = orientation;
  ra = orientation + ((float)ray_count / 2.0f) * DEG2RAD;
  fix_angle(&ra);

  for (int r = 0; r < ray_count; ++r) {
    //---Vertical---
    dof = 0;
    side = 0;
    disV = 100000;
    float Tan = tan(ra);
    if (cosf(ra) > 0.001) {
      rx = x + MAP_S;
      ry = (x - rx) * Tan + y;
      xo = -MAP_S;
      yo = xo * Tan;
    } // looking left
    else if (cosf(ra) < -0.001) {
      rx = x;
      ry = (x - rx) * Tan + x;
      xo = MAP_S;
      yo = xo * Tan;
    } // looking right
    else {
      rx = x;
      ry = y;
      dof = DEPS_OF_FIELD;
    } // looking up or down. no hit

    while (dof < DEPS_OF_FIELD) {
      mx = (int)(rx) >> 6;
      my = (int)(ry) >> 6;
      mp = my * MAP_X + mx;
      if (mp > 0 && mp < MAP_X * MAP_Y && map[mp] == 1) {
        dof = DEPS_OF_FIELD;
        disV = cosf(ra) * (rx - x) - sinf(ra) * (ry - y);
      } // hit
      else {
        rx += xo;
        ry += yo;
        dof += 1;
      } // check next horizontal
    }
    vx = rx;
    vy = ry;

    //---Horizontal---
    dof = 0;
    disH = 100000;
    // Tan = 1.0 / Tan;
    if (sinf(ra) > 0.001f) {
      ry = y;
      rx = (y - ry) * Tan + x;
      yo = -MAP_S;
      xo = yo * Tan;
    } // looking up
    else if (sin(ra) < -0.001) {
      ry = y + MAP_S;
      rx = (y - ry) * Tan + x;
      yo = MAP_S;
      xo = yo * Tan;
    } // looking down
    else {
      rx = x;
      ry = y;
      dof = DEPS_OF_FIELD;
    } // looking straight left or right

    while (dof < DEPS_OF_FIELD) {
      mx = (int)(rx) >> 6;
      my = (int)(ry) >> 6;
      mp = my * MAP_X + mx;
      if (mp > 0 && mp < MAP_X * MAP_Y && map[mp] == 1) {
        dof = DEPS_OF_FIELD;
        disH = cosf(ra) * (rx - x) - sinf(ra) * (ry - y);
      } // hit
      else {
        rx += xo;
        ry += yo;
        dof += 1;
      } // check next horizontal
    }

    if (disV < disH) {
      rx = vx;
      ry = vy;
      disH = disV;
    } // horizontal hit first
    DrawLine(x, y, rx, ry, PURPLE);

    float ca = orientation - ra;
    fix_angle(&ca);
    disH = disH * cosf(ca); // fix fisheye
    int lineH = (MAP_S * 320) / (disH);
    if (lineH > 320) {
      lineH = 320;
    }                                 // line height and limit
    int lineOff = 160 - (lineH >> 1); // line offset

    DrawLineEx((Vector2){r * 8 + HALF_WIDTH + 20, lineOff},
               (Vector2){r * 8 + HALF_WIDTH + 20, lineOff + lineH}, 8.0f, GREEN);
    ra -= 1.0f * DEG2RAD;
    fix_angle(&ra); // go to next ray
  }
}