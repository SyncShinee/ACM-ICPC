#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <queue>
#define N 1024
#define M 1024
#define MOD 1000000007
#define EPS 1e-9
using namespace std;
int n, m, a, b, odd, even, x;
int main() {
	scanf("%d%d", &n, &m);
	odd = even = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &x);
		if (x & 1)
			odd++;
		else
			even++;
	}
	b = (n - m) / 2;
	a = n - m - b;
	if (n == m) {
		if (odd & 1) {
			printf("Stannis\n");
		}
		else {
			printf("Daenerys\n");
		}
	}
	else if (odd <= b) {
		printf("Daenerys\n");
	}
	else if (even <= a) {
		if ((odd - (a + b - even)) % 2) {
			printf("Stannis\n");
		}
		else if (even <= b) {
			printf("Daenerys\n");
		}
		else 
			printf("Stannis\n");
	}
	else if (odd % 2 == 0) {
		if (a == b) {
			printf("Daenerys\n");
		}
		else {
			printf("Stannis\n");
		}
	}
	else {
		if (a == b) {
			printf("Daenerys\n");
		}
		else {
			printf("Stannis\n");
		}
	}
	return 0;
}