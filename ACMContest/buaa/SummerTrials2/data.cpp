#include <cstdio>
#include <ctime>
#include <cstdlib>
using namespace std;
int main() {
	freopen("in.txt", "w", stdout);
	srand((unsigned)time(NULL));
	long long n = rand() % 100000000001;
	printf("%lld\n", n);
	return 0;
}