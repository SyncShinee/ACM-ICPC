#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char a[64], b[64];
int main() {
	int T;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++ cas) {
		scanf("%s%s", a, b);
		printf("Case #%d: ", cas);
		if (strlen(a) == 2) {
			if (((a[0] - b[1] + 26) % 26 == (a[1] - b[0] + 26) % 26 && (a[0] - b[1] + 26) % 2 == 1) || 
				((a[0] - b[0] + 26) % 26 == (a[1] - b[1] + 26) % 26 && (a[0] - b[0] + 26) % 2 == 0)) {
				puts("YES");
			}
			else {
				puts("NO");
			}
			continue;
		}
		int sum = 0;
		for (int i = 0; i < strlen(a); ++ i) {
			sum += a[i] - b[i];
		}
		if (sum & 1) {
			puts("NO");
		}
		else {
			puts("YES");
		}
	}
	return 0;
}