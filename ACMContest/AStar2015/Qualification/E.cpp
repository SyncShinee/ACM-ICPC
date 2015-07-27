#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
int n, m, k;
struct node {
	int x, y;
}u, tmp;
queue<node> q;
int movex[8][2] = {1,  2,  1,  1,  0, -1, -1, -2, -1,  1, -1,  2,  0, -1,  1, -2},
	movey[8][2] = {0,  1, -1,  2, -1,  2, -1,  1,  0, -2,  1, -1,  1, -2,  1, -1};
bool vis[1024][1024];
int f[1024][1024][2];

bool legal(node tt) {
	if (tt.x < 1 || tt.x > n || tt.y < 1 || tt.y > m)
		return false;
	return true;
}

void bfs(int sx, int sy, int fl) {
	u.x = sx;
	u.y = sy;
	q.push(u);
	memset(vis, 0, sizeof(vis));
	vis[sx][sy] = true;
	f[sx][sy][fl] = 0;
	while (!q.empty()) {
		u = q.front();
		q.pop();
		for (int i = 0; i < 8; ++i) {
			tmp.x = u.x + movex[i][fl];
			tmp.y = u.y + movey[i][fl];
			if (!legal(tmp))
				continue;
			if (!vis[tmp.x][tmp.y]) {
				f[tmp.x][tmp.y][fl] = f[u.x][u.y][fl] + 1;
				vis[tmp.x][tmp.y] = true;
				q.push(tmp);
			}
		}
	}
}

int main() {
	int T, xk, yk, xn, yn;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		scanf("%d%d%d", &n, &m, &k);
		scanf("%d%d%d%d", &xk, &yk, &xn, &yn);
		printf("Case #%d:\n", cas);
		memset(f, -1, sizeof(f));
		bfs(xk, yk, 0);
		/*for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <=m; ++j)
				printf("%d", vis[i][j]);
			printf("\n");
		}*/
		bfs(xn, yn, 1);
		/*for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <=m; ++j)
				printf("%d", vis[i][j]);
			printf("\n");
		}*/
		int ans = k+1;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j) {
				if (f[i][j][0] == -1 || f[i][j][1] == -1)
					continue;
				if (f[i][j][0] <= f[i][j][1]) {
					if (f[i][j][0] == 0 && f[i][j][1] == 1) {
						ans = min(ans, 3);
					}
					else {
						ans = min(ans, f[i][j][1]);
					}
				}
				else if (f[i][j][0] > f[i][j][1]) {
					if ((f[i][j][0] - f[i][j][1]) & 1)
						ans = min(ans, f[i][j][0] + 1);
					else
						ans = min(ans, f[i][j][0]);
				}
				//printf("%d %d %d %d %d\n", i, j, ans, f[i][j][0], f[i][j][1]);
			}
		if (ans <= k) {
			printf("%d\n", ans);
		}
		else {
			printf("OH,NO!\n");
		}
	}
	return 0;
}