#include <stdio.h>
#define N 3

int main(void){
    int scores[N] = {73, 43, 100};

    int sum = 0;
    for(int i=0; i <N; i++){
        sum += scores[i];
    }
    //printf("%d\n", sum);
    int s[3] = 123;
    printf("%d\n", s);
    return 0;
}