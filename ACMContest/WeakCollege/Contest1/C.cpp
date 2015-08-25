#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;
int R, C, m;
char s[64][64];
int pre[3000];
int deep[3000];
int op[3000];
int cost[3000];
int cls[3000];
queue <int> q;
int x[1010], y[1010];
const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
vector <int> tim[3000];
bool vis[3000];
int f[3000][1024];
int calc(int x, int y) {
	return x * C + y;
}
bool legal(int x, int y) {
	return x >= 0 && x < R && y >= 0 && y < C;
}

int bfs(int st, int st_time) {
	memset(vis, 0, sizeof vis);
	memset(deep, 0, sizeof deep);
	int sid = calc(x[st], y[st]);
	q.push(sid);
	vis[sid] = 1;
	pre[sid] = -1;
	deep[sid] = 0;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		int ux = u / C, uy = u % C;
		for (int i = 0; i < 4; ++ i) {
			int tx = ux + dx[i], ty = uy + dy[i];
			if (!legal(tx, ty) || vis[calc(tx, ty)] || s[tx][ty] == '#') continue;
			 int tid = calc(tx, ty);
			 q.push(tid);
			 vis[tid] = true;
			 pre[tid] = u;
			 deep[tid] = deep[u] + 1;
		}
	}
	int tx = x[st + 1], ty = y[st + 1];
	while (pre[calc(tx, ty)] != -1) {
		tim[calc(tx, ty)].push_back(st_time + deep[calc(tx, ty)]);
		int tmp = pre[calc(tx, ty)];
		tx = tmp / C, ty = tmp % C;
	}
	return st_time + deep[calc(x[st + 1], y[st + 1])];
}
int main()
{
	freopen("in.txt", "r", stdin);
	while (~scanf("%d%d%d", &R, &C, &m)) {
		for (int i = 0; i < R;  ++ i) scanf("%s", s[i]);
		for (int i = 0; i < R * C; ++ i) scanf("%d", &cost[i]);
		for (int i = 0; i < R * C; ++ i) scanf("%d", &op[i]);
		for (int i = 0; i < R * C; ++ i) scanf("%d", &cls[i]);
		for (int i = 0; i < m; ++ i) scanf("%d%d", &x[i], &y[i]);
		for (int i = 0; i < R * C; ++ i) tim[i].clear();
		//x[0] = y[0] = 0;
		tim[calc(x[0],y[0])].push_back(0);
		int ed_time = 0;
		for (int i = 0;  i < m - 1; ++ i) {
			ed_time = bfs(i, ed_time);
		}

		//puts("sdfsag");
		for (int x = 0; x < R * C; ++ x) {
			f[x][0] = op[x] + cls[x];
			//printf("%d--%d\n", x, tim[x].size());
			if (tim[x].size() == 0)
			continue;
			int mn = min(f[x][0] - cost[x] * tim[x][1], -cost[x] * tim[x][0]);
			for (int i = 1; i < tim[x].size(); ++ i) {
				f[x][i] = mn + op[x] + cls[x] + cost[x] * tim[x][i];
				if (i < tim[x].size() - 1)
				mn = min(mn, f[x][i] - cost[x] * tim[x][i+1]);
			}
		}
		//puts("123");
		int ans = 0;
		for (int i = 0; i < R * C; ++ i)
		if (tim[i].size() > 0) {
			//printf("%d\n", f[i][tim[i].size() - 1]);
			ans += f[i][tim[i].size() - 1];
		}
		printf("%d\n", ans);
	}
}
