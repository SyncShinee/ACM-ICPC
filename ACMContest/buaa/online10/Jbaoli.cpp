#include <cstdio>
#include <algorithm>
using namespace std;
long long p[100010], ans, n;
int cas;
int main() {
	while (~scanf("%lld", &n)) {
		ans = 0;
		for (int i = 0; i < n; ++i)
			p[i] = i+1;
		do {
			int t = 0;
			for (int i = 0; i < n; ++i)
				if (p[i] != i+1)
					t = t+1;
			if (t > 0)
				t--;
			ans = (ans+t)%1000000007;
		}
		while (next_permutation(p, p+n));
		printf("%d\n", ans);
	}
}