#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <bitset>
#define N 200010
using namespace std;
char s[N], t[N];
bitset<N> bt[4], ans;
int pre[4];
int main() {
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	scanf("%s%s", s, t);
	pre[0] = pre[1] = pre[2] = pre[3] = -N;
	for (int i = 0; i < n; ++i) {
		if (s[i] == 'A') {
			pre[0] = i;
		}
		else if (s[i] == 'G') {
			pre[1] = i;
		}
		else if (s[i] == 'C') {
			pre[2] = i;
		}
		else if (s[i] == 'T') {
			pre[3] = i;
		}
		for (int j = 0; j < 4; ++j) {
			if (i - pre[j] <= k) {
				bt[j].set(i);
			}
		}
	}
	pre[0] = pre[1] = pre[2] = pre[3] = N + N;
	for (int i = n - 1; i >= 0; --i) {
		if (s[i] == 'A') {
			pre[0] = i;
		}
		else if (s[i] == 'G') {
			pre[1] = i;
		}
		else if (s[i] == 'C') {
			pre[2] = i;
		}
		else if (s[i] == 'T') {
			pre[3] = i;
		}
		for (int j = 0; j < 4; ++j) {
			if (pre[j] - i<= k) {
				bt[j].set(i);
			}
		}
	}
	ans.set();
	for (int i = 0; i < m; ++i) {
		if (t[i] == 'A') {
			ans &= bt[0] >> i; 
		}
		else if (t[i] == 'G') {
			ans &= bt[1] >> i;
		}
		else if (t[i] == 'C') {
			ans &= bt[2] >> i;
		}
		else if (t[i] == 'T') {
			ans &= bt[3] >> i;
		}
	}
	cout << ans.count() << endl;
	return 0;
}