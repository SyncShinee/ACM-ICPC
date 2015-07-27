#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int main() {
	long long a1, a2, a3, a4, a5, a6, ans = 0;
	scanf("%I64d%I64d%I64d%I64d%I64d%I64d", &a1, &a2, &a3, &a4, &a5, &a6);
	printf("%I64d\n", (a1 + a2 + a6) * (a1 + a2 + a6) - a2 * a2 - a4 * a4 - a6 * a6);
	return 0;
}