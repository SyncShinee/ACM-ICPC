#include <cstdio>
#include <cstring>
using namespace std;
char model[32][200010], p[16][200010], nul[2];
int next[100010], n, m;
bool judge(char a[][200010], int i1, int j1, char b[][200010], int i2, int j2) {
	for (int i = 0; i < n; ++i)
		if (a[i1+i][j1] != b[i2+i][j2])
			return false;
	return true;
}
bool solve() {
	for (int offset = 1; offset <= n; ++offset) {
		int tmp = 0;
		for (int i = 1; i <= 2*m; ++i) {
			while (tmp > 0 && !judge(model, offset, i, p, 1, tmp+1))
				tmp = next[tmp];
			//printf("%d %d ,%d %d %d\n", offset, i, 1, tmp+1, judge(model, offset, i, p, 1, tmp+1));
			if (judge(model, offset, i, p, 1, tmp+1)) {
				++tmp;
				if (tmp == m)
					return true;
			}
		}
	}
	return false;
}
int main() {
	while (scanf("%d%d", &n, &m), n|m) {
		gets(nul);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				scanf("%c", &model[i][j]);
				model[i+n][j] = model[i][j+m] = model[i+n][j+m] = model[i][j];
			}
			gets(nul);
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j)
				scanf("%c", &p[i][j]);
			gets(nul);
		}
		next[1] = 0;
		int tmp = 0;
		for (int i = 2; i <= m; ++i) {
			while (tmp > 0 && !judge(p, 1, tmp+1, p, 1, i))
				tmp = next[tmp];
			if (judge(p, 1, tmp+1, p, 1, i))
				++tmp;
			next[i] = tmp;
		}
		if (solve())
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}