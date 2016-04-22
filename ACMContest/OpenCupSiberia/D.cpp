#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int maxn = 1e5 + 100;
const double eps = 1e-8;
const double INF = 1e30;
const int limit = 60;

double shou[maxn], x[maxn], p[maxn];
double f[maxn][70], g[maxn];
int n;

void solve() {
    memset(f, 0, sizeof(f));
    for(int i = 1; i <= n; i++) {
	f[i][0] = x[i];
	for(int j = 1; j <= limit; j++) {
	    f[i][j] = f[i][j - 1] * (1 + p[i + j - 1]);
	}
    }
    g[0] = 0;
    for(int i = 1; i <= n; i++) {
	double tmp = shou[i] + x[i];
	g[i] = INF;
	for(int j = i - 1; (i - j) <= limit && j >= 0; j--) {
	    g[i] = min(g[i], g[j] + tmp);
	    tmp += f[j][i - j];
	}
    }
    printf("%.10f\n", g[n]);
}
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    while(scanf("%d", &n) != EOF) {
	for(int i = 1; i <= n; i++) {
	    scanf("%lf %lf %lf", &x[i], &shou[i], &p[i]);
	    p[i] /= 100;
	}
	solve();
    }
    return 0;
}
