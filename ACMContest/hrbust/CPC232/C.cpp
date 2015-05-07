#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
int x1, y01, x2, y2, v1, v2;
bool flag;
double dist() {
	return sqrt((x1-x2)*(x1-x2) + (y01-y2)*(y01-y2));
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d%d%d%d", &x1, &y01, &x2, &y2, &v1, &v2);
		flag = false;
		if (dist() < v1 || fabs(dist()-v1) < 1e-9) {
			printf("Alice\n");
		}
		else {
			if (v1 < v2) {
				int t = v1;
				v1 = v2;
				v2 = t;
				flag = true;
			}
			if (v1 >= 2*v2) {
				if (flag)
					printf("Bob\n");
				else
					printf("Alice\n");
			}
			else
				printf("Sad\n");
		}
	}
	return 0;
}