#include <cstdio>
using namespace std;
/**
 * when we used this method to calculate x / y % p, we also need x and p is coprime 
 * Method 1: 	Extended Euclid
 * Requires:	a and b is coprime
 * Modify:		x, y
 * Effects:		when the method is finished, x is a's inverse element about b.
 * Return:		gcd(a, b)
 */
int ex_gcd(int a, int b, int &x, int &y) {
	int ret, tmp;
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	ret = ex_gcd(b, a % b, x, y);
	tmp = x;
	x = y;
	y = tmp - a / b * y;
	return ret;
}

/**
 * when we used this method to calculate x / y % p, we also need x and p is coprime
 * Method 2:	Quick Power
 * Requires:	p is prime
 * Modify:		none
 * Effects:		return n's inverse element about p
 * Return:		n's inverse element about p
 */
int quick_inverse(int n, int p) {
	int ret = 1;
	int exponent = p - 2;
	for (int i = exponent; i; i >>= 1, n = n * n % p) {
		if (i & 1) {
			ret = ret * n % p;
		}
	} 
	return ret;
}

/**
 * when we used this method to calculate x / y % p, we also need x and p is coprime
 * Method 3:	Recursive to get i's inverse element
 * Requires:	p is prime and p != 2
 * Modify:		inv[]
 * Effects:		inv[i] is i's inverse element about p;
 */
int inv[N];
void get_inverse(int n, int p) {
	inv[1] = 1;
	for (int i = 2; i <= n; ++i) {
		inv[i] = (p - p / i) * inv[p % i] % p;
	}
}

/**
 * when we used this method to calculate x / y % p, we also need x and p is coprime
 * Method 4:	Recursive to get Factorial[i] and their inverse element
 * Requires:	p is prime
 * Modify:		invf[], factor[]
 * Effects:		factor[i] is i's factorial, invf[i] is factor[i]'s inverse element
 */
int invf[N], factor[N];
void get_factorial_inverse(int n, int p) {
	factor[0] = 1;
	for (int i = 1; i <= n; ++i) {
		factor[i] = i * factor[i - 1] % p;
	}
	invf[n] = quick_inverse(factor[n], p);
	for (int i = n-1; i >= 0; --i) {
		invf[i] = invf[i + 1] * (i + 1) % p;
	}
}

int main() {
	return 0;
}