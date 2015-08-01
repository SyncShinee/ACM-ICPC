#include <cstdio>
#include <cstring>
#include <stack>
#include <algorithm>
#include <iostream>
#include <bitset>
#define M 100000000
#define N 10010
using namespace std;
bool vis[M + 10];
int ans[N], p[N];
int main() {
	int T, tot = 0, x;
	for (int i = 2; i <= M; ++i) {
		if (!vis[i]) {
			if (i < N)
			p[tot++] = i; 
		}
		for (int j = 0; j < tot && p[j] * i <= M; ++j) {
			vis[i * p[j]] = true;
			if (i % p[j] == 0) {
				break;
			}
		}
	}
	int num = 2, sum = 0;
	for (int i = 1; i < N; ++i) {
		while (num < M && num <= i * i) {
			if (!vis[num]) {
				sum++;
			}
			num++;
		}
		ans[i] = sum;
	}
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		scanf("%d", &x);
		printf("Case %d: %d\n", cas, ans[x]);
	}
}