#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#define EPS 1e-9
using namespace std;
struct node {
	double x, y;
}p[4096], up[4096], down[4096], st;
int len_up, len_down, n, num_up, num_down, online_up, online_down, it_up, it_down, ans;
double ang;
double cross(node stds, node a, node b) {
	return (a.x - stds.x) * (b.y - stds.y) - (a.y - stds.y) * (b.x - stds.x);
}
bool cmp(node a, node b) {
	if (cross(st, a, b) > 0)
		return true;
	return false;
}
double dot(node stds, node a, node b) {
	return (a.x - stds.x) * (b.x - stds.x) + (a.y - stds.y) * (b.y - stds.y);
}
double length(node a, node b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
double angel(node from, node to, double start) {
	node tmp;
	tmp.x = from.x + start;
	tmp.y = from.y;
	return dot(from, tmp, to) / length(from, to);
}
int main() {
	freopen("c-large-practice.in", "r", stdin);
	freopen("c.out", "w", stdout);
	int T;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf("%lf%lf", &p[i].x, &p[i].y);
		}
		printf("Case #%d:\n", cas);
		for (int i = 0; i < n; ++i) {
			ans = 4096;
			len_down = len_up = 0;
			for (int j = 0; j < n; ++j) {
				if (j == i)
					continue;
				if (p[j].y > p[i].y || fabs(p[j].y - p[i].y) < EPS && p[j].x > p[i].x)
					up[len_up++] = p[j];
				else 
					down[len_down++] = p[j];
			}
			st = p[i];
			if (len_up == 0 || len_down == 0) {
				printf("0\n");
				continue;
			}
			sort(up, up + len_up, cmp);
			sort(down, down + len_down, cmp);
			num_up = len_up;
			num_down = len_down;
			for (it_up = 0; it_up < len_up; ++it_up) {
				if (fabs(up[it_up].y - st.y) > EPS)
					break;
			}
			num_up -= it_up;
			online_up = it_up;
			for (it_down = 0; it_down < len_down; ++it_down) {
				if (fabs(down[it_down].y - st.y) > EPS)
					break;
			}
			num_down -= it_down;
			online_down = it_down;
			ans = min(ans, min(num_down, num_up));
			while (it_down < len_down || it_up < len_up) {
				num_down += online_up;
				num_up += online_down;
				online_up = online_down = 0;
				if (it_up == len_up)
					ang = angel(st, down[it_down], -1);
				else if (it_down == len_down)
					ang = angel(st, up[it_up], 1);
				else
					ang = max(angel(st, up[it_up], 1), angel(st, down[it_down], -1));
				while (it_up < len_up && fabs(angel(st, up[it_up], 1) - ang) < EPS) {
					it_up++;
					online_up++;
				}
				while (it_down < len_down && fabs(angel(st, down[it_down], -1) - ang) < EPS) {
					it_down++;
					online_down++;
					
				}
				num_down -= online_down;
				num_up -= online_up;
				ans = min(ans, min(num_up, num_down));
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}