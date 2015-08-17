#include <cstdio>
#include <queue>
#include <cstring>
#include <vector>
#include <stack>
using namespace std;
int b[128][128], h[128][128], l[128][128];
bool usedh[128], usedl[128], used[512];
stack <int> sta;
int n, m;
int main() {
	//freopen("in.txt", "r", stdin);
	int T, x, y, sum;
	char s[2];
	scanf("%d", &T);
	while (T--) {
		memset(h, 0, sizeof h);
		memset(l, 0, sizeof l);
		memset(used, 0, sizeof used);
		memset(usedl, 0, sizeof usedl);
		memset(usedh, 0, sizeof usedh);
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				scanf("%d", &b[i][j]);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				scanf("%d", &b[i][j]);
		for (int i = 1; i <= m; ++i) {
			scanf("%s%d%d", s, &x, &y);
			if (s[0] == 'H') {
				h[x][y] = i;
			}
			else {
				l[x][y] = i;
			}
		}
		for (int t = 0; t < 2 * n; ++t) {
			for (int i = 1; i <= n; ++i) {
				int col = -1, flag = true;
				if (usedh[i])
					continue;
				for (int j = 1; j <= n; ++j) {
					if (!usedl[j]) {
						if (col == -1) {
							col = b[i][j];
						}
						else if (col != b[i][j]){
							flag = false;
							break;
						}
					}
				}
				if (col > -1 && flag && h[i][col] > 0) {
					usedh[i] = true;
					used[h[i][col]] = true;
					sta.push(h[i][col]);
				}
			}
			for (int j = 1; j <= n; ++j) {
				int col = -1, flag = true;
				if (usedl[j])
					continue;
				for (int i = 1; i <= n; ++i) {
					if (!usedh[i]) {
						if (col == -1) {
							col = b[i][j];
						}
						else if (col != b[i][j]) {
							flag = false;
							break;
						}
					}
				}
				if (col > -1 && flag && l[j][col] > 0) {
					used[l[j][col]] = true;
					sta.push(l[j][col]);
					usedl[j] = true;
				}
			}
		}
		sum = 0;
		for (int i = 1; i <= m; ++i)
			if (!used[i]) {
				sum ++;
				printf("%d%c", i, " \n"[sum == m]);
			}
		while (!sta.empty()) {
			sum ++;
			printf("%d%c", sta.top(), " \n"[sum == m]);
			sta.pop();
		}
	}
	return 0;
}