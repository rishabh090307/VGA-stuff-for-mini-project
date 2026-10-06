#include "random_number.h"

static unsigned int random_value = 1;

void random_seed(unsigned int seed){
    random_value = seed;
}

unsigned int random_number(void){
    random_value = random_value * 767350 + 80294427;
    return random_value;
}