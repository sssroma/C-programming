#include <stdio.h>
#include <string.h>
#include <ctype.h>


void shifr(signed int a, char t[], int n){
    char text1[n];
    int j;
    for (int i = 0; i <= n; i++){
        j = t[i] + a;
        if (j>97+25){
            j = j-25;
        }
        if (j<97){
            j = j+26;
        }
        if (t[i] == ' '){text1[i] = ' ';}
        else {text1[i] = j;}
    }
    printf("%s\n", text1);
}

void deshifr(signed int a, char t[], int n){
    char text1[n];
    int j;
    for (int i = 0; i <= n; i++){
        j = t[i] - a;
        if (j>97+25){
            j = j-26;
        }
        if (j<97){
            j = j+25;
        }
        if (t[i] == ' '){text1[i] = ' ';}
        else {text1[i] = j;}
    }
    printf("%s", text1);
}

int main(){
    char text[] = "the quick brown fox jumps over the lazy dog";
    char text2[] = "qeb nrfzh yoltk clu grjmp lsbo qeb ixwv ald";
    signed int a = 0;
    /*char alphabet[26] = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g',
    'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u',
    'v', 'w', 'x', 'y', 'z' };*/
    scanf("%d", &a);
    shifr(a, text, strlen(text));
    deshifr(a, text2, strlen(text2));
}
