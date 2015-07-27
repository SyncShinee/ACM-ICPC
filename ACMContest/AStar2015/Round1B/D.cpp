#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <cmath>
#define EPS 1e-6
#define N 100010
using namespace std;
typedef long long ll;
double x, a1, a2, a3, pre, nxt, ten[16];
vector <double> ans;
int main() {
	int T;
	scanf("%d", &T);
	ten[0] = 1.0;
	for (int i = 1; i <= 10; ++i)
		ten[i] = ten[i-1] * 10.0;
	for (int cas = 1; cas <= T; ++cas) {
		ans.clear();
		scanf("%lf", &x);
		printf("Case #%d:\n", cas);
		if (fabs(x-1.0) < EPS) {
			printf("0\n");
			continue;
		}
		for (int i = 2; i <= 10; ++i) {
			for (a1 = 1; a1 < 9 + EPS; a1 += 1.0) {
				for (a3 = 0; a3 < 9 + EPS; a3 += 1.0) {
					a2 = ((a3 - a1 * x) * ten[i-1] + a1 - x * a3)/10.0/(x-1.0);
					if (a2 < 0-EPS || a2 - floor(a2+EPS) > EPS || a2 / ten[i-2] > 1.0 -1e-10) {
						continue;
					}
					pre = a1 * ten[i-1] + a2 * 10 + a3;
					nxt = a3 * ten[i-1] + a2 * 10 + a1;
					if (fabs(pre * x - nxt) < EPS) {
						ans.push_back(pre);
					}
				}
			}
		}
		printf("%d\n", ans.size());
		for (int i = 0; i < ans.size(); ++i) {
			printf("%.0f%c", ans[i], " \n"[i == ans.size()-1]);
		}

	}
	return 0;
}