#include <cstdio>
#include <vector>
using namespace std;
vector<int> a[2000001];
int pow(int x) {
	return 1<<x;
}
int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	int row = 1, col = 2, p = 1;
	a[0].push_back(0);
	a[0].push_back(1);
	while (col < pow(m) || row < pow(n)) {
		if (col < pow(m)) {
			for (int j = col-1; j >= 0; --j)
				for (int i = 0; i < row; ++i)
					a[i].push_back(pow(p) + a[i][j]);
			p++;
			col *= 2;
		}
		if (row < pow(n)) {
			for (int i = row-1; i >= 0; --i)
				for (int j = 0; j < col; ++j)
					a[row*2-i-1].push_back(pow(p) + a[i][j]);
			p++;
			row *= 2;
		}
	}
	for (int i = 0; i < pow(n); ++i) {
		for (int j = 0; j < pow(m); ++j)
			printf("%d%c", a[i][j], (j == pow(m)-1) ? '\n' : ' ');
	}
	return 0;
}