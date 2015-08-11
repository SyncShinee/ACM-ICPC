#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <map>
#include <set>
#include <queue>
#include <cmath>
#define N 100010
using namespace std;
typedef long long ll;
bool check(int x) {
	bool flag[10] = {0};
	while (x > 0) {
		if (flag[x % 10]) {
			return false;
		}
		flag[x % 10] = true;
		x /= 10;
	}
	return true;
}
int main() {
	int n, m, ans;
	while (~scanf("%d%d", &n, &m)) {
		ans = 0;
		for (int i = n; i <= m; ++i) {
			if (check(i))
				
				ans ++;
		}
		printf("%d\n", ans);
	}
	return 0;
}