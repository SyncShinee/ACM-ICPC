#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int maxn = 100 + 10;
const int INF = 1e5 + 100;
int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
int a[maxn][maxn];
int n, m, si, sj, ei, ej;
int ds[maxn][maxn], dt[maxn][maxn];
int vis[maxn][maxn], inq[maxn][maxn];
struct node {
    int i, j;
    node(int _i = 0, int _j = 0) {
	i = _i;
	j = _j;
    }
};
int check(int i, int j) {
    if(i >= 1 && i <= n && j >= 1 && j <= m)
	return 1;
    return 0;
}

void spfa(int starti, int startj, int limit, int d[][maxn]) {
    memset(vis, 0, sizeof(vis));
    for(int i = 1; i <= n; i++) {
	for(int j = 1; j <= m; j++) {
	    d[i][j] = INF;
	}
    }
    d[starti][startj] = 0;
    queue<node> q;
    q.push(node(starti, startj));
    vis[starti][startj] = 1;
    
    while(!q.empty()) {
	int ui = q.front().i;
	int uj = q.front().j;
	q.pop();
	//printf("**  %d  %d\n", ui, uj);
	vis[ui][uj] = 0;
	for(int k = 0; k < 4; k++) {
	    int ni = ui + dx[k], nj = uj + dy[k];
	    if(check(ni, nj) && a[ni][nj] != 0 && a[ni][nj] <= limit) {
		if(d[ni][nj] > d[ui][uj] + a[ni][nj]) {
		    d[ni][nj] = d[ui][uj] + a[ni][nj];
		    if(vis[ni][nj] == 0) {
			q.push(node(ni, nj));
			vis[ni][nj] = 1;
		    }
		}
	    }
	}
    }
}
void solve() {
    int ans = INF;
    for(int t = 9; t >= 1; t--) {
	spfa(si, sj, t, ds);
	spfa(ei, ej, t, dt);
	int temp = INF;
	for(int i = 1; i <= n; i++) {
	    for(int j = 1; j <= m; j++) {
		if(a[i][j] == t) {
		    // printf("11 %d  %d\n", ds[i][j], dt[i][j]);
		    temp = min(temp, ds[i][j] + dt[i][j]);
		}
	    }
	}
	if(temp != INF) {
	    temp -= 2*t;
	    ans = min(ans, temp);
	}
    }
    if(ans == INF) {
	printf("0\n");
    }
    else {
	int sum = 0;
	for(int i = 1; i <= n; i++) {
	    for(int j = 1; j <= m; j++) {
		sum += a[i][j];
	    }
	}
	printf("%d\n", sum - ans);
    }
}
char str[maxn];
int main() {
    freopen("g.txt", "r", stdin);
    int ncase;
    scanf("%d", &ncase);
    for(int _ = 1; _ <= ncase; _++) {
	printf("Case #%d: ", _);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) {
	    scanf("%s", str + 1);
	    for(int j = 1; j <= m; j++) {
		if(str[j] == 'A') {
		    a[i][j] = 0;
		    si = i;
		    sj = j;
		}
		else if(str[j] == 'B') {
		    a[i][j] = 0;
		    ei = i;
		    ej = j;
		}
		else {
		    a[i][j] = str[j] - '0';
		}
	    }
	}
	solve();
    }
    return 0;
}
