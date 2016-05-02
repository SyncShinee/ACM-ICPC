#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>

using namespace std;

struct Point{
    double x, y;
    Point(double _x = 0, double _y = 0) {
	x = _x;
	y = _y;
    }
};
double dist(Point a, Point b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

const int maxn = 1600 + 100;
const double INF = 1e18;
double a[maxn][maxn], v1, v2;
Point p[maxn];
int n, m;
double d[maxn];
int vis[maxn], from[maxn];
int loc[maxn];
int k;
vector<int> vec;

void dijstra(int s) {
    memset(vis, 0, sizeof(vis));
    for(int i = 1; i <= n; i++) {
	d[i] = INF;
    }
    d[s] = 0;
    from[s] = -1;
    
    double ans = INF;
    int ans_no = -1;
    int cnt = 0;
    while(cnt < n) {
	//printf("111  %d\n", cnt);
	ans = INF;
	for(int i = 1; i <= n; i++) {
	    if(vis[i] == 0 && d[i] < ans) {
		ans = d[i];
		ans_no = i;
	    }
	}
	vis[ans_no] = 1;
	cnt++;
	for(int i = 1; i <= n; i++) {
	    //	    d[i] = min(d[i], d[ans_no] + a[ans_no][i]);
	    if(d[i] > d[ans_no] + a[ans_no][i]) {
		d[i] = d[ans_no] + a[ans_no][i];
		from[i] = ans_no;
	    }
	}
    }
}

void print_path(int x, int s) {
    //printf("33 %d  \n", x);
    if(x != s)
	print_path(from[x], s);
    vec.push_back(x);
    //    printf("%d ", x);
}

void solve() {
    for(int i = 1; i <= n; i++) {
	for(int j = 1; j <= n; j++) {
	    a[i][j] = dist(p[i], p[j]) / v1;
	}
    }
    for(int i = 1; i <= m; i++) {
	int x, y;
	scanf("%d%d", &x, &y);
	a[x][y] = dist(p[x], p[y]) / v2;
	a[y][x] = dist(p[x], p[y]) / v2;
    }
    for(int i = 1; i <= k; i++) {
	scanf("%d", &loc[i]);
    }
    double ans = 0;
    vec.clear();
    loc[0] = 1;
    loc[k + 1] = n;
    for(int i = 0; i <= k; i++) {
	dijstra(loc[i]);
	ans += d[loc[i + 1]];
	print_path(from[loc[i + 1]], loc[i]);
    }
    vec.push_back(n);
    printf("%.10lf\n", ans);
    for(int i = 0; i < vec.size(); i++) {
	printf("%d%c", vec[i], (i == vec.size() - 1 ? '\n' : ' '));
    }
}

int main() {
    //freopen("E.txt", "r", stdin);
    while(scanf("%d%d%d%lf%lf", &n, &m, &k, &v2, &v1) != EOF) {
	for(int i = 1; i <= n; i++) {
	    scanf("%lf%lf", &p[i].x, &p[i].y);
	}
	solve();
    }
    return 0;
}
