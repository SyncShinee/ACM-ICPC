#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;

typedef long long LL;
const int N = 1e5 + 5;
const int D = 18;
const int P = 998244353;

struct Inter {
    int x, l, r, id;

    int operator < (const Inter &a) const {
        if (x != a.x) return x < a.x;
        return id < a.id;
    }
}qq[N * 25];
    
int rmq[D][N], LOG[N];
int tree[2][N];
int f[N], g[N];

int getgcd(int l, int r) {
    int s = LOG[r - l + 1];
    return __gcd(rmq[s][l], rmq[s][r - (1 << s) + 1]);
}

int n;

pair<int, int> fmx(pair<int, int> a, pair<int, int> b) {
    if (a.first > b.first) return a;
    else if (a.first < b.first) return b;
    return make_pair(a.first, (a.second + b.second) % P);
}

int addmx(int x, int s) {
    ++x;
    while (x <= n + 1) {
        //assert(x > 0 && x <= n + 1);
        tree[0][x] = max(tree[0][x], s);
        x += x & -x;
    }
}

int findmx(int x) {
    ++x;
    int ans = 0;
    while (x > 0) {
        ans = max(tree[0][x], ans);
        x -= x & -x;
    } 
    return ans; 
}

void updata(int &x, int y) {
    x += y;
    if (x >= P) x -= P;
}

void add(int x, int s, int t) {
    if (t == 1) s = (LL)s * x % P;
    ++x;
    while (x <= n + 1) {
        updata(tree[t][x], s);
        x += x & -x;
    }
}

int find(int x, int tree[]) {
    ++x;
    int ans = 0;
    while (x > 0) {
        updata(ans, tree[x]);
        x -= x & -x;
    }
    return ans;
}

void clean(int x, int tree[]) {
    ++x;
    while (x <= n + 1) {
        tree[x] = 0;
        x += x & -x;
    }
}

void solve(pair<int, int> &ans, int l, int r) {
    // printf("!%d %d\n", l, r);
    for (int i = l; i <= r; ++i) {
        int t = findmx(qq[i].r) + 1;
        f[qq[i].id] = t;
        addmx(qq[i].id, t);
    }
    for (int i = l; i <= r; ++i) {
        clean(qq[i].id, tree[0]);
        clean(qq[i].id, tree[1]);
    }
    //int flag = 1;
   // add(0, 1, 0);
    for (int i = l, j = l; i <= r; ++i) {
        while (j < i && f[qq[j].id] < f[qq[i].id] - 1) {
            add(qq[j].id, P - g[qq[j].id], 0);
            add(qq[j].id, P - g[qq[j].id], 1);
            ++j;
        }
        //if (f[qq[i].id] > 1 && flag) {
        //    add(0, P - 1, 0);
        //    flag = 0;
        //}
        if (f[qq[i].id] == 1) {
            g[qq[i].id] = qq[i].r - qq[i].l + 1;
            add(qq[i].id, g[qq[i].id], 0);
            add(qq[i].id, g[qq[i].id], 1);
            continue;
        }
        int L = qq[i].l, R = qq[i].r;
        int tmp = (LL)(R - L + 1) * find(L, tree[0]) % P;
        int res = ((LL)find(L, tree[1]) - find(R, tree[1]) + P) % P;
        res += ((LL)find(R, tree[0]) - find(L, tree[0])) * (R + 1) % P;
        if (res < 0) res += P;
        if (res >= P) res -= P;
        g[qq[i].id] = (res + tmp) % P;
        add(qq[i].id, g[qq[i].id], 0);
        add(qq[i].id, g[qq[i].id], 1);
    }
    for (int i = l; i <= r; ++i) {
        clean(qq[i].id, tree[0]);
        clean(qq[i].id, tree[1]);
        printf("--%d-- ", g[qq[i].id]);
        ans = fmx(ans, make_pair(f[qq[i].id], g[qq[i].id]));
    }
    //ans = fmx(ans, make_pair(f[qq[r].id], g[qq[r].id]));
    printf("debug ---%d %d %d %d\n", qq[r].x, qq[r].id, f[qq[r].id], g[qq[r].id]);
    clean(0, tree[0]);
}

int main() {
    freopen("in.txt", "r", stdin);
    freopen("stdout.txt", "w", stdout);
    for (int i = 0; 1 << i < N; ++i)
        LOG[1 << i] = i;
    for (int i = 2; i < N; ++i)
        if (!LOG[i]) LOG[i] = LOG[i - 1]; 
    while (scanf("%d", &n) == 1) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &rmq[0][i]);
        }
        for (int j = 1; j < D; ++j)
            for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
                int p = i + (1 << j - 1);
                rmq[j][i] = __gcd(rmq[j - 1][i], rmq[j - 1][p]);
            }
        int r = 0;
        for (int i = 1; i <= n; ++i) {
            int x = i;
            while (x > 0) {
                int p = getgcd(x, i);
                int y;
                if (getgcd(1, i) == p) y = 1;
                else {
                    int head = 1, tail = x;
                    while (head < tail - 1) {
                        int mid = (head + tail) >> 1;
                        if (getgcd(mid, i) == p) tail = mid;
                        else head = mid;
                    }
                    y = tail;
                }
                qq[r++] = (Inter){p, y - 1, x - 1, i};
                x = y - 1;
            }
        }
        sort(qq, qq + r);
        pair<int, int> ans = make_pair(0, 1);
        for (int i = 0; i < r; ++i) {
            int j = i;
            while (j + 1 < r && qq[j + 1].x == qq[j].x)
                ++j;
            solve(ans, i, j);
            i = j;
        }
        printf("%d %d\n", ans.first, ans.second);
    }
    return 0;
}