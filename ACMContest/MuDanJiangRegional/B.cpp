#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
vector<int> gra[200010];
int prex[200010], prey[200010], n, deep[200010];
bool vis[200010];
queue<int> q;
void init() {
	for (int i = 1; i <= n; ++i) {
		gra[i].clear();
	}
	memset(prex, 0, sizeof(prex));
	memset(prey, 0, sizeof(prey));
}

int findlongest(int start, int pre[]) {
	int u;
	memset(vis, 0, sizeof(vis));
	vis[start] = true;
	q.push(start);
	while (!q.empty()) {
		u = q.front();
		q.pop();
		for (int i = 0; i < gra[u].size(); ++i) {
			if (!vis[gra[u][i]]) {
				pre[gra[u][i]] = u;
				vis[gra[u][i]] = true;
				q.push(gra[u][i]);
			}
		}
	}
	return u;
}

void bfs(int start1, int start2, int length) {
	int u;
	memset(vis, 0, sizeof(vis));
	memset(deep, 0, sizeof(deep));
	vis[start1] = true;
	vis[start2] = true;
	q.push(start1);
	q.push(start2);
	while (!q.empty()) {
		u = q.front();
		q.pop();
		if (deep[u] == length)
			continue;
		for (int i = 0; i < gra[u].size(); ++i) {
			if (!vis[gra[u][i]]) {
				vis[gra[u][i]] = true;
				deep[gra[u][i]] = deep[u] +1;
				q.push(gra[u][i]);
			}
		}
	}
}

bool judge() {
	for (int i = 1; i <= n; ++i) {
		if (!vis[i])
			return false;
	}
	return true;
}

int main() {
	int T, x, y, l, r, mid, s1, s2;
	freopen("2Bin.txt", "r", stdin);
	freopen("2Bout.txt", "w", stdout);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		init();
		for (int i = 1; i < n; ++i) {
			scanf("%d%d", &x, &y);
			gra[x].push_back(y);
			gra[y].push_back(x);
		}
		x = findlongest(1, prex);
		y = findlongest(x, prey);
		memset(prex, 0, sizeof(prex));
		for (int i = y; prey[i] > 0; i = prey[i]) {
			prex[prey[i]] = i;
		}
		//printf("%d %d\n", x, y);
		l = 0;
		r = n;
		while (l <= r) {
			mid = (l+r) >> 1;
			s1 = x; s2 = y;
			for (int i = 0; i < mid; ++i) {
				if (prex[s1] > 0)
					s1 = prex[s1];
				if (prey[s2] > 0) 
					s2 = prey[s2];
			}
			if (s1 == s2) {
				if (s1 == 1)
					s2 = 2;
				else
					s2 = 1;
			}
			bfs(s1, s2, mid);
			if (judge()) {
				r = mid-1;
			}
			else {
				l = mid+1;
			}
		}
		if (s1 == 0)
			s1 = y;
		if (s2 == 0)
			s2 = x;
		printf("%d %d %d\n", l, s1, s2);
	}
	return 0;
}