// квик сорт по схеме Хоара

void quick_sort(int *a, int left, int right) {
    if (left >= right) return;
    int pivot = a[(left + right) / 2];
    int i = left, j = right;
    while (i <= j) {
        while (a[i] < pivot) i++;
        while (a[j] > pivot) j--;
        if (i <= j) {
            int tmp = a[i]; a[i] = a[j]; a[j] = tmp;
            i++; j--;
        }
    }
    quick_sort(a, left, j);
    quick_sort(a, i, right);
}

// Сортирует быстрее, чем я делаю лабы