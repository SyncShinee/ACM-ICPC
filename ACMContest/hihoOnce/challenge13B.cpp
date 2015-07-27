#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
int v[128][128], mv, x, y, n;
vector <int> gra[128];
int dfs(int x, int pre) {
	if (pre != -1) {
		for (int i = 0; i <= mv; ++i) {
			v[x][i] = v[pre][i];
		}
		v[x][++mv] = 1;
	}
	for (int i = 0; i < gra[x].size(); ++i) {
		if (gra[x][i] == pre)
			continue;
		dfs(gra[x][i], x);
	}
}

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i < n; ++i) {
		scanf("%d%d", &x, &y);
		gra[x].push_back(y);
		gra[y].push_back(x);
	}
	mv = -1;
	dfs(0, -1);
	printf("%d\n", mv + 1);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j <= mv; ++j) {
			printf("%d%c", v[i][j], j == mv ? '\n' : ' ');
		}
	}
	return 0;
}