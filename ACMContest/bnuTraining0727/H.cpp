/*#include <cstdio>
#include <cstring>
#include <set>

using namespace std;

const int N = 100005;

int type[N], h[N], g[N], f[N], co[N], q[N];

int main() {
	int T, ca = 0;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
			scanf("%d%d", &type[i], &h[i]);
		g[1] = 1;
		memset(co, 0, sizeof(co));
		co[type[1]] = 1;
		int j = 1;
		for (int i = 2; i <= n; ++i) {
			if (co[type[i]]) {
				do {
					co[type[j]] = 0;
					++j;
				} while (co[type[i]]);
			}
			co[type[i]] = 1;
			g[i] = j;
		}
		f[1] = h[1];
		multiset<int> S;
		int head = 0, tail = 1;
		q[head] = 1;
		S.insert(h[1]);
		for (int i = 2; i <= n; ++i) {
			while (tail - head && h[q[tail - 1]] <= h[i]) {
				if (tail - head == 1)
					S.erase(S.find(h[q[tail - 1]] + f[g[i - 1] - 1]));
				else S.erase(S.find(h[q[tail - 1]] + f[q[tail - 2]]));
				--tail;
			} 
			q[tail++] = i;
			if (tail - head == 1)
				S.insert(h[i] + f[g[i - 1] - 1]);
			else
				S.insert(h[i] + f[q[tail - 2]]);
			for (int k = g[i - 1]; k < g[i]; ++k) {
				S.erase(S.find(f[k - 1] + h[q[head]]));
				if (k - 1 == q[head]) {
					++head;
					S.erase(S.find(f[k - 1] + h[q[head]]));
				}
				S.insert(f[k] + h[q[head]]);
			}
			f[i] = *S.begin();
		}
		printf("Case %d: %d\n", ++ca, f[n]);
	}
	return 0;
}
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
int n, head, tail;
int front[N], have[N], type[N], height[N], q[N];
multiset <int > st; 
int main() {
	int T;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", &type[i], &height[i]);
		}
		front[1] = 1;
		have[type[1]] = 1;
		int pos = 1;
		for (int i = 2; i <= n; ++i) {
			while (have[type[i]]) {
				have[type[pos]] = 0;
				pos++;
			}
			front[i] = pos;
			have[type[i]] = 1;
		}
		st.clear();
		memset(f, 0, sizeof f);
		f[1] = height[1];
		st.insert(height[1]);
		head = tail = 1;
		q[head] = 1;
		for (int i = 2; i <= n; ++i) {
			while (head <= tail && height[i] >= height[q[tail]]) {
				if (head < tail) {
					st.erase(st.find(height[q[tail]] + f[q[tail - 1]]))
				}
				else {
					st.erease(st.find(height[q[tail]] + f[front[i - 1] - 1]]));
				}
				tail--;
			}
			q[tail++] = height[i];
			if (tail < head) {
				st.insert(height[i] + f[front[i] - 1]);
			}
			else {
				st.insert(height[i] + f[q[tail]]);
			}
		}
	}
	return 0;
}