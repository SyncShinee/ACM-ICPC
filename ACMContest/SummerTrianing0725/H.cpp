#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int n, m, k;
char f[2048][2048];
char s[2048];
char dfs(int x, int y) {
	if (f[x][y] > 0){
		return f[x][y];
	}
	if (y <= k) {

		f[x][y] = s[x];
		return s[x];
	}
	for (int i = 1; i <= k; ++i) {
		if (dfs(x+1, y - i) == s[x]) {
			f[x][y] = s[x];
			return f[x][y];
		}
	}
	int tmp = 'A';
	tmp += 'B';
	tmp -= s[x];
	f[x][y] = (char)tmp;
	return f[x][y];
}

int main() {
	int T;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		memset(f, 0, sizeof f);
		scanf("%d%d%d", &n, &m, &k);
		scanf("%s", s + 1);
		printf("Case #%d: %c\n",cas, dfs(1, m));
	}
	return 0;
}