#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
const int N = 500;
// 并查集维护
int belong[N];
int findb(int x) {
    return belong[x] == x ? x : belong[x] = findb(belong[x]);
}
void unit(int a, int b) {
    a = findb(a);
    b = findb(b);
    if (a != b) belong[a] = b;
}
int n, match[N];
vector<int> e[N];
int ttt[N], lo[N];
int Q[N], rear;
int next[N], mark[N], vis[N];
// 朴素算法求某阶段中搜索树上两点x, y的最近公共祖先r
int LCA(int x, int y) {
    static int t = 0; t++;
    while (true) {
        if (x != -1) {
            x = findb(x); // 点要对应到对应的花上去
            if (vis[x] == t) return x;
            vis[x] = t;
            if (match[x] != -1) x = next[match[x]];
            else x = -1;
        }
        swap(x, y);
    }
}
void group(int a, int p) {
    while (a != p) {
        int b = match[a], c = next[b];
        // next数组是用来标记花朵中的路径的，综合match数组来用，实际上形成了
        // 双向链表，如(x, y)是匹配的，next[x]和next[y]就可以指两个方向了。
        if (findb(c) != p) next[c] = b;
        // 奇环中的点都有机会向环外找到匹配，所以都要标记成S型点加到队列中去，
        // 因环内的匹配数已饱和，因此这些点最多只允许匹配成功一个点，在aug中
        // 每次匹配到一个点就break终止了当前阶段的搜索，并且下阶段的标记是重
        // 新来过的，这样做就是为了保证这一点。
        if (mark[b] == 2) mark[Q[rear++] = b] = 1;
        if (mark[c] == 2) mark[Q[rear++] = c] = 1;
        unit(a, b); unit(b, c);
        a = c;
    }
}
// 增广
void aug(int s) {
    for (int i = 0; i < n; i++) // 每个阶段都要重新标记
    next[i] = -1, belong[i] = i, mark[i] = 0, vis[i] = -1;
    mark[s] = 1;
    Q[0] = s; rear = 1;
    for (int front = 0; match[s] == -1 && front < rear; front++) {
        int x = Q[front]; // 队列Q中的点都是S型的
        for (int i = 0; i < (int)e[x].size(); i++) {
            int y = e[x][i];
            if (match[x] == y) continue; // x与y已匹配，忽略
            if (findb(x) == findb(y)) continue; // x与y同在一朵花，忽略
            if (mark[y] == 2) continue; // y是T型点，忽略
            if (mark[y] == 1) {
                int r = LCA(x, y);
                if (findb(x) != r) next[x] = y;
                if (findb(y) != r) next[y] = x;
                group(x, r); // 缩路径r --- x为点
                group(y, r); // 缩路径r --- y为点
            }
            else if (match[y] == -1) { // y自由，可以增广，R12规则处理
                next[y] = x;
                for (int u = y; u != -1; ) { // 交叉链取反
                    int v = next[u];
                    int mv = match[v];
                    match[v] = u, match[u] = v;
                    u = mv;
                }
                break; // 搜索成功，退出循环将进入下一阶段
            }
            else { // 当前搜索的交叉链+y+match[y]形成新的交叉链，将match[y]加入队列作为待搜节点
                next[y] = x;
                mark[Q[rear++] = match[y]] = 1; // match[y]也是S型的
                mark[y] = 2; // y标记成T型
            }
        }
    }
}
bool g[N][N];
int main() {
    int T, m;
    freopen("in.txt", "r", stdin);
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) g[i][j] = false;
        for (int i = 0; i < n; ++ i) e[i].clear();
        // 建图，双向边
        for (int i = 0; i < n; ++ i) {
            scanf("%d", &ttt[i]);
        }
        for (int i = 1; i <= m; ++ i) {
            scanf("%d", &lo[i]);
        }
        sort(lo + 1, lo + m + 1);
        lo[m + 1] = -1;
        for (int i = 0; i < n; ++ i) {
            for (int j = i + 1; j < n; ++ j) {
                if (*lower_bound(lo + 1, lo + m + 1, ttt[i] + ttt[j]) == ttt[i] + ttt[j]) {
            e[i].push_back(j), e[j].push_back(i);
            g[i][j] = g[j][i] = true;
                }
            }
        }
        // 增广匹配
        for (int i = 0; i < n; i++) match[i] = -1;
        for (int i = 0; i < n; i++) if (match[i] == -1) aug(i);
        // 输出答案
        int tot = 0;
        for (int i = 0; i < n; i++) if (match[i] != -1) tot++;
        printf("%d\n", tot/2);
    }
    return 0;
}