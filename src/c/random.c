#include "../header/random.h"

long random_lcg(int n,long seed){
    for(int i = 1 ; i <= n ; i++){
        seed %= 16777216;
        seed = (16598013  *seed+2820163) % 16777216;
    }
    return seed;
}