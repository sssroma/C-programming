#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MINE   '@'
#define CLOSED '.'
#define FLAG   'F'

//создание матрицы по параметрам
char **create_matrix(int n, char fill){
    char **m = malloc(n * sizeof(char *));
    if (m == NULL) return NULL;
    for (int i = 0; i < n; i++){
        m[i] = malloc(n * sizeof(char));
        if (m[i] == NULL){
            for (int k = 0; k < i; k++) free(m[k]);
            free(m);
            return NULL;
        }
        for (int j = 0; j < n; j++){
            m[i][j] = fill;
        }
    }
    return m;
}

//чистка памяти
void free_matrix(char **matrix, int n){
    for (int i = 0; i < n; i++){
        free(matrix[i]);
    }
    free(matrix);
}

//цвета
#define RESET "\033[0m"

void clear_screen(void){
    printf("\033[H\033[J");
}

const char *cell_color(char c){
    switch (c){
        case '1': return "\033[1;34m";   // синий
        case '2': return "\033[1;32m";   // зелёный
        case '3': return "\033[1;31m";   // красный
        case '4': return "\033[1;35m";   // фиолетовый
        case '5': return "\033[1;33m";   // жёлтый
        case '6': return "\033[1;36m";   // голубой
        case '7':
        case '8': return "\033[1m";      // жирный
        case MINE: return "\033[1;41m";  // мина: красный фон
        case FLAG: return "\033[1;33m";  // флажок: жёлтый
        case '0': return "\033[90m";     // ноль: серый
        default:  return "";             // закрытая клетка - обычный цвет
    }
}

//вывод матрицы
void print_matrix(char **matrix, int n){
    printf("   ");
    for (int j = 1; j <= n; j++){
        printf("%2d ", j);
       }   // номера столбцов

    printf("\n");
    for (int i = 0; i < n; i++){
        printf("%2d ", i + 1);  // номер строки                      
        for (int j = 0; j < n; j++){
            char c = matrix[i][j];
            printf(" %s%c%s ", cell_color(c), c, RESET);
        }
        printf("\n");
    }
    printf("\n");
}

//логика поля

int in_field(int x, int y, int n){
    return x >= 0 && x < n && y >= 0 && y < n;
}

//зона
int zone_size(int n, int fx, int fy){
    int count = 0;
    for (int dx = -1; dx <= 1; dx++){
        for (int dy = -1; dy <= 1; dy++){
            if (fx + dx >= 0 && fx + dx < n && fy + dy >= 0 && fy + dy < n) count++;
            }
        }
    return count;
}

//рандомно ставим мины учитывая защищённый радиус
void random_mines(char **back, int n, int mines, int fx, int fy){
    int radius = (mines <= n * n - zone_size(n, fx, fy)) ? 1 : 0;
    for (int i = 0; i < mines; i++){
        int x, y;
        do {
            x = rand() % n;
            y = rand() % n;
        } while (back[x][y] == MINE || (abs(x - fx) <= radius && abs(y - fy) <= radius));
        back[x][y] = MINE;
    }
}

//колво мин вокруг точки
int mines_around_dot(char **back, int x, int y, int n){
    int count = 0;
    for (int dx = -1; dx <= 1; dx++){
        for (int dy = -1; dy <= 1; dy++){
            if (dx == 0 && dy == 0) continue;   // саму клетку не считаем
            int nx = x + dx, ny = y + dy;
            if (in_field(nx, ny, n) && back[nx][ny] == MINE) {
                count++;
            }
        }
    }
    return count;
}

// один раз после расстановки мин записываем цифры во все безопасные клетки
void fill_numbers(char **back, int n){
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (back[i][j] != MINE)
                back[i][j] = '0' + mines_around_dot(back, i, j, n);
}

