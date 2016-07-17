/*
SAM 的状态结点包含了很多重要的信息：
max：即代码中 val 变量，它表示该状态能够接受的最长的字符串长度。
min：表示该状态能够接受的最短的字符串长度。实际上等于该状态的 par 指针指向的结点的 val + 1。
max-min+1：表示该状态能够接受的不同的字符串数。
right：即 end-set 的个数，表示这个状态在字符串中出现了多少次，该状态能够表示的所有字符串均出现过 right 次。
par：par 指向了一个能够表示当前状态表示的所有字符串的最长公共后缀的结点。所有的状态的 par 指针构成了一个 parent 树，恰好是字符串的逆序的后缀树。
parent 树的拓扑序：序列中第i个状态的子结点必定在它之后，父结点必定在它之前。
*/
int newnode(int _val) {
    tot++;
    memset(ch[tot], -1, sizeof ch[tot]);
    pre[tot] = 0;
    val[tot] = _val;
    tag[tot] = 0;
    cnt[tot] = 0;
    return tot;
}
void init() {
    root = 0;
    tot = -1;
    tot = newnode(0);
    pre[tot] = -1;
}
void add(int x) {
    int p = last;
    int np = newnode(val[p] + 1);
    cnt[np] = 1;//同样的子串出现了多少次
    last = np;
    while (p >= 0 && ch[p][x] == -1) {
        ch[p][x] = np, p = pre[p];
    }
    if (p < 0) {
        pre[np] = root;
    }
    else {
        int q = ch[p][x];
        if (val[q] == val[p] + 1) {
            pre[np] = q;
        }
        else {
            int nq = newnode(val[p] + 1);
            memcpy(ch[nq], ch[q], sizeof ch[nq]);
            pre[nq] = pre[q];
            pre[q] = pre[np] = nq;
            while (p >= 0 && ch[p][x] == q)
                ch[p][x] = nq, p = pre[p];
        }
    }
}
void Top() {
    int l = strlen(str);
    for (int i = 1; i <= tot; i++) snt[val[i]]++;
    for (int i = 1; i <= l; i++) snt[i] += snt[i - 1];
    for (int i = 1; i <= tot; i++) top[snt[val[i]]--] = i;
    for (int i = tot; i >= 1; i--) {
        int u = top[i];
        cnt[pre[u]] += cnt[u];//向pre传包含同一字串出现的次数
        snt[u] = 1;//u != 0
        for (int j = 0; j < M; j++)
            if (ch[now][j] != -1)
                snt[now] += snt[ch[now][j]]; // 不同子串的出现个数
    }
}
