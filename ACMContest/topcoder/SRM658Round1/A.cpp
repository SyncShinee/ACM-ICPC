#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
class MutaliskEasy {
public:
	int f[64][64][64];
	int minimalAttacks(vector <int> x) {
		while (x.size() < 3)
			x.push_back(0);
		f[0][0][0] = 0;
		for (int i = 0; i <= x[0]; ++i)
			for (int j = 0; j <= x[1]; ++j)
				for (int t = 0; t <= x[2]; ++t) {
					if (i == 0 && j == 0 && t == 0)
						continue;
					f[i][j][t] = f[max(i-9,0)][max(j-3,0)][max(t-1,0)]+1;
					f[i][j][t] = min(f[i][j][t], f[max(i-9,0)][max(j-1,0)][max(t-3,0)]+1);
					f[i][j][t] = min(f[i][j][t], f[max(i-3,0)][max(j-9,0)][max(t-1,0)]+1);
					f[i][j][t] = min(f[i][j][t], f[max(i-3,0)][max(j-1,0)][max(t-9,0)]+1);
					f[i][j][t] = min(f[i][j][t], f[max(i-1,0)][max(j-3,0)][max(t-9,0)]+1);
					f[i][j][t] = min(f[i][j][t], f[max(i-1,0)][max(j-9,0)][max(t-3,0)]+1);
				}
		return f[x[0]][x[1]][x[2]];
	}
};
int main() {
	vector<int >x1,x2;
	x1.push_back(1);
	x1.push_back(1);
	x2.push_back(15);
	x2.push_back(5);
	MutaliskEasy t;
	printf("%d\n", t.minimalAttacks(x1));
	return 0;
}