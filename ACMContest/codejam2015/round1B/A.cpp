#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
using namespace std;
long long binPow(long long a, long long b) {
    long long res = 1;
    for (;b > 0; b /= 2) {
        if (b % 2 == 1) res = (res * a);
        a *= a;
    }
    return res;
}

long long solve(long long n) {
    if (n % 10 == 0) {
        return solve(n - 1) + 1;
    }

    long long res = 1;
    long long x = 1; 
    int k;
    if (n <= 10) return n;
    for (k = 1; x * 10 <= n; k++) {
        if (k % 2 == 1) {
            int d = (k + 1) / 2;
            res += binPow(10, d) - 1 + binPow(10, d - 1);
            if (k == 1)
                res--;
        } 
        else {
            res += binPow(10, k / 2) * 2 - 1;
        }
        x *= 10; 
    }
    int d = (k + 1) / 2;
    int tmp = n / binPow(10, d);
    if (tmp != binPow(10, k - d - 1))
        res++; 
    res += n % binPow(10, d);

    long long sim = 0; 
    for (; tmp > 0; tmp /= 10) {
        sim = sim * 10 + tmp % 10;
    }  
    res += sim - 1;
    return res;

}

int main() {
	freopen("A-large-practice.in", "r", stdin);
	freopen("A.out", "w", stdout);
	int T;
	long long n;
	scanf("%d", &T);
    for (int cas = 1; cas <= T; ++cas) {
        printf("Case #%d: ", cas);
        scanf("%lld", &n);
        long long res = solve(n);
        printf("%lld\n", res);
    }
	return 0;
}
