#include <cmath>
#include <cstdio>
#define BILL 1000000000
#define EPS 1e-9
class PolynomialRemainder {
public:
	int findRoot(int a, int b, int c) {
		if (a == 0) {
			if (b == 0) {
				if (c % BILL == 0)
					return 0;
				else return-1;
			}
			else {
				b %= BILL;
				c %= BILL;
				int x = c/b;
				if ((x*b-c)%BILL == 0)
					return x;
				return -1;
			}
		}
		else {
			a %= BILL;
			b %= BILL;
			c %= BILL;
			double ans = (-b+sqrt(1.0*b*b-4.0*a*c))/2.0/a;
			if (fabs(ans - (int)ans) < EPS)
				return (int)ans;
			else
				return -1;
		}
	}
};
int main() {
	PolynomialRemainder a;
	printf("%d\n", a.findRoot(123456000,789012345,678901230));
}