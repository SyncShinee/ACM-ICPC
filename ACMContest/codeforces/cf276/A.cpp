#include <cstdio>
using namespace std;
long long l, r, x;
int n, bl[64], br[64], lenl, lenr;
bool flag;
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		lenl = lenr = 0;
		x = 0;
		flag = false;
		scanf("%I64d%I64d", &l, &r);
		while (l > 0) {
			bl[lenl++] = l & 1;
			l >>= 1;
		}
		while (r > 0) {
			br[lenr++] = r & 1;
			r >>= 1;
		}
		//printf("%d %d\n", lenl, lenr);
		if (lenl < lenr) {
			for (int j = 0; j < lenr-1; ++j) {
				if (br[j] == 0) {
					br[j] = 1;
					flag = true;
				}
			}
			if (flag)
				br[lenr-1] = 0;
		}
		else {
			lenl--;
			while (bl[lenl] == br[lenl] && lenl > 0)
				lenl--;
			//printf("%d\n", lenl);
			if (lenl > 0) {
				for (int j = 0; j < lenl; ++j) {
					if (br[j] == 0) { 
						flag = true;
						br[j] = 1;
					}
				}
				if (flag)
					br[lenl] = 0;
			}
		}
		for (int j = lenr-1; j >= 0; --j) {
			x = x*2+br[j];
		}
		printf("%I64d\n", x);
	}
	return 0;
}