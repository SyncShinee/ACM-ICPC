#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <ctime>
using namespace std;
bool q[2048][2048];
int kk = 0;
int main() {
	freopen("in.txt", "w", stdout);
	printf("1\n");
	srand(time(0));
	int n = rand()%128;
	printf("%d\n", n);
	int num = 0;
	while (num < n) {
			printf("%d ", rand()%8);
			num++;
		}
	return 0;
}