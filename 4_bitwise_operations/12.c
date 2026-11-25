#include <stdio.h>

int bits(unsigned int a){
    unsigned int lowb = (a & 0xFF) << 8;
    unsigned int oldb = (a >> 8) & 0xFF;
    unsigned int hdb = a & 0xFFFF0000;
    return a = hdb | lowb | oldb;
}

int main(void){
    printf("0x%X", bits(0x99991234));
    return 0;
}