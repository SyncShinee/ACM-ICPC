#include <cstdio>
using namespace std;
int n, m, w[512], b[1024], sta[512], side, ans;
bool flag[512];
int main() {
	scanf("%d%d", &n, &m);
	side = ans = 0;
	for (int i = 1; i <= n; ++i)
		scanf("%d", &w[i]);
	for (int i = 1; i <= m; ++i)
		scanf("%d", &b[i]);
	for (int i = 1; i <= m; ++i)
		if (!flag[b[i]]) {
			flag[b[i]] = true;
			sta[++side] = b[i];
		}
	for (int i = 1; i <= m; ++i) {
		int j, sum = 0;
		for (j = 1; j <= side; ++j) {
			if (sta[j] == b[i])
				break;
			sum += w[sta[j]];
		}
		ans += sum;
		while (j > 1) {
			sta[j] = sta[j-1];
			j--;
		}
		sta[1] = b[i];
	}
	printf("%d\n", ans);
	return 0;
}