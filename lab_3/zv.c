#include <stdio.h>
#include <math.h>

int main() {
    int width = 70;
    int height = 20;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double rad = (x - width / 2.0) * 3.14159 / (width / 2.0);
            double sin_val = sin(rad);
            int y_sin = (int)(height / 2.0 - sin_val * (height / 2.0 - 1));
            if (y == y_sin) {
                printf("*");
            } else if (y == height / 2) {
                printf("_"); // ось X
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}