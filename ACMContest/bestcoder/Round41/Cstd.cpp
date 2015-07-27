#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;

#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define sz(x) (int((x).size()))
#define bit(x) (1 << (x))
#define cnt1(x) (__builtin_popcount(x))

template<class T>
inline void chkmax(T& x, T y) {
    if (x < y) x = y;
}

template<class T>
inline void chkmin(T& x, T y) {
    if (y < x) x = y;
}

typedef long long LL;
typedef double DB;
typedef pair<int, int> PII;
typedef vector<int> VI;
const int MX = 100005;
const int MC = 450;
const int MOD = 998244353;
int f[MX], g[MX];
int *p = f, *q = g;
int s[MX];

void init() {
    int i, j;
    
    p[0] = 1;
    for (i = 1; i < MC; i++) {
        for (j = 0; j < MX; j++) s[j] = (s[j] + p[j]) % MOD;
        for (j = 0; j < i; j++) q[j] = 0;
        for (j = i; j < MX; j++) q[j] = (p[j - i] + q[j - i]) % MOD;
        swap(p, q);
    }
    
    for (j = 1; j < MX; j++) s[j] = (s[j] + s[j - 1]) % MOD;
}

int main() {
    freopen("in.txt", "r", stdin);
    //freopen("std.out", "w", stdout);
    int tc, n, c, st, en, rlt;
    
    init();
    for (scanf("%d", &tc); tc--; ) {
        scanf("%d%d%d%d", &n, &c, &st, &en);
        rlt = s[en - c];
        if (st > c) rlt = (rlt + MOD - s[st - c - 1]) % MOD;
        printf("%d\n", rlt);
    }
    return 0;
}