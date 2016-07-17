void get_next() {
    int j, k;
    j = 0;
    k = -1;
    next[0] = -1;
    while (j < m) {
        if (k == -1 || b[j] == b[k]){
            next[++j] = ++k;
        }
        else {
            k = next[k];
        }
    }
}
void kmp() {
    int i = 0, j = 0;
    get_next();

    while (i < n) {
        if (j == -1 || a[i] == b[j]) {
            j++;
            i++;
        }
        else {
            j = next[j];
        }
        if (j == m) {
            printf("%d\n", i - m + 1);
            return;
        }
    }
    printf("-1\n");
}
