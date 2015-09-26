#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
int n, k;
vector <int> v[4096]; 
struct node {
	int num, fac[4096];
} p[4096];
bool operator < (const node &A, const node &B) {
	return A.num > B.num;
}
bool cmp(int x, int y) {
	return x > y;
}
int ans[4096];
int main() {
	int x, y;
	while (~scanf("%d%d", &n, &k)) {
		for (int i = 0; i <= 4000; ++ i)
			v[i].clear();
		for (int i = 0; i < n; ++ i) {
			scanf("%d%d", &x, &y);
			v[x].push_back(y);
		}
		int tot = 0;
		for (int i = 0; i <= 4000; ++ i) {
			if (v[i].size() == 0) continue;
			for (int j = 0; j < v[i].size(); ++ j) {
				p[tot].fac[j] = v[i][j];
			}
			p[tot].num = v[i].size();
			sort(p[tot].fac, p[tot].fac + v[i].size(), cmp);
			tot ++;
		}
		sort(p, p + tot);
		if (tot < k) {
			puts("0 0");
		}
		else {
			int sz = p[k - 1].num;
			int cnt = 0;
			for (int i = 0; i < tot; ++ i) {
				if (p[i].num < sz) break;
				ans[cnt] = 0;
				for (int j = 0; j < sz; ++ j) {
					ans[cnt] += p[i].fac[j];
				}
				cnt++;
			}
			sort(ans, ans + cnt, cmp);
			int ret = 0;
			for (int i = 0; i < k; ++ i) {
				ret += ans[i];
			}
			printf("%d %d\n", sz, ret);
		}
	}
	return 0;
}