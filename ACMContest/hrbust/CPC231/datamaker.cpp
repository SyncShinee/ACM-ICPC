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
	srand(time(0));
	int n = rand()%20;
	printf("%d\n", n);
	int num = 0;
	while (num < n-1) {
		int x = (rand()% 2000);
		int y = (rand() % 2000);
		int z = (rand() % 2);
		if (!q[x][y]) {
			q[x][y] = true;
			if (z == 0)
				kk++;
			printf("%d %d %d\n", x, y, z);
			num++;
		}
	}
	if (kk % 2 == 1) 
		printf("%d %d %d\n", rand()% 2000, rand()% 2000, 0);
		else
			printf("%d %d %d\n", rand()% 2000, rand()% 2000, 1);
	printf("0");
	return 0;
}