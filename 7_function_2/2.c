#include <stdio.h>
#include <ctype.h>

int main(void) {
    char text[] = "hello world this is a test string for count letter functionooooooooooooooooooooooooooo";

    char letters[26];
    int counts[26] = {0};
    int n = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        char c = tolower((unsigned char)text[i]);
        if (c < 'a' || c > 'z') {
            continue;
        }
        int j = 0;
        while (j < n && letters[j] != c) {
            j++;
        }

        if (j < n) {
            counts[j]++;
        } else {
            letters[n] = c;
            counts[n] = 1;
            n++;
        }
    }

    for (int k = 0; k < 3 && k < n; k++) {
        int maxIndex = -1;

        for (int i = 0; i < n; i++) {
            if (counts[i] > 0 &&
                (maxIndex == -1 || counts[i] > counts[maxIndex] ||
                 (counts[i] == counts[maxIndex] &&
                  letters[i] < letters[maxIndex]))) {
                maxIndex = i;
            }
        }

        printf("%c: %d\n", letters[maxIndex], counts[maxIndex]);
        counts[maxIndex] = 0;
    }

    return 0;
}