#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <queue>
#define N 1024
#define M 1024
#define MOD 1000000007
#define EPS 1e-9
using namespace std;
int n, m, ans1, ans2, d1[128], d2[128];
char s[128][128];
int main() {
	scanf("%d%d", &n, &m);
	gets(s[0]);
	for (int i = 0; i < n; ++i)
		gets(s[i]);
	memset(d1, 0, sizeof(d1));
	memset(d2, 0, sizeof(d2));
	ans1 = ans2 = 0;
	for (int i = n-1; i >= 0; --i) {
		for (int j = m-1; j >= 0; --j) {
			if (s[i][j] == 'W') {
				if (d1[j] != 1) {
					for (int t = 0; t <= j; ++t)
						d1[t] += 1 - d1[j];
					ans1++;
				}
			}
			else {
				if (d1[j] != -1) {
					for (int t = 0; t <= j; ++t)
						d1[t] += -1 - d1[j];
					ans1++;
				}
			}
			if (s[i][j] == 'W') {
				if (d2[j] != -1) {
					for (int t = 0; t <= j; ++t)
						d2[t] += -1 - d2[j];
					ans2++;
				}
			}
			else {
				if (d2[j] != 1) {
					for (int t = 0; t <= j; ++t)
						d2[t] += 1 - d2[j];
					ans2++;
				}
			}
		}
	}
	printf("%d\n", min(ans1, ans2));
	return 0;
}