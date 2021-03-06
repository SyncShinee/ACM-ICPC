#include <cstdio>
#include <algorithm>
#include <cstring>
#define N 100010
#define M 16
#define BLOCK_SIZE 317
using namespace std;

int n, m, q;
char direct[N][M];
pair<int,int> dst[N][M];

pair<int,int> dfs(int x, int y, int limit) {
	if (x < limit || x > n || y <= 0 || y > m)
		return make_pair(x, y);
	if (direct[x][y] == '^') {
		if (x == limit)
			return make_pair(x-1, y);
		else
			return dst[x-1][y];
	}
	if (direct[x][y] == '<') {
		if (y > 1 && direct[x][y - 1] == '>')
			return make_pair(-1, -1);
		return dfs(x, y - 1, limit);
	}
	if (direct[x][y] == '>') {
		if (y < m && direct[x][y + 1] == '<')
			return make_pair(-1, -1);
		return dfs(x, y + 1, limit);
	}
}

void update_block(int base) {
	for (int i = base; i < min(base + BLOCK_SIZE, n + 1); ++i) {
		for (int j = 1; j <= m; ++j) {
			dst[i][j] = dfs(i, j, base);
		}
	}
}

void query(int x,int y) {
	while (x > 0 && x <= n && y > 0 && y <= m) {
		pair<int,int> t = dst[x][y];
		x = t.first;
		y = t.second;
	}
	printf("%d %d\n", x, y);
}

int main() {
	//freopen("in.txt","r",stdin);
	char opt[2], ch[2];
	int x, y;
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", direct[i] + 1);
	}
	for (int i = 1; i <= n; i += BLOCK_SIZE) {
		update_block(i);
	}
	while (q--) {
		scanf("%s%d%d", opt, &x, &y);
		if (opt[0] == 'A') {
			query(x, y);
		} else {
			scanf("%s", ch);
			direct[x][y] = ch[0];
			update_block((x - 1) / BLOCK_SIZE * BLOCK_SIZE + 1);
		}
	}
	return 0;
}