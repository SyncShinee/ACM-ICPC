#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#define MOD 1000000007
using namespace std;
int n, color[100010], len, start;
typedef long long ll;
ll ans, num[100010];
bool vis[100010];
vector<int> gra[100010];
void build(int x, int y) {
	gra[x].push_back(y);
	gra[y].push_back(x);
}
void dfs(int x, int length) {
	vis[x] = true;
	if (color[x] == 1 && length != 0) {
		num[len++] = length;
		for (int i = 0; i < gra[x].size(); ++i) {
			if (!vis[gra[x][i]]) {
				dfs(gra[x][i], 1);
			}
		}
	}
	else
		for (int i = 0; i < gra[x].size(); ++i) {
			if(!vis[gra[x][i]])
				dfs(gra[x][i], length+1);
		}
}
int main() {
	len = 0;
	int tmp;
	scanf("%d", &n);
	for (int i = 1; i < n; ++i) {
		scanf("%d", &tmp);
		build(i, tmp);
		build(tmp, i);
	}
	start = -1;
	for (int i = 0; i < n; ++i) {
		scanf("%d", &color[i]);
		if (color[i] == 1)
			start = i;
	}

	if (start == -1)
		printf("0\n");
	else {
		dfs(start, 0);
	}
	ans = 1;
	for (int i = 0; i < len; ++i)
		ans = (ans * num[i]) % MOD;
	printf("%d\n", ans);
	return 0;
}