#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
char s[16], t[16], ans[1024][16];
int lens, lent, num, n;
int main() {
	int i, j;
	while (~scanf("%s", s)) {
		num = 0;
		lens = strlen(s);
		scanf("%d", &n);
		for (i = 0; i < n; ++i) {
			scanf("%s", t);
			lent = strlen(t);
			if (lens != lent)
				continue;
			for (j = 0; j < lens; ++j)
				if (s[j] != '*' && s[j] != t[j])
					break;
			if (j == lens)
				strcpy(ans[num++], t);
		}
		printf("%d\n", num);
		for (i = 0; i < num; ++i)
			printf("%s\n", ans[i]);
	}
	return 0;
}