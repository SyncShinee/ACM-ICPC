#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include <ctype.h>
#include <limits.h>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include <set>
#include <bitset>
#define CLR(a) memset(a, 0, sizeof(a))
#define REP(i, a, b) for(int i = a;i < b;i++)
#define REP_D(i, a, b) for(int i = a;i <= b;i++)

using namespace std;

const int maxn = 1e4 + 100;
const int MOD = 21092013;

vector<int> G[maxn];

int n, a[maxn], dp[maxn][2];
int L[maxn],R[maxn],f[maxn],ans[64];

void dfs_dp(int u, int fa)
{
    int have_one =a[u], have_two = a[u];
    dp[u][0] = 0;
    REP(i, 0, G[u].size())
    {
        int v = G[u][i];
        if(v!=fa)
        {
            dfs_dp(v, u);
            have_two = (have_two + 1ll * have_one*dp[v][1]%MOD)%MOD;
            have_one = (have_one + 1ll * dp[v][1]*a[u]%MOD)%MOD;

            dp[u][0] = (dp[u][0]+dp[v][0])%MOD;
        }
    }
    dp[u][1] = have_one;
    dp[u][0] = (dp[u][0]+ have_two)%MOD;
}

int main() {
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
	int T;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
            G[i].clear();
		for (int i = 1; i < n; ++i) {
                int x,y;
			scanf("%d%d", &x, &y);
			G[x].push_back(y);
			G[y].push_back(x);
		}
		for (int i = 1; i <= n; ++ i)
			scanf("%d", &L[i]);
		for (int i = 1; i <= n; ++ i)
			scanf("%d", &R[i]);
		for (int g = 1; g <= 50; ++g) {
			for (int i = 1; i <= n; ++i)
				a[i] = R[i] / g - (L[i] - 1) / g;
			dfs_dp(1, 0);
			f[g] = dp[1][0];
		}
		for (int i = 50; i > 0; --i) {
			ans[i] = f[i];
			for (int j = 2 * i; j <= 50; j += i)
				ans[i] = ((ans[i] - ans[j]) % MOD + MOD) % MOD;
		}
		printf("Case %d:\n", cas);
		for (int i = 1; i <= 50; ++i)
			printf("%d: %d\n",i, ans[i]);
	}
}