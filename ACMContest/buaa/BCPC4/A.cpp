#include <cstdio>
#include <cstring>
using namespace std;
double rat[1024], f[1024];
int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		int n, s, p;
		double max, tmp;
		scanf("%d%d%d", &n, &s, &p);
		for (int i = 1; i <= n; ++i)
			scanf("%lf", &rat[i]);
		f[0] = f[1] = p;
		for (int i = 2; i <= n; ++i) {
			tmp = 0;
			max = p;
			for (int j = 1; j < i; ++j) {
				if (tmp < (int)(max/rat[j])*rat[i]-s+max-rat[j]*(int)(max/rat[j]))
					tmp = (int)(max/rat[j])*rat[i]-s+max-rat[j]*(int)(max/rat[j]);
				if (max < f[j])
					max = f[j];
			}
			f[i] = tmp;
		}
		for (int i = 1; i <= n; ++i)
			if (max < f[i])
				max = f[i];
		printf("%.2f\n", max-p);
	}
	return 0;
}