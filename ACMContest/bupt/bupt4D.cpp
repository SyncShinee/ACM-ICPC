#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
ll f[70], sum[70];
int 
int main() {
	f[0] = f[1] = f[2] = 1;
	sum[0] = 1;
	sum[1] = 2;
	sum[2] = 3;
	for (int i = 3; i <= 64; ++i) {
		f[i] = f[i-1] + f[i-2];
		sum[i] = sum[i-1] + f[i];
	}
	while (~scanf("%d", &n)) {
		
	}
	return 0;
}