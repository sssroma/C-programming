#include <stdio.h>

void octal(int a) {
    if (a > 0) {
        octal(a >> 3); 
        printf("%d", a & 7); 
    }
}

int main() {
    int a=0;
    printf("Введите число a > 0: ");
    scanf("%d", &a);

    if (a > 0) {
        octal(a);
        printf("\n");
    } else {
        printf("Число должно быть больше нуля.\n");
    }
    
    return 0;
}