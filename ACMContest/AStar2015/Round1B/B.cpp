#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <cmath>
#define EPS 1e-9
#define N 1024
using namespace std;
typedef long long ll;
int n, m;
struct node {
	int x, y;
}tmp;
vector <node> e[128];
int a[N][N], ans, num, f[1000010], rank[1000010];
int gf(int x) {
	if (f[x] == x)
		return x;
	return f[x] = gf(f[x]);
}
int merge(int x, int y) {
	int i = gf(x), j = gf(y);
	if (rank[i] < rank[j]) {
		f[i] = j;
		f[x] = j;
	}
	else if (rank[i] > rank[j]) {
		f[j] = i;
		f[y] = i;
	}
	else {
		f[i] = j;
		f[x] = j;
		rank[j]++;
	}
}
int main() {
	int T;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		memset(rank, 0, sizeof(rank));
		scanf("%d%d", &n, &m);
		ans = num = 0;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j) {
				scanf("%d", &a[i][j]);
				f[(i-1)*m+j] = (i-1)*m+j;
			}
		for (int i = 0; i <= 100; ++i)
			e[i].clear();
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j) {
				if (i > 1) {
					tmp.x = m*(i-2)+j;
					tmp.y = m*(i-1)+j;
					e[abs(a[i][j]-a[i-1][j])].push_back(tmp);
				}
				if (j > 1) {
					tmp.x = m*(i-1)+j-1;
					tmp.y = m*(i-1)+j;
					e[abs(a[i][j]-a[i][j-1])].push_back(tmp);
				}
			}
		for (int i = 0; i <= 100; ++i) {
			for (int j = 0; j < e[i].size(); ++j) {
				//printf("%d  %d %d\n",i, e[i][j].x, e[i][j].y);
				if (gf(e[i][j].x) != gf(e[i][j].y)) {
					merge(e[i][j].x, e[i][j].y);
					ans += i;
					num++;
					//printf("%d -----%d %d\n", i, e[i][j].x, e[i][j].y);
					if (num == n*m-1) {
						i = 100;
						break;
					}
				}
			}
		}
		printf("Case #%d:\n", cas);
		printf("%d\n", ans);
	}
	return 0;
}