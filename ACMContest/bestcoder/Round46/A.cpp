#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	int ang, ang1, ang2, k;
	while (~scanf("%d", &ang)) {
		for (int i = 0; i < 12; ++i) 
			for (int j = 0; j < 60; ++j) 
				for (int t = 0; t < 60; t += 10) {
					ang1 = j*6*12000 + t * 1200;
					ang2 = i * 30 * 12000 + j * 6000 + t * 100;
					if (ang2 < ang1) {
						k = ang1;
						ang1 = ang2;
						ang2 = k;
					}
					if (ang2 - ang1  == ang || -ang2 + ang1 + 360 * 12000 == ang) {
						printf("%02d:%02d:%02d\n", i, j, t);
					}
				}
	}
	return 0;
}