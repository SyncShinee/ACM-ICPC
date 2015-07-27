#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <queue>
#define N 1000010
#define MOD 1000000007
using namespace std;
typedef long long ll;

ll ex_gcd(ll a, ll b, ll &x, ll &y) {
	ll ret, tmp;
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	ret = ex_gcd(b, a % b, x, y);
	tmp = x;
	x = y;
	y = tmp - a / b * y;
	return ret;
}

ll vis[N];
int main() {
	ll m, h1, a1, x1, y1, h2, a2, x2, y2, tmp, timx, timy, pos1, pos2;
	bool flag1 = true, flag2 = true;
	scanf("%I64d", &m);
	scanf("%I64d%I64d", &h1, &a1);
	scanf("%I64d%I64d", &x1, &y1);
	scanf("%I64d%I64d", &h2, &a2);
	scanf("%I64d%I64d", &x2, &y2);
	memset(vis, 0, sizeof(vis));
	tmp = h1;
	timx = 0;
	pos1 = -1;
	while (vis[tmp] == 0) {
		timx++;
		vis[tmp] = timx;
		if (tmp == a1) {
			pos1 = timx;
		}
		tmp = (x1 * tmp + y1) % m;
	}
	if (pos1 < vis[tmp]) {
		flag1 = false;
	}
	timx -= vis[tmp] - 1;
	tmp = h2;
	timy = 0;
	pos2 = -1;
	memset(vis, 0, sizeof(vis));
	while (!vis[tmp]) {
		timy++;
		vis[tmp] = timy;
		if (tmp == a2) {
			pos2 = timy;
		}
		tmp = (x2 * tmp + y2) % m;
	}
	if (pos2 < vis[tmp]) {
		flag2 = false;
	}
	timy -= vis[tmp] - 1;
	if (pos1 == -1 || pos2 == -1) {
		printf("-1\n");
	}
	else {
		if (!flag1 && !flag2) {
			if (pos1 == pos2) {
				printf("%I64d\n", pos1 - 1);
			}
			else {
				printf("-1\n");
			}
		}
		else if (!flag1 && flag2) {
			if (pos1 < pos2) {
				printf("-1\n");
			}
			else {
				if ((pos1 - pos2) % timy) {
					printf("-1\n");
				}
				else {
					printf("%I64d\n", pos1 - 1);
				}
			}
		}
		else if (flag1 && !flag2) {
			if (pos1 > pos2) {
				printf("-1\n");
			}
			else {
				if ((pos2 - pos1) % timx) {
					printf("-1\n");
				}
				else {
					printf("%I64d\n", pos2 - 1);
				}
			}
		}
		else {
			ll xxx1, xxx2, you;
			you = pos2 - pos1;
			ll gc = ex_gcd(timx, timy, xxx1, xxx2);
			if (you == 0) {
				printf("%I64d\n", pos1 - 1);
			}
			else if (abs(you) % gc) {
				printf("-1\n");
			}
			else {
				xxx1 *= you / gc;
				xxx2 *= you / gc;
				if (you > 0) {
					while (xxx1 > 0) {
						xxx1 -= timy / gc;
						xxx2 += timx / gc;
					}
					while (xxx1 < 0 || xxx2 > 0) {
						xxx1 += timy / gc;
						xxx2 -= timx / gc;
					}
					printf("%I64d\n", xxx1 * timx + pos1 - 1);
				}
				else {
					xxx1 = -xxx1;
					xxx2 = -xxx2;
					while (xxx2 > 0){
                        xxx1 += timy / gc;
                        xxx2 -= timx / gc;
                    }
                    while (xxx2 < 0 || xxx1 > 0) {
                        xxx1 -= timy / gc;
                        xxx2 += timx / gc;
                    }
                    printf("%I64d\n", xxx2 * timy + pos2 - 1);
				}
				
			}
		}
	}
	return 0;
}