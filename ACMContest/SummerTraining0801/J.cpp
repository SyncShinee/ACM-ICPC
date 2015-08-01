#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;
vector <double> s;
priority_queue<double> q;
int n;
double a[20];
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf("%lf", &a[i]);
		}
		while (!q.empty()) {
			q.pop();
		}
		for (int sta = 3; sta < (1 << n); ++sta) {
			if ((sta & (sta - 1)) == 0) {
				continue;
			}
			s.clear();
			for (int i = 0; i < n; ++i) {
				if (sta & (1 << i)) {
					s.push_back(a[i]);
				}
			}
			int len = s.size();
			double l = 0, r = 1e5, mid, sum;
			while (fabs(l - r) > 1e-8) {
				mid = (l + r) / 2;
				sum = 0;
				for (int j = 0; j < len; ++j) {
					sum += pow(s[j], mid);
				}
				if (fabs(sum - 1) < 1e-8) {
					break;
				}
				if (sum > 1 + 1e-8) {
					l = mid;
				}
				else {
					r = mid;
				}
			}
			q.push(mid);
		}
		while (q.size() > 1) {
			double s1 = q.top();
			q.pop();
			double s2 = q.top();
			q.pop();
			q.push(max(s1/2, s2/2));
		}
		printf("%f\n", q.top());
	}
	return 0;
}