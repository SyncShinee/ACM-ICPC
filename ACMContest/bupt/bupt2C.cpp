#include<cstdio>
using namespace std;
int c[4210][4210];
long long g[4210];
int main() {
	int n, p;
	while (~scanf("%d%d", &n, &p)){
		for (int i = 1; i <= n; ++i) {
			c[i][0] = c[i][i] = 1;
			for (int j = 1; j < i; ++j)
				c[i][j] = (c[i-1][j] + c[i-1][j-1]) % p;
		}
		g[0] = 1;
		g[1] = 1;
		for (int i = 2; i <= n; ++i) {
			g[i] = 0;
			for (int j = 0; j < i; j += 2)
				g[i] = (g[i] + ((long long)c[i-1][j] * g[j] % p) * g[i-j-1] % p) % p;  
		}
		printf("%lld\n", (2*g[n]) % p);
	}
	return 0;
}