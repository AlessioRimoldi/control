#include "utils.h"

int next_2_power(int num) {
    int v = num;
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v |= v >> 32;
    v |= v >> 64;
    v++;
    v+=(v==0);
    return v;
}
