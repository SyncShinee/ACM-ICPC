#include <cstdio>
using namespace std;
int main() {
	int n, tmp, ans = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &tmp);
		ans ^= tmp;
	}
	if (ans == 0)
		printf("Bob\n");
	else
		printf("Alice\n");
	return 0;
}