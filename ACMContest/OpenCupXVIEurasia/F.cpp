#include <bits/stdc++.h>

using namespace std;
typedef long double ldb;
typedef long long ll;
const long double EPS = 1e-15;
double a, b, c;
int main(){
    //freopen("in.txt", "r", stdin);
    int t; scanf("%d", &t);
    while (t--){
	scanf("%lf %lf %lf", &a, &b, &c);
        ll A = a * 100000 + 0.1;
	ll B = b * 100000 + 0.1;
	ll C = c * 100000 + 0.1;
	ll ans = A * B * C - (A * B + A * C + B * C) * 100000;
	if (ans > 0) printf("YES\n");
	else
	    printf("NO\n");
    }
}
