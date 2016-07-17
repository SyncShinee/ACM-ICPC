//定义母串ch1，和字串ch2，设S的长度为n，T的长度为m，求T与S的每一个后缀的最长公共前缀，也就是说，设extend数组, extend[i]表示T与S[i, n - 1]的最长公共前缀，要求出所有extend[i](0 <= i<n)。
void get_next() {
    int k = 0;
    Next[0] = n;
    while (k + 1 < n && ch1[k] == ch1[1 + k]) k++;
    Next[1] = k;
    int a = 1;
    for (int j = 2; j < n; j++) {
        int p = Next[a] + a - 1;
        int l = Next[j - a];
        if (l + j < p + 1) Next[j] = l;
        else {
            k = max(0, p - j + 1);
            while (k + j < n 
                   && ch1[k + j] == ch1[k]) k++;
            Next[j] = k;
            a = j;
        }
    }

    k = 0;
    while (k < n && k < m && ch1[k] == ch2[k]) k++;
    extend[0] = k;
    a = 0;
    for (int i = 1; i < m; i++) {
        int p = extend[a] + a - 1;
        int l = Next[i - a];
        if (l + i < p + 1) extend[i] = l;
        else {
            int j = max(0, p - i + 1);
            while (i + j < m && j < n && ch1[j] == ch2[i + j]) j++;
            extend[i] = j;
            a = i;
        }
    }
}
