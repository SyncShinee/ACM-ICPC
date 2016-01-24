#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 2e5 + 100;
const int MOD = 1e9 + 7;
int fac[N * 3], inv[N * 3];
int a,b,c;
void init(){
    fac[0] = fac[1] = 1;
    for (int i = 2;i <= 600000;i++){
	fac[i] = 1ll * fac[i - 1] * i % MOD;
    }
    inv[1] = 1;
    for (int i = 2;i <= 600000;i++){
	inv[i] = 1ll * (MOD - MOD/i) * inv[MOD%i] % MOD; 
    }
}
int mult(int x,int y){
    return 1ll * x * y % MOD;
}
int add(int x, int y){
    return (x + y) % MOD;
}
int f(int n, int m){
    if (n < m) return 0;
    int res = mult(fac[n], fac[m]);
    res = mult(res, fac[n - m]);
    return res;
}
void solve(){
    int tot = mult(f(a + b + c, a), f(b + c, b));
    int A = add(tot, MOD - f(b + c + 1, a));
    int B = add(tot, MOD - f(a + c + 1, b));
    int C = add(tot, MOD - f(a + b + 1, c));
    int nAB = mult(f(c + 1, b), f(b + c + 1, a));
    int AB = add(tot, MOD - add(add(A + B), nAB));
    int nBC = mult(f(a + 1, b), f(a + b + 1, c));
    int BC = add(tot, MOD - add(add(B + C), nBC));
    int nAC = mult(f(b + 1, a), f(b + a + 1, c));
    int AC = add(tot, MOD - add(add(A + C), nAC));
    int ABC = ;
    int ans = A + B + C - (AB + BC + AC) + ABC;
    ans = tot - ans;
}
int main(){
    init();
    while (~scanf("%d %d %d",&a,&b,&c)){
	solve();
    }
					  
}
