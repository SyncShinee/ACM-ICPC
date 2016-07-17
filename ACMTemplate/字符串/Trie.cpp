struct Trie {
    int tot;
    int ch[N][M], val[N];
    int newnode() {
        tot++;
        memset(ch[tot], 0, sizeof ch[tot]);
        val[tot] = 0;
        return tot;
    }
    void init() {
        tot = -1;
        newnode();
    }
    void insert(char * s) {
        int len = strlen(s);
        int now = 0;
        for (int i = 0; i < len; i++) {
            int c = s[i] - 'a';
            if (!ch[now][c])
                ch[now][c] = newnode();
            now = ch[now][c];
            val[now] = 1;
        }
    }
};
