#pragma comment(linker, "/STACK:102400000000,102400000000")
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
const int N = 100010;
ll C[N << 1];
vector <int> G[N];
ll v[N];
int n, m;
int num;
int ins[N], out[N];

void get_inout(int x, int pre) { 
    ins[x] = ++ num;
    C[ins[x]] = v[x];
    for (int i = 0; i < G[x].size(); ++ i) {
        if (G[x][i] == pre) continue;
        get_inout(G[x][i], x);
    }
    out[x] = ++ num;
    C[out[x]] = -v[x];
}
struct node {
    ll val, tag;
}T[N << 3];
void pushup(int rt) {
    T[rt].val = max(T[rt << 1].val, T[rt << 1 | 1].val);
    T[rt].tag = 0;
}
void pushdown(int rt) {
    T[rt << 1].val += T[rt].tag;
    T[rt << 1 | 1].val += T[rt].tag;
    T[rt << 1].tag += T[rt].tag;
    T[rt << 1 | 1].tag += T[rt].tag;
    T[rt].tag = 0;
}
void build(int l, int r, int rt) {
    if (l == r) {
        T[rt].val = C[l];
        T[rt].tag = 0;
        return;
    }
    int mid = l + r >> 1;
    build(lson);
    build(rson);
    pushup(rt);
}
void update(int lr, int rr, ll tt, int l, int r, int rt) {
    //printf("%d %d\n", l, r);
    if (lr <= l && r <= rr) {
        T[rt].val += tt;
        T[rt].tag += tt;
        return;
    }
    if (T[rt].tag) pushdown(rt);
    int mid = l + r >> 1;
    if (lr <= mid) {
        update(lr, rr, tt, lson);
    }
    if (rr >= mid + 1) {
        update(lr, rr, tt, rson);
    }
    pushup(rt);
}
ll query(int lr, int rr, int l, int r, int rt) {
    //printf("%d %d\n", l, r);
    if (lr <= l && r <= rr) {
        return T[rt].val;
    }
    if (T[rt].tag) pushdown(rt);
    int mid = l + r >> 1;
    if (rr <= mid) return query(lr, rr, lson);
    if (lr >= mid + 1) return query(lr, rr, rson);
    return max(query(lr, rr, lson), query(lr, rr, rson));
}
int main() {
    int T, x, y;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++ cas) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++ i) {
            G[i].clear();
        }
        for (int i = 1; i < n; ++ i) {
            scanf("%d%d", &x, &y);
            G[x].push_back(y);
            G[y].push_back(x);
        }
        for (int i = 0; i < n; ++ i) {
            scanf("%lld", &v[i]);
        }
        num = 0;
        get_inout(0, -1);
        for (int i = 1; i <= num; ++ i) {
            C[i] += C[i - 1];
        }
        build(1, num, 1);
        printf("Case #%d:\n", cas);
        while (m --) {
            int type, x, y;
            scanf("%d%d", &type, &x);
            if (type == 1) {
                printf("%lld\n", query(ins[x], out[x] - 1, 1, num, 1));
            } else {
                scanf("%d", &y);
                ll dis = y - v[x];
                v[x] = y;
                update(ins[x], out[x] - 1, dis, 1, num, 1);
            }
        }
    }
    return 0;
}
