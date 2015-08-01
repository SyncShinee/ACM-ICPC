#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cmath>
#define N 100010
using namespace std;
struct point {
	int x, y;
}p[16][16], pn;
int n, v[16];

int cross(point a, point b, point c) {
	point x1, x2;
	x1.x = b.x - a.x;
	x1.y = b.y - a.y;
	x2.x = c.x - a.x;
	x2.y = c.y - a.y;
	return x1.x * x2.y - x1.y * x2.x;
}

int sgn(int x) {
	if (x < 0)
		return -1;
	if (x == 0)
		return 0;
	return 1;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &pn.x, &pn.y);
		for (int i = 0; i < n; ++i) {
			scanf("%d", &v[i]);
			for (int j = 0; j < v[i]; ++j)
				scanf("%d%d", &p[i][j].x, &p[i][j].y);
			p[i][v[i]] = p[i][0];
		}
		for (int i = 0; i < n; ++i) {
			int flag = 0, tmp, sign;
			for (int j = 0; j < v[i]; ++j) {
				sign = sgn(cross(p[i][j], p[i][j + 1], pn));
				if (sign == 0) {
					printf("0%c", i == n-1 ? '\n' : ' ');
					flag = 1;
					break;
				}
				else {
					if (j == 0) {
						tmp = sign;
					}
					else {
						if (tmp * sign == -1) {
							flag = 1;
							printf("2%c", i == n-1 ? '\n' : ' ');
							break;
						}
					}
				}
			}
			if (!flag) {
				printf("1%c", i == n-1 ? '\n' : ' ');
			}
		}
	}
	return 0;
}