#include "utils.h"

#include <osqp.h>
#include <stdio.h>

int main(){
    unsigned int num = 0;
    int power = next_2_power(num);

    printf("Closest power of 2: %d", power);
    printf("\n");
    return 0;
}