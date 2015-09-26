#include <cstdio>
#include <algorithm>
#include <cstring>
#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1
using namespace std;
const int N = 20010, M = 200010, INF = 1e9 + 10;
struct edge {
    int to, nxt, val;
}e[N << 1];
struct Edge {
    int u, v, w, tag;
}E[M];
bool operator < (const Edge &A, const Edge &B) {
    return A.w < B.w;
}
int head[N], n, m, side, pos;
void build(int x, int y, int z) {
    e[side].to =y;
    e[side].val = z;
    e[side].nxt = head[x];
    head[x] = side ++;
}

int deep[N], fa[N], subtree_size[N], son[N], top[N], edge_p[N], fedge_p[N], ans;
int edge_v[N], son_v[N], mn[N];
struct tnode {
    int val, tag;
}seg[N << 2];

void dfs1(int x, int pre) {
    deep[x] = deep[pre] + 1;
    fa[x] = pre;
    subtree_size[x] = 1;
    for (int i = head[x]; ~i; i = e[i].nxt) {
        if (e[i].to == pre) continue;
        dfs1(e[i].to, x);
        subtree_size[x] += subtree_size[e[i].to];
        if (son[x] == -1 || subtree_size[son[x]] < subtree_size[e[i].to]) {
            son[x] = e[i].to;
            son_v[x] = e[i].val;
        }
    }
}

void get_pos(int x, int pre, int value) {
    top[x] = pre;
    if (son[x] != -1) {
        edge_p[x] = pos ++;
        fedge_p[edge_p[x]] = x;
        edge_v[x] = value;
        get_pos(son[x], pre, son_v[x]);
    }
    else {
        edge_p[x] = pos ++;
        fedge_p[edge_p[x]] = x;
        edge_v[x] = value;
        return;
    }
    for (int i = head[x]; ~i; i = e[i].nxt) {
        if (e[i].to == son[x] || e[i].to == fa[x]) continue;
        get_pos(e[i].to, e[i].to, e[i].val);
    }
}

void pushUp(int rt) {
    seg[rt].val = seg[rt << 1].val + seg[rt << 1 | 1].val;
}

void pushDown(int rt, int l, int r) {
    if (seg[rt].tag != 0) {
        int m = (r + l) / 2;
        seg[rt << 1].tag += seg[rt].tag;
        seg[rt << 1].val += seg[rt].tag * (m - l + 1);

        seg[rt << 1 | 1].tag += seg[rt].tag;
        seg[rt << 1 | 1].val += seg[rt].tag * (r - m);
        seg[rt].tag = 0;
    }
}

void buildT(int l, int r, int rt) {
    seg[rt].tag = 0;
    if (l == r) {
        seg[rt].val = 0;
        return;
    }
    int mid = (l + r) >> 1;
    buildT(lson);
    buildT(rson);
    pushUp(rt);
}

void update(int la, int ra, int l, int r, int rt, int value) {
    if (la <= l && r <= ra) {
        seg[rt].val += value * (r - l + 1); 
        seg[rt].tag += value;
        return;
    }
    pushDown(rt,l,r);
    int mid = (l + r) >> 1;
    if (la <= mid) update(la, ra, lson, value);
    if (mid < ra) update(la, ra, rson, value);
    pushUp(rt);
}

void get_min(int l, int r, int rt) {
    if (l == r) {
        mn[l] = seg[rt].val;
        return ;
    }
    pushDown(rt,l,r);
    int mid = (l + r) >> 1;
    get_min(lson);
    get_min(rson);
}

void modify(int u, int v, int val) {
    int f1 = top[u], f2 = top[v];
    while (f1 != f2) {
        if (deep[f1] < deep[f2]) {
            swap(f1, f2);
            swap(u, v);
        }
        update(edge_p[f1], edge_p[u], 1, pos, 1, val);
        u = fa[f1];
        f1 = top[u];
    }
    if (u == v) return;
    if (deep[u] > deep[v]) swap(u, v);
    update(edge_p[son[u]], edge_p[v], 1, pos, 1, val);
}

int main() {
    int T;
    freopen("in.txt", "r", stdin);
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++ cas) {
        scanf("%d%d", &n, &m);
        memset(head, -1, sizeof head);
        side = 0;
        for (int i = 0; i < m; ++ i){
            scanf("%d%d", &E[i].u, &E[i].v);
            E[i].tag = i < (n - 1);
            if (i < n - 1) {
                build(E[i].u, E[i].v, 1);
                build(E[i].v, E[i].u, 1);
            }
        }
        memset(son, -1, sizeof son);
        deep[0] = -1;
        pos = 0;
        dfs1(1, 0);
        get_pos(1, 0, INF);
        pos --;
        buildT(1, pos, 1);
        for (int i = m - 1; i >= 0; -- i) {
            if (!E[i].tag) {
                modify(E[i].u, E[i].v, 1);
            }
        }
        get_min(1, pos, 1);
        ans = INF;
        for (int i = 1; i <= pos; ++ i) {
            ans = min(ans, mn[i] + 1);
        }
        printf("Case #%d: %d\n", cas, ans);
    }
    return 0;
}