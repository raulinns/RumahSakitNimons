#ifndef RAND_H
#define RAND_H

extern long globalSeed;

// Generate angka random menggunakan Linear Congruential Generator (LCG) dengan seed dan iterasi n
long random_lcg(int n, long seed);

// Tampilkan jumlah Banarich (uang virtual) milik user yang sedang login
void LihatDompet();

// Tampilkan jumlah Banarich milik rumah sakit (user dengan role manager)
void LihatFinansial();

// Simulasi mesin Gacha yang menghasilkan koin acak dan memperbarui saldo user
void Gacha();

// Update saldo Banarich rumah sakit (manager) dengan perubahan delta
void UpdateKasRumahSakit(int delta);


#endif