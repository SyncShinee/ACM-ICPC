#pragma comment(linker, "/STACK:102400000000,102400000000")
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1
using namespace std;
const int N = 100010;
struct Edge {
    int to, val;
    Edge(int _t = 0, int _v = 0) : to(_t), val(_v) {}
};
vector <Edge> G[N];
int n, num;
int LOG[N << 1], euler[N << 1], point[N << 1], ins[N], dis[N], st[N << 1][20];
int LCA(int x, int y) {
    x = ins[x], y = ins[y];
    if (x > y) swap(x, y);
    int len = y - x + 1;
    int pos = min(st[x][LOG[len]], st[y - (1 << LOG[len]) + 1][LOG[len]]);
    return point[pos];
}
int dist(int x, int y) {
    //printf("%d---", LCA(x, y));
    return dis[x] + dis[y] - 2 * dis[LCA(x, y)];
}
void dfs(int x, int pre, int value) {
    ins[x] = ++ num;
    euler[num] = ins[x];
    point[ins[x]] = x;
    dis[x] = value;
    for (int i = 0; i < G[x].size(); ++ i) {
        int v = G[x][i].to;
        if (v == pre) continue;
        dfs(v, x, value + G[x][i].val);
        euler[++ num] = ins[x];
    }
}

struct Point {
    int x, y;
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
}T[N << 2];

Point pushup(const Point &A, const Point &B) {
    Point ret = A;
    if (dist(ret.x, ret.y) < dist(B.x, B.y)) {
        ret = B;
    }
    if (dist(ret.x, ret.y) < dist(A.x, B.x)) {
        ret = Point(A.x, B.x);
    }
    if (dist(ret.x, ret.y) < dist(A.y, B.x)) {
        ret = Point(A.y, B.x);
    }
    if (dist(ret.x, ret.y) < dist(A.x, B.y)) {
        ret = Point(A.x, B.y);
    }
    if (dist(ret.x, ret.y) < dist(A.y, B.y)) {
        ret = Point(A.y, B.y);
    }
    return ret;
} 

void build(int l, int r, int rt) {
    if (l == r) {
        T[rt].x = T[rt].y = l;
        return;
    }
    int mid = l + r >> 1;
    build(lson);
    build(rson);
    T[rt] = pushup(T[rt << 1], T[rt << 1 | 1]);
}

Point query(int L, int R, int l, int r, int rt) {
    if (L <= l && r <= R) {
        return T[rt];
    }
    int mid = l + r >> 1;
    if (R <= mid) return query(L, R, lson);
    if (L > mid) return query(L, R, rson);
    return pushup(query(L, R, lson), query(L, R, rson));
}

int main() {
    int x, y, z, q, a, b;
    scanf("%d", &n);
    LOG[0] = LOG[1] = num = 0;
    for (int i = 2; i < n + n; ++ i) LOG[i] = LOG[i >> 1] + 1; 
    for (int i = 1; i < n; ++ i) {
        scanf("%d%d%d", &x, &y, &z);
        G[x].push_back(Edge(y, z));
        G[y].push_back(Edge(x, z));
    }
    dfs(1, 0, 0);
    for (int i = 1; i <= num; ++ i) {
        st[i][0] = euler[i];
    }
    for (int j = 1; (1 << j) <= num; ++ j) {
        for (int i = 1; i + (1 << j) - 1 <= num; ++ i) {
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
    build(1, n, 1);
    scanf("%d", &q);
    while (q --) {
        scanf("%d%d%d%d", &x, &y, &a, &b);
        Point p1 = query(x, y, 1, n, 1);
        Point p2 = query(a, b, 1, n, 1);
        //printf("%d %d %d %d\n", p1.x, p1.y, p2.x, p2.y);
        //printf("%d %d %d %d\n",dist(p1.x, p2.x), dist(p1.y, p2.y),dist(p1.y, p2.x), dist(p1.x, p2.y));
        printf("%d\n", max(max(dist(p1.x, p2.x), dist(p1.y, p2.y)), max(dist(p1.y, p2.x), dist(p1.x, p2.y))));
    }
    return 0;
}
