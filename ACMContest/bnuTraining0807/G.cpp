#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
#define N 128
using namespace std;
char s[N][N];
bool vis[N][N], used[N * N];
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
int n, m;
int legal(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < m;
}
vector <int> a, b, gra[N * N];
int linker[N * N];

void dfs(int x, int y) {
	int u = x * m + y;
	vis[x][y] = true;
	if ((x + y) & 1) {
		a.push_back(u);
	}
	else {
		b.push_back(u);
	}
	for (int i = 0; i < 4; ++i) {
		int tx = x + dx[i], ty = y + dy[i];
		if (legal(tx, ty) && s[tx][ty] == '.') {
			int v = tx * m + ty;
			gra[u].push_back(v);
			gra[v].push_back(u);
		}
		if (legal(tx, ty) && s[tx][ty] == '.' && !vis[tx][ty]) {
			dfs(tx, ty);
		}
	}
}

bool hun(int x) {
	for (int i = 0; i < gra[x].size(); ++i) {
		int v = gra[x][i];
		if (!used[v]) {
			used[v] = true;
			if (linker[v] == -1 || hun(linker[v])) {
				linker[v] = x;
				return true;
			}
		}
	}
	return false;
}

bool check(int x, int y) {
	a.clear();
	b.clear();
	memset(linker, -1, sizeof linker);
	for (int i = 0; i < n * m; ++i)
			gra[i].clear();
	dfs(x, y);
	if (a.size() != b.size())
		return true;
	int sum = 0;
	for (int i = 0; i < a.size(); ++i) {
		memset(used, 0, sizeof used);
		if (hun(a[i])) {
			sum++;
		}
	}
	//printf("sum = %d %d\n", sum, a.size());
	return sum < a.size();
	//return a.size() != b.size();
}
int main() {
	while (~scanf("%d%d", &n, &m)) {
		
		memset(vis, 0, sizeof vis);
		
		for (int i = 0; i < n; ++i)
			scanf("%s", s[i]);
		bool flag = false;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (!vis[i][j] && s[i][j] == '.') {
					if (check(i, j)) {
						flag = true;
						i = n;
						//printf("legallegal==%d %d\n", i, j);
						break;
					}
				}
			}
		}
		if (flag) {
			puts("1");
		}
		else {
			puts("2");
		}
	}
	return 0;
}