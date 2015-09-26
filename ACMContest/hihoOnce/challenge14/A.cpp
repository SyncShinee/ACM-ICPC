#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <string>
#include <map>
#include <set>
using namespace std;
typedef long long ll;
const int N = 100010;
int n;
int num[2048];
char s[16];
int x;
int main() {
	while (~scanf("%d", &n)) {
		memset(num, 0, sizeof num);
		for (int i = 0; i < n; ++ i) {
			scanf("%s%s%d", s, s, &x);
			x ++;
			x *= 2;
			if (strcmp(s, "=") == 0) {
				num[x]++;
			}
			else if (strcmp(s, ">") == 0) {
				for (int j = x + 1; j < 2048; ++ j) num[j] ++;
			}
			else if (strcmp(s, ">=") == 0) {
				for (int j = x; j < 2048; ++ j) num[j] ++;
			}
			else if (strcmp(s, "<") == 0) {
				for (int j = x - 1; j >= 0; -- j) num[j] ++;
			}
			else if (strcmp(s, "<=") == 0) {
				for (int j = x; j >= 0; -- j) num[j] ++;
			}
		}
		int ans = 0;
		for (int i = 0; i < 2048; ++ i) {
			ans = max(ans, num[i]);
		}
		printf("%d\n", ans);
	}
	return 0;
}