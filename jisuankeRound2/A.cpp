#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 320;
int n;
int a[128][N][N];
ll ans;
int nw;
void upd(int l, int r, int A[][N], int B[][N]) {
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= n; ++ j) {
            B[i][j] = A[i][j];
        }
    }
    for (int t = l; t <= r; ++ t) {
        for (int i = 1; i <= n; ++ i) {
            if (i == t) continue;
            for (int j = 1; j <= n; ++ j) {
                if (i == j || j == t || B[i][t] == -1 || B[t][j] == -1) continue;
                if (B[i][j] == -1 || B[i][j] > B[i][t] + B[t][j]) {
                    B[i][j] = B[i][t] + B[t][j];
                }
            }
        }
    }
}
void dfs(int l, int r) {
    if (l == r) {
        for (int i = 1; i <= n; ++ i) {
            if (i == l) continue;
            for (int j = 1; j <= n; ++ j) {
                if (i == j || j == l) continue;
                ans += a[nw][i][j];
            }
        }
        return;
    }
    int mid = l + r >> 1;
    upd(l, mid, a[nw], a[nw + 1]);
    nw += 1;
    dfs(mid + 1, r);
    nw -= 1;
    upd(mid + 1, r, a[nw], a[nw + 1]);
    nw += 1;
    dfs(l, mid);
    nw -= 1;
}
int main() {
    scanf("%d", &n);
    ans = nw = 0;
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= n; ++ j) {
            scanf("%d", &a[0][i][j]);
        }
    }
    dfs(1, n);
    cout << ans << endl;
    return 0;
}
