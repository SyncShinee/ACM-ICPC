#include <cstdio>
#include <queue>
using namespace std;
int p[512], f[512], n;
char a[512][512], s[8];
priority_queue<int> cap[512];
bool vis[512];
int gf(int x) {
	if (x == f[x])
		return x;
	return f[x] = gf(f[x]);
}
int merge(int x, int y) {
	int i = gf(x), j = gf(y);
	f[i] = j;
	f[x] = j;
}
int dfs(int x) {
	vis[x] = true;
	for (int i = 1; i <= n; ++i)
		if (a[x][i] == '1' && !vis[i]) {
			merge(x, i);
			dfs(i);
		}
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &p[i]);
		f[i] = i;
	}
	gets(s);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j)
			scanf("%c", &a[i][j]);
		gets(s);
	}
	for (int i = 1; i <= n; ++i) {
		if (!vis[i])
			dfs(i);
	}
	for (int i = 1; i <= n; ++i)
		cap[gf(i)].push(-p[i]);
	for (int i = 1; i <= n; ++i) {
		p[i] = -cap[gf(i)].top();
		cap[gf(i)].pop();
	}
	for (int i = 1; i <= n; ++i)
		printf("%d%c", p[i], i == n ? '\n' : ' ');
	return 0;
}