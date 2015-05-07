#include <cstdio>
using namespace std;
int main() {
	freopen("A-large.in", "r", stdin);
	freopen("A-large.out", "w", stdout);
	int T, n, sum, ans;
	char s[1024];
	scanf("%d", &T);
	for(int cas = 1; cas <= T; ++cas) {
		scanf("%d%s", &n, s);
		sum = 0; ans = 0;
		for (int i = 0; i <= n; ++i) {
			if (sum >= i) {
				sum += s[i]-'0';
			}
			else {
				ans += i-sum;
				sum += i-sum+s[i]-'0';
			}
		}
		printf("Case #%d: %d\n", cas, ans);
	}
	return 0;
}