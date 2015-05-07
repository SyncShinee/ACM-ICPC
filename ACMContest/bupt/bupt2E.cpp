#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#define pi 3.14159265

using namespace std;

struct node {
	int x, y;
	double d;
}mays, luke[16];

struct rad_node {
	double l, r;
}rad[32], range[32];

double dist(node a, node b) {
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

bool cmp(rad_node a, rad_node b) {
	return a.l < b.l;
}

int main() {
	int T, num, num1;
	double dis, del, rad1, rad2;
	bool cover;
	scanf("%d", &T);
	while (T--) {
		cover = false;
		scanf("%d%d", &mays.x, &mays.y);
		rad2 = atan((double)(30-mays.y)/(double)(-mays.x))+pi;
		rad1 = atan((double)(38-mays.y)/(double)(-mays.x))+pi;
		for (int i = 0; i < 11; ++i) 
			scanf("%d%d%lf", &luke[i].x, &luke[i].y, &luke[i].d);
		
		for (int i = 0; i < 11; ++i) {
			if (luke[i].x < mays.x)
				rad[i].l = atan((double)(luke[i].y-mays.y)/(double)(luke[i].x-mays.x)) + pi;
			else if (luke[i].x == mays.x) {
				if (luke[i].y > mays.y)
					rad[i].l = pi/2;
				else 
					rad[i].l = -pi/2;
			}
			else
				rad[i].l = atan((double)(luke[i].y-mays.y)/(double)(luke[i].x-mays.x));
			dis = dist(mays, luke[i]);
			if (abs(dis - luke[i].d) <= 1e-8) {
				cover = true;
				break;
			}
			del = asin(luke[i].d/dis);
			rad[i].r = rad[i].l+del;
			rad[i].l = rad[i].l-del;
		}
		if (cover) {
			printf("Poor Mays!\n");
			continue;
		}
		
		num = 11;
		for (int i = 0; i < 11; ++i)
			if (rad[i].l < -pi/2) {
				rad[num].l = rad[i].l + 2*pi;
				rad[num++].r = 3*pi/2;
				rad[i].l = -pi/2;
			} else if (rad[i].r > 3*pi/2) {
				rad[num].l = -pi/2;
				rad[num++].r = rad[i].r - 2*pi;
				rad[i].r = 3*pi/2;
			}
		sort(rad, rad+num, cmp);
		num1 = 1;
		int k = 0;

		while (k < num) {
			range[num1].l = rad[k].l;
			range[num1].r = rad[k].r;
			++k;
			while (k < num && range[num1].r > rad[k].l) {
				if (range[num1].r < rad[k].r)
					range[num1].r = rad[k].r;
				++k;
			}
			num1++;
		}
		
		for (int i = 1; i < num1; ++i) {
			if (rad1 > range[i].l && rad2 < range[i].r) {
				cover = true;
				break;
			}
		}
		if (cover) {
			printf("Poor Mays!\n");
		}
		else {
			printf("Shoot!\n");
		}
	}
	return 0;
}