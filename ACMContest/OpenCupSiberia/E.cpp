#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long ll;

const int maxn = 200 + 10;
const int M = 1e9 + 7.1;

int f[maxn][maxn][2], n, m, p;
int len[maxn];

int add(int a, int b) {
    int c = a + b;
    if(c >= M) {
	c -= M;
    }
    return c;
}
int mult(int a, int b) {
    int c = (ll)a * (ll)b % M;
    return c;
}
void solve() {
    //printf("fdsaf");
    memset(f, 0, sizeof(f));
    for(int i = 1; i <= n; i++) {
	for(int j = 0; j < m; j++) {
	    if(i >= 2)
		f[i][j][1] = add(f[i][j][1], f[i - 2][j][0]);
	    else
		f[i][j][1] = 0;
	    if(len[j] == i) {
		f[i][j][1] = add(f[i][j][1], 1);
	    }
	    f[i][j][0] = add(f[i][j][0], f[i][j][1]);
	    for(int k = 1; k <= i - 2; k++) {
		for(int t = 0; t < m; t++) {
		    int t1, t2;
		    t1 = ((j - t) % m + m) % m;
		    t2 = (j + t) % m;
		    f[i][j][0] = add(f[i][j][0], mult(f[k][t][1], f[i - k - 1][t1][0]));
		    f[i][j][0] = add(f[i][j][0], mult(f[k][t][1], f[i - k - 1][t2][0]));
		}
	    }
	}
    }
    printf("%d\n", f[n][p][0]);
}

int main() {
    //freopen("E.txt", "r", stdin);
      freopen("input.txt", "r", stdin);
      freopen("output.txt", "w", stdout);
    for(int i = 0; i <= 9; i++) {
	len[i] = 1;
    }
    for(int i = 10; i <= 99; i++) {
	len[i] = 2;
    }
    for(int i = 100; i <= 200; i++) {
	len[i] = 3;
    }
    while(scanf("%d%d%d", &n, &m, &p) != EOF) {
	solve();
    }
    return 0;
}
