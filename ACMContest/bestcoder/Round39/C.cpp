#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

void moblus() {
	memset(vis, 0, sizeof(vis));
	mu[1] = 1;
	cnt = 0;
	for (int i = 2; i < N; ++i) {
		if (!vis[i] {
			prime[cnt++] = i;
			mu[i] = -1;
		}
		for (int j = 0; j < cnt & i *prime[j] < N; ++j){
			vis[i*prime[j]] = 1;
			if (i % prime[j])
				mu[i*prime[j]] = -mu[i];
			else {
				mu[i*prime[i]] = 0;
				break;
			}
		}
	}
}
int main() {
	
	return 0;
}