#ifndef RAND_H
#define RAND_H

extern long globalSeed;
/* Memberikan angka random berdasarkan n dan seed */
long random_lcg(int n,long seed);

#endif