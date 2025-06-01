#include "../header/random.h"
#include "../header/externalfile.h"
#include "../header/role.h"

long globalSeed;

long random_lcg(int n,long seed){
    for(int i = 1 ; i <= n ; i++){
        seed %= 16777216;
        seed = (16598013  *seed+2820163) % 16777216;
    }
    globalSeed = seed%500;
    return seed;
}

void LihatDompet(){
    int pos = userPosByID(masterID);
    char *role = Ulist.contents[pos].field[3]; 
    printf("\nBanarich milik kamu saat ini adalah %d Banarich.\n", banarich[pos]);
}

void LihatFinansial(){
    int pos = -1;
    
    for(int i = 0 ; i < Ulist.len ; i++){
        if( strcmp(Ulist.contents[i].field[3],"manager") == 0 ) {pos = i; break;}
    }

    if( pos == -1 ){
        printf("\nManager tidak ditemukan!\n");
        return;
    }

    printf("\nBanarich milik rumah sakit saat ini adalah %d Banarich.\n", banarich[pos]);
}

void Gacha(){
    long result = random_lcg(masterID,globalSeed);
    globalSeed++;
    result %= 200;

    printf("\nMesin GACHA-X 2.0 sedang bekerja...\n");
    
    if( globalSeed > 400  ){
        result *= -1;
        printf("Yah.. rungkad %d koin\n", result);
    }
    else if (result >= 0 && result <= 50) {
        printf("Cuma dapat %d koin...\n", result);
    } else if (result >= 51 && result <= 100) {
        printf("Dapat %d koin. Yah, standar lah.\n", result);
    } else if (result >= 101 && result <= 150) {
        printf("%d koin! Udah mulai keliatan hoki.\n", result);
    } else if (result >= 151 && result <= 190) {
        printf("Mantap! %d koin berhasil dikantongi!\n", result);
    } else if (result >= 191 && result <= 199) {
        printf("GACOR! %d koin langsung masuk dompet!\n", result);
    }

    banarich[userPosByID(masterID)] += result;
}

UpdateKasRumahSakit(int delta){
    int pos = -1;
    
    for(int i = 0 ; i < Ulist.len ; i++){
        if( strcmp(Ulist.contents[i].field[3],"manager") == 0 ) {pos = i; break;}
    }

    if( pos == -1 ){
        printf("\nManager tidak ditemukan!\n");
        return;
    }

    banarich[pos] += delta;
}