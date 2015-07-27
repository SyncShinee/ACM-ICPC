#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
double n, det;

int main() {
	int T;
	scanf("%d", &T);
	det = 0;
	for (int i = 0; i < 10; ++i)
		det += 1.0*(9-i)*(9-i)/810 + 1.0*i*i/810; 
	for (int i = 1; i <= T; ++i) {
		printf("Case #%d:\n", i);
		scanf("%lf", &n);
		printf("%f ", (n-2) * det + 1);
		printf("%f\n", ((n-2) * det + n) / ((n-2) * det + 1));
	}
}