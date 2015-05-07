#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const long double pi = acos(-1);
const long double s3 = sqrt(3.0);
long double r, x, y, z;
int main() {
	while (~scanf("%Lf", &r)) {
		x = (1+pi/3-s3)*r*r;
		y = 4*(pi/12+s3/2-1)*r*r;
		z = 4*(1-s3/4-pi/6)*r*r;
		printf("%.6Lf %.6Lf %.6Lf\n", x, y, z);
	}
	return 0;
}