#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <queue>
#define N 128
#define DEBUG 1
using namespace std;
typedef long long ll;
char s[N][N];
int n, m;
int f[N][N][128];

int dfs(int x, int y, char ch) {
	if (ch == '^' && x == 0)
		return 0;
	else if (ch == 'v' && x == n-1) {
		return 0;
	} 
	else if (ch == '>' && y == m-1) {
		return 0;
	}
	else if (ch == '<' && y == 0)
		return 0;
	if (ch == '^' && s[x-1][y] != '.')
		return 1;
	if (ch == 'v' && s[x+1][y] != '.')
		return 1;
	if (ch == '<' && s[x][y-1] != '.')
		return 1;
	if (ch == '>' && s[x][y+1] != '.')
		return 1;
	if (ch == '^')
		return dfs(x-1, y, '^');
	if (ch == 'v')
		return dfs(x+1, y, 'v');
	if (ch == '<')
		return dfs(x, y-1, '<');
	if (ch == '>' )
		return dfs(x, y+1, '>');
}

int stress(int x, int y) {
	if (dfs(x, y, s[x][y])) {
		return 0;
	}
	//printf("111\n");
	if (dfs(x, y, '^')) {
		return 1;
	}

	if (dfs(x, y, 'v')) {
		return 1;
	}
	if (dfs(x, y, '<')) {
		return 1;
	}
	if (dfs(x, y, '>')) {
		return 1;
	}
	return -1;
}



int solve() {
	int ret = 0;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j) {
			int t = 0;
			if (s[i][j] != '.') {
				t = stress(i, j);
			}
			if (t == -1)
				return -1;
			ret += t;
			//printf("%d\n", ret);
		}
	return ret;
}

void init() {
	int T;
	freopen("A-large.in", "r", stdin);
	freopen("A.out", "w", stdout);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		scanf("%d %d", &n, &m);gets(s[0]);
		for (int i = 0; i < n; ++i) {
			gets(s[i]);
		}
		if (solve() > -1)
		printf("Case #%d: %d\n", cas, solve());
	else 
		printf("Case #%d: IMPOSSIBLE\n", cas);
	}
}

int main() {
	init();
}