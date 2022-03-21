#include "utils.h"
#include <raymath.h>

void fix_angle(float* angle){
    if(*angle >= PI*2)
        *angle -= PI*2;
    if(*angle < 0.0f)
        *angle += PI*2;
}