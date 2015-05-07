#include <cstdio>
using namespace std;
long long l, r, add, sub;
int main() {
	while (scanf("%lld%lld", &l, &r), l|r) {
		if (l == 0) {
			printf("%lld\n", r/5 + 1);
			continue;
		}
		add = r/5 + 1;
		sub = (l-1)/5 + 1;
		if (l % 5 == 0) {
			printf("%lld\n", add - sub);
		}
		else {
			printf("%lld\n", add - sub + 1);
		}
	}
	return 0;
}