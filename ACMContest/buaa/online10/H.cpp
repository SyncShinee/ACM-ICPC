#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
struct point {
	double x, y;
}p[30010];
double dist(point a, point b) {
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
struct e{
	int u, v;
	double value;
	friend bool operator < (e a, e b) {
		return a.value < b.value;
	}
}edge[2000010];
int n, m, q, side, num, f[30010];
double ans;
int gf(int x) {
	if (x == f[x])
		return x;
	return (x = gf(f[x]));
}
void merge(int x,  int y) {
	int i = gf(x), j = gf(y);
	f[i] = j;
	f[x] = j;
}
int main() {
	while (~scanf("%d%d%d", &n, &m, &q)) {
		side = 0;
		for (int i = 1; i <= n+m+q; ++i)
			f[i] = i;
		for (int i = 1; i <= n; ++i)
			scanf("%lf%lf", &p[i].x, &p[i].y);
		for (int i = n+1; i <= n+m; ++i)
			scanf("%lf%lf", &p[i].x, &p[i].y);
		for (int i = n+m+1; i <= n+m+q; ++i)
			scanf("%lf%lf", &p[i].x, &p[i].y);
		for (int i = 1; i < n; ++i) {
			edge[side].u = i;
			edge[side].v = i+1;
			edge[side++].value = p[i+1].y-p[i].y;

		}
		for (int i = n+1; i < n+m; ++i) {
			edge[side].u = i;
			edge[side].v = i+1;
			edge[side++].value = p[i+1].y-p[i].y;
		}
		for (int i = n+m+1; i < n+m+q; ++i) {
			edge[side].u = i;
			edge[side].v = i+1;
			edge[side++].value = p[i+1].y-p[i].y;
		}
		//printf("11\n");
		int j = n+1;
		for (int i = 1; i <= n; ++i) {
			int t = j-1;
			while (t >= n+1 && i > 1 && p[t].y - p[i-1].y > -1e-9) {
				edge[side].u = i;
				edge[side].v = t;
				edge[side++].value = dist(p[i], p[t]);
				t--;
			}
			while (j <= n+m && ((i < n &&  p[i+1].y - p[j].y > -1e-9) || i == n)) {
				edge[side].u = i;
				edge[side].v = j;
				edge[side++].value = dist(p[i], p[j]);
				j++;
				//printf("%d%d%d\n", side, i, j);
			}
		}
		j = n+m+1;
		//printf("12\n");
		for (int i = n+1; i <= n+m; ++i) {
			int t = j-1;
			while (t >= n+m+1 && i > n+1 && p[t].y - p[i-1].y > -1e-9) {
				edge[side].u = i;
				edge[side].v = t;
				edge[side++].value = dist(p[i], p[t]);
				t--;
			}
			while (j <= n+m+q && ((i < n+m && p[i+1].y - p[j].y > -1e-9) || i == n+m)) {
				edge[side].u = i;
				edge[side].v = j;
				edge[side++].value = dist(p[i], p[j]);
				j++;
			}
		}
		//printf("13\n");
		j = 1;
		for (int i = n+m+1; i <= n+m+q; ++i) {
			int t = j-1;
			while (t >= 1 && i > n+m+1 && p[t].y - p[i-1].y > -1e-9) {
				edge[side].u = i;
				edge[side].v = t;
				edge[side++].value = dist(p[i], p[t]);
				t--;
			}
			while (j <= n && ((i < n+m+q && p[i+1].y - p[j].y > -1e-9) || i == n+m+q)) {
				edge[side].u = i;
				edge[side].v = j;
				edge[side++].value = dist(p[i], p[j]);
				j++;
			}
		}
		//printf("1111\n");
		sort(edge, edge+side);
		ans = 0;
		num = 0;
		for (int i = 0; i < side; ++i) {
			if (gf(edge[i].u) != gf(edge[i].v)) {
				merge(edge[i].u, edge[i].v);
				ans += edge[i].value;
				num++;
			}
			if (num == n+m+q-1)
				break;
		}
		printf("%.6f\n", ans);
	}
	return 0;
}
