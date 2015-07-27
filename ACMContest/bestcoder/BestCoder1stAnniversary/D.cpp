#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
#include <cmath>
#include <bitset>
#include <iostream>
using namespace std;
struct node {
	int a, b;
	friend bool operator < (node x, node y) {
		return abs(x.a - x.b) > abs(y.a - y.b);
	} 
}p[10010];
vector <int> gra[10010];
int n, m, xa, xb, len, x, y;
bool vis[10010];
void dfs(int x, int sign) {
	vis[x] = true;
	if (sign == 0) {
		xa ++;
	}
	else {
		xb++;
	}
	for (int i = 0; i < gra[x].size(); ++i) {
		if (vis[gra[x][i]])
			continue;
		dfs(gra[x][i], 1 - sign);
	}
}
bitset <10010> f[2];
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		memset(vis, 0, sizeof vis);
		for (int i = 1; i <= n; ++i) {
			gra[i].clear();
		}
		for (int i = 0; i < m; ++i) {
			scanf("%d%d", &x, &y);
			gra[x].push_back(y);
			gra[y].push_back(x);
		}
		len = 0;
		for (int i = 1; i <= n; ++i) {
			if (!vis[i]) {
				xa = xb = 0;
				dfs(i, 0);
				p[len].a = xa;
				p[len++].b = xb;
			}
		}
		f[1].reset();
		f[1].set(0);
		for (int i = 0; i < len; ++i) {
			f[i & 1].reset();
			f[i & 1] |= f[(i-1) & 1] << p[i].a;
			f[i & 1] |= f[(i-1) & 1] << p[i].b;
		}
		int ans = n / 2;
		while (ans > 0 && !f[(len-1) & 1].test(ans)) {
			ans--;
		}
		printf("%d\n", ans * (n - ans) - m);
	}
	return 0;
}