//рекурсивное открытие + создание после открытия первой
void open_cell(char **back, char **front, int n, int x, int y, int *opened){
    if (!in_field(x, y, n)) return;
    if (front[x][y] != CLOSED) return;
    front[x][y] = back[x][y];
    (*opened)++;
    if (back[x][y] == '0'){
        for (int dx = -1; dx <= 1; dx++)
            for (int dy = -1; dy <= 1; dy++)
                if (dx != 0 || dy != 0)
                    open_cell(back, front, n, x + dx, y + dy, opened);
    }
}

//показ мин после проигрыша
void reveal_mines(char **back, char **front, int n){
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (back[i][j] == MINE) front[i][j] = MINE;
}

//функции ввода

void skip_line(void){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int read_int(const char *prompt, int min, int max){
    int v=0;
    while (1){
        printf("%s", prompt);
        if (scanf("%d", &v) == 1 && v >= min && v <= max){
            skip_line();
            return v;
        }
        if (feof(stdin)) exit(1);
        skip_line();
        printf("Неверный ввод.\n");
    }
}

int main(void){
    srand(time(NULL));

    int n = read_int("Введите размер поля (2..30): ", 2, 30);
    char prompt[100];
    sprintf(prompt, "Введите количество мин (1..%d): ", n * n - 1);
    int mines = read_int(prompt, 1, n * n - 1);

    char **back  = create_matrix(n, '0');      //заднее поле мины и цифры
    char **front = create_matrix(n, CLOSED);   //видимое поле что открыл игрок
    if (back == NULL || front == NULL){
        printf("Не хватило памяти\n");
        return 1;
    }

    int opened = 0, flags = 0;
    int first_move = 1;
    int result = 0;                 // 0 играем 1 победа -1 поражение 2 выход
    int safe_cells = n * n - mines;

    const char *msg = "";

    while (result == 0){
        clear_screen();
        print_matrix(front, n);
        printf("Мин: %d  Флажков: %d\n", mines, flags);
        printf("%s\n", msg);
        msg = "";
        printf("Команда (o строка столбец - открыть, f строка столбец - флажок, q - выход): ");
        fflush(stdout);

        char cmd;
        int x, y;
        if (scanf(" %c", &cmd) != 1) break;
        if (cmd == 'q'){
            result = 2;
            break;
        }
        if ((cmd != 'o' && cmd != 'f') || scanf("%d %d", &x, &y) != 2){
            skip_line();
            msg = "Не понял команду.";
            continue;
        }

        x--;
        y--;

        if (!in_field(x, y, n)){
            msg = "Координаты вне поля.";
            continue;
        }

        if (cmd == 'f'){
            if (front[x][y] == CLOSED){
                front[x][y] = FLAG;
                flags++;
            }
            else if (front[x][y] == FLAG){
                front[x][y] = CLOSED;
                flags--;
            }
            else msg = "Клетка уже открыта.";
            continue;
        }

        //cmd o
        if (front[x][y] == FLAG){
            msg = "Сначала снимите флажок.";
            continue;
        }

        if (front[x][y] != CLOSED){
            msg = "Уже открыта.";
            continue; 
        }

        if (first_move){                        // мины только сейчас, мимо первой клетки
            random_mines(back, n, mines, x, y);
            fill_numbers(back, n);
            first_move = 0;
        }

        if (back[x][y] == MINE){
            reveal_mines(back, front, n);
            result = -1;
        }
        
        else {
            open_cell(back, front, n, x, y, &opened);
            if (opened == safe_cells) result = 1;
        }
    }

    clear_screen();
    print_matrix(front, n);
    if (result == 1)  printf("\033[1;32mПобеда!\033[0m\n");
    if (result == -1) printf("\033[1;31mБУМ! Вы попали на мину.\033[0m\n");

    printf("--- Статистика ---\n");
    printf("Открыто клеток:     %d из %d\n", opened, safe_cells);
    printf("Поставлено флажков: %d\n", flags);
    printf("Осталось мин:       %d\n", mines - flags);

    free_matrix(back, n);
    free_matrix(front, n);
    return 0;

}