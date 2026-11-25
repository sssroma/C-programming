#include <stdio.h>

int main(void){
    int n=0;
    printf("Введите число?: ");
    scanf("%d", &n);
    char o = 'o';
    for (int i=1; i<=n; i++){
        printf("%d", i);
        for (int z=n+1-i; z>=1; z--){
            printf("%c", o);
        }
        printf("\n");
    }
}