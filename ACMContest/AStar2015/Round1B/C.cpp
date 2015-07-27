#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#define EPS 1e-9
#define N 1024
using namespace std;
typedef long long ll;
int n, m, num;
struct node {
	int x, y;
}tmp, u, jj;
queue<node> q;
int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};
int j1x[4] = {1,1,-1,-1};
int j1y[4] = {1,1,1,-1};
int j2x[4] = {1,-1,-1,1};
int j2y[4] = {-1,1,-1,-1};

bool legal(node tt) {
	if (tt.x < 1 || tt.x > n || tt.y < 1 || tt.y > m)
		return false;
	return true;
}
bool vis[N][N];
int main() {
	int T;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		memset(vis, 0, sizeof(vis));
		scanf("%d%d", &n, &m);
		scanf("%d", &num);
		for (int i = 0; i < num; ++i) {
			scanf("%d%d", &tmp.x, &tmp.y);
			if (!vis[tmp.x][tmp.y]) {
				q.push(tmp);
				vis[tmp.x][tmp.y] = 1;
			}
		}
		while (!q.empty()) {
			u = q.front();
			q.pop();
			for (int i = 0; i < 4; ++i) {
				tmp.x = u.x + dx[i];
				tmp.y = u.y + dy[i];
				if (legal(tmp)) {
					if (vis[tmp.x][tmp.y])
						continue;
					jj.x = u.x + j1x[i];
					jj.y = u.y + j1y[i];
					if (legal(jj) && vis[jj.x][jj.y]) {
						q.push(tmp);
						vis[tmp.x][tmp.y] = true;
						continue; 
					}
					jj.x = u.x + j2x[i];
					jj.y = u.y + j2y[i];
					if (legal(jj) && vis[jj.x][jj.y]) {
						q.push(tmp);
						vis[tmp.x][tmp.y] = true;
					}
				}
			}
		}
		int ans = 0;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				if (vis[i][j])
					ans++;
		printf("Case #%d:\n%d\n", cas, ans);

	}
	return 0;
}