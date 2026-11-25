#include <stdio.h>
#include <stdlib.h>

int main() {
    const int rows = 9, cols = 9;  // размеры матрицы
    int **matrix;

    // Выделяем память для массива указателей
    matrix = (int **)malloc(rows * sizeof(int *));
    if (matrix == NULL) {
        fprintf(stderr, "Не удалось выделить память для строк\n");
        return 1;
    }

    // Для каждой строки выделяем память под её элементы
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            // Освобождаем уже выделенную память при ошибке
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            fprintf(stderr, "Не удалось выделить память для строки %d\n", i);
            return 1;
        }
    }

    // Пример использования: заполняем и выводим массив
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * cols + j;
        }
    }

    printf("Массив:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // Освобождаем память (важно делать это в обратном порядке)
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
