#include <cstdio>
using namespace std;
int n, m, a[32][32], ans_x, ans_y, ans;
bool legal(int x, int y) {
	return x > 0 && x <= n && y > 0 && y <= m && a[x][y] > 0;
}
bool center(int x, int y) {
	return x > 1 && x < n && y > 1 && y < m && a[x][y] == 1 && a[x-1][y] > 0 && a[x+1][y] > 0 && a[x][y-1] > 0 && a[x][y+1] > 0;
}
bool dfs(int x, int y, int sum) {
	//printf("x === %d y ===== %d sum ===== %d   ans === %d\n", x, y,sum, ans);
	int len = 1, tx, ty;
	if (sum == 0) {
		//printf("%d\n", ans);
		return true;
	}
	if (ans > 9)
		return false;
	while (!center(x, y)) {
		//printf("---->%d %d", x, y);
		y++;
		if (y > m) {
			x++;
			y = 1;
		}
		if (x > n)
			return false;
	}
	//printf("\n");
	
	while (legal(x + len, y) && legal(x - len, y) && legal(x, y + len) && legal(x, y - len) )
		len++;
	a[x][y]--;
	for (int i = 1; i < len; ++i) {
		a[x + i][y]--;
		a[x - i][y]--;
		a[x][y + i]--;
		a[x][y - i]--;
	}
	ans_y = y; ans_x = x;
	ty = y+1;
	tx = x;
	if (ty > m) {
		ty = 1;
		tx++;
	}
	ans ++;//printf("%d %d %d %d\n",len, x, y, sum-4*len+3);
	if (dfs(tx, ty, sum-4*len+3))
		return true;

	a[x][y]++;
	for (int i = 1; i < len; ++i) {
		a[x + i][y]++;
		a[x - i][y]++;
		a[x][y + i]++;
		a[x][y - i]++;
	}
	ans--;
	return (dfs(tx, ty, sum));
}
int main() {
	//freopen("out.txt", "w", stdout);
	int T, sum, tt;
	scanf("%d", &T);
	while (T--) {
		sum = 0;
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j) {
				scanf("%d", &a[i][j]);
				sum += a[i][j];
			}
		ans = 0;
		//printf("%d\n", ans);
		tt = dfs(1,1, sum);
		printf("%d\n", ans);
		printf("%d %d\n", ans_x, ans_y);
	}
	return 0;
}