#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
int main() {
	srand(time(NULL));
	int n = 10;
	printf("%d\n", n);;
	for (int i = 0; i < n; ++i)
		printf("%d\n", rand() % 100001);
	return 0;
}