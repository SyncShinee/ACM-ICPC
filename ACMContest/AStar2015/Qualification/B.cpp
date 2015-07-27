#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
int k, T, len, row, col;
char s[100010], sl[10];
vector<char> gra[100010];
int main() {
	scanf("%d", &T);gets(sl);
	for (int cas = 1; cas <= T; ++cas) {
		gets(s);
		scanf("%d", &k);gets(sl);
		int len = strlen(s);
		row = (len + k - 1) / k;
		for (int i = 0; i < row; ++i)
			gra[i].clear();
		col = len % k;
		if (col == 0)
			col = k;
		int l = 0;
		for (int i = 0; i < k; ++i) {
			for (int j = 0; j < row; ++j) {
				if (i >= col && j == row-1)
					break;
				gra[j].push_back(s[l++]);
			}
		}
		printf("Case #%d:\n", cas);
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < gra[i].size() && gra[i][j] != 0; ++j)
				printf("%c", gra[i][j]);
		}
		printf("\n");
	}
	return 0;
}