#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int n;
const int N = 500010;
struct node {
    int l, r, id, ans, op;
}p[N];
bool operator < (const node &A, const node &B) {
    return A.l < B.l || A.l == B.l && A.r < B.r;
}
int hs[N], len_hs;
int C[N];
int getSum(int x) {
    int ret = 0;
    while (x) {
        ret += C[x];
        x -= x & -x;
    }
    return ret;
}
bool cmp(node A, node B) {
    return A.id < B.id;
}
void solve(int l, int r) {
    if (l == r) {
        return;
    }
    int mid = (l + r) >> 1;
    solve(l, mid);
    sort(p + l, p + mid + 1);
    sort(p + mid + 1, p + r + 1);
    len_hs = 1;
    for (int i = l; i <= mid; ++ i) {
        if (p[i].op) hs[len_hs++] = p[i].r;
    }
    sort(hs + 1, hs + len_hs);
    len_hs = unique(hs + 1, hs + len_hs) - hs;
    for (int i = 0; i < len_hs; ++ i) {
        C[i] = 0;
    }
    int pl = l;
    for (int i = mid + 1; i <= r; ++ i) {
        while (pl <= mid && p[pl].l <= p[i].l) {
            if (!p[pl].op) {
                pl++;
                continue;
            }
            int x = lower_bound(hs + 1, hs + len_hs, p[pl].r) - hs;
            for (; x < len_hs; x += x & -x) {
                ++ C[x];
            }
            pl++;
        }
        if (!p[i].op) {
            int x = lower_bound(hs + 1, hs + len_hs, p[i].r) - hs;
            p[i].ans += getSum(len_hs - 1);
            if (x > 0) p[i].ans -= getSum(x - 1);
        }
    }
    sort(p + mid + 1, p + r + 1, cmp);
    solve(mid + 1, r);
}
int main() {
    int x, y;
    char s[2];
    //freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        scanf("%s%d%d", s, &p[i].l, &p[i].r);
        p[i].id = i;
        p[i].op = s[0] == '+';
    }
    solve(1, n);
    sort(p + 1, p + n + 1, cmp);
    for (int i = 1; i <= n; ++ i) {
        if (!p[i].op){
            printf("%d\n", p[i].ans);
        }
    }
    return 0;
}