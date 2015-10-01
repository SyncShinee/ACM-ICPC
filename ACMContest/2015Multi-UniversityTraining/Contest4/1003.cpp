#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
using namespace std;
const int N = 100010;
struct edge {
    int to, nxt;
}e[N << 1];
int head[N], side, n, b[N];
void build(int x, int y) {
    e[side].to = y;
    e[side].nxt = head[x];
    head[x] = side ++;
}

int f[N];
int gf(int x) {
    return x == f[x] ? x : x = gf(f[x]);
}
void merge(int x, int y) {
    int i = gf(x), j = gf(y);
    f[i] = j;
    f[x] = j;
}
bool judge(int x, int y) {
    return gf(x) == gf(y);
}

int len_cir, cir[N], subtree_size[N];
bool in_cir[N];

int num[N], sum[N], sum_cir[N], num_cir[N];

void dfs(int x, int pre) {
    subtree_size[x] = 1;
    for (int i = head[x]; ~i; i = e[i].nxt) {
        if (e[i].to == pre || in_cir[e[i].to]) continue;
        dfs(e[i].to, x);
        subtree_size[x] += subtree_size[e[i].to];
    }
}
int main() {
    freopen("in.txt", "r", stdin);
    while (~scanf("%d", &n)) {
        memset(head, -1, sizeof head);
        side = 0;
        memset(num, 0, sizeof num);
        memset(sum, 0, sizeof sum);
        memset(in_cir, 0, sizeof in_cir);
        len_cir = 0;
        for (int i = 1; i <= n; ++ i) f[i] = i;
        for (int i = 1; i <= n; ++ i) {
            scanf("%d", &b[i]);
            build(b[i], i);
            build(i, b[i]);
            if (!judge(b[i], i)) {
                merge(b[i], i);
            }
            else {
                in_cir[i] = true;
                cir[len_cir ++] = i;
            }
        }
        int Next = b[cir[0]];
        while (Next != cir[0]) {
            cir[len_cir ++] = Next;
            in_cir[Next] = true;
            Next = b[Next];
        }
        for (int i = 1; i <= n; ++ i) {
            if (in_cir[i]) {
                dfs(i, -1);
            }
        }
        for (int i = 1; i <= n; ++ i) {
            if (!in_cir[i]) num[subtree_size[i]] ++;
        }
        for (int j = 1; j <= n; ++ j) {
            for (int i = j; i <= n; i += j) {
                sum[j] += num[i];
            }
        }
        int ans = 0;
        for (int k = 1; k <= n; ++ k) {
            for (int i = 0; i <= k; ++ i) num_cir[i] = 0;
            bool flag = false;
            if (n % k) continue;
            sum_cir[0] = subtree_size[0] % k;
            num_cir[sum_cir[0]] ++;
            for (int i = 1; i < len_cir; ++ i) {
                sum_cir[i] = (sum_cir[i - 1] + subtree_size[cir[i]]) % k;
                num_cir[sum_cir[i]] ++;
            }
            int tmp = sum_cir[len_cir - 1];
            for (int i = 0; i < len_cir; ++ i) {
                if (num_cir[tmp] + sum[k] == n / k) {
                    flag = true;
                    break;
                }
                tmp = (tmp + subtree_size[cir[i]]) % k;
            }
            ans += flag;
        }
        printf("%d\n", ans);
    }
    return 0;
}