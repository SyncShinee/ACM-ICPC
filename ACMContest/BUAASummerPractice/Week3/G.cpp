#include <cstdio>
#include <algorithm>
#include <cstring>
#define lson Tree[now].son[0]
#define rson Tree[now].son[1]
using namespace std;
const int N = 100010;
struct T {
    int d[3], mn[3], mx[3], w, son[2];
}Tree[N];
struct node {
    int d[3], w;
    node (int _l = 0, int _r = 0, int _x = 0, int _w = 0) {
        d[0] = _l;
        d[1] = _r;
        d[2] = _x;
        w = _w;
    }
}p[N];
int ans, rt, las[N], L[N], R[N], pos[3][2], D, l, r, a[N], n, m;
bool operator < (const node &A, const node &B) {
    return A.d[D] < B.d[D];
}
void update(int o, int s) {
    for (int i = 0; i < 3; ++ i) {
        Tree[o].mn[i] = min(Tree[o].mn[i], Tree[s].mn[i]);
        Tree[o].mx[i] = max(Tree[o].mx[i], Tree[s].mx[i]);
    }
    Tree[o].w = max(Tree[o].w, Tree[s].w);
}
int build(int l, int r, int d) {
    D = d;
    int now = l + r >> 1;
    nth_element(p + l, p + now, p + r + 1);
    Tree[now].w = p[now].w;
    for (int i = 0; i < 3; ++ i) {
        Tree[now].d[i] = Tree[now].mn[i] = Tree[now].mx[i] = p[now].d[i];
    }
    if (l < now) {
        lson = build(l, now - 1, (d + 1) % 3);
        update(now, lson);
    }
    if (now < r) {
        rson = build(now + 1, r, (d + 1) % 3);
        update(now, rson);
    }
    return now;
}
bool check(int now) {
    for (int i = 0; i < 3; ++ i) {
        if (pos[i][0] > Tree[now].mx[i] || pos[i][1] < Tree[now].mn[i]){
            return false;
        }
    }
    return true;
}
void query(int now) {
    if (Tree[now].w < ans) return;
    bool flag = true;
    for (int i = 0; i < 3; ++ i) {
        if (pos[i][0] > Tree[now].mn[i] || Tree[now].mx[i] > pos[i][1]) {
            flag = false;
        }
    }
    if (flag) {
        ans = max(ans, Tree[now].w);
        return;
    }
    flag = 1;
    for (int i = 0; i < 3; ++ i) {
        if (p[now].d[i] < pos[i][0] || pos[i][1] < p[now].d[i]) {
            flag = 0;
        }
    }
    if (flag) {
        ans = max(ans, p[now].w);
    }
    if (lson && check(lson)) query(lson);
    if (rson && check(rson)) query(rson);
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; ++ i) {
        L[i] = las[a[i]];
        las[a[i]] = i;
    }
    for (int i = 1; i <= n; ++ i) {
        las[i] = n + 1;
    }
    for (int i = n; i > 0; -- i) {
        R[i] = las[a[i]];
        las[a[i]] = i;
    }
    for (int i = 1; i <= n; ++ i) {
        p[i] = node(L[i], R[i], i, a[i]);
    }
    rt = build(1, n, 0);
    while (m --) {
        scanf("%d%d", &l, &r);
        l = (l + ans) % n + 1;
        r = (r + ans) % n + 1;
        if (l > r) {
            swap(l, r);
        }
        ans = 0;
        pos[0][0] = 0;
        pos[0][1] = l - 1;
        pos[1][0] = r + 1;
        pos[1][1] = n + 1;
        pos[2][0] = l;
        pos[2][1] = r;
        query(rt);
        printf("%d\n", ans);
    }
    return 0;
}
