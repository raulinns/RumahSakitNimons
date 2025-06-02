#include <stdio.h>
#include "../../header/adt/map.h"

// int main(){
//     long x,y;
//     long z;
//     Map l = NULL;
//     scanf("%ld", &x);
//     while(x > 0){
//         if( x == 1 ){ // push
//             scanf("%ld %ld", &y, &z);
//             map_insertData(&l,y,z);
//         }
//         if( x == 2 ){ // pop
//             scanf("%ld", &y);
//             map_popData(l,y);
//         }
//         if( x == 3 ){ //print
//             scanf("%ld", &y);
//             Map cek = map_findMap(l,y);
//             if( cek == NULL){
//                 printf("Node dengan id %ld tidak ditemukan!", y);
//             }
//             else{
//                 printf("Queue id %ld : ", y);
//                 Node* Q = (cek->data).front;
//                 while( Q != NULL ){
//                     printf("%d ", Q->data);
//                     Q = Q->next;
//                 }
//                 printf("\n");
//             }
//         }
//         scanf("%ld", &x);
//     }
// }