#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define n 10
int main(void){
    srand(time(NULL));
    int s[n] = {};
    int s1[n] = {};
    for (int i=0; i<n; i++){
        s[i] = (int)((double)rand() / RAND_MAX * 65535.0) - 32768;
        s1[i] = (int)((double)rand() / RAND_MAX * 65535.0) - 32768;
    }
    /*printf("s=");
    for (int i=0; i<n; i++){
        printf("%d, ",s[i]);
    }
    printf("s1=");
    for (int i=0; i<n; i++){
        printf("%d, ",s1[i]);
    }*/
    for (int i=0; i<n; i++){
        printf("s[%d] = %d + i * (%d)\n", i, s[i], s1[i]);
    }
    int E = 0;
    for (int i=0; i<n; i++){
        E+= (s[i]*s[i] + s1[i]*s1[i]);
    }
    printf("%d\n", E);
    int maxv = 0;
    int mi = 0;
    for (int i=0; i<n; i++){
        if (s[i]>maxv){
            maxv = s[i];
            mi = i;
        }
    }
    printf("MAX value: %d index: %d\n", maxv, mi);
}