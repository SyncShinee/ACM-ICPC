#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
int main() {
	freopen("in.txt", "w", stdout);
	printf("1\n");
	srand(time(NULL));
	int n = rand() % 100001;
	int c = rand() % 100001;
	int l = rand() % n;
	int r = rand() % n;
	if (l > r) {
		int t = l;
		l = r;
		r = t;
	}
	printf("%d %d %d %d\n", n, c, c+l, c+r);

}