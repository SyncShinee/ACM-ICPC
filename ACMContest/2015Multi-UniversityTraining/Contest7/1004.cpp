#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int main() {
	int cas = 0, n, t;
	while (scanf("%d%d", &n, &t), n != -1 || t != -1) {
		cas ++;
		int sum1 = 0, sum2 = 0;
		sum2 = n % 11;
		while (n) {
			sum1 += n % 10;
			n /= 10;
		}
		for (int i = 0; i < t; ++i) {
			int tmp = sum1, tag = 1, ad = 0;
			while (tmp > 0) {
				ad += tmp % 10;
				tmp /= 10;
				tag = -tag;
			}
			sum2 = ((sum2 * tag + sum1 % 11) % 11 + 11) % 11;
			sum1 += ad;
		}
		printf("Case #%d: ", cas);
		if (sum2 == 0)
			puts("Yes");
		else {
			puts("No");
		}
	}
	return 0;
}