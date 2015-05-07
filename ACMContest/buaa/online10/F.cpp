#include <cstdio>
#include <cstring>
using namespace std;
char a[128], b[128];
int k, la, lb, ta, tb, remain, ans;
int main() {
	while (~scanf("%s%s%d", a, b, &k)) {
		la = strlen(a);
		lb = strlen(b);
		ans = 0;
		for (int i = 0; i < la; ++i) {
			for (int j = 0; j < lb; ++j) {
				if (a[i] == b[j]) {
					remain = k;
					ta = i;
					tb = j;
					while (ta < la && tb < lb) {
						if (a[ta] == b[tb]) {
							ta++;
							tb++;
						}
						else {
							remain--;
							tb++;
						}
						if (remain < 0)
							break;
					}
					if (ta - i > ans)
						ans = ta-i;
				}
			}
		}
		for (int i = 0; i < lb; ++i) {
			for (int j = 0; j < la; ++j) {
				if (b[i] == a[j]) {
					remain = k;
					tb = i;
					ta = j;
					while (ta < la && tb < lb) {
						if (a[ta] == b[tb]) {
							ta++;
							tb++;
						}
						else {
							remain--;
							ta++;
						}
						if (remain < 0)
							break;
					}
					if (tb - i > ans)
						ans = tb-i;
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}